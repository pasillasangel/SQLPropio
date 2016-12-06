//############################################################################################################################
//Librerias
//############################################################################################################################
#include <cstdlib>      //Comandos basicos del sistema
#include <iostream>     //Comandos basicos
#include <fstream>      //archivos
#include <windows.h>    //Direcctorios
#include <conio.h>      //Color del sistema
#include <string.h>     //Cadenas
#include "stdio.h"      //Comandos basicos (char)
#include <string>	    //Strings
#include <direct.h>     //Directorios
#include <dirent.h>     //Directorios
#include <cstring>      //Validacion char
#include <ctype.h>      //Minusculas
#include <regex>        //Expresiones Regulares
#define TAM 50
//############################################################################################################################
//Palabras reservadas
//############################################################################################################################
using namespace std;

//############################################################################################################################
//CONSTANTES
//############################################################################################################################
const char FINCAD = char(0);
const int MAXCAD = 20;
const char SP = ' ';
int mensajeInicio = 0;

//############################################################################################################################
//Expresiones regulares
//############################################################################################################################
regex cSalir("^(salir|SALIR)$");
regex cLimpiar("^(-l)$");
regex cComando("^(-com)$");
regex cAyuda("^(-a)$");
//--
regex cCrearUsuario("^(CREAR USUARIO|crear usuario)$");
regex cEliminarUsuarios("^(eliminar usuario|ELIMINAR USUARIO)$");
regex cMostrarUsuariosAdmin("^(mostrar usuarios administradores|MOSTRAR USUARIOS ADMINISTRADORES)$");
regex cMostrarUsuariosComunes("^(mostrar usuarios comunes|MOSTRAR USUARIOS COMUNES)$");
regex cUsuario("^(usuario|USUARIO)$");
regex cCerrar("^(cerrar|CERRAR)$");
//--
regex cCrearBaseDatos("^(crear basedatos\\s[A-Za-z](\\w)+|CREAR BASEDATOS\\s[A-Za-z](\\w)+)$");
regex cUsarBaseDatos("^(usar\\s[A-Za-z](\\w)+|USAR\\s[A-Za-z](\\w)+)$");
regex cMostrarBaseDatos("^(mostrar basedatos|MOSTRAR BASEDATOS)$");
regex cEliminarBaseDatos("^(eliminar basedatos\\s[A-Za-z](\\w)+|ELIMINAR BASEDATOS\\s[A-Za-z](\\w)+)$");
regex cRetirarBaseDatos("^(retirar|RETIRAR)$");
//--
regex cCrearTabla("^(crear tabla\\s[A-Za-z](\\w)+|CREAR TABLA\\s[A-Za-z](\\w)+)$");
regex cEliminarTabla("^(eliminar tabla\\s[A-Za-z](\\w)+|ELIMINAR TABLA\\s[A-Za-z](\\w)+)$");
regex cMostrarTablas("^(mostrar tablas|MOSTRAR TABLAS)$");
//--
regex cSeleccionarTabla("^(S \\* DESDE [A-Za-z](\\w)+|s \\* desde [A-Za-z](\\w)+)$");
regex cExplicarTabla("^(EXPLICAR [A-Za-z](\\w)+|explicar [A-Za-z](\\w)+)$");
//--
regex cInsertarAtributo("^([A-Za-z](\\w)+\\s(\\w)+,)$");
regex cInsertarAtributoFinal("^([A-Za-z](\\w)+\\s(\\w)+;)$");
regex cInsertarAtributoPrimario("^([A-Za-z](\\w)+\\s(\\w)+\\s(PRIMARIO|primario),)$");
regex cInsertarAtributoFinalPrimario("^([A-Za-z](\\w)+\\s(\\w)+\\s(PRIMARIO|primario);)$");
regex TipoDato("^(ent|ENT|var|VAR|)$");
//--
regex cInsertarTabla("^(INSERTAR EN [A-Za-z](\\w)+|insertar en [A-Za-z](\\w)+)$");
regex cInsertarTablaDatos("^(([(A-zA-Z)|(0-9)]+,)+[(A-zA-Z)|(0-9)]+:)$");
regex cInsertarTablaDatosFinal("^(([(A-zA-Z)|(0-9)]+,)+[(A-zA-Z)|(0-9)]+;)$");
regex cDigito("^([-|+]?[0-9]+)$");
regex cComa("^(\\w+,)$");

//############################################################################################################################
//Definiendo estructura
//############################################################################################################################
typedef char TCadena[MAXCAD+1]; // MAXCAD caracteres + FINCAD
struct Persona_R
{
	TCadena PASS;
};

//############################################################################################################################
//Instancias de los metodos principales
//############################################################################################################################
void pausa();
void pausaSinMensaje();
void gotoxy(int x, int y);
void pantallaPrincipal();
void iniciarSesionUsuario();
void iniciarSesionAdmin();

//############################################################################################################################
// CABECERA DE PROCEDIMIENTOS Y FUNCIONES
//############################################################################################################################
void finalizar_programa();
void borrar_pantalla();
void Ingresar_PASS(Persona_R &p);
void confirmar_PASS(Persona_R &p);
//##########################################
// Algoritmos de Manejo de Ficheros de Texto
//##########################################
//Usuario Comun
//##########################################
//##########################################
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p);
void verificar_existencia_de_usuario(TCadena nombreFichero);
void verificar_usuario_contrasena(TCadena nombreFichero,Persona_R &password);
void PrincipalComun(TCadena nombreFichero);

