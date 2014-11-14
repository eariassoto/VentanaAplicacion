#include "Analizador.h"
#include <sstream>

//tomado de http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
template <typename T>
string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}
//fin cita

Analizador::Analizador(){
    pair<char,string> inic = make_pair('0',"0");
    arbolAnalizador.agregarRaiz(inic);
}

Analizador::~Analizador(){
    //dtor
}

void Analizador::analizarCodigo(const char* entrada) {
    Nodo* clase = 0;
    Nodo* metodo = 0;
    Nodo* ciclo = 0;
    char actual = '0';

    string hilera = entrada;
    string palabraClave = "class";
    string instr = "";
    int contadorLlaves = 0;
    int tamHilera = hilera.size();
    char caracter = hilera[0];

    for(int i=0; i< tamHilera; i++) {
        caracter = hilera[i];
        switch(caracter) {
        case 'c':
            if(i+6 < tamHilera ) {
                {
                    string subHilera;
                    for(int j=0; j<5; j++) {
                        subHilera+=hilera[i+j];
                    }
                    if(subHilera.compare(palabraClave) == 0 && actual == '0') {
                        instr = conseguirHileraClase(hilera,i);
                        pair<char,string> dato = make_pair(CLASE, instr);
                        Nodo* raiz=arbolAnalizador.obtenerRaiz();
                        clase = arbolAnalizador.agregarDato(raiz,dato);
                        actual = CLASE;
                    }
                }
            }
            break;
        case ')':
        {
            if(actual == CLASE) {
                instr = conseguirHileraMetodo(hilera,i);
                pair<char,string> dato = make_pair(METODO, instr);
                metodo = arbolAnalizador.agregarDato(clase,dato);
                actual = METODO;
            }
            else {
                if(actual == METODO || actual == CICLO) {
                    if((hilera[i+1] == '{')) {
                        instr = conseguirHileraCiclo(hilera,i);
                        pair<char,string> dato = make_pair(CICLO, instr);
                        ciclo = arbolAnalizador.agregarDato(metodo,dato);
                        actual = CICLO;
                    }
                }
            }
        }
        break;
        case';':
        {
            if(actual==CLASE) {
                instr = conseguirHileraAtributo(hilera,i);
                pair<char,string> dato = make_pair(ATRIBUTO, instr);
                arbolAnalizador.agregarDato(clase, dato);
            }
            else {
                if(hilera[i-1]==')') {
                    instr = conseguirHileraLinea_Llamado(hilera,i);
                    pair<char,string> dato = make_pair(LLAMADO_METODO, instr);
                    if(actual == CICLO) {
                        arbolAnalizador.agregarDato(ciclo,dato);
                    }
                    else {
                        if(actual == METODO) {
                            arbolAnalizador.agregarDato(metodo,dato);
                        }
                    }
                }
                else {
                    instr = conseguirHileraLinea_Llamado(hilera, i);
                    pair<char,string> dato = make_pair(INSTRUCCION, instr);
                    if(actual == CICLO) {
                        arbolAnalizador.agregarDato(ciclo,dato);

                    }
                    else {
                        if(actual == METODO) {
                            arbolAnalizador.agregarDato(metodo,dato);
                        }
                    }
                }
            }
        }
        break;
        case '{':
        {
            contadorLlaves++;
            actual = actualizarActual(actual,contadorLlaves);

        }
        break;
        case '}':
        {
            contadorLlaves--;

            if(actual == CICLO) {
                if(ciclo != 0) {
                    ciclo = arbolAnalizador.padre(ciclo,ciclo->dato);
                }
            }
            actual = actualizarActual(actual, contadorLlaves);

        }
        break;
        default:
            break;
        }
    }
}
char Analizador::actualizarActual(char actual,int contadorLlaves) {
    switch (actual) {
    case CLASE:
    {
        switch(contadorLlaves) {
        case 0:
        {
            actual = '0';
        }
        break;
        case 1:
        {
            actual = CLASE;
        }
        break;
        case 2:
        {
            actual = METODO;
        }
        break;
        }
    }
    break;
    case METODO:
    {
        switch(contadorLlaves) {
        case 1:
        {
            actual = CLASE;
        }
        break;
        case 2:
        {
            actual = METODO;
        }
        break;
        case 3:
        {
            actual = CICLO;
        }
        break;
        }
    }
    break;
    case CICLO:
    {
        if(contadorLlaves == 2) {
            actual = METODO;
        }
    }
    break;
    default:
        break;
    }
    return actual;
}
string Analizador::conseguirHileraClase(string hilera,int indice) {
    int contadorLlaves = 0;
    string respuesta = "";
    int tamH = hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!='{' && contadorLlaves==0) {
            respuesta += hilera[i];
        }
        else {
            if(indice < i) {
                i = hilera.size();
            }
        }
        if(hilera[i] == '{') {
            contadorLlaves++;
        }
        if(hilera[i] == '}') {
            contadorLlaves--;
            respuesta = "";
        }
    }
    return respuesta;
}

