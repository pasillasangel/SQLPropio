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
#define TAM 10

using namespace std;

/*
    Problemas por solucionar
    -- Agregar el mensaje "EXITOSO"
    -- Hacer un arreglo para evitar que se agregen campos repetidos
    Eliminar los archivos al dar errorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
    Identificar los campos primarios
    Que solo se pueda ingresarn un campo primario por tabla
*/

regex cCrearTabla("^(crear tabla\\s(\\w)+|CREAR TABLA\\s(\\w)+)$");
regex cInsertarAtributo("^([A-Za-z](\\w)+\\s(\\w)+,)$");
regex cInsertarAtributoFinal("^([A-Za-z](\\w)+\\s(\\w)+;)$");
regex cInsertarAtributoPrimario("^([A-Za-z](\\w)+\\s(\\w)+\\s(PRIMARIO|primario),)$");
regex cInsertarAtributoFinalPrimario("^([A-Za-z](\\w)+\\s(\\w)+\\s(PRIMARIO|primario);)$");
regex TipoDato("^(ent|ENT|var|VAR|)$");

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
        //***
        //Variables
        //***
    //Para salir del ciclo de ingrsar 'campos'
    bool bandera = false;
    //Para saber cuando se repitio un campo
    bool repetir = false;
    //Para contar cada palabra y tomar solo TIPO DE DATO y validarlo
    int cPalabra = 0;
    //Para saber que solo se ingreso una llave primaria
    bool bPrimario = false;
    //Arreglo de string para almacenar los campos  (para que no se repitan) y su contador
    string arrayGA[TAM];
    int contadorGA = 0;

    //Almanecenara el TIPO DE DATO
    string GetTP = "";

    //Almanecenara todo la instruccion
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
                repetir = false;
                bPrimario = false;
                contadorGA = 0;


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
                                    bandera=true;
                                    cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <- "<<endl;
                                }
                            }
                        }
                        else if (regex_match(query,cInsertarAtributoPrimario))
                        {
                            if (bPrimario)
                            {
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
                                bandera=true;
                                cout<<" -> Error: Ingrese un tipo de dato correcto. Intente de nuevo. <-"<<endl;
                            }
                        }
                        else
                        {
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


            //Limpiando el arreglo
            for (unsigned int conta = 0; conta < TAM; conta++)
            {
                arrayGA[conta] = "";
            }

        }
    }

    return 0;
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
