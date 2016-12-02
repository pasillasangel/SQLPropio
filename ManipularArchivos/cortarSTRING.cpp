#include <iostream>
#include <string.h>
#include <regex>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

regex Patron("^([A-Za-z](\\w)+\\s(ent|ENT|varcarac|VARCARAC),)$");


int main()
{

    string query = "angelito,";
    cout<<query<<endl;
    //string token = query.substr(0, query.find(";"));
    //cout<<token<<endl;
    string token1 = query.substr(0, query.find(","));
    cout<<token1<<endl;
    return 0;
}
/*

    string x = "hello world";
    char *y = x.c_str();

    cout<<x<<endl;
    puts(y);


    string str;
    char *arr;

    std::cin >> str;
    strcpy(arr,str.c_str());

    puts(arr);

    return 0;
}
*/
/*
int main(){
    string z = "";
    string texto="Hola Ana Fernanda";
    cout<<texto[3]<<endl;

    int c = texto.length();
    cout<<c<<endl;

    z = z + texto[0];
    z = z + texto[1];

    cout<<z<<endl;

    return 0;
}
*/