string Analizador::conseguirHileraMetodo(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves = 0;
    int tamH = hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i] != '{' && contadorLlaves == 1) {
            respuesta += hilera[i];
        }
        else {
            if(indice < i) {
                i = hilera.size();
            }
        }
        if(hilera[i] == '{') {
            if(contadorLlaves == 0) {
                respuesta = "";
            }
            contadorLlaves++;
        }
        if(hilera[i] == '}') {
            contadorLlaves--;
            respuesta = "";
        }
        if(hilera[i] == ';') {
            respuesta = "";
        }
    }
    return respuesta;
}
string Analizador::conseguirHileraCiclo(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves = 0;
    int tamH = hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i] != '{' && contadorLlaves == 2) {
            respuesta += hilera[i];
        }
        if(indice <= i) {
            i = hilera.size();
        }
        if(hilera[i] == '{') {
            if(contadorLlaves == 0) {
                respuesta = "";
            }
            contadorLlaves++;
        }
        if(hilera[i] == '}') {
            contadorLlaves--;
            respuesta = "";
        }
        if(hilera[i] == ';') {
            respuesta = "";
        }
    }
    return respuesta;
}
string Analizador::conseguirHileraAtributo(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves=0;
    int tamH = hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i] != ';' && contadorLlaves == 1) {
            respuesta += hilera[i];
        }
        if(indice <= i) {
            i = hilera.size();
        }
        if(hilera[i] == '{') {
            if(contadorLlaves == 0) {
                respuesta = "";
            }
            contadorLlaves++;
        }
        if(hilera[i] == '}') {
            contadorLlaves--;
            respuesta = "";
        }
        if(hilera[i] == ';') {
            respuesta = "";
        }
    }
    return respuesta;
}

string Analizador::conseguirHileraLinea_Llamado(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves=0;
    int tamH = hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i] != ';' && contadorLlaves >= 2) {
            respuesta += hilera[i];
        }
        if(indice <= i) {
            i= hilera.size();
        }

        if(hilera[i] == '{') {
            respuesta = "";
            contadorLlaves++;
        }
        if(hilera[i] == '}') {
            contadorLlaves--;
            respuesta = "";
        }
        if(hilera[i] == ';') {
            respuesta = "";
        }
    }
    return respuesta;
}

string Analizador::generarAnalisis() {
    string analisis = "";

    analisis += "Análisis del código:\n";
    analisis += analizarProfundidadCodigo();

    analisis += "\nAnálisis por clases:\n";

    Nodo* raiz = arbolAnalizador.obtenerRaiz();
    vector<Nodo*>::iterator it = raiz->hijos.begin();
    vector<Nodo*>::iterator itFin = raiz->hijos.end();

    for(; it!=itFin; it++) {
        analisis += "Clase " + (*it)->obtenerNombreClase() +":\n";
        analisis += usoAtributosMetodos(*it);
        analisis += usoAtributosTotal(*it);
        analisis += analizarAtributosMetodos(*it);
        analisis += analizarMaximoAnidamiento(*it);
        analisis += analizarMetodosMorfosis(*it);
        analisis += frecuenciaUsoMetodos(*it);
        analisis += metodosConHerencia(*it);
        analisis += metodosRecursivos(*it);
        analisis += "\n";
    }

    return analisis;
}

string Analizador::analizarAtributosMetodos(Nodo* n) {
    string s = "";
    int atributos, metodos;
    atributos = arbolAnalizador.contarNodosPorId(n, 'A');
    metodos = arbolAnalizador.contarNodosPorId(n, 'M');
    if(atributos > metodos) {
        s = "* Esta clase posee mas atributos que métodos, posiblemente sea una clase contenedora.\n";
    } else if(atributos == metodos) {
        s = "* Esta clase posee igual número de métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";
    } else {
        s = "* Esta clase posee mas métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";
    }
    return s;
}

