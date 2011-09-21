#ifndef GDX_CPP_BACKEND_SELECTOR_HPP
#define GDX_CPP_BACKEND_SELECTOR_HPP

#ifdef CURRENT_BACKEND_LINUX
#include <gdx-cpp-backend-linux/init.hpp>
#elif CURRENT_BACKEND_ANDROID
#include <gdx-cpp-backend-android/init.hpp>
#endif

#endif // GDX_CPP_TESTS_BACKEND_SELECTOR_HPP