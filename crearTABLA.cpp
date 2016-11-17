#include <iostream>
#include <sstream> //Cortar palabras string
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv){

    //string str = "some string";
    //const char * ch = str.c_str ();
    //ch = str.c_str ();

    string nombreBaseDATOS = "ejemplo";
    cout <<"CREAR TABLA Alumnos"<<endl;

    string rutabasedatos = "c:/BaseDeDatos/BD/";
    string str("CREAR BASE DATOS Alumnos");
    string tempNombre;
    istringstream isstream(str);
    while(!isstream.eof()){
        string tempStr;
        isstream >> tempStr;
        tempNombre = tempStr;
    }
    cout << "Nombre de la base de datos es: "<< tempNombre << endl;

    cout<<"\n";

	string rutaDefinitiva = rutabasedatos + tempNombre;
	cout<<rutaDefinitiva;
	cout<<"\n";

	if (is_dir(rutaDefinitiva))
    {
        cout<<"EXISTE"<<endl;
	}
	else
    {
        cout<<"NOOOOOOO EXISTE"<<endl;
    }


    return 0;
}
