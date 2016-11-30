	#include<conio.h>
	#include<stdio.h>
	
	int circulo(int r)
	{
		int radio;
		radio= 3.1416*r*r;
		return radio;
	}
			
	main()
	{
	
		int x; 
		x = circulo (7);
		printf("El area es: %d", x );	
			
	}
			
	
		
