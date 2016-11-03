//Librerias
#include <cstdlib>
#include <iostream>
#include <fstream> //archivos
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "stdio.h"
#include <string>	//Strings
#include <direct.h> //Direcctorios
#include <cstring> //Validacion char
#include <ctype.h> //Minusculas

using namespace std;

//CONSTANTES
const char FINCAD = char(0);
const int MAXCAD = 20;
const char SP = ' ';
/*
char contrasena;
int i;
int contador=0;
*/
//Expresiones regulares (simuladas)
char crearUsuario[] = "crear usuario";

//TIPOS
typedef char TCadena[MAXCAD+1]; // MAXCAD caracteres + FINCAD
struct Persona_R
{
	TCadena PASS;
};

//Instancias de los metodos principales
void pausa();
void pausaSinMensaje();
void gotoxy(int x, int y);
void pantallaPrincipal();
void iniciarSesionUsuario();
void iniciarSesionAdmin();

// CABECERA DE PROCEDIMIENTOS Y FUNCIONES
void finalizar_programa();
void borrar_pantalla();
void Ingresar_PASS(Persona_R &p);
void confirmar_PASS(Persona_R &p);

// Algoritmos de Manejo de Ficheros de Texto
//Usuario Comun
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p);
void verificar_existencia_de_usuario(TCadena nombreFichero);
void verificar_usuario_contrasena(TCadena nombreFichero,Persona_R &password);
void PrincipalComun(TCadena nombreFichero);

//Usuario Administrador
void insertarPersonaTXTADMIN(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXTADMIN(ofstream &fichero, Persona_R p);
void verificar_existencia_de_usuarioADMIN(TCadena nombreFichero);
void verificar_usuario_contrasenaADMIN(TCadena nombreFichero,Persona_R &password);
void PrincipalADMIN(TCadena nombreFichero);



//Metodo principal
int main()
{	
	//Color fondo: de Azul y Amarillo
	system("color 0E");
	
	//Variables
	char opcion;
	bool bandera = false;
	
	do
	{
		//Limpiar pantalla
		system("cls");
		//Limpiar variables
		cin.clear();
		
		gotoxy(72,1);cout<<"BASE DE DATOS";
		gotoxy(70,2);cout<<"----------------";
		gotoxy(22,2);cout<<"              NMMMMMMMMMM";
		gotoxy(22,3);cout<<"            MMMMMMMMMMMMMMM";
		gotoxy(22,4);cout<<"          MMMMM:........MMMMM";
		gotoxy(22,5);cout<<"        MMMM...............MMMM";
		gotoxy(22,6);cout<<"        MMMM...............MMMM";
		gotoxy(22,7);cout<<"        MMMMM.............MMMMM";
		gotoxy(22,8);cout<<"        MMMMMMM.........MMMMMMM";
		gotoxy(22,9);cout<<"        MMM.MMMMMMMMMMMMMMM.MMM";
		gotoxy(22,10);cout<<"        MMMM. MMMMMMMMMMM .MMMM";
		gotoxy(22,11);cout<<"        MMMMMM..... ......MMMMM";
		gotoxy(22,12);cout<<"        MMMM MMM ..... MMM MMMM";
		gotoxy(22,13);cout<<"         MMMM...MMMMMMM...MMMM";
		gotoxy(22,14);cout<<"          MMMMN.........MMMMM";
		gotoxy(22,15);cout<<"           MMMMMMMMMMMMMMMMM";
		gotoxy(22,16);cout<<"             MMMMMMMMMMMMM";
		
		gotoxy(10,19);cout<<"1.- Iniciar Sesion como cuenta de ADMIN";
		gotoxy(10,20);cout<<"2.- Iniciar Sesion como cuenta de USUARIO";
		gotoxy(10,21);cout<<"3.- Salir";
		
		//Crear la carpeta contenedora
		string directorio = "c:/BaseDeDatos/";
		if (mkdir(directorio.c_str()) == 0)
		{
			gotoxy(8,2);cout << "CARPETA";
			gotoxy(8,3);cout << "CONTENEDORA";
			gotoxy(8,4);cout << "CREADA";
			
			//Creacion de las carpetas
			mkdir("c:/BaseDeDatos/Usuarios");
			mkdir("c:/BaseDeDatos/Usuarios/Admin");
			mkdir("c:/BaseDeDatos/Usuarios/Comunes");
			mkdir("c:/BaseDeDatos/BD");
			
			//Creacion de el usuario angel
			ofstream usuarioRoot;
			usuarioRoot.open ("c:/BaseDeDatos/Usuarios/Admin/pasillas");
			usuarioRoot << "pasillas";
			usuarioRoot.close();
			
			//Creacion de el usuario ana
			ofstream usuarioChipres;
			usuarioChipres.open ("c:/BaseDeDatos/Usuarios/Admin/chipres");
			usuarioChipres << "chipres";
			usuarioChipres.close();
			 
		}
		
		gotoxy(10,22);cout<<"Opcion: "; cin>>opcion;
	
		switch(opcion)
		{
			case '1':
				//Llamar al metodo...
				iniciarSesionAdmin();
				break;
			case '2':
				//Llamar al metodo...
				iniciarSesionUsuario();
				break;
			case '3':
				//Limpiar pantalla
				system("cls");
				//Cambiar Color
				system("color 09");
				//Cambiar el color de la bandera para salir
				bandera = true;
				//Mostrar un mensaje
				pausa();
				break;
			default:
				gotoxy(10,24);cout<<"OPCION NO VALIDA: INGRESE UNA CORRECTA";
				pausaSinMensaje();
				break;
		}
	}while(bandera!=true);
    return 0;
}

//Metodo para realizar diseño en el consola
void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}  

