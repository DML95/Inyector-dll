#include "process.h"
#include "internalError.h"
#include "vector.h"

#include <psapi.h>
#include <cstring>

Process::Process(){
    std::memset(&this->processInfo,0,sizeof(PROCESS_INFORMATION));
    this->processInfo.dwProcessId=GetCurrentProcessId();
    this->processInfo.hProcess=GetCurrentProcess();
}

Process::Process(unsigned long pid){
    std::memset(&this->processInfo,0,sizeof(PROCESS_INFORMATION));
    this->processInfo.hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,pid);
    if(!this->processInfo.hProcess) throw InternalError();
    processInfo.dwProcessId=pid;
}

Process::Process(std::string commandLine){
    STARTUPINFO startupInfo;
    std::memset(&startupInfo,0,sizeof(STARTUPINFO));
    startupInfo.cb=sizeof(STARTUPINFO);
    if(!CreateProcess(NULL,(LPSTR)commandLine.data(),NULL,NULL,FALSE,0,NULL,NULL,&startupInfo,&this->processInfo)) throw InternalError();
    WaitForInputIdle(this->processInfo.hProcess,INFINITE);
}

Process::~Process(){
    if(this->processInfo.hProcess!=GetCurrentProcess()){
        CloseHandle(this->processInfo.hProcess);
    }
    if(!this->processInfo.hThread)CloseHandle(this->processInfo.hThread);
}

HANDLE Process::get(){
    return this->processInfo.hProcess;
}

unsigned long Process::getPID(){
    return this->processInfo.dwProcessId;
}

std::vector<HMODULE> Process::getAddressModule(){
    std::vector<HMODULE> addressModule(0xffff);
    unsigned long size=addressModule.size()*sizeof(HMODULE);
    if(!EnumProcessModules(this->processInfo.hProcess,addressModule.data(),size,&size)) throw InternalError();
    addressModule.resize(size/sizeof(HMODULE));
    return addressModule;
}

std::string Process::getFileToModuleAddress(HMODULE address){
    std::string file(MAX_PATH,0);
    int size=file.size();
    size=GetModuleFileNameEx(this->processInfo.hProcess,address,(char*)file.data(),size);
    if(!size) throw InternalError();
    file.resize(size);
    return file;
}
