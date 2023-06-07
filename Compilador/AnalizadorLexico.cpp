/**
 * @file ANALIZADOR.cpp
 * @author Lissete Lopez Hernandez
 * @brief El programa es un analizador lexico de un evaluador de formulas, que utiliza un AFD para operar y su salida es en un archivo txt, mientras que los mensajes se muestran en consola
 * @version 0.1
 * "@date 2022-04-23"
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * TODO:El usuario debe ingresar en orden los datos de:
 * * num edos num caracteres o conjuntos num edos_finales
 * * idconjunto numsimbolos del conjunto tipo de token que representa el conjunto
 * * simbolos del conjunto
 * * ids de conjuntos para cada columna de tabla de transicion
 * * edos tabla de transicion
 * * edos finales
 * * num palabras
 * * palabras a testear
 *? Ejemplo:
 * *8 5 4
 * *A 26 Identificador
 * *A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 * *B 26 Identificador
 * *a b c d e f g h i j k l m n o p q r s t u v w x y z
 * *C 10 Entero
 * *0 1 2 3 4 5 6 7 8 9
 * *D 2 Operador
 * *- +
 * *E 1 Espacio
 * *esp
 * *A	B	C	D	E
 * *2	2	1	7	0
 * *7	7	1	3	4
 * *6	6	7	3	4
 * *5	5	5	7	3
 * *7	7	7	3	4
 * *6	6	5	0	5
 * *7	7	7	3	6
 * *7	7	7	7	7
 * *1 2 5 6
 * *4
 * *ac +  10 - 7
 * *a+  10 - ab +15
 * *43-9+3- ab +8-c
 * *43-9+3}- ab +8-c
 * * */

/***
 * !ARREGLAR
 * !No tiene validaciones para cuando no recibe valores
 */

#include <bits/stdc++.h>
using namespace std;
// globales
unordered_map<string, short int> tokenNumerico;
// Banderas que estan en cero cuando no se ha encontrado el lexema de inideclaraciones o findeclaraciones, tienen el valor de 1 cuando se encuentra.
char flagIniDeclaraciones = '0';
char flagFinDeclaraciones = '0';
char flagIniAsignaciones = '0';
char flagFinAsignaciones = '0';

//* Prototipos
void searchSet(int caracteres);
void fillTable(int edos, int conjuntosCaracteres, vector<vector<int>> &tabla);
void printTable(int edos, int caracteres, vector<vector<int>> &tabla);
vector<string> evaluaPalabra(int &edoActual, vector<vector<int>> tabla, string &palabra, unordered_map<char, int> &alphabet, multimap<char, char> &conjuntos, unordered_map<int, int> &finales, unordered_map<char, string> &token, int &index, unordered_map<string, string> &palabrasReservadas, short int &CommentsCounter);
void printWord(string &palabra);

