#ifndef INTERNALERROR_H_INCLUDED
#define INTERNALERROR_H_INCLUDED

    #include <string>

    class InternalError{
        private:
            int code;
            std::string message;
        public:
            //constructor
            InternalError();
            InternalError(std::string message);

            //getter y setter
            int getCode();
            std::string &getMessage();

            void print();
    };

#endif // INTERNALERROR_H_INCLUDED
