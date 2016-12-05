#include <iostream>
#include <fstream>
using namespace std;

int main () {


 ifstream ficheroEntrada;
 string frase;

 ficheroEntrada.open ("ficheroTexto.txt");
 getline(ficheroEntrada, frase);

 ficheroEntrada.close();


 cout << "Frase leida: " << frase << endl;

 return 0;

}