//Usuario Administrador
//##########################################
//##########################################
void insertarPersonaTXTADMIN(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXTADMIN(ofstream &fichero, Persona_R p);
void verificar_existencia_de_usuarioADMIN(TCadena nombreFichero);
void verificar_usuario_contrasenaADMIN(TCadena nombreFichero,Persona_R &password);
void PrincipalADMIN(TCadena nombreFichero);

//Comandos
//##########################################
void Comando_Crear_Usuarios();
void Comando_Ayuda();
void Comando_Comandos();
void Comando_Mostrar_Usuarios_Admin();
void Comando_Mostrar_Usuarios_Comunes();
void Comando_Mostrar_BaseDatos();
void Comando_Eliminar_BD(string ruta);
void Comando_BuscarEliminar_Usuarios();
void Comando_Eliminar_Usuario(string ruta);
bool Buscar_Bd(string dir);
bool is_file(string file);
void Comando_Mostrar_Tablas(string dir);

//##########################################
//Metodo principal
//##########################################
int main()
{
	//Color fondo: de Azul y Amarillo
	system("color 0E");

    //##########################################
	//Variables
	//##########################################
	//Opcion
	char opcion;
	//Opcion
	bool bandera = false;

	do
	{
		//Limpiar pantalla
		system("cls");
		//Limpiar variables
		cin.clear();

        //############################################################################################################################
        //Imprimiendo mesanej personalizado
        //############################################################################################################################
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

		//############################################################################################################################
		//Crear la carpeta contenedora
		//Con carpetas, archivos y usuarios por defecto
		//############################################################################################################################
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
			mkdir("c:/BaseDeDatos/BD/Ejemplo1");
			mkdir("c:/BaseDeDatos/BD/Ejemplo1/Tablas");
			mkdir("c:/BaseDeDatos/BD/Ejemplo1/Atributos");

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

            //Creacion la tabla ejemplo 1
            ofstream ejemploTabla1;
            ejemploTabla1.open ("c:/BaseDeDatos/BD/Ejemplo2/Tablas/Alumnos.txt");
            ejemploTabla1 << "NumControl ent PRINCIPAL" << endl;
            ejemploTabla1 << "Nombre var NO" << endl;
            ejemploTabla1 << "ApellidoP var NO"<< endl;
            ejemploTabla1 << "ApellidpM var NO"<<endl;
            ejemploTabla1 << "Semestre ent NO" <<endl;
            ejemploTabla1 << "Carrera var NO" << endl;
            ejemploTabla1.close();

            //Agregando datos a la tabla 1
            ofstream ejemploTabla1Archivo;
            ejemploTabla1Archivo.open ("c:/BaseDeDatos/Usuarios/Alumnos");
            ejemploTabla1Archivo << "14210475 Ana Chipres Castellanos 6 ISC" << endl;
            ejemploTabla1Archivo << "14210423 Angel Pasillas Luis 6 ISC" << endl;
            ejemploTabla1Archivo << "14210434 Maria Castellanos Chipres 7 ISC" << endl;
            ejemploTabla1Archivo << "14210432 Miguel Luis Pasillas 7 ISC" << endl;
            ejemploTabla1Archivo.close();

                //Creacion la tabla ejemplo 1
            ofstream ejemploTabla2;
            ejemploTabla2.open ("c:/BaseDeDatos/Usuarios/Materias.txt");
            ejemploTabla2 << "Clave ent PRINCIPAL" << endl;
            ejemploTabla2 << "Materia var NO" << endl;
            ejemploTabla2 << "Dias var NO"<< endl;
            ejemploTabla2 << "Semestre ent NO"<< endl;
            ejemploTabla2 << "Carrera var NO"<<endl;
            ejemploTabla2.close();

            //Agregando datos a la tabla 1
            ofstream ejemploTabla2Archivo;
            ejemploTabla2Archivo.open ("c:/BaseDeDatos/Usuarios/Materias");
            ejemploTabla2Archivo << "0971 AdmonBD L-V 6 ISC" << endl;
            ejemploTabla2Archivo << "0973 Automatas L-V 6 ISC" << endl;
            ejemploTabla2Archivo << "0975 Simulacion L-V 6 ISC" << endl;
            ejemploTabla2Archivo << "0977 Redes L-V 6 ISC" << endl;
            ejemploTabla2Archivo << "0979 Ing.Soft L-V 6 ISC" << endl;
            ejemploTabla2Archivo << "0980 Arquitectura L-V 6 ISC" << endl;
            ejemploTabla2Archivo.close();

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
		gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS -";
	    Sleep(3000);
	}
	else
  	{
		string cadena;
		string contrase;

		gotoxy(40,11);cin>> password.PASS;
        //nuevaCadena = (string)password.PASS;
		ifstream fichero(rutaUsuarioComun,ios::in);

		while(!fichero.eof())
		{
			fichero >> cadena;
		}

		if(cadena!=password.PASS)
		{
	    	gotoxy(20,20);cout<<"- NOMBRE Y/O CONTRASEÑA SON ERRONEOS - ";
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
	    	borrar_pantalla();
	    	PrincipalADMIN(nombreFichero);
	  	}
	}
}

void PrincipalComun(TCadena nombreFichero)
{
	system("cls");
    //######
    //Crear tabla
    //######
    //Para salir del ciclo de ingrsar 'campos'
    bool bandera = false;
    //Para saber cuando se repitio un campo
    bool repetir = false;
    //Para contar cada palabra y tomar solo TIPO DE DATO y validarlo
    int cPalabra = 0;
    //Para saber que solo se ingreso una llave primaria
    bool bPrimario = false;
    //Si por alguna razon hubo error al ingresar campos, que elimine los archivos temp
    bool errorAtr = false;
    //Arreglo de string para almacenar los campos  (para que no se repitan) y su contador
    string arrayGA[TAM];
    //Su propio contador
    int contadorGA = 0;

    //Almanecenara el TIPO DE DATO
    string GetTP = "";

    //Almanecenara todo la instruccion
    string query = "";


    //Explicar tabla
    int cCantidadCampos = 0;
    int numCampos = 0;
    int adentroAUX = 0;
    int adentro = 0;
    string save[TAM];
    string arrayleerCampos[TAM];

    int num_campos = 0;
    int cTipoDato = 0;
    int campoExitoso = 0;
    string arrayTipoDato[TAM];
    string arrayNombresCampos[TAM];

    //Insertar
    bool bandInsertar = false;
    bool bandValidCampo = false;
    int contadorInsertar = 0;
    string CamposInsert[TAM];
    string arrayExitoso[TAM];
    string axuCampos = "";



    string nombreBaseDatos = "";
    //string rutabasedatos = "c:/BaseDeDatos/BD/";
    string rutabasedatos = "c:\\BaseDeDatos\\BD\\";
    string tempNombre = "";
    string rutaDefinitiva = "";
    string rutaDefinitiva1 = "";
    string nombreTabla = "";
	bool salida = false;
	char desicion;

	while(salida!= true)
    {
		string consulta = "";
        rutaDefinitiva = "";
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
			cout<<"Te haz conectado con la cuenta con privilegios de: "; puts(nombreFichero);
			cout<<"Version de la Base de Datos: 1.0.1"<<endl;
			cout<<"Creada por Ana Maria Chipres Castellanos y Miguel Angel Pasillas Luis. <c> 2016"<<endl;

            cout<<""<<endl;
            cout<<"Escriba -a para obtener ayuda. Escribe -l para limpiar pantalla. \nEscribe -com para mostrar todos los comandos."<<endl;

            mensajeInicio = 1;
		}

        if(nombreBaseDatos=="")
        {
            cout<<""<<endl;
            cout<<"SQL> ";
            getline(cin, consulta, '\n');
        }
        else
        {
            cout<<""<<endl;
            cout<<"SQL ["<<nombreBaseDatos<<"]> ";
            getline(cin, consulta, '\n');
        }


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
            cout<<"\t¿Seguro que desea salir? (S/N): ";
            cin>>desicion;
            if (desicion == 'S' || desicion == 's')
            {
                cout<<"Cerrando el programa..."<<endl;
                Sleep(3000);
                exit(0);
            }
		}//Creacion de Usuarios -- ADMIN
		else if(regex_match(consulta,cCrearUsuario))
		{
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
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
            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            rutaDefinitiva = rutabasedatos + tempNombre;
            if (Buscar_Bd(rutaDefinitiva))
            {
                nombreBaseDatos = tempNombre;
                cout<<" -> Usando la Base de Datos '"<< nombreBaseDatos <<"' <-"<<endl;
            }
            else
            {
                cout<<"-> NO se encontro la base de datos '"<< tempNombre <<"'.Intente con otro nombre. <-"<<endl;
            }
        }
        else if(regex_match(consulta, cCrearBaseDatos))
        {
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta, cEliminarBaseDatos))
        {

            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta,cEliminarUsuarios))
        {
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta, cCerrar))
        {
            cout<<"\t¿Seguro que desea cerrar sesion? (S/N): ";
            cin>>desicion;
            if (desicion == 'S' || desicion == 's')
            {
                cout<<"Cerrando sesion..."<<endl;
                Sleep(3000);
                salida = true;
            }
        }
        else if (regex_match(consulta, cCrearTabla))
        {
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta, cRetirarBaseDatos))
        {
            if (nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                cout<<" ->Retirada la Base de datos '" + nombreBaseDatos + "' CORRECTAMENTE. <-"<<endl;
                nombreBaseDatos = "";
            }
        }
        else if(regex_match(consulta, cEliminarTabla))
        {
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta, cMostrarTablas))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                istringstream isstream(consulta);
                while(!isstream.eof()){
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas";

                Comando_Mostrar_Tablas(rutaDefinitiva);
            }
        }
        else if (regex_match(consulta, cExplicarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                //Cortar para obtener el nombre de la tabla
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                //Tabla
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                //Atributos
                rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";

                //Buscar la tabla
                if (!is_file(rutaDefinitiva1))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea EXPLICAR no existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    cCantidadCampos = 0;
                    numCampos = 0;
                    adentroAUX = 0;
                    adentro = 0;
                    query = "";

                    string variablez = "";
                    int longQ = 0;

                    //variable de lectura
                    ifstream leerCampos;
                    //Leer el archivo
                    leerCampos.open(rutaDefinitiva1,ios::out|ios::in);

                    //Abrir archivo (siempre se abrira y no habra error, porque si existe)
                    if(leerCampos.is_open())
                    {
                        //######################################################
                        //Contar el numero campos
                        //######################################################

                        //lectura adelantada
                        leerCampos>>save[cCantidadCampos];
                        while(!leerCampos.eof())
                        {
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                            cCantidadCampos++;
                            leerCampos>>save[cCantidadCampos];

                            //Es divisible de tres, entonces
                            if((cCantidadCampos%3)==0)
                            {
                                numCampos++;
                            }

                        }
                        //guardar el ultimo valor
                        arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                        //Para que no salga impar, y se haga par y se pueda dividir
                        cCantidadCampos++;

                        //###########################################
                        //EXPLICAR CADA ATRIBUTO
                        //###########################################
                        cout<<endl;
                        cout<<"|----------------------------------------------------|"<<endl;
                        cout<<"|       CAMPO       |    TIPO    |       LLAVE       |"<<endl;
                        cout<<"|----------------------------------------------------|"<<endl;
                        //Insertar los archivos en el archivo
                        do
                        {
                            for (int i = 0; i<3; i++)
                            {
                                variablez = save[adentro];
                                longQ = variablez.length();
                                if(longQ<=2)
                                {
                                    cout<<"        "<<save[adentro]<<"         ";
                                }
                                else if (longQ>2 && longQ<=6)
                                {
                                    cout<<"      "<<save[adentro]<<"       ";
                                }
                                else if (longQ>6 && longQ<10)
                                {
                                    cout<<"    "<<save[adentro]<<"    ";
                                }
                                else
                                {
                                    cout<<"    "<<save[adentro]<<"    ";
                                }
                                adentro++;
                            }
                            cout<<endl;
                            adentroAUX++;

                        }while(adentroAUX<numCampos);
                        cout<<"|----------------------------------------------------|"<<endl;
                    }
                    //Cerrar la lectura
                    leerCampos.close();

                    //Limpiar arreglos
                    for(unsigned int i = 0; i < TAM; i++)
                    {
                        arrayleerCampos[i] = "";
                        save[i] = "";
                    }

                    query = "";

                }
            }
        }
        else if(regex_match(consulta,cInsertarTabla))
        {
            cout<<"\n\tNecesita una cuenta con privilegios."<<endl;
        }
        else if(regex_match(consulta, cSeleccionarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                //Cortar para obtener el nombre de la tabla
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                //Tabla
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                //Atributos
                rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";

                //Buscar la tabla
                if (!is_file(rutaDefinitiva1))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea insertar no existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    cCantidadCampos = 0;
                    numCampos = 0;
                    cTipoDato = 0;
                    adentroAUX = 0;
                    adentro = 0;
                    query = "";
                    string variabley = "";
                    int camposReales = 0;
                    int longQ = 0;

                    //variable de lectura
                    ifstream leerCampos;
                    //Leer el archivo
                    leerCampos.open(rutaDefinitiva1,ios::out|ios::in);

                    //Abrir archivo (siempre se abrira y no habra error, porque si existe)
                    if(leerCampos.is_open())
                    {
                        //######################################################
                        //Contar el numero campos
                        //######################################################

                        //lectura adelantada
                        leerCampos>>save[cCantidadCampos];
                        while(!leerCampos.eof())
                        {
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                            cCantidadCampos++;
                            leerCampos>>save[cCantidadCampos];
                        }

                        //Contar los atriburoa
                        while(!leerCampos.eof())
                        {
                            getline(leerCampos,variabley);
                        }

                        //guardar el ultimo valor
                        arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                        //Para que no salga impar, y se haga par y se pueda dividir
                        cCantidadCampos++;

                        //Contando y leyendo los campos
                        getline(leerCampos,variabley);
                        istringstream isstream(variabley);
                        while(!isstream.eof())
                        {
                            string tempStr;
                            isstream >> tempStr;
                            //tempNombre = tempStr;
                            camposReales++;
                        }

                        //######################################################
                        //Conocer los nombres de los campos
                        //######################################################
                        for(int i = 0; i<(cCantidadCampos-1); i=i+3)
                        {
                            arrayNombresCampos[cTipoDato]=arrayleerCampos[i];
                            cTipoDato++;

                        }
                        //Imprimiendo los CAMPOS de la tabla
                        cout<<"-----------------------------------------------------------------------------------------------"<<endl;
                        for(int i = 0; i<=cTipoDato; i++)
                        {
                            variabley = arrayNombresCampos[i];
                            longQ = variabley.length();
                            if(longQ<=2)
                            {
                                cout<<"     "<<arrayNombresCampos[i]<<"      ";
                            }
                            else if (longQ>2 && longQ<=6)
                            {
                                cout<<"     "<<arrayNombresCampos[i]<<"     ";
                            }
                            else if (longQ>6 && longQ<10)
                            {
                                cout<<"    "<<arrayNombresCampos[i]<<"    ";
                            }
                            else
                            {
                                cout<<"    "<<arrayNombresCampos[i]<<"    ";
                            }
                        }
                        cout<<"\n--------------------------------------------------------------------------------------------"<<endl;


                        //Limpiar datos
                        for(unsigned int i = 0; i < TAM; i++)
                        {
                            arrayleerCampos[i] = "";
                            arrayNombresCampos[i] = "";
                            save[i] ="";
                        }
                        cCantidadCampos = 0;
                        variabley = "";


                        //Cerrar la lectura
                        leerCampos.close();

                        //variable de lectura
                        ifstream leerDatos;
                        //Leer el archivo
                        leerDatos.open(rutaDefinitiva,ios::out|ios::in);


                        if(leerDatos.is_open())
                        {

                            //lectura adelantada
                            leerDatos>>save[cCantidadCampos];
                            while(!leerDatos.eof())
                            {
                                arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                                cCantidadCampos++;
                                leerDatos>>save[cCantidadCampos];

                                //Es divisible de tres, entonces
                                if((cCantidadCampos%3)==0)
                                {
                                    numCampos++;
                                }
                            }

                            //guardar el ultimo valor
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                            //Para que no salga impar, y se haga par y se pueda dividir
                            cCantidadCampos++;

                            do
                            {
                                for (int i = 0; i<cTipoDato; i++)
                                {
                                    variabley = save[adentro];
                                    longQ = variabley.length();
                                    if(longQ<=2)
                                    {
                                        cout<<"        "<<save[adentro]<<"         ";
                                    }
                                    else if (longQ>2 && longQ<=6)
                                    {
                                        cout<<"      "<<save[adentro]<<"       ";
                                    }
                                    else if (longQ>6 && longQ<10)
                                    {
                                        cout<<"    "<<save[adentro]<<"    ";
                                    }
                                    else
                                    {
                                        cout<<"    "<<save[adentro]<<"    ";
                                    }
                                    adentro++;
                                }
                                cout<<endl;
                                adentroAUX++;

                            }while(adentroAUX<numCampos);
                            cout<<"--------------------------------------------------------------------------------------------"<<endl;

                        }


                    }

                    //Limpiar arreglos
                    for(unsigned int i = 0; i < TAM; i++)
                    {
                        arrayleerCampos[i] = "";
                        arrayNombresCampos[i] = "";
                        save[i] ="";
                    }

                }
            }
        }
        else if(consulta=="")
        {
            //Nada, para que no muestra error
        }
        else
        {
            cout <<"Error: Error en su comando."<<endl;
        }
	}
	//pausaSinMensaje();

}

