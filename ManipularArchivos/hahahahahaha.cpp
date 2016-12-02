#include <cstdlib>
#include <iostream>
#include <fstream> //Manipulacion de archivos
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
int main(){

        for (int i = 0; i < 100; i++) {
            if (i % 3 == 0) {
                cout<<i+" CHOCO"<<endl;
            }
            if (i % 5 == 0) {
                cout<<i+" LATE"<<endl;
            }
            if (i % 15 == 0) {
                cout<<i+" CHOCOLATE   "<<endl;
            }
        }
}
