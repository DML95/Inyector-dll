#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

    #include <windows.h>
    #include <vector>
    #include <string>

    class Process{
        private:
            PROCESS_INFORMATION processInfo;
        public:
            //constructores
            Process();
            Process(unsigned long pid);
            Process(std::string commandLine);
            //destructor
            ~Process();
            //getter y setter
            HANDLE get();
            unsigned long getPID();
            std::vector<HMODULE> getAddressModule();
            std::string getFileToModuleAddress(HMODULE address);
    };

#endif // PROCESS_H_INCLUDED
