#include<conio.h>
#include<stdio.h>

int pares()
{
	int x = 0;
	int sum = 0;
	printf("Ingrese un numero: ");
	scanf ("%d", &x);
	do 
	{
		if(x%2 == 0)
		{
	    	sum++;
	    }   
	    x--;
	}while(x!=80);
	return sum;
}
		
main()
{
	int num; 
	num = pares ();
	printf("El numero de pares es: %d", num );	
}
			
