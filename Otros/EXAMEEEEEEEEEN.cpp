#include<conio.h>
#include<stdio.h>

main()
{
	int gastos = 0;
	float promedio = 0;
	printf("CUales son tus gastos semanales: ");
	scanf ("%d", &gastos);
	promedio = gastos / 7;
	printf("Los gastos en promedio diarios es: %f", promedio);
	
	if (gastos >= 7000)
	{
		for (int i = 1; i < 8; i++)
		{
			promedio = promedio * 1.10;
			
			printf("\n%d:  %f", i,promedio);
		}
	}
}
