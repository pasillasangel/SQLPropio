#include <iostream>     //Comandos basicos
#include <fstream>      //archivos
#include <windows.h>    //Direcctorios

using namespace std;

main()
{
    //Creacion la tabla ejemplo 1
    ofstream ejemploTabla1;
    ejemploTabla1.open ("c:/BaseDeDatos/Usuarios/Alumnos.txt");
    ejemploTabla1 << "NumControl ent PRINCIPAL" << endl;
    ejemploTabla1 << "Nombre var NO" << endl;
    ejemploTabla1 << "ApellidoP var NO"<< endl;
    ejemploTabla1 << "ApellidpM var NO"<<endl;
    ejemploTabla1 << "Semestre ent NO" <<endl;
    ejemploTabla1 << "Carrera var NO" << endl;
    ejemploTabla1.close();

    //Agregando datos a la tabla 1
    ofstream ejemploTabla1Archivo;
    ejemploTabla1Archivo.open ("c:/BaseDeDatos/Usuarios/Alumnos");
    ejemploTabla1Archivo << "14210475 Ana Chipres Castellanos 6 ISC" << endl;
    ejemploTabla1Archivo << "14210423 Angel Pasillas Luis 6 ISC" << endl;
    ejemploTabla1Archivo << "14210434 Maria Castellanos Chipres 7 ISC" << endl;
    ejemploTabla1Archivo << "14210432 Miguel Luis Pasillas 7 ISC" << endl;
    ejemploTabla1Archivo.close();

        //Creacion la tabla ejemplo 1
    ofstream ejemploTabla2;
    ejemploTabla2.open ("c:/BaseDeDatos/Usuarios/Materias.txt");
    ejemploTabla2 << "Clave ent PRINCIPAL" << endl;
    ejemploTabla2 << "Materia var NO" << endl;
    ejemploTabla2 << "Dias var NO"<< endl;
    ejemploTabla2 << "Semestre ent NO"<< endl;
    ejemploTabla2 << "Carrera var NO"<<endl;
    ejemploTabla2.close();

    //Agregando datos a la tabla 1
    ofstream ejemploTabla2Archivo;
    ejemploTabla2Archivo.open ("c:/BaseDeDatos/Usuarios/Materias");
    ejemploTabla2Archivo << "0971 AdmonBD L-V 6 ISC" << endl;
    ejemploTabla2Archivo << "0973 Automatas L-V 6 ISC" << endl;
    ejemploTabla2Archivo << "0975 Simulacion L-V 6 ISC" << endl;
    ejemploTabla2Archivo << "0977 Redes L-V 6 ISC" << endl;
    ejemploTabla2Archivo << "0979 Ing.Soft L-V 6 ISC" << endl;
    ejemploTabla2Archivo << "0980 Arquitectura L-V 6 ISC" << endl;
    ejemploTabla2Archivo.close();



    cout<<"\nBien";
}
