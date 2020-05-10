#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

    #include <memory>

    #include "process.h"

    class Vector{
        private:
            void* ptr;
            std::shared_ptr<Process> process;
        public:
            //constructores
            Vector(std::shared_ptr<Process> &process,unsigned long size);
            //destructor
            ~Vector();
            //getter y setter
            int write(std::string string);
            void* get();
    };

#endif // VECTOR_H_INCLUDED
