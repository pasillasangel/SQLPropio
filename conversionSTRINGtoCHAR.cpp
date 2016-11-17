
#include <iostream>
#include <sstream> //Cortar palabras string
#include <string>
#include <stdio.h>

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
