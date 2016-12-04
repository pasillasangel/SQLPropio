
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

                        //Esdivisible de tres, entonces
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

                    cout<<"\nadentroaux: "<<adentroAUX<<" - numCampos: "<<numCampos<<" - adentro: "<<adentro<<" - "<<endl;

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