//Metodo que permite dar pausa al programa
void pausaSinMensaje()
{
	//Metodo para pausar similar a: system("PAUSE");.
    getwchar();
    getwchar();
}

//Metodo que permite dar pausa al programa
void pausa()
{
	gotoxy(20,9);cout<<"+------------------------------------------------+";
	gotoxy(20,10);cout<<"+ Pulse una tecla para salir del programa...     +";
	gotoxy(20,11);cout<<"+------------------------------------------------+";
	//Metodo para pausar similar a: system("PAUSE");.
    getwchar();
    getwchar();
}

//Metodo para inicar sesion
void iniciarSesionAdmin()
{
	//Variables
    TCadena nombre_usuario_registrado;
    Persona_R password;;
    
	//Limpiar pantalla
	system("cls");
	//Limpiar variables
	cin.clear();
	
	gotoxy(72,2);cout<<"BASE DE DATOS";
	gotoxy(70,3);cout<<"----------------";
	gotoxy(33,3);cout<<"+-----------------+";
	gotoxy(33,4);cout<<"+  ADMINISTRADOR  +";
	gotoxy(33,5);cout<<"+-----------------+";
	gotoxy(20,6);cout<<"+------------------------------------------+";
	gotoxy(20,7);cout<<"|  --------------- ENTRAR ---------------  |";
	gotoxy(20,8);cout<<"+---------------+--------------------------+";
	gotoxy(20,9);cout<<"|     Usuario   +                          |";
	gotoxy(20,10);cout<<"+---------------+--------------------------+";
	gotoxy(20,11);cout<<"|   Contraseña  +                          |";
	gotoxy(20,12);cout<<"+---------------+--------------------------+";
	gotoxy(40,9);cin>> nombre_usuario_registrado;
	
	//Verificar Usuario y Contraseña
	verificar_usuario_contrasenaADMIN(nombre_usuario_registrado,password);
}

