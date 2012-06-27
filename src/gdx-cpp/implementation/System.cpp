#include <gdx-cpp/implementation/System.hpp>

using namespace gdx;

/* -- Attribute accessors -- */
/* Constants for simple boolean attributes */
const int System::BA_EXISTS = 0x01;
const int System::BA_REGULAR   = 0x02;
const int System::BA_DIRECTORY = 0x04;
const int System::BA_HIDDEN    = 0x08;

const int System::ACCESS_READ    = 0x04;
const int System::ACCESS_WRITE   = 0x02;
const int System::ACCESS_EXECUTE = 0x01;

