project(gdx_squirrel)


include_directories(/home/victor/libs/SQUIRREL3/include/)
include_directories(/home/victor/libs/sqrat-0.8.2/include/)

set(SQ_SOURCES VmController.cpp)

gdx_setup_target(gdx-squirrel SHARED "${SQ_SOURCES}")