//Metodo para inicar sesion como USUARIO NORMAL
void iniciarSesionUsuario()
{
	//Variables
    TCadena nombre_usuario_registrado;
    Persona_R p;;
    Persona_R password;;
    
	//Limpiar pantalla
	system("cls");
	//Limpiar variables
	cin.clear();
	
	gotoxy(72,2);cout<<"BASE DE DATOS";
	gotoxy(70,3);cout<<"----------------";
	gotoxy(33,3);cout<<"+-----------------+";
	gotoxy(33,4);cout<<"+     USUARIO     +";
	gotoxy(33,5);cout<<"+-----------------+";
	gotoxy(20,6);cout<<"+------------------------------------------+";
	gotoxy(20,7);cout<<"|  -------- Entrar como USUARIO ---------  |";
	gotoxy(20,8);cout<<"+---------------+--------------------------+";
	gotoxy(20,9);cout<<"|     Usuario   +                          |";
	gotoxy(20,10);cout<<"+---------------+--------------------------+";
	gotoxy(20,11);cout<<"|   Contraseña  +                          |";
	gotoxy(20,12);cout<<"+---------------+--------------------------+";
	gotoxy(40,9);cin>> nombre_usuario_registrado;

    //Verificar Usuario y Contraseña
	verificar_usuario_contrasena(nombre_usuario_registrado,password);
}

// IMPLEMENTACIÃON DE PROCEDIMIENTOS Y FUNCIONES
void finalizar_programa()
{
  borrar_pantalla();     
  printf("El Programa CERRARA en Cualquier Momento"); 
  Sleep(3000);
  exit(0);
}
void borrar_pantalla()
{
  system("CLS");
}

void Ingresar_PASS(Persona_R &p)
{
  cout << "Escriba su password del Usuario: " ;
  cin >> p.PASS;
  cout<<"\nSE HA REGISTRADO CORRECTAMENTE"<<endl; 
  Sleep(2500); 
}
void confirmar_PASS(Persona_R &password)
{
  //cout << "Escriba su PASS:                 " ;
  gotoxy(40,11); cin >> password.PASS;
}
//-------------------------------------------------------------------USUARIO COMUN
// Algoritmos de Manejo de Ficheros de Texto
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p)
{
	char rutaUsuarioComun[100] = "c:/BaseDeDatos/Usuarios/Comunes/";
	strcat(rutaUsuarioComun,nombreFichero); 
	
  ofstream out;
  out.open(rutaUsuarioComun,ios::app);
  // Abro el fichero para aÃ±adir
  if (out.bad())
  {
    // El fichero no existe ... lo creo
    out.open(rutaUsuarioComun);
  }	
  EscribePersonaFicheroTXT(out,p);
  out.close();
  
}

void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p)
{
  fichero << p.PASS << SP;
}

void verificar_existencia_de_usuario(TCadena nombreFichero)
{
	char rutaUsuarioComun[100] = "c:/BaseDeDatos/Usuarios/Comunes/";
	strcat(rutaUsuarioComun,nombreFichero); 
  ifstream archivo(rutaUsuarioComun); 
  if (!archivo)
  {
    cout<<"\nNombre de Usuario DISPONIBLE\n"<<endl;Sleep(2500);
  }
  else 
  {
    cout<<"\n Este Nombre de Usuario ya Existe.....INTENTELO DE NUEVO"<<endl; Sleep(2500); borrar_pantalla();main();      
  }   
}

void verificar_usuario_contrasena(TCadena nombreFichero,Persona_R &password)
{
	char rutaUsuarioComun[100] = "c:/BaseDeDatos/Usuarios/Comunes/";
	strcat(rutaUsuarioComun,nombreFichero);
	
	ifstream archivo(rutaUsuarioComun); 
  	if (!archivo)
	{
		string error;
		gotoxy(40,11);cin >> error;
		
		//Error al no encontrar el archivo
		gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS -"; 
	    Sleep(3000);
	}
	else
  	{
		string cadena;
		string contrase;
		gotoxy(40,11);cin >> password.PASS;
		ifstream fichero(rutaUsuarioComun,ios::in);	
		     
		while(!fichero.eof())
		{                 
			fichero >> cadena;   
		}
		  
		if(cadena!=password.PASS)
		{
	    	gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS -"; 
	    	Sleep(3000);
		    fichero.close();
		}
		
		if(cadena==password.PASS)
		{
	    	gotoxy(38,18);cout<<"Espere...";
	    	Sleep(3000);
	    	PrincipalComun(nombreFichero);
		}
	}
}

//-------------------------------------------------------------------USUARIO ADMINISTRADOR

