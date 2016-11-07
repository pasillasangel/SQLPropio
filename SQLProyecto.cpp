
//Librerias
#include <cstdlib>
#include <iostream>
#include <fstream> //archivos
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "stdio.h"
#include <string>	//Strings
#include <direct.h> //Directorios
#include <dirent.h> //Directorios
#include <cstring> //Validacion char
#include <ctype.h> //Minusculas
#include <regex> //Expresiones Regulares

using namespace std;

//CONSTANTES
const char FINCAD = char(0);
const int MAXCAD = 20;
const char SP = ' ';
int mensajeInicio = 0;

//Expresiones regulares (simuladas)
regex cCrearUsuario("^(CREAR USUARIO|crear usuario)$");
regex cSalir("^(salir|SALIR)$");
regex cLimpiar("^(-l)$");
regex cComando("^(-com)$");
regex cAyuda("^(-a)$");
regex cUsuario("^(usuario|USUARIO)$");
regex cMostrarUsuariosAdmin("^(mostrar usuarios administradores|MOSTRAR USUARIOS ADMINISTRADORES)$");
regex cMostrarUsuariosComunes("^(mostrar usuarios comunes|MOSTRAR USUARIOS COMUNES)$");
regex cMostrarBaseDatos("^(mostrar basedatos|MOSTRAR BASEDATOS)$");
regex cCrearBaseDatos("^(crear basedatos\\s(\\w)+|CREAR BASEDATOS\\s(\\w)+)$");
regex cUsarBaseDatos("^(usar basedatos\\s(\\w)+|USAR BASEDATOS\\s(\\w)+)$");

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

//Comandos
void Comando_Crear_Usuarios();
void Comando_Ayuda();
void Comando_Comandos();
void Comando_Mostrar_Usuarios_Admin();
void Comando_Mostrar_Usuarios_Comunes();
void Comando_Mostrar_BaseDatos();
bool Buscar_Bd(string dir);

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

		gotoxy(82,1);cout<<"BASE DE DATOS";
		gotoxy(80,2);cout<<"----------------";
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

//Metodo para realizar dise�o en el consola
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
	gotoxy(20,11);cout<<"|   Contrase�a  +                          |";
	gotoxy(20,12);cout<<"+---------------+--------------------------+";
	gotoxy(40,9);cin>> nombre_usuario_registrado;

	//Verificar Usuario y Contrase�a
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
	gotoxy(20,11);cout<<"|   Contrase�a  +                          |";
	gotoxy(20,12);cout<<"+---------------+--------------------------+";
	gotoxy(40,9);cin>> nombre_usuario_registrado;

    //Verificar Usuario y Contrase�a
	verificar_usuario_contrasena(nombre_usuario_registrado,password);
}

