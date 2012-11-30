project(gdx_lua)

include_directories(/home/victor/libs/LuaJIT-2.0.0-beta11/src/)
include_directories(/home/victor/libs/SLB-2.00/)
include_directories(/home/victor/libs/luawrapper/)

set(GDX_LUA_SOURCES 
LuaBinder.cpp /home/victor/libs/SLB-2.00/SLB.cpp /home/victor/libs/SLB-2.00/lua.c)

gdx_setup_target(gdx-lua SHARED "${GDX_LUA_SOURCES}")
