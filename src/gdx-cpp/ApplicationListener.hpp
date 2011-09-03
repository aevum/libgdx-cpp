
#ifndef GDXCPP_APPLICATION_LISTENER_H
#define GDXCPP_APPLICATION_LISTENER_H

namespace gdx_cpp {
  
class ApplicationListener {
public:
    virtual void create () = 0;
    virtual void resume () = 0;
    virtual void render () = 0;
    virtual void resize (int width, int height) = 0;
    virtual void pause () = 0;
    virtual void dispose () = 0;
};

}

#endif // GDXCPP_APPLICATION_LISTENER_H