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

Analizador::Analizador()
{

    pair<char,string> inic = make_pair('0',"0");
    arbolAnalizador.agregarRaiz(inic);

}

Analizador::~Analizador()
{
    //dtor
}
//"public class Clase{ int x; char c; void metodo(){ Syso;  while(){ Syso;}}}";
/**
C= clase
A= atributo
M= metodo
B= ciclo
I= instruccionNormal
L= llamadoAMetodo

*/

void Analizador::analizarCodigo(const char* entrada) {
    Nodo * clase=0;
    Nodo * metodo=0;
    Nodo * ciclo=0;
    char actual = '0';

    string hilera = entrada;
    cout<<hilera<<endl;
    string palabraClave ="class";
    string instr="";
    int contadorLlaves=0;
    int tamHilera= hilera.size();
    char caracter = hilera[0];

    for(int i=0; i< tamHilera; i++) {
        caracter = hilera[i];
        //cout<<"AAAH:"<<caracter<<endl;
        switch(caracter) {
        case 'c':
            if(i+6 <tamHilera ) {
                {
                    string subHilera;
                    for(int j=0; j<5; j++) {
                        subHilera+=hilera[i+j];
                    }
                    if(subHilera.compare(palabraClave)==0 && actual=='0') {
                        cout<<"*Clase"<<endl;
                        instr= conseguirHileraClase(hilera,i);
                        pair<char,string> dato = make_pair(CLASE, instr);
                        clase= agregarClase_Atributo(dato);
                        actual=CLASE;
                    }
                }
            }
            break;
        case ')':
        {
            if(actual==CLASE) {
                cout<<"*Metodo"<<endl;
                instr= conseguirHileraMetodo(hilera,i);
                pair<char,string> dato = make_pair(METODO, instr);
                metodo = arbolAnalizador.agregarDato(clase,dato);
                actual=METODO;
            }
            else {
                if(actual==METODO||actual==CICLO) {
                    if(!(hilera[i+1]=='{')) {
                        cout<<"*Ciclo"<<endl;
                        instr= conseguirHileraCiclo(hilera,i);
                        pair<char,string> dato = make_pair(CICLO, instr);
                        ciclo=arbolAnalizador.agregarDato(metodo,dato);
                        actual=CICLO;
                    }
                }
            }
        }
        break;
        case';':
        {
            if(actual==CLASE) {
                cout<<"*Atributo"<<endl;
                instr= conseguirHileraAtributo(hilera,i);
                pair<char,string> dato = make_pair(ATRIBUTO, instr);
                arbolAnalizador.agregarDato(clase, dato);
            }
            else {
                if(hilera[i-1]==')') {
                    cout<<"*LLamadoMetodo"<<endl;
                    instr= conseguirHileraLinea_Llamado(hilera,i);
                    pair<char,string> dato = make_pair(LLAMADO_METODO, instr);
                    if(actual==CICLO) {
                        arbolAnalizador.agregarDato(ciclo,dato);
                    }
                    else {
                        if(actual==METODO) {
                            arbolAnalizador.agregarDato(metodo,dato);
                        }
                    }
                }
                else {
                    cout<<"*Instruccion"<<endl;
                    instr= conseguirHileraLinea_Llamado(hilera,i);
                    pair<char,string> dato = make_pair(INSTRUCCION, instr);
                    if(actual==CICLO) {
                        arbolAnalizador.agregarDato(ciclo,dato);

                    }
                    else {
                        if(actual==METODO) {
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
            cout<<"CONTA:"<<contadorLlaves<<endl;
            actual=actualizarActual(actual,contadorLlaves);

        }
        break;
        case '}':
        {
            contadorLlaves--;

            if(actual==CICLO) {
                if(ciclo!=0) {
                    ciclo= arbolAnalizador.padre(ciclo,ciclo->dato);//NECESITO QUE DEVUELVA EL PAPI
                }
                else {
                    cout<<"ciclo 0"<<endl;
                }
            }
            actual=actualizarActual(actual,contadorLlaves);

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
            actual= '0';
        }
        break;
        case 1:
        {
            actual=CLASE;
        }
        break;
        case 2:
        {
            actual=METODO;
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
            actual=CLASE;
        }
        break;
        case 2:
        {
            actual=METODO;
        }
        break;
        case 3:
        {
            actual=CICLO;
        }
        break;
        }
    }
    break;
    case CICLO:
    {
        if(contadorLlaves==2) {
            actual= METODO;
        }
    }
    break;
    default:
        break;
    }
    return actual;
}
string Analizador::conseguirHileraClase(string hilera,int indice) {
    int contadorLlaves=0;
    string respuesta= "";
    int tamH= hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!='{' && contadorLlaves==0) {
            respuesta+=hilera[i];
        }
        else {
            if(indice<i) {
                i= hilera.size();
            }
        }
        if(hilera[i]=='{') {
            contadorLlaves++;
        }
        if(hilera[i]=='}') {
            contadorLlaves--;
            respuesta="";
        }
    }
    return respuesta;
}

string Analizador::conseguirHileraMetodo(string hilera,int indice) {
    string respuesta = "";
    int contadorLlaves=0;
    int tamH= hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!='{' && contadorLlaves==1) {
            respuesta+=hilera[i];
        }
        else {
            if(indice<i) {
                i= hilera.size();
            }
        }
        if(hilera[i]=='{') {
            if(contadorLlaves==0) {
                respuesta="";
            }
            contadorLlaves++;
        }
        if(hilera[i]=='}') {
            contadorLlaves--;
            respuesta="";
        }
        if(hilera[i]==';') {
            respuesta="";
        }
    }
    return respuesta;
}
string Analizador::conseguirHileraCiclo(string hilera, int indice) {
    cout<<indice<<endl;
    cout<<hilera[indice]<<endl;
    string respuesta = "";
    int contadorLlaves=0;
    int tamH= hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!='{' && contadorLlaves==2) {
            respuesta+=hilera[i];
        }
        if(indice<=i) {
            i= hilera.size();
        }
        if(hilera[i]=='{') {
            if(contadorLlaves==0) {
                respuesta="";
            }
            contadorLlaves++;
        }
        if(hilera[i]=='}') {
            contadorLlaves--;
            respuesta="";
        }
        if(hilera[i]==';') {
            respuesta="";
        }
    }
    return respuesta;
}
string Analizador::conseguirHileraAtributo(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves=0;
    int tamH= hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!=';' && contadorLlaves==1) {
            respuesta+=hilera[i];
        }
        if(indice<=i) {
            i= hilera.size();
        }
        if(hilera[i]=='{') {
            if(contadorLlaves==0) {
                respuesta="";
            }
            contadorLlaves++;
        }
        if(hilera[i]=='}') {
            contadorLlaves--;
            respuesta="";
        }
        if(hilera[i]==';') {
            respuesta="";
        }
    }
    return respuesta;
}
/**NO ESTA TERMINADO*/
string Analizador::conseguirHileraLinea_Llamado(string hilera, int indice) {
    string respuesta = "";
    int contadorLlaves=0;
    int tamH= hilera.size();
    for(int i=0; i<tamH; i++) {
        if(hilera[i]!=';' && contadorLlaves>=2) {
            respuesta+=hilera[i];
        }
        if(indice<=i) {
            i= hilera.size();
        }

        if(hilera[i]=='{') {
            respuesta="";
            contadorLlaves++;
        }
        if(hilera[i]=='}') {
            contadorLlaves--;
            respuesta="";
        }
        if(hilera[i]==';') {
            respuesta="";
        }
    }
    return respuesta;
}