int main()
{
    // Entrada de datos rapida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ///////////////////////////////////////////////////////////
    //*Init
    int edos;
    int caracteres;
    int edos_finales;
    int numpalabras;
    short int CommentsCounter = 0; // cada que este en / sera un numero par de veces, entonces cada que se encuentren dos comentarios // y // volvera a imprimir
    string palabra;
    vector<vector<int>> tabla;
    unordered_map<char, int> alphabet;
    unordered_map<int, int> finales;

    int edoActual = 0;
    //*Solicitud de datos de tabla de transicion: num de edos totales, num caracteres, contenido tabla de transicion.
    // cout<< "Ingresa> el numero de estados, numero de caracteres del alfabeto, numero de estados finales, y numero de conjuntos (de caracteres) (e.g A=abcde B=12345) cada numero separado por un espacio unicamente. Ejemplo: 3 2 1 2";
    cin >> edos >> caracteres >> edos_finales;

    multimap<char, char> conjuntos; // diccionario con multiples entradas indicara a que conjunto de simbolos pertenece cada dato
    // tABLA HASH DE LISTA DE LEXEMAS Y TOKENS
    unordered_map<char, string> token;
    // Palabras reservadas
    unordered_map<string, string> palabrasReservadas;
    palabrasReservadas["int"] = "TipoDato";
    palabrasReservadas["return"] = "palabraReservada";
    palabrasReservadas["iniciar"] = "iniciar";
    palabrasReservadas["inideclaraciones"] = "inideclaraciones";
    palabrasReservadas["findeclaraciones"] = "findeclaraciones";
    palabrasReservadas["iniasignaciones"] = "iniasignaciones";
    palabrasReservadas["finasignaciones"] = "finasignaciones";
    palabrasReservadas["inideffunciones"] = "inideffunciones";
    palabrasReservadas["findeffunciones"] = "findeffunciones";
    palabrasReservadas["inifunciones"] = "inifunciones";
    palabrasReservadas["finfunciones"] = "finfunciones";
    palabrasReservadas["inimain"] = "inimain";
    palabrasReservadas["finmain"] = "finmain";
    palabrasReservadas["terminar"] = "terminar";
    palabrasReservadas["iniexpresiones"] = "iniexpresiones";
    palabrasReservadas["finexpresiones"] = "finexpresiones";
    // Valores de tokens numericos
    tokenNumerico["iniciar"] = 10;
    tokenNumerico["inideclaraciones"] = 11;
    tokenNumerico["findeclaraciones"] = 12;
    tokenNumerico["iniasignaciones"] = 13;
    tokenNumerico["finasignaciones"] = 14;
    tokenNumerico["inideffunciones"] = 15;
    tokenNumerico["findeffunciones"] = 16;
    tokenNumerico["inimain"] = 17;
    tokenNumerico["finmain"] = 18;
    tokenNumerico["terminar"] = 19;
    tokenNumerico["iniexpresiones"] = 20;
    tokenNumerico["finexpresiones"] = 21;
    tokenNumerico["inifunciones"] = 22;
    tokenNumerico["finfunciones"] = 23;
    tokenNumerico["TipoDato"] = 24;
    tokenNumerico["Identificador"] = 30;
    tokenNumerico["palabraReservada"] = 31;
    tokenNumerico["("] = 40;
    tokenNumerico[")"] = 41;
    tokenNumerico["{"] = 42;
    tokenNumerico["}"] = 43;
    tokenNumerico[","] = 44;
    tokenNumerico[";"] = 45;
    tokenNumerico["="] = 46;
    tokenNumerico["_"] = 47;
    tokenNumerico["/"] = 48;
    tokenNumerico["Numero"] = 50;
    tokenNumerico["Operador1"] = 60;
    tokenNumerico["Operador2"] = 61;
    tokenNumerico["indefinido"] = 70;

    // caracteres=numero de conjuntos
    for (int i = 0; i < caracteres; i++)
    {
        char conjunto; // id de conjunto
        cin >> conjunto;
        int numsimbolos; // num de elementos que tendra ese conjunto
        cin >> numsimbolos;
        string tipoToken;
        cin >> tipoToken;
        token[conjunto] = tipoToken;
        for (int j = 0; j < numsimbolos; j++)
        {
            string simbolo;
            cin >> simbolo;
            // solo lee el caracter
            char caracter = simbolo[0];
            conjuntos.insert({caracter, conjunto}); // simbolo - conjunto al que pertenece
        }
    }

    // cout<<"Ingresa los id de conjunto separados por espacios. Ejemplo: a b ";

    for (int i = 0; i < caracteres; i++)
    {
        char letra;
        cin >> letra;

        alphabet[letra] = i;
    }
    // cout<<"Ingresa los estados en la tabla de transicion. Ejemplo: 1 2 1 1 2 2";
    fillTable(edos, caracteres, tabla);
    // printTable(edos,caracteres,tabla);
    //  cout<<"Ingresa los estados finales. Ejemplo: 1";
    for (int i = 0; i < edos_finales; i++)
    {
        int num;
        cin >> num;
        finales[num] = i;
    }
    cin >> numpalabras;
    for (int i = 0; i < numpalabras; i++)
    {
        cin >> palabra;
        // printWord(palabra);
        for (auto error : evaluaPalabra(edoActual, tabla, palabra, alphabet, conjuntos, finales, token, i, palabrasReservadas, CommentsCounter))
        {
            cout << "Error--> " << error << endl;
        }
    }
    cout<<"Analisis lexico terminado";

    //////////////////////////////////////////////////////////

    return 0;
}

//////////////////////////
// Funciones

//**Llena la tabla de transiciones
void fillTable(int edos, int conjuntosCaracteres, vector<vector<int>> &tabla)
{
    int dato;
    for (int i = 0; i < edos; i++)
    {
        vector<int> temporal;
        for (int j = 0; j < conjuntosCaracteres; j++)
        {
            cin >> dato;
            // cout <<dato<<endl;
            temporal.push_back(dato); // datos de cada fila
        }
        tabla.push_back(temporal); // insercion de columnas
    }
}

