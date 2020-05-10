#ifndef TESTLIBRARY_H_INCLUDED
#define TESTLIBRARY_H_INCLUDED

    #include <windows.h>

    #include <string>

    class TestLibrary{
        private:
            HMODULE library;
        public:
            //constructor
            TestLibrary(std::string dllPath);
            //destructor
            ~TestLibrary();
    };

#endif // TESTLIBRARY_H_INCLUDED
