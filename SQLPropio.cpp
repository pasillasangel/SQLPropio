//Example 1
#include <iostream>
#include <regex>
#include <string>


using namespace std;

int main()
{
    regex integer("(\\+|-)?[[:digit:]]+");
    regex ABC("^[A-Z]|[a-z]$");
    regex CREAR("^(crear usuario)$");

    string str;
 	//string str;
	//As long as the input is correct ask for another number
 	while(true)
 	{
 		cout<<"Give me an integer!"<<endl;
 		getline(cin, str, '\n');
 		//getline(cin, str);
 		//cin.getline(str, 500, ';');

 		if(!cin) break;
 		//Exit when the user inputs q
 		if(str=="q")
 			break;
 		if(regex_match(str,integer))
        {
 			cout<<"integer"<<endl;
 		}
 		else if (regex_match(str,ABC))
        {
            cout<<"LETRA"<<endl;
        }
        else if(regex_match(str,CREAR))
        {
            cout<<"CREAR UN SUPER USUARIO"<<endl;
        }
 		else
 		{
 			cout<<"Invalid input"<<endl;
 		}
 	}
 }
