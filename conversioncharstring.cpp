#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int main()
{

    string pass;
    char caracter;
    cout << "Ingrese su pass: "<<endl;
    caracter = getch();
     while(caracter != 13)
     {
         pass.push_back(caracter);
         cout << "*";
         caracter = getch();
     }
    cout<<"\n\nTu password es: " << pass;

    return 0;

}
