#include "testLibrary.h"
#include "internalError.h"

TestLibrary::TestLibrary(std::string dllPath){
    this->library=LoadLibraryEx(dllPath.c_str(),NULL,LOAD_LIBRARY_AS_DATAFILE);
    if(!this->library)throw InternalError();
}

TestLibrary::~TestLibrary(){
    FreeLibrary(this->library);
}
