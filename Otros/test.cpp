#include<conio.h>
#include<stdio.h>
int calcular(int c)
{
	int cubo;
	cubo = c*c*c;
	return cubo;
}	
main()
{
	int num;
	printf("Ingrese el numero que desea eleval al cubo:");
	scanf ("%d", &num);
	int n = calcular(num);
	printf("El cubo es: %d", n);
	return 0;	
}
		
	
		
