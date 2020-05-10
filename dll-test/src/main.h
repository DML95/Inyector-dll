#ifndef __MAIN_H__
#define __MAIN_H__

    #include <windows.h>

    /*  To use this exported function of dll, include this header
     *  in your project.
     */

    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif

    static std::string fdwReasonToString(DWORD fdwReason);

    #ifdef __cplusplus
        extern "C"{
    #endif
        DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
    #ifdef __cplusplus
        }
    #endif

#endif // __MAIN_H__
