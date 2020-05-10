#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

    #include <windows.h>
    #include <memory>

    #include "process.h"

    class Core{
        private:
            Core();

            //optine la direccion de kernel32 en un proceso
            static HMODULE getAddressKernel32(std::shared_ptr<Process> &process);
            //optine la direccion de LoadLibrary en un proceso
            static void* getAddressLoadLibrary(std::shared_ptr<Process> &process);
            //carga una dll en un proceso ya abierto
            static void load(std::shared_ptr<Process> &process,std::string dllPath);
        public:
            //lista las dlls de todos los procesos
            static void list();
            //lista las dlls de un proceso
            static void list(unsigned long pid);
            //carga una dll en un proceso
            static void load(unsigned long pid,std::string dllPath);
            //carga una dll en este proceso
            static void load(std::string dllPath);
            //carga una dll e inicia el proceso
            static void load(std::string commandLine,std::string dllPath);
    };

#endif // CORE_H_INCLUDED
