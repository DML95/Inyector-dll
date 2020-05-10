#include "internalError.h"

#include <windows.h>
#include <iostream>

InternalError::InternalError(std::string message):
    code(0),
    message(message){
}

InternalError::InternalError(){
    this->code=GetLastError();
    if(this->code){
        std::string message(255,0);
        int size=message.size();
        size=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,this->code, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(char*)message.c_str(),size,NULL);
        message.resize(size-2);
        this->message=message;
    }
}

int InternalError::getCode(){
    return this->code;
}

std::string & InternalError::getMessage(){
    return this->message;
}

void InternalError::print(){
    std::cout<<"Error: "<<this->code<<" , \""<<this->message<<"\""<<std::endl;
}
