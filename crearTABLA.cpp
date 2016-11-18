#include <cstdlib>
#include <iostream>
#include <fstream> //archivos
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "stdio.h"
#include <string>	//Strings
#include <direct.h> //Directorios
#include <dirent.h> //Directorios
#include <cstring> //Validacion char
#include <ctype.h> //Minusculas
#include <regex> //Expresiones Regulares

using namespace std;

void Comando_Mostrar_Tablas(string dir)
{
    cout<<"+------------------+"<<endl;
    cout<<"|       TABLAS     |"<<endl;
    cout<<"+------------------+"<<endl;
    //string dir = "c:/BaseDeDatos/Usuarios/Admin";
    DIR * directorio;
    struct dirent * elemento;
    string elem;
    if (directorio = opendir(dir.c_str()))
    {
        while (elemento = readdir(directorio))
        {
            elem = elemento->d_name;
            if (elem != "." && elem != "..")
            {
                cout << "--> " <<elem<< endl;
                //cout<<"+------------------+"<<endl;
            }
        }
    }
    closedir(directorio);
}

bool is_file(string file)
{
    FILE * archivo;
    if (archivo = fopen(file.c_str(), "r"))
    {
        fclose(archivo);
        return true;
    }
    else
    {
        return false;
    }
}

void Comando_Eliminar_Usuario(string ruta)
{
    string comando; //rmdir o del
    if (is_file(ruta))
    {
    comando = "del " + ruta;
    system(comando.c_str());
    }
}

int main(int argc, char** argv){

    string rutaDefinitiva;
    string rutabasedatos = "C:\\BaseDeDatos\\BD\\";
    string nombreBaseDATOS = "ejemplo";
    string consulta = "ELIMINAR BASEDATOS perros";
    string tempNombre;

    istringstream isstream(consulta);
    while(!isstream.eof()){
        string tempStr;
        isstream >> tempStr;
        tempNombre = tempStr;
    }
    cout << "Nombre de la tabla es: "<< tempNombre << endl;

    cout<<"\n";

    rutaDefinitiva = rutabasedatos + nombreBaseDATOS;
	cout<<rutaDefinitiva;
	cout<<"\n";

	Comando_Mostrar_Tablas(rutaDefinitiva);

/*
    //Eliminar tabla
    if(is_file(rutaDefinitiva))
    {
        Comando_Eliminar_Usuario(rutaDefinitiva);
        cout<<" -> La Tabla '"<< tempNombre <<"' ha sido eliminado correctamente. <-"<<endl;
    }
    else
    {
        cout<<"-> La tabla  '"<< tempNombre <<"' que desea eliminar no existe. Intente con otro nombre.<-"<<endl;
    }

    //CREAR TABLA
	if (is_file(rutaDefinitiva))
    {
        cout<<"-> La tabla '" + tempNombre + "'que desea crear ya existe. Intente con otro nombre.<-"<<endl;
        //SLEEEEP
	}
	else
    {
        ofstream fs(rutaDefinitiva);
        cout<<"-> Tabla '" + tempNombre + "' creada correctamente."<<endl;
    }
*/
    return 0;
}
