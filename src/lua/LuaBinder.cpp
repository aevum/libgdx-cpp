#include "LuaBinder.hpp"

#include <gdx-cpp/graphics/Texture.hpp>
#include <LuaContext.h>
#include <luabind/luabind.hpp>

#include <SLB.hpp>
#include <chrono>
#include <cmath>

using namespace gdx;

class A {
public:
    void print() {
        i += std::sqrt(i);
    }
    
    float i = 1;
};

class Builder {
public:
    static A* build() {
        return new A;
    }
    
};

template <typename T>
constexpr T* shared_ptr_conversor(std::shared_ptr< T >* ptr) {
    return ptr->get();
}

namespace gdx {

void bind_lua() {
    SLB::Class< Builder >("Builder")
        .constructor()
        .set("build" , Builder::build);

    SLB::Class< A >("A")
        .constructor()
        .set("print" , &A::print);
        
    SLB::Class< std::shared_ptr< A > >("A::ptr").convertibleTo( shared_ptr_conversor<A> );
        
    SLB::Script s;
    auto b = std::chrono::steady_clock::now();
    s.doString("SLB.using(SLB);io.write(type(Builder)); x = Builder.build(); for i = 0, 100000 do x:print() end;");

    std::cout << " " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - b).count() << std::endl;  
    
    
//     lua_State* L = lua_open();
//     luaL_openlibs(L);
//     luabind::open(L);
// 
//     luabind::module(L)[
//         luabind::class_<A, std::shared_ptr<A>> ("A").def("print", &A::print).def_readonly("i", &A::i),
//         luabind::class_< Builder, std::shared_ptr< Builder > > ("Builder").scope[luabind::def("build", &Builder::build)],
//         luabind::class_< std::shared_ptr<A> > ("A::ptr")
//     ];
// 
//     auto b = std::chrono::steady_clock::now();
//     
//    
//     luaL_dostring(L, "local x = Builder.build();for i = 0, 100000 do x:print() end; io.write(x.i);");        
//     
//     const char* error = lua_tostring(L, -1);
//     //std::cout << error << std::endl;
//     
//     std::cout << " " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - b).count() << std::endl;  
    
    auto a = Builder::build();

    b = std::chrono::steady_clock::now();
    
    for (int i = 0; i < 100000; ++i) {
        a->print();
    }   
    
    std::cout << std::endl << std::fixed << a->i << " " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - b).count() << std::endl; 
}

}