void PrincipalADMIN(TCadena nombreFichero)
{
    //######
    //Crear tabla
    //######
    //Para salir del ciclo de ingrsar 'campos'
    bool bandera = false;
    //Para saber cuando se repitio un campo
    bool repetir = false;
    //Para contar cada palabra y tomar solo TIPO DE DATO y validarlo
    int cPalabra = 0;
    //Para saber que solo se ingreso una llave primaria
    bool bPrimario = false;
    //Si por alguna razon hubo error al ingresar campos, que elimine los archivos temp
    bool errorAtr = false;
    //Arreglo de string para almacenar los campos  (para que no se repitan) y su contador
    string arrayGA[TAM];
    //Su propio contador
    int contadorGA = 0;

    //Almanecenara el TIPO DE DATO
    string GetTP = "";

    //Almanecenara todo la instruccion
    string query = "";


    //Explicar tabla
    int cCantidadCampos = 0;
    int numCampos = 0;
    int adentroAUX = 0;
    int adentro = 0;
    string save[TAM];
    string arrayleerCampos[TAM];

    int num_campos = 0;
    int cTipoDato = 0;
    int campoExitoso = 0;
    string arrayTipoDato[TAM];
    string arrayNombresCampos[TAM];

    //Insertar
    bool bandInsertar = false;
    bool bandValidCampo = false;
    int contadorInsertar = 0;
    string CamposInsert[TAM];
    string arrayExitoso[TAM];
    string axuCampos = "";



    string nombreBaseDatos = "";
    //string rutabasedatos = "c:/BaseDeDatos/BD/";
    string rutabasedatos = "c:\\BaseDeDatos\\BD\\";
    string tempNombre = "";
    string rutaDefinitiva = "";
    string rutaDefinitiva1 = "";
    string nombreTabla = "";
	bool salida = false;
	char desicion;

	while(salida!= true)
    {
		string consulta = "";
        rutaDefinitiva = "";
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
			cout<<"Te haz conectado con la cuenta con privilegios de: "; puts(nombreFichero);
			cout<<"Version de la Base de Datos: 1.0.1"<<endl;
			cout<<"Creada por Ana Maria Chipres Castellanos y Miguel Angel Pasillas Luis. <c> 2016"<<endl;

            cout<<""<<endl;
            cout<<"Escriba -a para obtener ayuda. Escribe -l para limpiar pantalla. \nEscribe -com para mostrar todos los comandos."<<endl;

            mensajeInicio = 1;
		}

        if(nombreBaseDatos=="")
        {
            cout<<""<<endl;
            cout<<"SQL> ";
            getline(cin, consulta, '\n');
        }
        else
        {
            cout<<""<<endl;
            cout<<"SQL ["<<nombreBaseDatos<<"]> ";
            getline(cin, consulta, '\n');
        }


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
            cout<<"\t¿Seguro que desea salir? (S/N): ";
            cin>>desicion;
            if (desicion == 'S' || desicion == 's')
            {
                cout<<"Cerrando el programa..."<<endl;
                Sleep(3000);
                exit(0);
            }
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
            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            rutaDefinitiva = rutabasedatos + tempNombre;
            if (Buscar_Bd(rutaDefinitiva))
            {
                nombreBaseDatos = tempNombre;
                cout<<" -> Usando la Base de Datos '"<< nombreBaseDatos <<"' <-"<<endl;
            }
            else
            {
                cout<<"-> NO se encontro la base de datos '"<< tempNombre <<"'.Intente con otro nombre. <-"<<endl;
            }
        }
        else if(regex_match(consulta, cCrearBaseDatos))
        {
            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            rutaDefinitiva = rutabasedatos + tempNombre;

            if (Buscar_Bd(rutaDefinitiva))
            {
                cout<<" -> Ya existe una base de datos con el nombre: '"<< tempNombre <<"'. Intente con otro nombre. <-"<<endl;
            }
            else
            {
                //Creacion de las tablas
                mkdir(rutaDefinitiva.c_str());
                rutaDefinitiva = rutabasedatos + tempNombre + "\\Atributos";
                mkdir(rutaDefinitiva.c_str());
                rutaDefinitiva = rutabasedatos + tempNombre + "\\Tablas";
                mkdir(rutaDefinitiva.c_str());

                cout<<"-> Creada CORRECTAMENTE la base de datos '"<< tempNombre <<"' <-"<<endl;
            }
        }
        else if(regex_match(consulta, cEliminarBaseDatos))
        {

            istringstream isstream(consulta);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                tempNombre = tempStr;
            }
            rutaDefinitiva = rutabasedatos + tempNombre;

            if (Buscar_Bd(rutaDefinitiva))
            {
                Comando_Eliminar_BD(rutaDefinitiva);
                cout<<" -> La base de datos '"<< tempNombre <<"' se ha eliminado correctamente. <-"<<endl;
                cout<<rutaDefinitiva<<endl;
            }
            else
            {
                cout<<"-> La base de datos '"<< tempNombre <<"' que desea eliminar no existe. Intente con otro nombre. <-"<<endl;
            }
        }
        else if(regex_match(consulta,cEliminarUsuarios))
        {
            Comando_BuscarEliminar_Usuarios();
        }
        else if(regex_match(consulta, cCerrar))
        {
            cout<<"\t¿Seguro que desea cerrar sesion? (S/N): ";
            cin>>desicion;
            if (desicion == 'S' || desicion == 's')
            {
                cout<<"Cerrando sesion..."<<endl;
                Sleep(3000);
                salida = true;
            }
        }
        else if (regex_match(consulta, cCrearTabla))
        {
            if(nombreBaseDatos=="")
            {
                    cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                    cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                cout<<"\n";

                //CREAR TABLA
                if (is_file(rutaDefinitiva))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea crear ya existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    bandera = false;
                    repetir = false;
                    bPrimario = false;
                    contadorGA = 0;
                    errorAtr = false;
                    query = "";

                    //Creacion de la tabla
                    ofstream fs(rutaDefinitiva);
                    //Cambiando la direccion
                    rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";
                    //Creacion de la variable
                    ofstream atributos;
                    //Creacion de la variable
                    atributos.open(rutaDefinitiva1,ios::out|ios::app);
                    if(atributos.is_open())
                    {
                        do
                        {
                            //contador de palabra a 0
                            cPalabra = 0;

                            cout<<"\t->";
                            getline(cin, query, '\n');
                            if (regex_match(query,cInsertarAtributoFinalPrimario))
                            {
                                if (bPrimario)
                                {
                                    errorAtr = true;
                                    bandera = true;
                                    cout<<" -> Error: Ya ingreso un valor primario. No puede tener dos campos primarios una tabla.";
                                }
                                else
                                {
                                    //para saber cuando se ingreso un valor primario
                                    bPrimario = true;

                                    //Quitarle la coma
                                    string completo1 = query.substr(0, query.find(";"));
                                    string GetAtributo1 = completo1.substr(0, completo1.find(" "));
                                    istringstream coma1(completo1);
                                    while(!coma1.eof())
                                    {
                                        string tempStr;
                                        coma1 >> tempStr;
                                        if(cPalabra==1)
                                        {
                                            GetTP = tempStr;
                                        }
                                        cPalabra++;
                                    }

                                    if(regex_match(GetTP,TipoDato))
                                    {
                                        for(unsigned int conta = 0; conta < TAM; conta++)
                                        {
                                            if(arrayGA[conta]==GetAtributo1)
                                            {
                                                //Si es que encontro un campo igual, repetir se ponga true
                                                repetir = true;
                                            }
                                        }

                                        if(repetir)
                                        {
                                            errorAtr = true;
                                            bandera = true;
                                            cout<<"-> Error: El atributo '" + GetAtributo1 + "' se ha repetido. Intente otra vez.<-"<<endl;
                                        }
                                        else
                                        {
                                            //Agregamos el atributo al array, para que no se vuelva elegir
                                            arrayGA[contadorGA] = GetAtributo1;

                                            //Aumentar el contador de Array de Atributos
                                            contadorGA++;

                                            //GetAtributo - Nombre Atributo
                                            //TP - Tipo Datos
                                            atributos<<GetAtributo1<<" "<<GetTP<<" Primario"<<endl;
                                            //Salir del programa
                                            bandera = true;

                                            cout<<" -> La tabla '" + tempNombre +"' ha sido creada correctamente. <- "<<endl;
                                        }

                                    }
                                    else
                                    {
                                        errorAtr = true;
                                        bandera=true;
                                        cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <- "<<endl;
                                    }
                                }
                            }
                            else if (regex_match(query,cInsertarAtributoPrimario))
                            {
                                if (bPrimario)
                                {
                                    errorAtr = true;
                                    bandera = true;
                                    cout<<" -> Error: Ya ingreso un valor primario. No puede tener dos campos primarios una tabla.";
                                }
                                else
                                {
                                    //para saber cuando se ingreso un valor primario
                                    bPrimario = true;
                                    //Quitarle la coma
                                    string completo = query.substr(0, query.find(","));
                                    string GetAtributo = completo.substr(0, completo.find(" "));
                                    istringstream coma(completo);
                                    while(!coma.eof())
                                    {
                                        string tempStr;
                                        coma >> tempStr;
                                        if(cPalabra==1)
                                        {
                                            GetTP = tempStr;
                                        }
                                        cPalabra++;
                                    }
                                    if(regex_match(GetTP,TipoDato))
                                    {
                                        for(unsigned int conta = 0; conta < TAM; conta++)
                                        {
                                            if(arrayGA[conta]==GetAtributo)
                                            {
                                                //Si es que encontro un campo igual, repetir se ponga true
                                                repetir = true;
                                            }
                                        }

                                        if(repetir)
                                        {
                                            errorAtr = true;
                                            bandera = true;
                                            cout<<"-> Error: El atributo '" + GetAtributo + "' se ha repetido. Intente otra vez.<-"<<endl;
                                        }
                                        else
                                        {
                                            //Agregamos el atributo al array, para que no se vuelva elegir
                                            arrayGA[contadorGA] = GetAtributo;

                                            //Aumentar el contador de Array de Atributos
                                            contadorGA++;

                                            //GetAtributo - Nombre Atributo
                                            //TP - Tipo Datos
                                            atributos<<GetAtributo<<" "<<GetTP<<" Primario"<<endl;
                                        }
                                    }
                                    else
                                    {
                                        errorAtr = true;
                                        bandera=true;
                                        cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <-"<<endl;
                                    }
                                }
                            }
                            else if(regex_match(query, cInsertarAtributoFinal))
                            {
                                //Quitarle la coma
                                string completo1 = query.substr(0, query.find(";"));
                                string GetAtributo1 = completo1.substr(0, completo1.find(" "));
                                istringstream coma1(completo1);
                                while(!coma1.eof())
                                {
                                    string tempStr;
                                    coma1 >> tempStr;
                                    GetTP = tempStr;
                                }

                                if(regex_match(GetTP,TipoDato))
                                {
                                    for(unsigned int conta = 0; conta < TAM; conta++)
                                    {
                                        if(arrayGA[conta]==GetAtributo1)
                                        {
                                            //Si es que encontro un campo igual, repetir se ponga true
                                            repetir = true;
                                        }
                                    }

                                    if(repetir)
                                    {
                                        errorAtr = true;
                                        bandera = true;
                                        cout<<"-> Error: El atributo '" + GetAtributo1 + "' se ha repetido. Intente otra vez.<-"<<endl;
                                    }
                                    else
                                    {
                                        //Agregamos el atributo al array, para que no se vuelva elegir
                                        arrayGA[contadorGA] = GetAtributo1;

                                        //Aumentar el contador de Array de Atributos
                                        contadorGA++;

                                        //GetAtributo - Nombre Atributo
                                        //TP - Tipo Datos
                                        atributos<<GetAtributo1<<" "<<GetTP<<" No"<<endl;
                                        //Salir del programa
                                        bandera = true;

                                        cout<<" -> La tabla '" + tempNombre +"' ha sido creada correctamente. <- "<<endl;
                                    }

                                }
                                else
                                {
                                    errorAtr = true;
                                    bandera=true;
                                    cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <- "<<endl;
                                }
                            }
                            else if(regex_match(query,cInsertarAtributo))
                            {
                                //Quitarle la coma
                                string completo = query.substr(0, query.find(","));
                                string GetAtributo = completo.substr(0, completo.find(" "));
                                istringstream coma(completo);
                                while(!coma.eof())
                                {
                                    string tempStr;
                                    coma >> tempStr;
                                    GetTP = tempStr;
                                }

                                if(regex_match(GetTP,TipoDato))
                                {
                                    for(unsigned int conta = 0; conta < TAM; conta++)
                                    {
                                        if(arrayGA[conta]==GetAtributo)
                                        {
                                            //Si es que encontro un campo igual, repetir se ponga true
                                            repetir = true;
                                        }
                                    }

                                    if(repetir)
                                    {
                                        //Eliminar archivos
                                        errorAtr = true;
                                        bandera = true;
                                        cout<<"-> Error: El atributo '" + GetAtributo + "' se ha repetido. Intente otra vez.<-"<<endl;
                                    }
                                    else
                                    {
                                        //Agregamos el atributo al array, para que no se vuelva elegir
                                        arrayGA[contadorGA] = GetAtributo;

                                        //Aumentar el contador de Array de Atributos
                                        contadorGA++;

                                        //GetAtributo - Nombre Atributo
                                        //TP - Tipo Datos
                                        atributos<<GetAtributo<<" "<<GetTP<<" No"<<endl;
                                    }
                                }
                                else
                                {
                                    errorAtr = true;
                                    bandera=true;
                                    cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <-"<<endl;
                                }
                            }
                            else
                            {
                                //Eliminar archivos
                                errorAtr = true;
                                bandera = true;
                                cout<<" -> Error: Revise su instruccion. Intente de nuevo. <-"<<endl;
                            }
                        }while(bandera!=true);

                        atributos.close();
                    }
                    else
                    {
                        cout<<"-> Error al crear la tabla '" + tempNombre + "'. Intentelo de nuevo. <-"<<endl;
                    }
                }

                //eliminar arhivos temporales por si llega a ver error
                if (errorAtr)
                {
                    //tabla
                    Comando_Eliminar_Usuario(rutaDefinitiva1);
                    //atributos
                    Comando_Eliminar_Usuario(rutaDefinitiva);
                }

                //Limpiando el arreglo
                for (unsigned int conta = 0; conta < TAM; conta++)
                {
                    arrayGA[conta] = "";
                }

                query = "";

            }
        }
        else if(regex_match(consulta, cRetirarBaseDatos))
        {
            if (nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                cout<<" ->Retirada la Base de datos '" + nombreBaseDatos + "' CORRECTAMENTE. <-"<<endl;
                nombreBaseDatos = "";
            }
        }
        else if(regex_match(consulta, cEliminarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                istringstream isstream(consulta);
                while(!isstream.eof()){
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                cout<<"\t¿Seguro que desea eliminar la tabla '" + tempNombre + "'? (S/N): ";
                cin>>desicion;
                if (desicion == 'S' || desicion == 's')
                {
                    rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                    rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributoa\\" + tempNombre + ".txt";

                    if(is_file(rutaDefinitiva))
                    {
                        Comando_Eliminar_Usuario(rutaDefinitiva);
                        Comando_Eliminar_Usuario(rutaDefinitiva1);
                        cout<<" -> La Tabla '"<< tempNombre <<"' ha sido eliminado correctamente. <-"<<endl;
                    }
                    else
                    {
                        cout<<"-> La tabla  '"<< tempNombre <<"' que desea eliminar no existe. Intente con otro nombre.<-"<<endl;
                    }
                }
            }
        }
        else if(regex_match(consulta, cMostrarTablas))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                istringstream isstream(consulta);
                while(!isstream.eof()){
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas";

                Comando_Mostrar_Tablas(rutaDefinitiva);
            }
        }
        else if (regex_match(consulta, cExplicarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                //Cortar para obtener el nombre de la tabla
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                //Tabla
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                //Atributos
                rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";

                //Buscar la tabla
                if (!is_file(rutaDefinitiva1))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea EXPLICAR no existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    cCantidadCampos = 0;
                    numCampos = 0;
                    adentroAUX = 0;
                    adentro = 0;
                    query = "";

                    string variablez = "";
                    int longQ = 0;

                    //variable de lectura
                    ifstream leerCampos;
                    //Leer el archivo
                    leerCampos.open(rutaDefinitiva1,ios::out|ios::in);

                    //Abrir archivo (siempre se abrira y no habra error, porque si existe)
                    if(leerCampos.is_open())
                    {
                        //######################################################
                        //Contar el numero campos
                        //######################################################

                        //lectura adelantada
                        leerCampos>>save[cCantidadCampos];
                        while(!leerCampos.eof())
                        {
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                            cCantidadCampos++;
                            leerCampos>>save[cCantidadCampos];

                            //Es divisible de tres, entonces
                            if((cCantidadCampos%3)==0)
                            {
                                numCampos++;
                            }

                        }
                        //guardar el ultimo valor
                        arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                        //Para que no salga impar, y se haga par y se pueda dividir
                        cCantidadCampos++;

                        //###########################################
                        //EXPLICAR CADA ATRIBUTO
                        //###########################################
                        cout<<endl;
                        cout<<"|----------------------------------------------------|"<<endl;
                        cout<<"|       CAMPO       |    TIPO    |       LLAVE       |"<<endl;
                        cout<<"|----------------------------------------------------|"<<endl;
                        //Insertar los archivos en el archivo
                        do
                        {
                            for (int i = 0; i<3; i++)
                            {
                                variablez = save[adentro];
                                longQ = variablez.length();
                                if(longQ<=2)
                                {
                                    cout<<"        "<<save[adentro]<<"         ";
                                }
                                else if (longQ>2 && longQ<=6)
                                {
                                    cout<<"      "<<save[adentro]<<"       ";
                                }
                                else if (longQ>6 && longQ<10)
                                {
                                    cout<<"    "<<save[adentro]<<"    ";
                                }
                                else
                                {
                                    cout<<"    "<<save[adentro]<<"    ";
                                }
                                adentro++;
                            }
                            cout<<endl;
                            adentroAUX++;

                        }while(adentroAUX<numCampos);
                        cout<<"|----------------------------------------------------|"<<endl;
                    }
                    //Cerrar la lectura
                    leerCampos.close();

                    //Limpiar arreglos
                    for(unsigned int i = 0; i < TAM; i++)
                    {
                        arrayleerCampos[i] = "";
                        save[i] = "";
                    }

                    query = "";

                }
            }
        }
        else if(regex_match(consulta,cInsertarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                //Cortar para obtener el nombre de la tabla
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                //Tabla
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                //Atributos
                rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";

                //Buscar la tabla
                if (!is_file(rutaDefinitiva1))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea insertar no existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    bandInsertar = false;
                    bandValidCampo = false;
                    contadorInsertar = 0;
                    cCantidadCampos = 0;
                    num_campos = 0;
                    numCampos = 0;
                    cTipoDato = 0;
                    campoExitoso = 0;
                    adentroAUX = 0;
                    adentro = 0;
                    query = "";

                    //variable de lectura
                    ifstream leerCampos;
                    //Leer el archivo
                    leerCampos.open(rutaDefinitiva1,ios::out|ios::in);

                    //Abrir archivo (siempre se abrira y no habra error, porque si existe)
                    if(leerCampos.is_open())
                    {
                        //######################################################
                        //Contar el numero campos
                        //######################################################

                        //lectura adelantada
                        leerCampos>>save[cCantidadCampos];
                        while(!leerCampos.eof())
                        {
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                            cCantidadCampos++;
                            leerCampos>>save[cCantidadCampos];
                        }
                        //guardar el ultimo valor
                        arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                        //Para que no salga impar, y se haga par y se pueda dividir
                        cCantidadCampos++;

                        //Numero de campos que contiene la tabla
                        num_campos = cCantidadCampos / 3;

                        //######################################################
                        //Conocer los tipos de de datos (Inicia en 1)
                        //######################################################
                        for(int i = 1; i<(cCantidadCampos-1); i=i+3)
                        {
                            arrayTipoDato[cTipoDato]=arrayleerCampos[i];
                            cTipoDato++;
                        }
                        //Volver a cponer el contador en cero
                        cTipoDato = 0;

                        //######################################################
                        //Conocer los nombres de los campos
                        //######################################################
                        for(int i = 0; i<(cCantidadCampos-1); i=i+3)
                        {
                            arrayNombresCampos[cTipoDato]=arrayleerCampos[i];
                            cTipoDato++;
                        }

                        //Imprimiendo los CAMPOS de la tabla
                        cout<<"\t-------> ";
                        for(int i = 0; i<cTipoDato; i++)
                        {
                            if(i==(cTipoDato-1))
                            {
                                cout<<arrayNombresCampos[i]+".";
                            }
                            else
                            {
                                cout<<arrayNombresCampos[i]+", ";
                            }
                        }
                        cout<<"\n";
                        //Imprimiendo los TIPOS DE DATOS de los campos
                        cout<<"\t-------> ";
                        for(int i = 0; i<cTipoDato; i++)
                        {
                            if(i==(cTipoDato-1))
                            {
                                cout<<arrayTipoDato[i]+".";
                            }
                            else
                            {
                                cout<<arrayTipoDato[i]+", ";
                            }
                        }

                        do
                        {
                            cout<<"\n\t->";
                            getline(cin, query, '\n');

                            //Numero de campos regresa a cero
                            numCampos = 0;

                            if(regex_match(query,cInsertarTablaDatos))
                            {
                                //contador de inserciones (rows)
                                contadorInsertar++;

                                //Quitarle los dos puntos
                                string query_corte = query.substr(0, query.find(":"));

                                //conocer la longitud del string
                                int longitudQ = query_corte.length();

                                //separar los campos introducirdos
                                for(int i =0; i<longitudQ; i++)
                                {
                                    //Ingresar datos
                                    axuCampos = axuCampos + query_corte[i];

                                    //Encontrar la coma para separala
                                    if(regex_match(axuCampos, cComa))
                                    {
                                        //Quitarle la coma
                                        string ax = axuCampos.substr(0, axuCampos.find(","));

                                        //Asignarle valor al arreglo
                                        CamposInsert[numCampos] = ax;

                                        //Aumentarle valor al campo
                                        numCampos++;

                                        //Limpiamos la variable, para ingresar otro campos
                                        axuCampos = "";
                                    }
                                }

                                //Ingresar el ultimo valor
                                CamposInsert[numCampos] = axuCampos;

                                //Aumentar el campo
                                numCampos++;

                                //Limpiar la variable auxiliar
                                axuCampos = "";

                                //Si son difirentes error, debera de dar igual si no esta mal
                                if(numCampos!=num_campos)
                                {
                                    //Salir del ciclo
                                    bandInsertar = true;
                                    //Mensaje de error
                                    cout<<"ERROR: Ingrese los numeros de campos correspondiente."<<endl;
                                }//si son iguales esta bien
                                else if (numCampos==num_campos)
                                {   //Ciclo que valida cada uno de los campo introducidos
                                    for(int i = 0; i < numCampos; i++)
                                    {   //Si son tipo entero tendran que ser digitos
                                        if (arrayTipoDato[i]=="ENT"||arrayTipoDato[i]=="ent")
                                        {   //Si llega un tipo entero, y no es numero levantara la bandera
                                            if(!regex_match(CamposInsert[i],cDigito))
                                            {
                                                bandValidCampo = true;
                                            }
                                        }
                                    }


                                    //Si llego a haber algun algun error al validar los campos, no introducirlos
                                    if (bandValidCampo)
                                    {
                                        //Salir del programa y mensaje
                                        bandInsertar = true;
                                        cout<<"\nERROR: Ingrese los datos correctos. Intente otra vez."<<endl;
                                    }
                                    else
                                    {
                                        //Pasar los valores a un arreglo
                                        for(int i = 0; i <numCampos; i++)
                                        {
                                            arrayExitoso[campoExitoso] = CamposInsert[i];
                                            campoExitoso++;
                                        }
                                    }
                                }
                            }
                            else if (regex_match(query, cInsertarTablaDatosFinal))
                            {
                                //contador de inserciones (rows)
                                contadorInsertar++;
                                //Quitarle los dos puntos
                                string query_corte = query.substr(0, query.find(";"));

                                //conocer la longitud del string
                                int longitudQ = query_corte.length();

                                //separar los campos introducirdos
                                for(int i =0; i<longitudQ; i++)
                                {
                                    //Ingresar datos
                                    axuCampos = axuCampos + query_corte[i];

                                    //Encontrar la coma para separala
                                    if(regex_match(axuCampos, cComa))
                                    {
                                        //Quitarle la coma
                                        string ax = axuCampos.substr(0, axuCampos.find(","));

                                        //Asignarle valor al arreglo
                                        CamposInsert[numCampos] = ax;

                                        //Aumentarle valor al campo
                                        numCampos++;

                                        //Limpiamos la variable, para ingresar otro campos
                                        axuCampos = "";
                                    }
                                }

                                //Ingresar el ultimo valor
                                CamposInsert[numCampos] = axuCampos;

                                //Aumentar el campo
                                numCampos++;

                                //Limpiar la variable auxiliar
                                axuCampos = "";

                                //Si son difirentes error, debera de dar igual si no esta mal
                                if(numCampos!=num_campos)
                                {
                                    //Salir del ciclo
                                    bandInsertar = true;
                                    //Mensaje de error
                                    cout<<"ERROR: Ingrese los numeros de campos correspondiente."<<endl;
                                }//si son iguales esta bien
                                else if (numCampos==num_campos)
                                {   //Ciclo que valida cada uno de los campo introducidos
                                    for(int i = 0; i < numCampos; i++)
                                    {   //Si son tipo entero tendran que ser digitos
                                        if (arrayTipoDato[i]=="ENT"||arrayTipoDato[i]=="ent")
                                        {   //Si llega un tipo entero, y no es numero levantara la bandera
                                            if(!regex_match(CamposInsert[i],cDigito))
                                            {
                                                bandValidCampo = true;
                                            }
                                        }
                                    }


                                    //Si llego a haber algun algun error al validar los campos, no introducirlos
                                    if (bandValidCampo)
                                    {
                                        //Salir del programa y mensaje
                                        bandInsertar = true;
                                        cout<<"\nERROR: Ingrese los datos correctos. Intente otra vez."<<endl;
                                    }
                                    else
                                    {
                                        //Pasar los valores a un arreglo
                                        for(int i = 0; i <numCampos; i++)
                                        {
                                            arrayExitoso[campoExitoso] = CamposInsert[i];
                                            campoExitoso++;
                                        }

                                        //#################################################
                                        //INSERTAR DATOS
                                        //#################################################
                                        //Variable de escritura
                                        ofstream escribir;

                                        //Los permisos para escribir
                                        escribir.open(rutaDefinitiva,ios::out|ios::app);

                                        //Si existe el archivo
                                        if(escribir.is_open())
                                        {
                                            //Insertar los archivos en el archivo
                                                do
                                                {
                                                    for (int i = 0; i<numCampos; i++)
                                                    {
                                                        escribir<<arrayExitoso[adentro]<<" ";
                                                        adentro++;
                                                    }
                                                    escribir<<endl;
                                                    adentroAUX++;

                                                }while(adentroAUX<contadorInsertar);
                                        }
                                        escribir.close();

                                        bandInsertar = true;

                                        cout<<"\n-> Se ha insertado correctamente los valores en la tabla " + nombreBaseDatos + ". <-"<<endl;

                                    }
                                }
                            }
                            else
                            {
                                //Salir del programa y mensaje
                                bandInsertar = true;
                                cout<<"\nERROR: Use la sintaxis correcta. Tecle -a para mostrar ayuda. Intente otra vez."<<endl;
                            }

                        }while(bandInsertar!=true);

                    }
                    //Cerrar la lectura
                    leerCampos.close();

                    //Limpiar arreglos
                    for(unsigned int i = 0; i < TAM; i++)
                    {
                        arrayExitoso[i] = "";
                        arrayleerCampos[i] = "";
                        arrayNombresCampos[i] = "";
                        arrayTipoDato[i] = "";
                        CamposInsert[i] = "";
                        save[i] ="";
                    }

                    query = "";

                }
            }
        }
        else if(regex_match(consulta, cSeleccionarTabla))
        {
            if(nombreBaseDatos=="")
            {
                cout<<"Primero debes de seleccionar una base de datos con el comando USAR nombre_bd"<<endl;
                cout<<"Teclea -a para ayuda o -com para ver todos los comandos."<<endl;
            }
            else
            {
                //Cortar para obtener el nombre de la tabla
                istringstream isstream(consulta);
                while(!isstream.eof())
                {
                    string tempStr;
                    isstream >> tempStr;
                    tempNombre = tempStr;
                }

                //Tabla
                rutaDefinitiva = rutabasedatos + nombreBaseDatos + "\\Tablas\\" + tempNombre;
                //Atributos
                rutaDefinitiva1 = rutabasedatos + nombreBaseDatos + "\\Atributos\\" + tempNombre + ".txt";

                //Buscar la tabla
                if (!is_file(rutaDefinitiva1))
                {
                    cout<<"-> La tabla '" + tempNombre + "'que desea insertar no existe. Intente con otro nombre.<-"<<endl;
                    //SLEEEEP
                }
                else
                {
                    cCantidadCampos = 0;
                    numCampos = 0;
                    cTipoDato = 0;
                    adentroAUX = 0;
                    adentro = 0;
                    query = "";
                    string variabley = "";
                    int camposReales = 0;
                    int longQ = 0;

                    //variable de lectura
                    ifstream leerCampos;
                    //Leer el archivo
                    leerCampos.open(rutaDefinitiva1,ios::out|ios::in);

                    //Abrir archivo (siempre se abrira y no habra error, porque si existe)
                    if(leerCampos.is_open())
                    {
                        //######################################################
                        //Contar el numero campos
                        //######################################################

                        //lectura adelantada
                        leerCampos>>save[cCantidadCampos];
                        while(!leerCampos.eof())
                        {
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                            cCantidadCampos++;
                            leerCampos>>save[cCantidadCampos];
                        }

                        //Contar los atriburoa
                        while(!leerCampos.eof())
                        {
                            getline(leerCampos,variabley);
                        }

                        //guardar el ultimo valor
                        arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                        //Para que no salga impar, y se haga par y se pueda dividir
                        cCantidadCampos++;

                        //Contando y leyendo los campos
                        getline(leerCampos,variabley);
                        istringstream isstream(variabley);
                        while(!isstream.eof())
                        {
                            string tempStr;
                            isstream >> tempStr;
                            //tempNombre = tempStr;
                            camposReales++;
                        }

                        //######################################################
                        //Conocer los nombres de los campos
                        //######################################################
                        for(int i = 0; i<(cCantidadCampos-1); i=i+3)
                        {
                            arrayNombresCampos[cTipoDato]=arrayleerCampos[i];
                            cTipoDato++;

                        }
                        //Imprimiendo los CAMPOS de la tabla
                        cout<<"-----------------------------------------------------------------------------------------------"<<endl;
                        for(int i = 0; i<=cTipoDato; i++)
                        {
                            variabley = arrayNombresCampos[i];
                            longQ = variabley.length();
                            if(longQ<=2)
                            {
                                cout<<"     "<<arrayNombresCampos[i]<<"      ";
                            }
                            else if (longQ>2 && longQ<=6)
                            {
                                cout<<"     "<<arrayNombresCampos[i]<<"     ";
                            }
                            else if (longQ>6 && longQ<10)
                            {
                                cout<<"    "<<arrayNombresCampos[i]<<"    ";
                            }
                            else
                            {
                                cout<<"    "<<arrayNombresCampos[i]<<"    ";
                            }
                        }
                        cout<<"\n--------------------------------------------------------------------------------------------"<<endl;


                        //Limpiar datos
                        for(unsigned int i = 0; i < TAM; i++)
                        {
                            arrayleerCampos[i] = "";
                            arrayNombresCampos[i] = "";
                            save[i] ="";
                        }
                        cCantidadCampos = 0;
                        variabley = "";


                        //Cerrar la lectura
                        leerCampos.close();

                        //variable de lectura
                        ifstream leerDatos;
                        //Leer el archivo
                        leerDatos.open(rutaDefinitiva,ios::out|ios::in);


                        if(leerDatos.is_open())
                        {

                            //lectura adelantada
                            leerDatos>>save[cCantidadCampos];
                            while(!leerDatos.eof())
                            {
                                arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];
                                cCantidadCampos++;
                                leerDatos>>save[cCantidadCampos];

                                //Es divisible de tres, entonces
                                if((cCantidadCampos%3)==0)
                                {
                                    numCampos++;
                                }
                            }

                            //guardar el ultimo valor
                            arrayleerCampos[cCantidadCampos] = save[cCantidadCampos];

                            //Para que no salga impar, y se haga par y se pueda dividir
                            cCantidadCampos++;

                            do
                            {
                                for (int i = 0; i<cTipoDato; i++)
                                {
                                    variabley = save[adentro];
                                    longQ = variabley.length();
                                    if(longQ<=2)
                                    {
                                        cout<<"        "<<save[adentro]<<"         ";
                                    }
                                    else if (longQ>2 && longQ<=6)
                                    {
                                        cout<<"      "<<save[adentro]<<"       ";
                                    }
                                    else if (longQ>6 && longQ<10)
                                    {
                                        cout<<"    "<<save[adentro]<<"    ";
                                    }
                                    else
                                    {
                                        cout<<"    "<<save[adentro]<<"    ";
                                    }
                                    adentro++;
                                }
                                cout<<endl;
                                adentroAUX++;

                            }while(adentroAUX<numCampos);
                            cout<<"--------------------------------------------------------------------------------------------"<<endl;

                        }


                    }

                    //Limpiar arreglos
                    for(unsigned int i = 0; i < TAM; i++)
                    {
                        arrayleerCampos[i] = "";
                        arrayNombresCampos[i] = "";
                        save[i] ="";
                    }

                }
            }
        }
        else if(consulta=="")
        {
            //Nada, para que no muestra error
        }
        else
        {
            cout <<"Error: Error en su comando."<<endl;
        }
	}
	//pausaSinMensaje();

}

