#include <iostream>
#include <string>

#include "core.h"
#include "main.h"
#include "internalError.h"

Main::Main(int argc,char **argv):
    args(argv+1, argv+argc){
}

Main::~Main(){

}

std::string* Main::getParameter(long long unsigned parameter){
    std::string *out=NULL;
    if(this->args.size()>=parameter+1){
        out=&this->args[parameter];
    }
    return out;
}

void Main::operation(){
    std::string *parameter=this->getParameter(0);
    if(parameter){
        if(!parameter->compare("-list")){
            this->list();
        }else if(!parameter->compare("-load")){
            this->load();
        }else if(!parameter->compare("-help")){
            this->help();
        }else throw InternalError("Parametro 1 invalido");
    }else this->help();
}

void Main::help(){
    std::cout<<
    "{COMANDOS}\n"
    "-help\n"
    "\tInformacion de los comandos\n"
    "-list -all\n"
    "\tLista las librerias de todos los procesos\n"
    "-list -pid [pid]\n"
    "\tLista las librerias de un proceso\n"
    "-load -pid [dll] [pid]\n"
    "\tInyecta una libreria en un proceso abierto\n"
    "-load -me [dll]\n"
    "\tInyecta una libreria en el propio inyector (usado para test)\n"
    "-load -exe [dll] [command line]\n"
    "\tInyecta una libreria en un proceso a partir de su lina de comandos\n\n"
    "{DESGLOSE}\n"
    "[pid]: Identificador de proceso\n"
    "[dll]: Ruta a la dll\n"
    "[command line]: Linea de comandos del ejecutable"
    <<std::endl;
}

void Main::list(){
    std::string *parameter=this->getParameter(1);
    if(parameter){
        if(!parameter->compare("-all")){
            Core::list();
        }else if(!parameter->compare("-pid")){
            std::string *strPid=this->getParameter(2);
            if(!strPid)throw InternalError("[pid] no encontrado");
            int pid;
            try{
                pid=std::stoi(strPid->c_str());
            }catch (const std::invalid_argument& e) {
                throw InternalError("[pid] invalido");
            }
            Core::list(pid);
        }else throw InternalError("Parametro 2 invalido");
    }else throw InternalError("Parametro 2 no encontrado");
}

void Main::load(){
    std::string *parameter=this->getParameter(1);
    if(parameter){
        if(!parameter->compare("-pid")){
            std::string *dllPath=this->getParameter(2);
            if(!dllPath)throw InternalError("[dll] no encontrado");
            std::string *strPid=this->getParameter(3);
            if(!strPid)throw InternalError("[pid] no encontrado");
            int pid;
            try{
                pid=std::stoi(strPid->c_str());
            }catch (const std::invalid_argument& e) {
                throw InternalError("[pid] invalido");
            }
            Core::load(pid,dllPath->c_str());
        }else if(!parameter->compare("-me")){
            std::string *dllPath=this->getParameter(2);
            if(!dllPath)throw InternalError("[dll] no encontrado");
            Core::load(dllPath->c_str());
        }else if(!parameter->compare("-exe")){
            std::string *dllPath=this->getParameter(2);
            if(!dllPath)throw InternalError("[dll] no encontrado");
            if(this->args.size()<=3)throw InternalError("[command line] no encontrado");
            std::string commandLine;
            std::vector<std::string> commandVector(this->args.begin()+3,this->args.end());
            for(std::string command:commandVector){
                commandLine+=command+' ';
            }
            Core::load(commandLine,dllPath->c_str());
        }else throw InternalError("Parametro 2 invalido");
    }else throw InternalError("Parametro 2 no encontrado");
}

void Main::run(){
    try {
        operation();
    }catch (InternalError e) {
        e.print();
    }
}

int main(int argc,char **argv){
    Main main(argc,argv);
    main.run();
    return 0;
}
