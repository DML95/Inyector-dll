#include <iostream>
#include <regex>

#include "core.h"
#include "internalError.h"
#include "vector.h"
#include "thread.h"
#include "testLibrary.h"

#include <psapi.h>

HMODULE Core::getAddressKernel32(std::shared_ptr<Process> &process){
    //listamos los modulos del proceso hasta encontrar kernel32
    std::vector<HMODULE> addressModule=process->getAddressModule();
    std::regex kernel32Regex(".*\\\\kernel32\\.dll$",std::regex_constants::icase);
    HMODULE addressKernel32Remote=0;
    for(int cont=0,size=addressModule.size();cont<size&&!addressKernel32Remote;cont++){
        HMODULE address=addressModule[cont];
        if(std::regex_match(process->getFileToModuleAddress(address),kernel32Regex)){
            addressKernel32Remote=address;
        }
    }
    if(!addressKernel32Remote)throw InternalError("kenel32.dll no encontrda en el proceso");
    return addressKernel32Remote;
}

void* Core::getAddressLoadLibrary(std::shared_ptr<Process> &process){
    //direccionLoadLibaryLocal - direccionKernel32Local + direccionKernel32remoto
    HMODULE addressKernel32Remote=Core::getAddressKernel32(process);
    unsigned long long loadLibraryOffset=(unsigned long long)LoadLibrary-(unsigned long long)GetModuleHandle("kernel32");
    return (void*)(loadLibraryOffset+(unsigned long long)addressKernel32Remote);
}

void Core::load(std::shared_ptr<Process> &process,std::string dllPath){

    //optenemos el puntero de loadLibrary del proceso
    void *addressLoadLibraryRemote=Core::getAddressLoadLibrary(process);

    //reservamos memoria en el proceso y escrivimos la ruta de la dll
    Vector vector(process,dllPath.size());
    vector.write(dllPath);

    //iniciamos el hilo que llama a LoadLibrary
    Thread thread(process,addressLoadLibraryRemote,vector.get());
    HMODULE address=(HMODULE)thread.join();
    if(address){
        std::cout<<"DLL cargada correctamente\n\tDirreccion: "<<address<<std::endl;
    }else throw InternalError("Error al cargar la dll");
}

void Core::list(){
    std::vector<unsigned long> processesID(0xffff);
    unsigned long size=processesID.size()*sizeof(unsigned long);
    if(!EnumProcesses(processesID.data(),size,&size)) throw InternalError();
    processesID.resize(size/sizeof(unsigned long));
    for(unsigned long pid:processesID){
        try {
            if(pid)Core::list(pid);
        }catch (InternalError e) {
            e.print();
        }
    }
}

void Core::list(unsigned long pid){
    std::cout<<"PID: "<<pid<<std::endl;
    Process process(pid);
    std::vector<HMODULE> addressModule=process.getAddressModule();
    std::stringstream ss;
    ss<<"\tDireccion\tRuta"<<std::endl;
    for(HMODULE address:addressModule){
        ss<<'\t'<<address<<'\t'<<process.getFileToModuleAddress(address)<<std::endl;
    }
    std::cout<<ss.str();
}

void Core::load(unsigned long pid,std::string dllPath){
    std::cout<<"PID: "<<pid<<std::endl;
    std::cout<<"DLL: "<<dllPath<<std::endl;

    //testeamoas que la dll se pueda cargar
    TestLibrary testLibrary(dllPath);

    //abrimos el proceso
    std::shared_ptr<Process> process=std::make_shared<Process>(pid);

    //cargamos la dll en el proceso abierto
    Core::load(process,dllPath);
}

void Core::load(std::string dllPath){
    std::cout<<"PID: "<<GetCurrentProcessId()<<std::endl;
    std::cout<<"DLL: "<<dllPath<<std::endl;

    //testeamoas que la dll se pueda cargar
    TestLibrary testLibrary(dllPath);

    //abrimos el proceso
    std::shared_ptr<Process> process=std::make_shared<Process>();

    //cargamos la dll en el proceso abierto
    Core::load(process,dllPath);
}

void Core::load(std::string commandLine,std::string dllPath){
    std::cout<<"Linea de comandos: "<<commandLine<<std::endl;
    std::cout<<"DLL: "<<dllPath<<std::endl;

    //testeamoas que la dll se pueda cargar
    TestLibrary testLibrary(dllPath);

    //creamos el proceso
    std::shared_ptr<Process> process=std::make_shared<Process>(commandLine);
    std::cout<<"PID: "<<process->getPID()<<std::endl;

    //cargamos la dll en el proceso abierto
    Core::load(process,dllPath);
}
