#include "vector.h"

#include "internalError.h"

Vector::Vector(std::shared_ptr<Process> &process,unsigned long size):
        process(process){
    this->ptr=VirtualAllocEx(process->get(),NULL,size,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
    if(!this->ptr)throw InternalError();
}

Vector::~Vector(){
    VirtualFreeEx(this->process->get(),this->ptr,0,MEM_RELEASE);
}

int Vector::write(std::string string){
    unsigned long long size;
    if(!WriteProcessMemory(process->get(),this->ptr,string.c_str(),string.size(),&size))throw InternalError();
    return size;
}

void* Vector::get(){
    return this->ptr;
}