// Algoritmos de Manejo de Ficheros de Texto
void insertarPersonaTXTADMIN(TCadena nombreFichero, Persona_R p)
{
	char rutaUsuarioAdmin[100] = "c:/BaseDeDatos/Usuarios/Admin/";
	strcat(rutaUsuarioAdmin,nombreFichero); 
	
	ofstream out;
	out.open(rutaUsuarioAdmin,ios::app);
	// Abre el fichero para añadir
	if (out.bad())
	{
    	// El fichero no existe ... lo creo
    	out.open(rutaUsuarioAdmin);
	}	
	EscribePersonaFicheroTXTADMIN(out,p);
	out.close();
}

void EscribePersonaFicheroTXTADMIN(ofstream &fichero, Persona_R p)
{
	fichero << p.PASS << SP;
}

void verificar_existencia_de_usuarioADMIN(TCadena nombreFichero)
{
	char rutaUsuarioAdmin[100] = "c:/BaseDeDatos/Usuarios/Admin/";
	strcat(rutaUsuarioAdmin,nombreFichero);
	 
	ifstream archivo(rutaUsuarioAdmin); 
	if (!archivo)
	{
    	cout<<"Nombre de Usuario DISPONIBLE"<<endl;
		Sleep(2500);
	}
	else 
	{
    	cout<<"\nEste Nombre de Usuario ya Existe. INTENTELO DE NUEVO"<<endl; 
		Sleep(2500);    
  	}   
}

void verificar_usuario_contrasenaADMIN(TCadena nombreFichero,Persona_R &password)
{
	char rutaUsuarioAdmin[100] = "c:/BaseDeDatos/Usuarios/Admin/";
	strcat(rutaUsuarioAdmin,nombreFichero); 
	
	//Buscar el archivo
	ifstream archivo(rutaUsuarioAdmin); 
	if (!archivo)
	{
		string error;
		gotoxy(40,11);cin >> error;
		
		//Error al no encontrar el archivo
		gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS -"; 
	    Sleep(3000);
	}
	else
	{
		//Si el usuario es correcto: Verificar contraseña
		string cadena;
		string contrase;

		gotoxy(40,11);cin >> password.PASS;
		ifstream fichero(rutaUsuarioAdmin,ios::in);
	     
		while(!fichero.eof())
		{                 
	    	fichero >> cadena;
		}
	  
	  	if(cadena!=password.PASS)
	  	{
	    	gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS -"; 
	    	Sleep(3000);
	    	fichero.close();
	  	}
	
	  	if(cadena==password.PASS)
	  	{
	    	gotoxy(38,18);cout<<"Espere..."; 
	    	Sleep(3000);
	    	PrincipalADMIN(nombreFichero);
	  	}
	}
}

