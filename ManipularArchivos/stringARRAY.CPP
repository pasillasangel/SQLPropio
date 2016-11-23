#include <iostream>
#include <string>
//#define SIZE 10

using namespace std;

int main()
{
    string GetAtributo = "id";
    int zzz = 0;

    string str[20];
    for (unsigned int i = 0; i < 3; ++i)
    {
        cout<<"ingrese valor  ";
        getline(cin, str[i]);
    }

    for ( int i = 0; i < 10; i++)
    {
        if(GetAtributo==str[i])
        {
            cout<<"\n\n\n\t [] - Se repitio el campo: " + GetAtributo<<endl;
        }
    }

    cout<<"\n\n\n\tIMPRIMIENDO el array:"<<endl;
    for( unsigned int i = 0; i < 10; i++)
    {
        cout<<str[i] + " ";
    }

    cout<<"\n\n\tLIMPIANDO el array:"<<endl;

    for( unsigned int i = 0; i < 20; i++)
    {
        str[i] = "";
    }
    cout<<"\n\n ";

    cout<<"\t\tIMPRIMIENDO el array:"<<endl;
    for( unsigned int i = 0; i < 20; i++)
    {
        cout<<"Numero: " + str[i]<<endl;
        zzz++;
    }
    return 0;
}