// IMPLEMENTACI�ON DE PROCEDIMIENTOS Y FUNCIONES
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
  cout<<" -> SE HA REGISTRADO CORRECTAMENTE <-"<<endl;
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
  // Abro el fichero para añadir
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
    	cout<<" -> Nombre de Usuario DISPONIBLE <- "<<endl;
		Sleep(2500);
	}
	else
	{
    	cout<<" -> Este Nombre de Usuario ya Existe. INTENTELO DE NUEVO <-"<<endl;
		Sleep(2500);
		PrincipalComun(nombreFichero);
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
		gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASE�A SON ERRONEOS -";
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
	    	gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASE�A SON ERRONEOS -";
	    	Sleep(3000);
		    fichero.close();
		}

		if(cadena==password.PASS)
		{
	    	gotoxy(38,18);cout<<"Espere...";
	    	Sleep(3000);
	    	borrar_pantalla();
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
	// Abre el fichero para a�adir
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
    	cout<<" -> Nombre de Usuario DISPONIBLE <- "<<endl;
		Sleep(2500);
	}
	else
	{
    	cout<<" -> Este Nombre de Usuario ya Existe. INTENTELO DE NUEVO <-"<<endl;
		Sleep(2500);
		PrincipalADMIN(nombreFichero);
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
		gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASE�A SON ERRONEOS -";
	    Sleep(3000);
	}
	else
	{
		//Si el usuario es correcto: Verificar contrase�a
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
	    	gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASE�A SON ERRONEOS -";
	    	Sleep(3000);
	    	fichero.close();
	  	}

	  	if(cadena==password.PASS)
	  	{
	    	gotoxy(38,18);cout<<"Espere...";
	    	Sleep(3000);
	    	borrar_pantalla();
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
			cout<<"                  | |    / _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\/ __|"<<endl;
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
    string nombreBaseDatos = "";
	bool salida = false;

	while(salida!= true)
    {
		string consulta;

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
			cout<<"Te haz conectado con la cuenta de: "; puts(nombreFichero);
			cout<<"Version de la Base de Datos: 1.0.1"<<endl;
			cout<<"Creada por Ana Maria Chipres Castellanos y Miguel Angel Pasillas Luis. <c> 2016"<<endl;

            cout<<""<<endl;
            cout<<"Escriba -a para obtener ayuda. Escribe -l para limpiar pantalla. \nEscribe -com para mostrar todos los comandos."<<endl;

            mensajeInicio = 1;
		}

		cout<<""<<endl;
		cout<<"SQL> ";
		getline(cin, consulta, '\n');

        //Mostrar ayuda
		if(regex_match(consulta,cAyuda))
		{
            Comando_Ayuda();
		}//Limpiar pantalla
		else if(regex_match(consulta,cLimpiar))
		{
			system("cls");
		}//Mostrar todos los comandos
		else if(regex_match(consulta,cComando))
		{
            Comando_Comandos();
		}//Salir
		else if(regex_match(consulta,cSalir))
		{
			cout<<"En unos momentos se cierra el programa...";
			Sleep(3000);
			exit(0);
			salida = true;
		}//Creacion de Usuarios -- ADMIN
		else if(regex_match(consulta,cCrearUsuario))
		{
		    Comando_Crear_Usuarios();
		}//Mostrar el usuario con el que se esta conectado
		else if(regex_match(consulta,cUsuario))
        {
            cout<<"Te haz conectado con la cuenta de: "; puts(nombreFichero);
        }//Mostrar todos los usuarios administradores -- ADMIN
        else if(regex_match(consulta, cMostrarUsuariosAdmin))
        {
            Comando_Mostrar_Usuarios_Admin();
        }
        else if(regex_match(consulta, cMostrarUsuariosComunes))
        {
            Comando_Mostrar_Usuarios_Comunes();
        }
        else if(regex_match(consulta, cMostrarBaseDatos))
        {
            Comando_Mostrar_BaseDatos();
        }
        else if (regex_match(consulta, cUsarBaseDatos))
        {
            string rutabasedatos = "c:/BaseDeDatos/BD/";
            string tempNombre;
            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            string rutaDefinitiva = rutabasedatos + tempNombre;
            if (Buscar_Bd(rutaDefinitiva))
            {
                nombreBaseDatos = tempNombre;
                cout<<" -> Usando la Base de Datos '"<< nombreBaseDatos <<"' <-"<<endl;
            }
            else
            {
                cout<<"-> NO se encontro la base de datos '"<< tempNombre <<"' <-"<<endl;
            }
        }
        else if(regex_match(consulta, cCrearBaseDatos))
        {
            string rutabasedatos = "c:/BaseDeDatos/BD/";
            string tempNombre;
            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            string rutaDefinitiva = rutabasedatos + tempNombre;

            if (Buscar_Bd(rutaDefinitiva))
            {
                cout<<" -> Ya existe una base de datos con el nombre: '"<< nombreBaseDatos <<"'. Intenta con otro nombre. <-"<<endl;
            }
            else
            {
                mkdir(rutaDefinitiva.c_str());
                cout<<"-> Creada satisfactoriamente la base de datos '"<< tempNombre <<"' <-"<<endl;
            }
        }
        else
        {
            cout <<"Error: Error en su comando."<<endl;
        }

	}
	pausaSinMensaje();

}

