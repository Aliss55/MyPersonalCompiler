#include "AnalizadorS.h"
/**
 * @brief Obtiene el primer simbolo de la cadena reconocido por la gramatica, por ejemplo: E' la identifica como un unico simbolo y no como E y '
 * 
 * @param cadena de la que se obtendran los simbolos
 * @return string con el simbolo obtenido
 */
string AnalizadorS::primerSimbolo(string &cadena, unordered_map<string, int> &tablaSimbolos)
{
    flag_suknown = 0;
    string mensaje="";
    //Primero se consideran dos caracteres de la cadena
    string nextSymbol = cadena.substr(0, 2);
    //Si esos 2 caracteres en conjunto forman un simbolo de la gramatica, se retorna el simbolo
    if (tablaSimbolos.find(nextSymbol) != tablaSimbolos.end())
    {
        longitudTopeCadena = nextSymbol.length();
        return nextSymbol;
    }
    else
    {
        //si  no se encuentra se considera unicamente el primer caracter de la cadena
        nextSymbol.pop_back();
        if (tablaSimbolos.find(nextSymbol) != tablaSimbolos.end())
        {
            longitudTopeCadena = nextSymbol.length();
            return nextSymbol;
        }
        else
        {
            //en caso de no encontrarse el simbolo no es reconocido
            mensaje="El simbolo ingresado en la cadena ";
            mensaje+=cadena;
            mensaje+=" no es reconocido por la gramatica: ";
            mensaje+=nextSymbol;
            errores.push_back(mensaje);
         longitudTopeCadena = 0;
            flag_suknown = 1;
            nextSymbol = "-1";
            return nextSymbol;
        }
    }
}

/**
 * @brief La coincidencia se forma con los datos del tope de pila y tope de cadena
 * 
 * @param cadena de la cual se obtendra el tope de cadena
 */
void AnalizadorS::calcCoincidencia(string &cadena, unordered_map<string, int> &tablaSimbolos)
{
    coincidencia.first = pila.top();
    coincidencia.second = primerSimbolo(cadena,tablaSimbolos);
}

/**
 * @brief Obtiene la produccion indicada por la coincidencia y la ingresa a la pila en orden inverso.
 * 
 */
void AnalizadorS::obtenerAccion(unordered_map<string, unordered_map<string, string>> &TablaM,unordered_map<string, int> &tablaSimbolos)
{
    stack<string> reverse;//pila auxiliar para invertir la cadena de produccion
    string simbolo;
    accion = TablaM[coincidencia.first][coincidencia.second]; //se busca la produccion

    //si la produccion es epsilon solo se saca el ultimo elemento de la pila
    if (accion.compare("Ɛ") == 0)
    {
        pila.pop();
        accion = "";
    }
    else
    {
        //si la produccion no es epsilon, y si exiSte una produccion
        if (!accion.empty())
        {
            //hasta que la produccion se haya ingresado completa a la pila
            while (!accion.empty())
            {
                //se obtiene el primer simbolo de la cadena
                simbolo = primerSimbolo(accion,tablaSimbolos);
                //se guarda en la pila auxiliar
                reverse.push(simbolo);
                //se elimina el simbolo de la cadena
                accion.erase(0, longitudTopeCadena);
            }
            pila.pop();//se elimina el no terminal a sustituir de la pila
            //hasta que la pila auciliar este vacia
            while (!reverse.empty())
            {
                //se obtiene el tope de la pila auxiliar y se ingresa a la pila si no es epsilon, tambien se saca el tope de la pila
                simbolo = reverse.top();
                reverse.pop();
                if (simbolo.compare("Ɛ") != 0) //si no es epsilon se agrega a la pila
                    pila.push(simbolo);
            }
        }
        else
        {
            veredicto = "Cadena no aceptada por produccion inexistente para la coincidencia ";
            veredicto += coincidencia.first + "," + coincidencia.second;
            errores.push_back(veredicto);
        }
    }
}

/**
 * @brief Indica si la cadena de entrada es aceptada por la gramatica
 * 
 * @return string 
 */
string AnalizadorS::evaluaCadena(unordered_map<string, unordered_map<string, string>> &TablaM,unordered_map<string, int> &tablaSimbolos)
{
    string accion;
    string temp;
    string mensaje="";
    input.append("$");
    /*mensaje+=input;
    mensaje+="Cadena no aceptada porque se esta evaluando aun";
    errores.push_back(mensaje);*/

    // si el tope de pila o la entrada son $, ya no entrara
    while (pila.top().compare("$") != 0 || input.compare("$") != 0)
    {
        calcCoincidencia(input,tablaSimbolos);

        /*Si ambos datos de la coincidencia son iguales, no son el fin de cadena y son terminales*/
        if (coincidencia.first == coincidencia.second && coincidencia.first.compare("$") != 0 && tablaSimbolos[coincidencia.first] == 1)
        {
            // se hace pop a la pila y pop front a la cadena para eliminar el terminal identificado
            pila.pop();
            input.erase(0, longitudTopeCadena);
        }
        else
        {
            //Si no existe una produccion para la conincidencia
            if (!TablaM.count(coincidencia.first) || !TablaM[coincidencia.first].count(coincidencia.second))
            {
                veredicto = "Cadena no aceptada, no existe una produccion para la coincidencia: ";
                veredicto += coincidencia.first + "," + coincidencia.second;
                errores.push_back(veredicto);
                break;
            }
        }
        //si un simbolo ingresado no es reconocido la cadena no se acepta
        if (flag_suknown == 1)
        {
            veredicto = "Cadena no aceptada";
            break;
        }
        /* Si los datos de la coincidencia son diferentes y ambos son reconocidos por la gramatica*/
        if (coincidencia.first != coincidencia.second && tablaSimbolos.find(coincidencia.first) != tablaSimbolos.end() && tablaSimbolos.find(coincidencia.second) != tablaSimbolos.end())
        {
            obtenerAccion(TablaM,tablaSimbolos);
        }

        /* Si la coincidencia es $,$ la cadena es aceptada*/
    }
    if (pila.top().compare("$") == 0 && input.compare("$") == 0)
    {
        return veredicto;
    }
}

