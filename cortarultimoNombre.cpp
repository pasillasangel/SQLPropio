#include <iostream>
#include <sstream> //Cortar palabras string
#include <direct.h> //Directorios
#include <dirent.h> //Directorios

using namespace std;

//Saber si una carpeta existe una carpeta o no existe
bool is_dir(string dir)
{
    DIR * directorio;
    if (directorio = opendir(dir.c_str()))
    {
        closedir(directorio);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char** argv){

	string rutabasedatos = "c:/BaseDeDatos/BD/";
    string str("CREAR BASE DATOS Escuela");
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
