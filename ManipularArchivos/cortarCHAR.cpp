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
int main ()
{   int cPalabra = 0;
    string GetTP = "";
    string query = "id var primario,";
    string completo = query.substr(0, query.find(","));
    string GetAtributo = completo.substr(0, completo.find(" "));
    istringstream coma(completo);
    while(!coma.eof())
    {
        string tempStr;
        coma >> tempStr;
        //Toma valor de 1 para tomar solo el tipo de dato
        if(cPalabra==1)
        {
            GetTP = tempStr;
        }
        cPalabra++;
    }
    cout<<GetTP<<endl;
}