void AnalizadorS::analizadorDescendente(){
    string aux;
    cin>>input;
    if(input=="10"){
        keywordsUsed.push_back("iniciar");
        //Declaracion de variables
        cin>>input;
        if(input=="11"){
            keywordsUsed.push_back("inideclaraciones");
            //cin>>input;
            while(cin>>input&&input!="12") {
                for (int i = 0; i < 2; ++i) {
                    cin >> aux;
                    if(aux=="12"){
                        erroresDecVar.push_back("Error en la declaracion de variables");
                        break;
                    }
                    input += aux;
                }
                while (!pila.empty())
                    pila.pop();
                pila.push("$");
                pila.push("D");
                evaluaCadena(TablaMDecVar,tablaSimbolosDecVar);
                //cout << "\n Veredicto=" << veredicto << endl;
            }
            if(input=="12")
                keywordsUsed.push_back("findeclaraciones");
            if(erroresDecVar.empty())
                erroresDecVar.push_back("Analizador sintactico dice: No hay errores encontrados en la seccion de declaracion de variables");
        }
        //Asignaciones
        cin>>input;
        if(input=="13"){
            keywordsUsed.push_back("iniasignaciones");
            while(cin>>input&&input!="14") {
                for (int i = 0; i < 3; ++i) {
                    cin >> aux;
                    if(aux=="14"){
                        erroresAsignaciones.push_back("Error en la asignacion de variables");
                        break;
                    }
                    input += aux;
                }
                while (!pila.empty())
                    pila.pop();
                pila.push("$");
                pila.push("A");
                evaluaCadena(TablaMAsignaciones,tablaSimbolosAsignaciones);
            }
            if(input=="14")
            keywordsUsed.push_back("finasignaciones");
            if(erroresAsignaciones.empty())
                erroresAsignaciones.push_back("Analizador sintactico dice: No hay errores encontrados en Asignaciones");
        }
        //Definicion de funciones
        cin>>input;
        if(input=="15"){
            keywordsUsed.push_back("inideffunciones");
            while(cin>>input&&input!="16") {
                for (int i = 0; i < 15; ++i) {
                    cin >> aux;
                    if(aux=="16"){
                        erroresDefFunciones.push_back("Error en la definicion de funciones");
                        break;
                    }
                    input += aux;
                }
                while (!pila.empty())
                    pila.pop();
                pila.push("$");
                pila.push("F");
                evaluaCadena(TablaMDefFunciones,tablaSimbolosDefFunciones);
            }
            if(input=="16")
                keywordsUsed.push_back("findeffunciones");
            if(erroresDefFunciones.empty())
                erroresDefFunciones.push_back("Analizador sintactico dice: No hay errores encontrados en Definicion de funciones");
        }
        //inimain
        cin>>input;
        if(input.compare("17")==0){
            keywordsUsed.push_back("inimain");
            cin>>input;
            if(input.compare("20")==0){
                keywordsUsed.push_back("iniexpresiones");
            while(cin>>input&&input!="21") {
                //aqui se vuelve finito cuando no le ponen ;
                for (int i = 0; i < 7; ++i)
                 {
                    cin >> aux;
                    if(aux=="21"){
                        erroresMain.push_back("Error en la seccion de expresiones");
                        break;
                    }
                    input += aux;
                }
                while (!pila.empty())
                    pila.pop();
                pila.push("$");
                pila.push("U");
                evaluaCadena(TablaMExpresiones,tablaSimbolosExpresiones);
            }
            if(input=="21")
                keywordsUsed.push_back("finexpresiones");
            if(erroresMain.empty())
                erroresMain.push_back("Analizador sintactico dice: No hay errores encontrados en la seccion de expresiones");
            }
        }
        //Ini usar funciones
            cin>>input;
            if(input.compare("22")==0){
                keywordsUsed.push_back("inifunciones");
                while(cin>>input&&input!="23") {
                    //aqui se vuelve finito cuando no le ponen ;
                    for (int i = 0; i < 8; ++i)
                    {
                        cin >> aux;
                        if(aux=="23"){
                            erroresMain.push_back("Error en la seccion de expresiones");
                            break;
                        }
                        input += aux;
                    }
                    while (!pila.empty())
                        pila.pop();
                    pila.push("$");
                    pila.push("N");
                    evaluaCadena(TablaMUsaFunciones,tablaSimbolosUsaFunciones);
                    //cout << "\n Veredicto=" << veredicto << endl;
                }
                if(input=="23")
                    keywordsUsed.push_back("finfunciones");
                if(erroresMain.empty())
                    erroresMain.push_back("Analizador sintactico dice: No hay errores encontrados en la seccion de uso de funciones");
            }
        cin>>input;
        if(input.compare("18")==0){
            keywordsUsed.push_back("finmain");
        }
        cin>>input;
        if(input=="19"){
            keywordsUsed.push_back("terminar");
            cout<<("Analisis sintactico terminado")<<endl;
        }
    }
    else{
       errores.push_back("Falta palabra reservada Iniciar");
    }
}


/*

    imprimir la pila
    while (!pila.empty())
    {
        cout << endl
             << pila.top();
        pila.pop();
    }*/