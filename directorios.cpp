#include <iostream>
#include <dirent.h>

using namespace std;


int main(int argc, char *argv[])
{

    cout<<"+------------------+"<<endl;
    cout<<"| ADMINISTRADORES  |"<<endl;
    cout<<"+------------------+"<<endl;


    string dir = "c:/BaseDeDatos/Usuarios/Admin";
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

 return 0;
}
