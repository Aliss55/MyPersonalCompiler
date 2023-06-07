# Anexo de implementacion
Las tablas de simbolos tendrán los valores de claves:
- 0 No terminales
- 1 Terminales
- 2 Es el simbolo inicial
- 3 Simbolo de fin de cadena
# Estructura general 
```html
Programa -> <iniciar> <declararVariables> <asignaciones> <definirFunciones> <main> <terminar>
```

# Definiciones de la gramatica

```html
<iniciar> -> _iniciar
<terminar> -> _terminar
```
# Declarar variables
```html
<declararVariables> -> <declaracion> D'
D' -> <declararVariables> | epsilon
    <declaracion> ->_int identificador ; 
```
##### Declarar variables LL(1)
Factorizando se obtiene:
```html
D -> d D'
D'-> D|epsilon
d -> 20 30 45
```
###### Tabla M
|No terminal|20|30|45|$|
|-----------|--|--|--|--|
|D|D -> d D'||||
|d|d -> 20 30 45||||
|D'|D' -> D|||D' -> epsilon|
# Asignaciones
```html
<asignaciones> -> <asignacion><asignaciones>|<asignacion>
<asignacion>-><nombreVariable>=<numero>;
```
##### Asignaciones LL(1)
Factorizando se obtiene:
```html
A -> a A'
A'-> A|epsilon
a -> 30 46 50 45
```
###### Tabla M
|No terminal|30|46|50|45|$|
|-----------|--|--|--|--|-|
|A|A -> a A'|||||
|A'|A' -> A||||A' -> epsilon||
|a|a -> 30 46 50 45|||||
# Definir funciones
Para funciones con operadores + -
```html
<definirFunciones> -> <definicion><definirFunciones>|<definicion>
<definicion>-><tipoDato><nombreVariable>(<tipoDato><nombreVariable>,<tipoDato><nombreVariable>){_return <nombreVariable><operador1><nombreVariable>;}
```
##### definicir funciones + - LL(1)
Factorizando se obtiene:
```html
F -> f F'
F'-> F|epsilon
f -> 24 30 40 24 30 44 24 30 41 42 31 30 60 30 45 43
```
###### Tabla M
|No terminal|24|30|40|24|$|
|-----------|--|--|--|--|-|
|F|F -> f F'|||||
|F'|F' -> F||||F' -> epsilon||
|f|f -> 24 30 40 24 30 44 24 30 41 42 31 30 60 30 45 43|||||
Para funciones con operador *
```html
<definirFunciones> -> <definicion><definirFunciones>|<definicion>
<definicion>-><tipoDato><nombreVariable>(<tipoDato><nombreVariable>,<tipoDato><nombreVariable>){_return <nombreVariable><operador2><nombreVariable>;}
```
##### definir funciones * LL(1)
Factorizando se obtiene:
```html
F -> f F'
F'-> F|epsilon
f -> 24 30 40 24 30 44 24 30 42 31 30 61 30 45 43
```
###### Tabla M
|No terminal|24|30|40|24|$|
|-----------|--|--|--|--|-|
|F|F -> f F'|||||
|F'|F' -> F||||F' -> epsilon||
|f|f -> 24 30 40 24 30 44 24 30 42 31 30 61 30 45 43|||||
# Expresiones con jerarquia de operaciones
Para los operadores +-*

##### gramatica de jerarquia de operaciones  LL(1)

```html
U -> u U'
U' -> U | epsilon
u -> 30 46 E 45
E -> T E'
E' -> 60 T E' | epsilon
T -> F T'
T' -> 61 F T' | epsilon
F -> 50 | 40 E 41
```
###### Tabla M
|No terminal|60 + |61 * |40 (|41 )|50 numero |30 nombreVar |46 = |45|$|
|-----------|----|----|----|----|----|----|----|----|----|
|U||||||U -> u U'||||
|U'|U'->U||||||||U' -> epsilon|
|u||||||u->30 46 E4 5||||
|E|||E->TE'||E->TE'|||||
|E'|E'->60TE'|||E'->epsilon||||E'->epsilon||
|T|||T->FT'||T->FT'|||||
|T'|T'->epsilon|T'->61FT'||T'->epsilon||||T'->epsilon||
|F|||F->40E41||F->50|||||

# Usar funciones 
```html
<usaFunciones> -> <usaFuncion><usaFunciones>|<usaFuncion>
<usaFuncion>-><nombreVariable>=<nombreVariable>(<nombreVariable>,<nombreVariable>);
```
##### Usa funciones LL(1)
Factorizando se obtiene:
```html
N -> n N'
N'-> N|epsilon
n -> 30 46 30 40 30 44 30 41 45
```
###### Tabla M
|No terminal|30|46|40|44|41|45|$|
|-----------|--|--|--|--|-|--|--|
|N|N -> n N'|||||||
|N'|N' -> N||||||N' -> epsilon|
|n|n -> 30 46 30 40 30 44 30 41 45|||||||




