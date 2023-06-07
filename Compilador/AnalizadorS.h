#ifndef ANALIZADORS_H
#define ANALIZADORS_H

#include <bits/stdc++.h>
using namespace std;

class AnalizadorS
{
public:
  // GLOBALES
  int flag_suknown = 1;
  int longitudTopeCadena = -1;
  string veredicto = "";
  stack<string> pila;
  pair<string, string> coincidencia;
  string input;
  string accion;
  //Globales para el analizador descendente recurisvo
  string palabra;
  string token;
    unordered_map<string, unordered_map<string, string>> TablaMDecVar;
    unordered_map<string, unordered_map<string, string>> TablaMAsignaciones;
    unordered_map<string, unordered_map<string, string>> TablaMDefFunciones;
    unordered_map<string, unordered_map<string, string>> TablaMExpresiones;
    unordered_map<string, unordered_map<string, string>> TablaMUsaFunciones;
    unordered_map<string, int> tablaSimbolosDecVar;
    unordered_map<string, int> tablaSimbolosAsignaciones;
    unordered_map<string, int> tablaSimbolosDefFunciones;
    unordered_map<string, int> tablaSimbolosExpresiones;
    unordered_map<string, int> tablaSimbolosUsaFunciones;
    vector<string> errores;
    vector<string> erroresDecVar;
    vector<string> erroresAsignaciones;
    vector<string> erroresDefFunciones;
    vector<string> erroresMain;
    int counter;
    vector<string> secciones{"iniciar","inideclaraciones","findeclaraciones","iniasignaciones","finasignaciones","inideffunciones","findeffunciones","inimain","iniexpresiones","finexpresiones","inifunciones","finfunciones","finmain","terminar"};
    vector<string> keywordsUsed;

 
  // FUNCIONES
  string primerSimbolo(string &cadena, unordered_map<string, int> &tablaSimbolos);
  void calcCoincidencia(string &cadena,unordered_map<string, int> &tablaSimbolos);
  string evaluaCadena(unordered_map<string, unordered_map<string, string>> &TablaM,unordered_map<string, int> &tablaSimbolos);
  void obtenerAccion(unordered_map<string, unordered_map<string, string>> &TablaM,unordered_map<string, int> &tablaSimbolos);
  void analizadorDescendente();
};
#endif