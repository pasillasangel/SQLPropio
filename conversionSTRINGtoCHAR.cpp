
#include <iostream>
#include <sstream> //Cortar palabras string
#include <string>
#include <stdio.h>

const char FINCAD = char(0);
const int MAXCAD = 20;
typedef char TCadena[MAXCAD+1]; // MAXCAD caracteres + FINCAD

using namespace std;

int main(int argc, char** argv){

    string str = "some string";
    const char * ch = str.c_str ();

    cout <<"\t\t\tCONVERSION 1"<<endl;
    cout << "Impresion de la Cadena: " + str << endl;
    cout << "\n";
    cout << "Impresion de la cadena: ";
    puts(ch);

    str = "sxxxxxxxxxxxxx";
    ch = str.c_str ();

    cout << "\n\n\n";
    cout <<"\t\t\tCONVERSION 2"<<endl;
    cout << "Impresion de la Cadena: " + str << endl;
    cout << "\n";
    cout << "Impresion de la cadena: "; puts(ch);

    return 0;
}


void verificar_existencia_Tabla(TCadena nombreFichero, TCadena nombre)
{
	char rutaUsuarioComun[100] = "c:/BaseDeDatos/BD/"; //dsfsfsfs
	strcat(rutaUsuarioComun,nombreFichero);
    ifstream archivo(rutaUsuarioComun);
	if (!archivo)
	{
    	cout<<" -> Nombre de Usuario DISPONIBLE <- "<<endl;
		Sleep(2500);
	}
	else
	{
    	cout<<" -> Este Nombre de Usuario ya Existe. INTENTELO DE NUEVO <-"<<endl;
		Sleep(2500);
		//PrincipalComun(nombreFichero);
  	}
}