void PrincipalComun(TCadena nombreFichero)
{
	system("cls");
	
	bool salida = false;
	int mensajeInicio = 0;
	
	do
	{
		string consulta = "";

		if (mensajeInicio == 0)
		{
			//http://www.network-science.de/ascii/ - doom
			gotoxy(20,1);cout<<"______ _                           _     _       ";
			gotoxy(20,2);cout<<"| ___ (_)                         (_)   | |      ";
			gotoxy(20,3);cout<<"| |_/ /_  ___ _ ____   _____ _ __  _  __| | ___  ";
			gotoxy(20,4);cout<<"| ___ \\ |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ ";
			gotoxy(20,5);cout<<"| |_/ / |  __/ | | \\ V /  __/ | | | | (_| | (_) |";
			gotoxy(20,6);cout<<"\\____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/ "<<endl;
		
			cout <<""<<endl;
			cout <<""<<endl;
			cout<<"Bienvenido a la Base de Datos."<<endl;
			cout<<"Te haz conectado con la cuenta de: ";puts(nombreFichero);
			cout<<"Version de la Base de Datos: 1.0.1"<<endl;
			cout<<"Creada por Ana Maria Chipres Castellanos y Miguel Angel Pasillas Luis. <c> 2016"<<endl;
			
			mensajeInicio = 1;
		
		cout<<""<<endl;
		cout<<"Escriba -a para obtener ayuda. Escribe -l para limpiar pantalla. \nEscribe -com para mostrar todos los comandos."<<endl;
		}
		
		cout<<""<<endl;
		cout<<"SQL> "; cin>>consulta;
		
		if(consulta=="-a")
		{
			cout<<"                  "<<endl;
			cout<<"                    ___                  _"<<endl;      
			cout<<"                   / _ \\                | | "<<endl;     
			cout<<"                  / /_\\ \\_   _ _   _  __| | __ _ "<<endl;
			cout<<"                  |  _  | | | | | | |/ _` |/ _` |"<<endl;
			cout<<"                  | | | | |_| | |_| | (_| | (_| |"<<endl; 
			cout<<"                  \\_| |_/\\__, |\\__,_|\\__,_|\\__,_|"<<endl; 
			cout<<"                          __/ | "<<endl;                
			cout<<"                         |___/  "<<endl;   
			cout<<"                  --MENSAJES DE AYUDA--"<<endl; 
		}
		else if(consulta=="-l")
		{
			system("cls");
		}
		else if(consulta=="-com")
		{
			cout<<"                   _____                                 _"<<endl;           
			cout<<"                  /  __ \\                               | | "<<endl;          
			cout<<"                  | /  \\/ ___  _ __ ___   __ _ _ __   __| | ___  ___ "<<endl; 
			cout<<"                  | |    / _ \\| '_ ` _ \ / _` | '_ \\ / _` |/ _ \\/ __|"<<endl; 
			cout<<"                  | \\__/\\ (_) | | | | | | (_| | | | | (_| | (_) \\__ \\"<<endl; 
			cout<<"                   \\____/\\___/|_| |_| |_|\\__,_|_| |_|\\__,_|\\___/|___/"<<endl;           
			cout<<"--TODOS LOS COMANDOS--"<<endl;
		}
		else if(consulta=="salir")
		{
			cout<<"Presione cualquier tecla para salir...";
			salida = true;
		}
		
	}while(salida!= true);
	pausaSinMensaje();
	
}

