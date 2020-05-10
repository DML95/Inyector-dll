# Inyector dll

:bangbang: **Atencion: No me hago responsable de su uso inadecuado.**

Aplicacion para inyectar y listar dlls a otros procesos

###### COMANDOS
<pre>
-help
        Informacion de los comandos
-list -all
        Lista las librerias de todos los procesos
-list -pid [pid]
        Lista las librerias de un proceso
-load -pid [dll] [pid]
        Inyecta una libreria en un proceso abierto
-load -me [dll]
        Inyecta una libreria en el propio inyector (usado para test)
-load -exe [dll] [command line]
        Inyecta una libreria en un proceso a partir de su lina de comandos
</pre>
###### DESGLOSE
<pre>
[pid]: Identificador de proceso
[dll]: Ruta a la dll
[command line]: Linea de comandos del ejecutable
</pre>
###### DESCARGAR

[Descargar programa](https://github.com/DML95/Inyector-dll/raw/master/inyector/bin/inyector.exe)

[Descargar dll de prueba](https://github.com/DML95/Inyector-dll/raw/master/dll-test/bin/dll-test.dll)

###### ENTORNO DE DESARROLLO

* Copilador -> GCC (mingw-w64)
* IDE -> Code::Blocks
* Sistema Opertivo -> Windows