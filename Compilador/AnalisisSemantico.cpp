#include <bits/stdc++.h>
//librerias
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string identificador;
    int counter=0;
      fstream usadas;
    unordered_map<string, int> declaradas;

    //Recibe los identificadores de las variables declaradas
    while(cin>>identificador){
        declaradas.insert({identificador,1});
    }
    
  
        usadas.open("VariablesUsadas.txt", ios_base::in);
        if (usadas.is_open()) {
            string variableUsada;

            while (getline(usadas,variableUsada)) {
                if(declaradas.find(variableUsada)==declaradas.end())
                cout<<"La variable "<<variableUsada<<" no esta declarada"<<endl;
            }

            usadas.close();
            if (usadas.is_open())
                cout << "Stream could not close!" << endl;
        }
        cout<<"Analisis semantico terminado";
    
    return 0;
}