void PrincipalADMIN(TCadena nombreFichero)
{
	system("cls");
	
	bool salida = false;
	int mensajeInicio = 0;
	
	do
	{
		char consulta[100];

		if (mensajeInicio == 0)
		{
			//http://www.network-science.de/ascii/ - doom
			gotoxy(20,1);cout<<"______ _                           _     _       ";
			gotoxy(20,2);cout<<"| ___ (_)                         (_)   | |      ";
			gotoxy(20,3);cout<<"| |_/ /_  ___ _ ____   _____ _ __  _  __| | ___  ";
			gotoxy(20,4);cout<<"| ___ \\ |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ ";
			gotoxy(20,5);cout<<"| |_/ / |  __/ | | \\ V /  __/ | | | | (_| | (_) |";
			gotoxy(20,6);cout<<"\\____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/ "<<endl;
		
			cout <<""<<endl;
			cout <<""<<endl;
			cout<<"Bienvenido a la Base de Datos."<<endl;
			cout<<"Te haz conectado con la cuenta de: ";puts(nombreFichero);
			cout<<"Version de la Base de Datos: 1.0.1"<<endl;
			cout<<"Creada por Ana Maria Chipres Castellanos y Miguel Angel Pasillas Luis. <c> 2016"<<endl;
			
			mensajeInicio = 1;
		
		cout<<""<<endl;
		cout<<"Escriba -a para obtener ayuda. Escribe -l para limpiar pantalla. \nEscribe -com para mostrar todos los comandos."<<endl;
		}
		
		cout<<""<<endl;
		cout<<"SQL> "; gets(consulta);
		
		for(int i = 0; consulta[i]; i++)
      	consulta[i] = tolower(consulta[i]); //<--convierte a minusculas 
		
		if(consulta=="-a")
		{
			cout<<"                  "<<endl;
			cout<<"                    ___                  _"<<endl;      
			cout<<"                   / _ \\                | | "<<endl;     
			cout<<"                  / /_\\ \\_   _ _   _  __| | __ _ "<<endl;
			cout<<"                  |  _  | | | | | | |/ _` |/ _` |"<<endl;
			cout<<"                  | | | | |_| | |_| | (_| | (_| |"<<endl; 
			cout<<"                  \\_| |_/\\__, |\\__,_|\\__,_|\\__,_|"<<endl; 
			cout<<"                          __/ | "<<endl;                
			cout<<"                         |___/  "<<endl;   
			cout<<"                  --MENSAJES DE AYUDA--"<<endl; 
		}
		else if(consulta=="-l")
		{
			system("cls");
		}
		else if(consulta=="-com")
		{
			cout<<"                   _____                                 _"<<endl;           
			cout<<"                  /  __ \\                               | | "<<endl;          
			cout<<"                  | /  \\/ ___  _ __ ___   __ _ _ __   __| | ___  ___ "<<endl; 
			cout<<"                  | |    / _ \\| '_ ` _ \ / _` | '_ \\ / _` |/ _ \\/ __|"<<endl; 
			cout<<"                  | \\__/\\ (_) | | | | | | (_| | | | | (_| | (_) \\__ \\"<<endl; 
			cout<<"                   \\____/\\___/|_| |_| |_|\\__,_|_| |_|\\__,_|\\___/|___/"<<endl;           
			cout<<"--TODOS LOS COMANDOS--"<<endl;
			cout<<"\n\tCREAR USUARIO"<<endl;
			cout<<"\t\tPermite crear un usuario, ya sea administrador o un usuario comun."<<endl;
			cout<<"\n\tMOSTRAR BASES"<<endl;
			cout<<"\t\tPermite ver todas las bases de datos existentes."<<endl;
			cout<<"\n\tCREAR TABLA [NOMBRE]"<<endl;
			cout<<"\t\tPermite crear una tabla."<<endl;
		}
		else if(consulta=="salir")
		{
			cout<<"En unos momentos se cierra...";
			Sleep(3000);
			exit(0);
			salida = true;
		}//Creacion de Usuarios
		else if(!strcmp (consulta,crearUsuario))
		{
			cout<<"\nCreara un Usuario."<<endl;
			cout<<"\t1.- Administrador"<<endl;
			cout<<"\t2.- Comun"<<endl;
			cout<<""<<endl;
			
			Persona_R p;;
			int tipoUsuario = 0;
			TCadena nombreUsuario;
			
			cout<<"Opcion: "; cin >> tipoUsuario;
			
			if(tipoUsuario==1)
			{
				cout<<"Ingrese el nombre de Usuario: "<<endl; cin >> nombreUsuario;
				//Administrador
				verificar_existencia_de_usuarioADMIN(nombreUsuario);
				Ingresar_PASS(p);
				insertarPersonaTXTADMIN(nombreUsuario,p);
			}
			else if(tipoUsuario==2)
			{
				cout<<"Ingrese el nombre de Usuario: "<<endl; cin >> nombreUsuario;
				//Comun
				verificar_existencia_de_usuario(nombreUsuario);
				Ingresar_PASS(p);
				insertarPersonaTXT(nombreUsuario,p);
			}
		}
		
	}while(salida!= true);
	pausaSinMensaje();
	
}



	/*
	//CREAR UNA BASE DE DATOS
	
	string nombre;
	string ruta = "c:/BaseDeDatos/";
	gotoxy(40,18);cout<<"Ingrese el Nombre de la Base de Datos: "<<endl;
	cin>> nombre;
	string ruta_absoluta = ruta + nombre;
	if (mkdir(ruta_absoluta.c_str()) == 0) cout << "La base de Datos se ha creado Correctamente" << endl;
    else cout << "La base de datos ya existe." << endl;
    pausaSinMensaje();
    */
    
    
    /*
    LEER LAS BASE DE DATOS
    
      DIR * directorio;
	  struct dirent * elemento;
	  string elem;
	  if (directorio = opendir(dir.c_str()))
	  { 
	   while (elemento = readdir(directorio))
	   {
	    elem = elemento->d_name;
	    if (elem != "." && elem != "..") cout << elem << endl;   
	   }            
	  }
	  closedir(directorio);
    
    
	*/

