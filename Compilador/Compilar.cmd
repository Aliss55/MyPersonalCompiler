cls
del inputLexico.txt
del FlujoTokens.txt
del TokensValores.txt
del VariablesDeclaradas.txt
del VariablesUsadas.txt
copy inputLexicoOrg.txt inputLexico.txt
cls
g++ wordcounter.cpp  -o ejecutable
ejecutable < programa.txt >> inputLexico.txt
g++ appender.cpp -o ejecutable
ejecutable < programa.txt >> inputLexico.txt
g++ AnalizadorLexico.cpp -o ejecutable
ejecutable < inputLexico.txt
g++ AnalizadorS.cpp AnalizadorSmain.cpp -o ejecutable
ejecutable <TokensValores.txt
g++ AnalisisSemantico.cpp -o ejecutable 
ejecutable <VariablesDeclaradas.txt