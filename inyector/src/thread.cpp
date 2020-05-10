#include "thread.h"
#include "internalError.h"

Thread::Thread(std::shared_ptr<Process> &process,void* address,void* parameter):
        process(process){
    this->thread=CreateRemoteThread(process->get(),NULL,0,(LPTHREAD_START_ROUTINE)address,parameter,0,NULL);
    if(!this->thread) throw InternalError();
}

Thread::~Thread(){
    WaitForSingleObject(this->thread,INFINITE);
    CloseHandle(this->thread);
}

HANDLE Thread::get(){
    return this->thread;
}

unsigned long Thread::join(){
    unsigned long exitCode;
    WaitForSingleObject(this->thread,INFINITE);
    GetExitCodeThread(this->thread,&exitCode);
    return exitCode;
}