Nodo * Analizador::agregarClase_Atributo(pair<char,string> dato) {
    //cout<<actual<<", "<<lineaActual<<endl;
    Nodo * n=0;
    Nodo* raiz=arbolAnalizador.raiz;
    n = arbolAnalizador.agregarDato((raiz),dato);
    return n;
}

string Analizador::generarAnalisis(){
    string analisis = "";
    
    analisis += "Análisis del código:\n";
    string str;
    
    str = analizarProfundidadCodigo();
    analisis += str;
    
    analisis += "\nAnálisis por clases:\n";
    
    Nodo* raiz = arbolAnalizador.obtenerRaiz();
    vector<Nodo*>::iterator it = raiz->hijos.begin();
    vector<Nodo*>::iterator itFin = raiz->hijos.end();
    
    for(; it!=itFin; it++) {
        str = "Clase " + (*it)->obtenerNombreClase() +":\n"; 
        analisis += str;
        str = analizarAtributosMetodos(*it);
        analisis += str;
        
        str = analizarMaximoAnidamiento(*it);
        analisis += str;
        
        analisis += "\n";
    }
    
    return analisis;
}

string Analizador::analizarAtributosMetodos(Nodo* n){
    string s = "";
    int atributos, metodos;
    atributos = arbolAnalizador.contarNodosPorId(n, 'A');
    metodos = arbolAnalizador.contarNodosPorId(n, 'M');   
    if(atributos > metodos){
        s = "Esta clase posee mas atributos que métodos, posiblemente sea una clase contenedora.\n";    
    }else if(atributos == metodos){
        s = "Esta clase posee igual número de métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";  
    }else{
        s = "Esta clase posee mas métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";  
    }
    return s;
}

string Analizador::analizarProfundidadCodigo(){
    return "Profundidad del código (altura del arbol): " + NumberToString(arbolAnalizador.altura()) + string("\n");
}

string Analizador::analizarMaximoAnidamiento(Nodo* n){
    pair<int, int> anch = arbolAnalizador.anchuraMaximaNodo(n);
    return "Nivel de máximo anidamiento: " + NumberToString(anch.first) + " con un ancho de " + NumberToString(anch.second) + string("\n");     
}

ArbolN Analizador::obtenerArbol(){
    return arbolAnalizador;
}
