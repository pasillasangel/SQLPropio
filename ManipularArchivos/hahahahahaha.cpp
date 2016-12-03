
#include <iostream>

using namespace std;
int main(){

    int c [50];

    for (int i = 0; i < 30; i++)
    {
        c[i] = i;
    }

    int numDATOS = 30;
    int numCAMPOS = 3;
    int ad = 0;
    int adentro = 0;

    do
    {
        for (int i = 0; i<numCAMPOS; i++)
        {
            cout<<c[adentro]<<" ";
            adentro++;
        }
        cout<<endl;
        ad++;

    }while(ad<numCAMPOS);
}
/*
    if(6%x==0)
    {
        cout<<"\n\n\nSiiiiiiiiiiiiiiiiiiiii";
    }
    else
    {
        cout<<"\n\n\nNooooooooooooooooooooo";
    }
}
*/
/*
            if((i%(3-1)==0) && (i!=0))
            {
                cout<<i;
                cout<<endl;
            }
            else if (i%3!=0)
            {
                cout<<i;
                cout<<" ";
            }else
            {
                cout<<i;
                cout<<" ";
            }
*/