void Comando_Crear_Usuarios()
{
	cout<<"Creara un Usuario con Privilegios de:"<<endl;
	cout<<"\t1.- Administrador"<<endl;
	cout<<"\t2.- Comunes"<<endl;
	cout<<""<<endl;

	Persona_R p;;
	char tipoUsuario = 0;
	TCadena nombreUsuario;

	cout<<"Opcion: "; cin >> tipoUsuario;

	if(tipoUsuario=='1')
	{
		cout<<"Ingrese el nombre de Usuario: "; cin >> nombreUsuario;
		//Administrador
		verificar_existencia_de_usuarioADMIN(nombreUsuario);
		Ingresar_PASS(p);
		insertarPersonaTXTADMIN(nombreUsuario,p);
	}
	else if(tipoUsuario=='2')
	{
		cout<<"Ingrese el nombre de Usuario: "; cin >> nombreUsuario;
		//Comun
		verificar_existencia_de_usuario(nombreUsuario);
		Ingresar_PASS(p);
		insertarPersonaTXT(nombreUsuario,p);
	}
	else
    {
        cout<<" -> Ingrese una Opcion Correcta. <-"<<endl;
    }
}

void Comando_Ayuda()
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

void Comando_Comandos()
{
    cout<<"                   _____                                 _"<<endl;
    cout<<"                  /  __ \\                               | | "<<endl;
    cout<<"                  | /  \\/ ___  _ __ ___   __ _ _ __   __| | ___  ___ "<<endl;
    cout<<"                  | |    / _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\/ __|"<<endl;
    cout<<"                  | \\__/\\ (_) | | | | | | (_| | | | | (_| | (_) \\__ \\"<<endl;
    cout<<"                   \\____/\\___/|_| |_| |_|\\__,_|_| |_|\\__,_|\\___/|___/"<<endl;
    cout<<"--TODOS LOS COMANDOS--"<<endl;
    cout<<"CREAR USUARIO"<<endl;
}

void Comando_Mostrar_Usuarios_Admin()
{
    cout<<"+------------------+"<<endl;
    cout<<"|  ADMINISTRADORES |"<<endl;
    cout<<"+------------------+"<<endl;
    string dir = "c:/BaseDeDatos/Usuarios/Admin";
    DIR * directorio;
    struct dirent * elemento;
    string elem;
    if (directorio = opendir(dir.c_str()))
    {
        while (elemento = readdir(directorio))
        {
            elem = elemento->d_name;
            if (elem != "." && elem != "..")
            {
                cout << "--> " <<elem<< endl;
                //cout<<"+------------------+"<<endl;
            }
        }
    }
    closedir(directorio);
}

void Comando_Mostrar_Usuarios_Comunes()
{
    cout<<"+------------------+"<<endl;
    cout<<"|     COMUNES      |"<<endl;
    cout<<"+------------------+"<<endl;
    string dir = "c:/BaseDeDatos/Usuarios/Comunes";
    DIR * directorio;
    struct dirent * elemento;
    string elem;
    if (directorio = opendir(dir.c_str()))
    {
        while (elemento = readdir(directorio))
        {
            elem = elemento->d_name;
            if (elem != "." && elem != "..")
            {
                cout << "--> " <<elem<< endl;
            }
        }
    }
    closedir(directorio);
}

void Comando_Mostrar_BaseDatos()
{
    cout<<"+------------------+"<<endl;
    cout<<"|  BASES DE DATOS  |"<<endl;
    cout<<"+------------------+"<<endl;
    string dir = "c:/BaseDeDatos/BD";
    DIR * directorio;
    struct dirent * elemento;
    string elem;
    if (directorio = opendir(dir.c_str()))
    {
        while (elemento = readdir(directorio))
        {
            elem = elemento->d_name;
            if (elem != "." && elem != "..")
            {
                cout << "--> " <<elem<< endl;
            }
        }
    }
    closedir(directorio);
}

//Saber si una carpeta existe una carpeta o no existe
bool Buscar_Bd(string dir)
{
    DIR * directorio;
    if (directorio = opendir(dir.c_str()))
    {
        closedir(directorio);
        return true;
    }
    else
    {
        return false;
    }
}

	/*
	//CREAR UNA BASE DE DATOS

	string nombre;
	string ruta = "c:/BaseDeDatos/BD";
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