void Comando_BuscarEliminar_Usuarios()
{
    cout<<"Eliminara un usuario del Rango:"<<endl;
	cout<<"\t1.- Administrador"<<endl;
	cout<<"\t2.- Comun"<<endl;
	cout<<""<<endl;

	char tipoUsuario = 0;
	string dir;
	string nombreUsuario;

	cout<<"Opcion: "; cin >> tipoUsuario;

	if(tipoUsuario=='1')
	{
	    string dir = "c:\\BaseDeDatos\\Usuarios\\Admin\\";
		cout<<"Ingrese el nombre de Usuario: "; cin >> nombreUsuario;
		string rutadefinitiva = dir + nombreUsuario;
		if(is_file(rutadefinitiva))
        {
            Comando_Eliminar_Usuario(rutadefinitiva);
            cout<<" -> EL Usuario '"<< nombreUsuario <<"' ha sido eliminado correctamente. <-"<<endl;
        }
        else
        {
            cout<<"-> El Usuario '"<< nombreUsuario <<"' que desea eliminar no existe. <-"<<endl;
        }
	}
	else if(tipoUsuario=='2')
	{
	    string dir = "c:\\BaseDeDatos\\Usuarios\\Comunes\\";
		cout<<"Ingrese el nombre de Usuario: "; cin >> nombreUsuario;
		string rutadefinitiva = dir + nombreUsuario;
		if(is_file(rutadefinitiva))
        {
            Comando_Eliminar_Usuario(rutadefinitiva);
            cout<<" -> El Usuario '"<< nombreUsuario <<"' ha sido eliminado correctamente. <-"<<endl;
        }
        else
        {
            cout<<"-> El Usuario '"<< nombreUsuario <<"' que desea eliminar no existe. <-"<<endl;
        }

	}
	else
    {
        cout<<" -> Ingrese una Opcion Correcta. <-"<<endl;
    }
}

