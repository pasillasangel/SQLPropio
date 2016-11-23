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

/*
    Eliminar los archivos al dar errorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
    -- Agregar el mensaje "EXITOSO"
    Hacer un arreglo para evitar que se agregen campos repetidos
*/

regex cCrearTabla("^(crear tabla\\s(\\w)+|CREAR TABLA\\s(\\w)+)$");
regex cInsertarAtributo("^([A-Za-z](\\w)+\\s(\\w)+,)$");
regex cInsertarAtributoFinal("^([A-Za-z](\\w)+\\s(\\w)+;)$");
regex TipoDato("^(ent|ENT|varcarac|VARCARAC|\\;)$");

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

int main(int argc, char** argv){

    bool bandera = false;
    string GetTP = "";
    string query = "";

    string rutaDefinitiva;
    string rutaDefinitiva1;
    string rutabasedatos = "C:\\BaseDeDatos\\BD\\";
    string nombreBaseDatos = "cortar";
    string consulta = "";
    string tempNombre;

    cout<<"Ingrese Consulta -> ";
    getline(cin, consulta, '\n');

    if(regex_match(consulta, cCrearTabla))
    {
        if(nombreBaseDatos=="")
        {
            cout<<"Seleccione una base de datos.";
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
                        cout<<"\t->";
                        getline(cin, query, '\n');

                        if(regex_match(query, cInsertarAtributoFinal))
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
                                //GetAtributo - Nombre Atributo
                                //TP - Tipo Datos
                                atributos<<GetAtributo1<<" "<<GetTP<<endl;
                                //Salir del programa
                                bandera = true;

                                cout<<" -> La tabla '" + tempNombre +"' ha sido creada correctamente. <- "<<endl;

                            }
                            else
                            {
                                bandera=true;
                                cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <- 1"<<endl;
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
                                //GetAtributo - Nombre Atributo
                                //TP - Tipo Datos
                                atributos<<GetAtributo<<" "<<GetTP<<endl;
                            }
                            else
                            {
                                bandera=true;
                                cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <- 1"<<endl;
                            }
                        }
                        else
                        {
                            bandera = true;
                            cout<<" -> Error: Revise su instruccion. Intente de nuevo. <- 2"<<endl;
                        }
                    }while(bandera!=true);

                    atributos.close();
                }
                else
                {
                    cout<<"-> Error al crear la tabla '" + tempNombre + "'. Intentelo de nuevo. <- 3"<<endl;
                }
            }
        }
    }
    else
    {
        cout<<"NOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
    }

	//Comando_Mostrar_Tablas(rutaDefinitiva);

/*
    //Eliminar tabla
    if(is_file(rutaDefinitiva))
    {
        Comando_Eliminar_Usuario(rutaDefinitiva);
        cout<<" -> La Tabla '"<< tempNombre <<"' ha sido eliminado correctamente. <-"<<endl;
    }
    else
    {
        cout<<"-> La tabla  '"<< tempNombre <<"' que desea eliminar no existe. Intente con otro nombre.<-"<<endl;
    }

    //CREAR TABLA
	if (is_file(rutaDefinitiva))
    {
        cout<<"-> La tabla '" + tempNombre + "'que desea crear ya existe. Intente con otro nombre.<-"<<endl;
        //SLEEEEP
	}
	else
    {
        ofstream fs(rutaDefinitiva);
        cout<<"-> Tabla '" + tempNombre + "' creada correctamente."<<endl;
    }
*/
    return 0;
}

/*
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

void Comando_Eliminar_Usuario(string ruta)
{
    string comando; //rmdir o del
    if (is_file(ruta))
    {
    comando = "del " + ruta;
    system(comando.c_str());
    }
}

*/
