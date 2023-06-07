#include "AnalizadorS.h"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    AnalizadorS analizador;
    string VeredictoFinal;


    //Tablas de Declaracion de variables
    analizador.TablaMDecVar["D"]["24"] = "dD'";
    analizador.TablaMDecVar["d"]["24"] = "243045";
    analizador.TablaMDecVar["D'"]["24"] = "D";
    analizador.TablaMDecVar["D'"]["$"] = "Ɛ";

    analizador.tablaSimbolosDecVar["D"] = 2;
    analizador.tablaSimbolosDecVar["D'"] = 0;
    analizador.tablaSimbolosDecVar["d"] = 0;
    analizador.tablaSimbolosDecVar["$"] = 3;
    analizador.tablaSimbolosDecVar["24"] = 1;
    analizador.tablaSimbolosDecVar["30"] = 1;
    analizador.tablaSimbolosDecVar["45"] = 1;
    //Tablas de Asignaciones
    analizador.TablaMAsignaciones["A"]["30"] = "aA'";
    analizador.TablaMAsignaciones["A'"]["30"] = "A";
    analizador.TablaMAsignaciones["a"]["30"] = "30465045";
    analizador.TablaMAsignaciones["A'"]["$"] = "Ɛ";

    analizador.tablaSimbolosAsignaciones["A"] = 2;
    analizador.tablaSimbolosAsignaciones["A'"] = 0;
    analizador.tablaSimbolosAsignaciones["a"] = 0;
    analizador.tablaSimbolosAsignaciones["$"] = 3;
    analizador.tablaSimbolosAsignaciones["30"] = 1;
    analizador.tablaSimbolosAsignaciones["46"] = 1;
    analizador.tablaSimbolosAsignaciones["50"] = 1;
    analizador.tablaSimbolosAsignaciones["45"] = 1;
    //Tablas de Definicion de funciones
    analizador.TablaMDefFunciones["F"]["24"] = "fF'";
    analizador.TablaMDefFunciones["F'"]["24"] = "F";
    analizador.TablaMDefFunciones["f"]["24"] = "24304024304424304142313060304543";
    analizador.TablaMDefFunciones["F'"]["$"] = "Ɛ";

    analizador.tablaSimbolosDefFunciones["F"] = 2;
    analizador.tablaSimbolosDefFunciones["F'"] = 0;
    analizador.tablaSimbolosDefFunciones["f"] = 0;
    analizador.tablaSimbolosDefFunciones["$"] = 3;
    analizador.tablaSimbolosDefFunciones["24"] = 1;
    analizador.tablaSimbolosDefFunciones["30"] = 1;
    analizador.tablaSimbolosDefFunciones["40"] = 1;
    analizador.tablaSimbolosDefFunciones["24"] = 1;
    analizador.tablaSimbolosDefFunciones["44"] = 1;
    analizador.tablaSimbolosDefFunciones["42"] = 1;
    analizador.tablaSimbolosDefFunciones["31"] = 1;
    analizador.tablaSimbolosDefFunciones["60"] = 1;
    analizador.tablaSimbolosDefFunciones["41"] = 1;
    analizador.tablaSimbolosDefFunciones["45"] = 1;
    analizador.tablaSimbolosDefFunciones["43"] = 1;
    //Tablas de Expresiones con jerarquia de operaciones
    analizador.TablaMExpresiones["U"]["30"] = "uU'";
    analizador.TablaMExpresiones["U'"]["60"] = "U";
    analizador.TablaMExpresiones["U'"]["$"] = "Ɛ";
    analizador.TablaMExpresiones["u"]["30"] = "3046E45";
    analizador.TablaMExpresiones["E"]["40"] = "TE'";
    analizador.TablaMExpresiones["E"]["50"] = "TE'";
    analizador.TablaMExpresiones["E'"]["60"] = "60TE'";
    analizador.TablaMExpresiones["E'"]["41"] = "Ɛ";
    analizador.TablaMExpresiones["E'"]["45"] = "Ɛ";
    analizador.TablaMExpresiones["T"]["40"] = "FT'";
    analizador.TablaMExpresiones["T"]["50"] = "FT'";
    analizador.TablaMExpresiones["T'"]["60"] = "Ɛ";
    analizador.TablaMExpresiones["T'"]["61"] = "61FT'";
    analizador.TablaMExpresiones["T'"]["41"] = "Ɛ";
    analizador.TablaMExpresiones["T'"]["45"] = "Ɛ";
    analizador.TablaMExpresiones["F"]["40"] = "40E41";
    analizador.TablaMExpresiones["F"]["50"] = "50";

    analizador.tablaSimbolosExpresiones["U"] = 2;
    analizador.tablaSimbolosExpresiones["U'"] = 0;
    analizador.tablaSimbolosExpresiones["u"] = 0;
    analizador.tablaSimbolosExpresiones["E"] = 0;
    analizador.tablaSimbolosExpresiones["E'"] = 0;
    analizador.tablaSimbolosExpresiones["T"] = 0;
    analizador.tablaSimbolosExpresiones["T'"] = 0;
    analizador.tablaSimbolosExpresiones["F"] = 0;
    analizador.tablaSimbolosExpresiones["30"] = 1;
    analizador.tablaSimbolosExpresiones["46"] = 1;
    analizador.tablaSimbolosExpresiones["45"] = 1;
    analizador.tablaSimbolosExpresiones["60"] = 1;
    analizador.tablaSimbolosExpresiones["61"] = 1;
    analizador.tablaSimbolosExpresiones["50"] = 1;
    analizador.tablaSimbolosExpresiones["40"] = 1;
    analizador.tablaSimbolosExpresiones["41"] = 1;
    analizador.tablaSimbolosExpresiones["$"] = 3;
    //Tablas de usar funciones
    analizador.TablaMUsaFunciones["N"]["30"] = "nN'";
    analizador.TablaMUsaFunciones["N'"]["30"] = "N";
    analizador.TablaMUsaFunciones["n"]["30"] = "304630403044304145";
    analizador.TablaMUsaFunciones["N'"]["$"] = "Ɛ";

    analizador.tablaSimbolosUsaFunciones["N"] = 2;
    analizador.tablaSimbolosUsaFunciones["N'"] = 0;
    analizador.tablaSimbolosUsaFunciones["n"] = 0;
    analizador.tablaSimbolosUsaFunciones["$"] = 3;
    analizador.tablaSimbolosUsaFunciones["30"] = 1;
    analizador.tablaSimbolosUsaFunciones["46"] = 1;
    analizador.tablaSimbolosUsaFunciones["40"] = 1;
    analizador.tablaSimbolosUsaFunciones["44"] = 1;
    analizador.tablaSimbolosUsaFunciones["41"] = 1;
    analizador.tablaSimbolosUsaFunciones["45"] = 1;



    analizador.analizadorDescendente();
    cout<<"Resumen de errores:"<<endl;
    for (auto error: analizador.errores) {
    cout << error<<endl<<endl;
    }
    for (auto error: analizador.erroresDecVar) {
        cout << error<<endl<<endl;
    }
    for (auto error: analizador.erroresAsignaciones) {
        cout << error<<endl<<endl;
    }
    for (auto error: analizador.erroresDefFunciones) {
        cout << error<<endl<<endl;
    }
    for (auto error: analizador.erroresMain) {
        cout << error<<endl<<endl;
    }

    if(!analizador.keywordsUsed.empty()){

    if(analizador.secciones.size()==analizador.keywordsUsed.size()&&analizador.secciones!=analizador.keywordsUsed){
        for (int i = 0; i < 14; ++i) {
            if(analizador.secciones.at(i)!=analizador.keywordsUsed.at(i)){
                cout<<"La ultima palabra reservada en el orden correcto es: "<<analizador.keywordsUsed.at(i-1);
            break;
            }
        }
    }

    if(analizador.secciones.size()>analizador.keywordsUsed.size()){
        short int flag=0;
        for (int i = 0; i < analizador.keywordsUsed.size(); ++i) {
            if(analizador.secciones.at(i)!=analizador.keywordsUsed.at(i)){
                cout<<"La ultima palabra reservada en el orden correcto es: "<<analizador.keywordsUsed.at(i-1);
                flag=1;
            break;
            }
        }
            if(flag==0){
                cout<<"La ultima palabra reservada en el orden correcto es: "<<analizador.keywordsUsed.at(analizador.keywordsUsed.size()-1);
            }
    }
    if(analizador.secciones.size()<analizador.keywordsUsed.size()){
        short int flag=0;
        for (int i = 0; i < analizador.secciones.size(); ++i) {
            if(analizador.secciones.at(i)!=analizador.keywordsUsed.at(i)){
                cout<<"La ultima palabra reservada en el orden correcto es: "<<analizador.keywordsUsed.at(i-1);
                flag=1;
                break;
            }
        }
        if(flag==0){
            cout<<"La ultima palabra reservada en el orden correcto es: "<<analizador.keywordsUsed.at(analizador.secciones.size()-1);
        }
    }
}

    return 0;
}