string Analizador::analizarProfundidadCodigo() {
    return "* Profundidad del código (altura del arbol): " + NumberToString(arbolAnalizador.altura()) + string("\n");
}

string Analizador::analizarMaximoAnidamiento(Nodo* n) {
    pair<int, int> anch = arbolAnalizador.anchuraMaximaNodo(n);
    return "* Nivel de máximo anidamiento: " + NumberToString(anch.first) + " con un ancho de " + NumberToString(anch.second) + string("\n");
}

ArbolN Analizador::obtenerArbol() {
    return arbolAnalizador;
}

string Analizador::analizarMetodosMorfosis(Nodo* n) {
    string respuesta = "";
    vector<Nodo*> vec;
    vector<Nodo*> hij = n->hijos;
    vector<Nodo*>::iterator it = hij.begin(), itFin = hij.end(), it2, itFin2;

    for(; it!=itFin; it++) {
        if((*it)->dato.first == 'M') {
            vec.push_back(*it);
        }
    }
    if(vec.size() < 2) {
        respuesta = "* Esta clase solo tiene un metodo y por lo tanto no se puede realizar el análisis morfológico de métodos.\n";
    } else {
        it    = vec.begin();
        itFin = vec.end();

        for(; it!=itFin; it++) {
            it2    = vec.begin();
            itFin2 = vec.end();

            for(; it2!=itFin2; it2++) {
                if(*it != *it2) {
                    respuesta += "* El método " + (*it)->obtenerNombreMetodo() + " y el método " + (*it2)->obtenerNombreMetodo() + " son iguales morfológicamente.\n";
                    vec.erase(it);
                }
            }
        }
    }
    return respuesta;
}

string Analizador::usoAtributosMetodos(Nodo* clase) {
    string respuesta="";

    int cantNodosMetodos=0;
    vector<Nodo*> hijos = clase->obtenerHijos();
    vector<Nodo *> metodos;
    int tamHijosClase = hijos.size();
    for(int i = 0; i < tamHijosClase; i++) {
        if(hijos[i]->dato.first == 'M') {
            metodos.push_back(hijos[i]);
        }
    }
    int tamMetodos = metodos.size();
    for(int i=0; i<tamMetodos; i++) {
        cantNodosMetodos += arbolAnalizador.contarNodosSA(metodos[i]);
    }
    cantNodosMetodos--;

    respuesta += "* Cantidad de nodos que usan métodos: " + NumberToString(cantNodosMetodos) + string("\n");

    int cantidadNodosUsanAtributos = nodosUsanAtributos(arbolAnalizador, clase);
    respuesta += "* Cantidad de nodos que usan atributos: " + NumberToString(cantidadNodosUsanAtributos) + string("\n");
    /*
        if(cantidadNodosUsanAtributos < cantNodosMetodos) {
            respuesta += "NO SE QUE DECIR1";
        }
        else {
            if(cantidadNodosUsanAtributos > cantNodosMetodos) {
                respuesta += "NO SE QUE DECIR2";
            }
            else {
                if(cantidadNodosUsanAtributos == cantNodosMetodos) {
                    respuesta += "NO SE QUE DECIR3";
                }
            }
        }*/
    return respuesta;

}
string Analizador::conseguirUltimaParte(string s) {
    string respuesta = "";
    int tam = s.size();
    for(int i=(tam-1); i>=0; i--) {
        if(s[i] == ' ') {
            i =- 1;
        }
        else {
            respuesta = s[i] + respuesta;
        }
    }
    return respuesta;
}

string Analizador::usoAtributosTotal(Nodo* clase) {
    string respuesta = "";

    int cantidadTotalNodos = arbolAnalizador.cantidadNodos(clase);
    respuesta += "* Cantidad total de nodos: " + NumberToString(cantidadTotalNodos-1) + "\n";
    /*
    int cantidadNodosUsanAtributos = nodosUsanAtributos(arbolAnalizador, clase);

     if(cantidadNodosUsanAtributos < cantidadTotalNodos) {
         respuesta += "NO SE QUE DECIR1.1";
     }
     else {
         if(cantidadNodosUsanAtributos > cantidadTotalNodos) {
             respuesta += "NO SE QUE DECIR2.1";
         }
         else {
             if(cantidadNodosUsanAtributos == cantidadTotalNodos) {
                 respuesta += "NO SE QUE DECIR3.1";
             }
         }
     }
    */
    return respuesta;
}

