#include <iostream>
#include <string.h>
#include <regex>

using namespace std;

regex Patron("^([A-Za-z](\\w)+\\s(ent|ENT|varcarac|VARCARAC),)$");
int main()
{
    string s = "scott ent,";
    string token = s.substr(0, s.find(","));
    string token1 = token.substr(0, s.find(" "));
    cout<<token<<endl;
    cout<<token1<<endl;

    if(regex_match(s,Patron))
    {
        cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
    }
    else
    {
        cout<<"No funciona!";
    }
    return 0;
}