//*Imprime la tabla de transiciones
void printTable(int edos, int caracteres, vector<vector<int>> &tabla)
{

    for (int i = 0; i < edos; i++)
    {
        cout << endl; // division entre filas
        for (int j = 0; j < caracteres; j++)
        {
            cout << tabla[i][j];
        }
    }
}
//*Evalua si la palabra ingresada pertenece al lenguaje del automata
vector<string> evaluaPalabra(int &edoActual, vector<vector<int>> tabla, string &palabra, unordered_map<char, int> &alphabet, multimap<char, char> &conjuntos, unordered_map<int, int> &finales, unordered_map<char, string> &token, int &index, unordered_map<string, string> &palabrasReservadas, short int &CommentsCounter)
{
    // Creacion o apertura del archivo donde se escrbiran los tokens
    fstream listaTokens, valoresTokens, Vardeclaradas, VarUsadas;
    valoresTokens.open("TokensValores.txt", ios::app | ios::out);
    listaTokens.open("FlujoTokens.txt", ios::app | ios::out);           // abre archivo txt para imprimir lista de tokens
    Vardeclaradas.open("VariablesDeclaradas.txt", ios::app | ios::out); // abre archivo txt para imprimir lista de tokens
    VarUsadas.open("VariablesUsadas.txt", ios::app | ios::out);         // abre archivo txt para imprimir lista de tokens
    if (!listaTokens)
        cout << "Analizador lexico dice: archivo de flujo de tokens no creado";
    if (!valoresTokens)
        cout << "Analizador lexico dice: archivo de valores de tokens no creado";
    if (!Vardeclaradas)
        cout << "Analizador lexico dice: archivo de variables declaradas no creado";
    if (!VarUsadas)
        cout << "Analizador lexico dice: archivo de variables declaradas no creado";
    edoActual = 0;
    vector<string> errores;
    char flag = '*';
    char tokenFlag = '|';
    string lexema = "";
    string tipoToken = "";

    //*Determinacion del último estado del autómata al que llegó la palabra
    /*For each Saca cada simbolo de la palabra entrante, (se almacena en simbolo)*/
    for (char simbolo : palabra)
    {
        char conjunto;
        // buca si encuentra el simbolo en el registro de conjuntos aceptados
        if (conjuntos.find(simbolo) != conjuntos.end())
            conjunto = conjuntos.lower_bound(simbolo)->second; // si se encuentra, etonces obtiene el id de conjunto
        else
        {
            conjunto = '-';
            tipoToken = "indefinido"; // si no se encuentra es indefinido
        }
        // si el conjunto se encuentra en el alfabeto se hace una comoaracion de conjuntos, cada que se encuentre con un simbolo de otro conjunto va a imprimir el lexema y el tipo de dato, esto para que se forme la palabra completa del lexema
        if (alphabet.count(conjunto))
        {
            if (tokenFlag != conjunto)
            {
                tokenFlag = conjunto;

                if (tipoToken.compare("Identificador") == 0)
                {

                    // si es identificador, busca el lexema en las palabras reservadas, si se encuentra es palabra reservada y el tipo de token cambia, si no, es identificador
                    if (palabrasReservadas.find(lexema) != palabrasReservadas.end())
                    {
                        tipoToken = palabrasReservadas[lexema];
                    }
                }
                // si los lexemas se encuentran dentro de un bloque de comentario delimmitado por //mensaje // no se imprime como lexema
                if (!lexema.empty() && CommentsCounter < 2 && tipoToken.compare("Comentario"))
                {
                    listaTokens << lexema << "\t\t" << tipoToken << endl;
                    valoresTokens << tokenNumerico[tipoToken] << endl;
                    // si un identificador se encuentra entre inideclaracion y findeclaraciones se escribe en VariablesDeclaradas.txt
                    if (lexema == "findeclaraciones")
                    {
                        flagFinDeclaraciones = '1';
                    }
                    if (flagFinDeclaraciones == '0' && flagIniDeclaraciones == '1')
                    {
                        Vardeclaradas << lexema << endl;
                    }
                    if (lexema == "inideclaraciones")
                    {
                        flagIniDeclaraciones = '1';
                    }
                    if (lexema == "finasignaciones")
                    {
                        flagFinAsignaciones = '1';
                    }
                    if (flagFinAsignaciones == '0' && flagIniAsignaciones == '1' && tipoToken.compare("Identificador") == 0)
                    {
                        VarUsadas << lexema << endl;
                    }
                    if (lexema == "iniasignaciones")
                    {
                        flagIniAsignaciones = '1';
                    }
                }
                // cuando termina e formar el lexema, limpia la variable para el nuevo lexema
                lexema.clear();
            }
            lexema.push_back(simbolo);   // va formando el lexema simbolo por simbolo
            tipoToken = token[conjunto]; // calcula el tipo de token
            if (tipoToken.compare("Comentario") == 0)
            {
                // si el lexema es un comentario determina el numero de / que se han identificado, cuando llegue a 4 se acabo el bloque de comentario entonces ya se puede imprimir
                CommentsCounter++;
                if (CommentsCounter == 4)
                    CommentsCounter = 0;
            }
            edoActual = tabla[edoActual][alphabet[conjunto]]; // calcula el estado actual en el automata
        }
        else
        {
            flag = 'x';
            tokenFlag = '-';
            // si no se trata de un comentario imprime los datos en los archivos
            if (CommentsCounter < 2 && tipoToken.compare("Comentario") == 0)
            {
                listaTokens << lexema << "\t\t" << tipoToken << endl;
                valoresTokens << tokenNumerico[tipoToken] << endl;
                if (lexema == "findeclaraciones")
                {
                    flagFinDeclaraciones = '1';
                }
                if (flagFinDeclaraciones == '0' && flagIniDeclaraciones == '1')
                {
                    Vardeclaradas << lexema << endl;
                }
                if (lexema == "inideclaraciones")
                {
                    flagIniDeclaraciones = '1';
                }
                if (lexema == "finasignaciones")
                {
                    flagFinAsignaciones = '1';
                }
                if (flagFinAsignaciones == '0' && flagIniAsignaciones == '1' && tipoToken.compare("Identificador") == 0)
                {
                    VarUsadas << lexema << endl;
                }
                if (lexema == "iniasignaciones")
                {
                    flagIniAsignaciones = '1';
                }
            }
            if (tokenFlag != conjunto)
                lexema.clear();
            lexema.push_back(simbolo);
            tipoToken = "indefinido";
            string error = simbolo + string(" No es un simbolo reconocido");
            if (CommentsCounter < 2)
                errores.push_back(error);
        }
    }
    // si se trata de un indentificador buscalo en palabras reservadas para verificar que no sea una
    if (tipoToken.compare("Identificador") == 0)
    {
        if (palabrasReservadas.find(lexema) != palabrasReservadas.end())
        {
            tipoToken = palabrasReservadas[lexema];
        }
    }
    // si no es un comentario imprime los datos en los archivos
    if (CommentsCounter < 2 && tipoToken.compare("Comentario"))
    {
        listaTokens << lexema << "\t\t" << tipoToken << endl;
        valoresTokens << tokenNumerico[tipoToken] << endl;
        if (lexema == "findeclaraciones")
        {
            flagFinDeclaraciones = '1';
        }
        if (flagFinDeclaraciones == '0' && flagIniDeclaraciones == '1' && tipoToken.compare("Identificador") == 0)
        {
            Vardeclaradas << lexema << endl;
        }
        if (lexema == "inideclaraciones")
        {
            flagIniDeclaraciones = '1';
        }
        if (lexema == "finasignaciones")
        {
            flagFinAsignaciones = '1';
        }
        if (flagFinAsignaciones == '0' && flagIniAsignaciones == '1' && tipoToken.compare("Identificador") == 0)
        {
            VarUsadas << lexema << endl;
        }
        if (lexema == "iniasignaciones")
        {
            flagIniAsignaciones = '1';
        }
    }
    //*Evalúa si el último estado el que llevó la palabra se encuentra en los Estados finales, en caso de que si se acepta la palabra, en caso contrario se deniega
    if (finales.count(edoActual) && flag == '*')
        ; // cout << " Analizador Lexico dice: Palabra aceptada" << endl;
    else
    {
        printWord(palabra);
        cout << "Analizador Lexico dice:Palabra denegada" << endl;
    }
    listaTokens.close();
    valoresTokens.close();
    return errores;
}
//*Imprime la palabra que evaluará el autómata
void printWord(string &palabra)
{
    cout << endl
         << "Palabra: "
         << palabra << " -> ";
}