int Analizador::nodosUsanAtributos(ArbolN arbol, Nodo * clase) {
    int cantidadNodosUsanAtributos = 0;
    vector<Nodo*> hijos = clase->obtenerHijos();
    vector<Nodo*> metodos;
    vector<Nodo*> atributos;
    int tamHijosClase = hijos.size();
    
    for(int i =0; i<tamHijosClase; i++) {
        if(hijos[i]->dato.first == 'M') {
            metodos.push_back(hijos[i]);
        }
        else {
            if(hijos[i]->dato.first == 'A') {
                atributos.push_back(hijos[i]);
            }
        }
    }
    int tamMetodos = metodos.size();
    int tamAtributos = atributos.size();
    for(int i=0; i<tamAtributos; i++) {
        string lineaAtr = atributos[i]->dato.second;
        lineaAtr = conseguirUltimaParte(lineaAtr);
        
        for(int j=0; j<tamMetodos; j++) {
            cantidadNodosUsanAtributos+=arbol.cantidadNodosCon(metodos[j],lineaAtr);
        }
    }
    return cantidadNodosUsanAtributos;
}

string Analizador::frecuenciaUsoMetodos(Nodo* clase) {
    string respuesta = "* Análisis de llamados a métodos:\n";
    vector<Nodo*> hijos = clase->obtenerHijos();
    vector<Nodo*> metodos;
    vector<int> llamadosRespectivos;
    int tamHijosClase = hijos.size();

    for(int i =0; i<tamHijosClase; i++) {
        if(hijos[i]->dato.first == 'M') {
            metodos.push_back(hijos[i]);
        }
    }
    int tamMetodos = metodos.size();
    for(int i=0; i<tamMetodos; i++) {
        llamadosRespectivos.push_back(arbolAnalizador.contarNodosPorId(metodos[i], 'L'));
    }
    for(int i=0; i<tamMetodos; i++) {
        respuesta += "-> Llamados a métodos en " +  metodos[i]->obtenerNombreMetodo() + ": " + NumberToString(llamadosRespectivos[i]) + "\n";
    }

    return respuesta;
}

string Analizador::metodosRecursivos(Nodo* clase) {
    string respuesta = "* Análisis de recursividad en métodos:\n";
    vector<Nodo*> hijos = clase->obtenerHijos();
    vector<Nodo*> metodos;
    int tamHijosClase = hijos.size();
    
    for(int i =0; i<tamHijosClase; i++) {
        if(hijos[i]->dato.first=='M') {
            metodos.push_back(hijos[i]);
        }
    }
    
    int tamMetodos = metodos.size();
    string nombreMetodo = "";
    int cantidadLlamadosRecursicos;
    for(int i=0; i<tamMetodos; i++) {
        cantidadLlamadosRecursicos = 0;
        nombreMetodo = metodos[i]->obtenerNombreMetodoSinParentesis();
        vector<Nodo*> hijosMet= metodos[i]->hijos;
        int tamHijosMet = hijosMet.size();
        
        for(int j=0; j<tamHijosMet; j++) {
            cantidadLlamadosRecursicos += arbolAnalizador.cantidadNodosConString(hijosMet[j], nombreMetodo+"(");
        }
        if(cantidadLlamadosRecursicos > 0) {
            respuesta += "-> El método "+nombreMetodo+" es recursivo.\n";
        }
        else {
            if(cantidadLlamadosRecursicos == 0) {
                respuesta += "-> El método "+nombreMetodo+" NO es recursivo.\n";
            }
        }
    }
    return respuesta;
}

/**
Extra: saber si una clase hereda
*/
string Analizador::metodosConHerencia(Nodo* clase) {
    string respuesta = "* Análisis de herencia: ";
    string nombreClase = clase->obtenerNombreClase();
    if(nombreClase.find(":") != string::npos) {
        respuesta += "La clase hereda.\n";
    }
    else {
        respuesta += "La clase NO hereda.\n";
    }

    return respuesta;
}