void Comando_Crear_Usuarios()
{
	cout<<"Creara un Usuario con Rango de:"<<endl;
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
    cout<<"\n\n\t\tCREAR TABLA"<<endl;
    cout<<"\n\nEn el momento de crear una tabla con el comando CREAR TABLA NOMBRE_TABLA ingresamos Campo y Tipo de Dato a ingresar seguido de una coma (,)";
    cout<<" seguido del siguiente Campo y Tipo de Dato a ingresar, asi sucesivamente hasta llegar al ultimo campo. En el ultimo campo se agrega dos punto (:)";
    cout<<" para dar un salgo de linea e introducir un nuevo registro. Si ya no se quieren introducir mas campos nuevos se termina la instruccion"<<endl;
    cout<<" con un punto y coma (;)."<<endl;
    cout<<"\n\n\t\tINSERTAR EN"<<endl;
    cout<<"\n\nEn el momento de crear una tabla con el comando INSERTAR EN NOMBRE_TABLA aparecera ayuda donde mostrara el nombre del campo y sus respectivos campos";
    cout<<" alli ingresamos los datos seguido de coma (,) para separalo del siguiente dato.";
    cout<<""<<endl;
}

void Comando_Comandos()
{
    cout<<"                   _____                                 _"<<endl;
    cout<<"                  /  __ \\                               | | "<<endl;
    cout<<"                  | /  \\/ ___  _ __ ___   __ _ _ __   __| | ___  ___ "<<endl;
    cout<<"                  | |    / _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\/ __|"<<endl;
    cout<<"                  | \\__/\\ (_) | | | | | | (_| | | | | (_| | (_) \\__ \\"<<endl;
    cout<<"                   \\____/\\___/|_| |_| |_|\\__,_|_| |_|\\__,_|\\___/|___/"<<endl;
    cout<<""<<endl;
    cout<<"-a"<<endl;
    cout<<"\t\tMuestra reglas basicas para majear las bases de datos."<<endl;
    cout<<"-com"<<endl;
    cout<<"\t\tMuestra todos los comandos disponibles y sus funciones."<<endl;
    cout<<"-l"<<endl;
    cout<<"\t\tPermite limpiar la pantalla."<<endl;
    cout<<"SALIR"<<endl;
    cout<<"\t\tCierra el programa."<<endl;
    cout<<"\n\n";
    cout<<"\t\t\tCOMANDOS DE USUARIOS"<<endl;
    cout<<"CREAR USUARIO"<<endl;
    cout<<"\t\tPermite crear un usuario del rango administrador o comun."<<endl;
    cout<<"USUARIO"<<endl;
    cout<<"\t\tMuestra el usuario con el que se ha conectado."<<endl;
    cout<<"MOSTRAR USUARIO ADMINISTRADORES"<<endl;
    cout<<"\t\tMuestra todos los usuarios con rango de Aministradores."<<endl;
    cout<<"MOSTRAR USUARIO COMUNES"<<endl;
    cout<<"\t\tMuestra todos los usuarios con rango de Comunes."<<endl;
    cout<<"ELIMINAR USUARIO"<<endl;
    cout<<"\tPermite eliminar un usuario de ambos rangos."<<endl;
    cout<<"CERRAR"<<endl;
    cout<<"\t\tCierra la sesion."<<endl;
    cout<<"\n\n";
    cout<<"\t\t\tCOMANDOS DE BASES DE DATOS"<<endl;
    cout<<"CREAR BASEDATOS nombre_bd"<<endl;
    cout<<"\t\tPermite crear una base de datos."<<endl;
    cout<<"USAR nombre_bd"<<endl;
    cout<<"\t\tUso de una de las bases de datos ya creada previamente."<<endl;
    cout<<"RETIRAR BASEDATOS"<<endl;
    cout<<"\t\tPermite dejar de usar la base de datos que esta seleccionada actualmente."<<endl;
    cout<<"MOSTRAR BASEDATOS"<<endl;
    cout<<"\t\tMuestra todas las bases de datos existentes."<<endl;
    cout<<"ELIMINAR BASEDATOS nombre_bd"<<endl;
    cout<<"\t\tElimina la base de datos seleccionada."<<endl;
    cout<<"\n\n";
    cout<<"\t\t\tCOMANDOS DE TABLAS"<<endl;
    cout<<"CREAR TABLA nombre_tabla"<<endl;
    cout<<"\t\tPermite crear una tabla en una base de datos ya seleccionada."<<endl;
    cout<<"ELIMINAR TABLA nombre_tabla"<<endl;
    cout<<"\t\tPermite eliminar una tabla existen dentro de una base datos."<<endl;
    cout<<"MOSTRAR TABLAS"<<endl;
    cout<<"\t\tMuestra todoas las tablas que contiene la base de datos seleccionada."<<endl;
    cout<<"EXPLICAR nombre_tabla"<<endl;
    cout<<"\t\tMuestra todos los atributos de la tabla con sus respectivos tipos de datos."<<endl;
    cout<<"INSERTAR EN nombre_tabla"<<endl;
    cout<<"\tPermite insertar datos en la tabla seleccionada."<<endl;
    cout<<"\S * DESDE nombre_tabla"<<endl;
    cout<<"\tMuestra todos los datos de la tabla."<<endl;
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

bool is_dir(string dir)
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

bool is_file(string file)
{
    FILE * archivo;
    if (archivo = fopen(file.c_str(), "r"))
    {
        fclose(archivo);
        return true;
    }
    else
    {
        return false;
    }
}

void Comando_Eliminar_BD(string ruta)
{
     string comando; //rmdir o del
     if (is_dir(ruta))
     {
      comando = "rmdir " + ruta + " /s /q";
      system(comando.c_str());
     }
}

void Comando_Eliminar_Usuario(string ruta)
{
    string comando; //rmdir o del
    if (is_file(ruta))
    {
    comando = "del " + ruta;
    system(comando.c_str());
    }
}

void Comando_Mostrar_Tablas(string dir)
{
    cout<<"+------------------+"<<endl;
    cout<<"|       TABLAS     |"<<endl;
    cout<<"+------------------+"<<endl;
    //string dir = "c:/BaseDeDatos/Usuarios/Admin";
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
