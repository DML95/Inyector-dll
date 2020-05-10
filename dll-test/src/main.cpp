#include <sstream>

#include "main.h"

static std::string fdwReasonToString(DWORD fdwReason){
    std::string text;
    switch(fdwReason){
        case DLL_PROCESS_ATTACH:
            text="DLL_PROCESS_ATTACH";
            break;
        case DLL_PROCESS_DETACH:
            text="DLL_PROCESS_DETACH";
            break;
        case DLL_THREAD_ATTACH:
            text="DLL_THREAD_ATTACH";
            break;
        case DLL_THREAD_DETACH:
            text="DLL_THREAD_DETACH";
            break;
        default:
            text="ERROR";
    }
    return text;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
    std::stringstream stream;
    stream<<"PID: "<<GetCurrentProcessId()<<
            "\nDllMain\n\tHINSTANCE: "<<hinstDLL<<
            "\n\tfdwReason: "<<fdwReasonToString(fdwReason)<<
            "\n\tlpvReserved: "<<(bool)lpvReserved;
    MessageBoxA(0,stream.str().data(),"Hola Mundo", MB_OK|MB_ICONINFORMATION);
    return true;
}
