#include <cstdlib>
#include <iostream>
#include <fstream> //Manipulacion de archivos
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
#define TAM 50

using namespace std;

regex cInsertarTabla("^(INSERTAR EN [A-Za-z](\\w)+|insertar en [A-Za-z](\\w)+)$");
regex cInsertarTablaDatos("^(([(A-zA-Z)|(0-9)]+,)+[(A-zA-Z)|(0-9)]+:)$");
regex cInsertarTablaDatosFinal("^(([(A-zA-Z)|(0-9)]+,)+[(A-zA-Z)|(0-9)]+;)$");

regex cDigito("^([-|+]?[0-9]+)$");
regex cComa("^(\\w+,)$");

bool is_file(string file);


main()
{
    int cCantidadCampos = 0;
    int cTipoDato = 0;
    float num_campos = 0;
    int numCampos = 0;
    int campoExitoso = 0;
    bool bandInsertar = false;
    bool bandValidCampo = false;
    int contadorInsertar = 0;
    int adentro = 0;
    int adentroAUX = 0;

    string save[TAM];
    string arrayleerCampos[TAM];
    string arrayNombresCampos[TAM];
    string arrayTipoDato[TAM];
    string CamposInsert[TAM];
    string arrayExitoso[TAM];
    string axuCampos = "";
    string query = "";

    string rutaDefinitiva;
    string rutaDefinitiva1;
    string rutabasedatos = "C:\\BaseDeDatos\\BD\\";
    string nombreBaseDatos = "cortar";
    string consulta = "";
    string tempNombre;

    cout<<"Ingrese Consulta -> ";
    getline(cin, consulta, '\n');

    if(nombreBaseDatos=="")
        {
            cout<<"Seleccione una base de datos.";
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
                    cout<<"\n";

                    do
                    {
                        cout<<"\t->";
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
                }

                query = "";

            }
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
