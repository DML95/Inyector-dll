#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

    #include <windows.h>

    #include <memory>

    #include "process.h"

    class Thread{
        private:
            HANDLE thread;
            std::shared_ptr<Process> process;
        public:
            //constructor
            Thread(std::shared_ptr<Process> &process,void* address,void* parameter);
            //destructor
            ~Thread();
            //getter y setter
            HANDLE get();
            unsigned long join();
    };

#endif // THREAD_H_INCLUDED
