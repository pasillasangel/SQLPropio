#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str[10];
    for (unsigned int i = 0; i < 10; ++i)
    {
        getline(cin, str[i]);
    }
    return 0;
}
