#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

    #include <memory>
    #include <vector>
    #include <string>

    class Main{
        private:
            std::vector<std::string> args;

            std::string* getParameter(long long unsigned parameter);
            void operation();
            void help();
            void list();
            void load();
        public:
            //constructor
            Main(int argc, char **argv);
            //destructor
            ~Main();
            //arranque
            void run();
    };

#endif // MAIN_H_INCLUDED
