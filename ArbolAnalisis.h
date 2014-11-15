#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <list>
#include <string.h>
#include <sstream>

using namespace std;

typedef char               id;
typedef string             codigo;
typedef pair<char, string> idCodigo;

class Nodo {
    //friend class ArbolN;
   //friend class ArbolAnalisis;
    //friend class Controlador;
    //friend class Analizador;

public:

    Nodo(idCodigo d):dato(d), hijos() {
        padre = 0;
    }
    
    Nodo(idCodigo d, Nodo* np):dato(d), hijos() {
        padre = np;
    }
    
    ~Nodo() {
    }

    id obtenerId(){
        return dato.first;    
    }
    
    codigo obtenerCodigo(){
        return dato.second;
    }
    
    idCodigo obtenerDato(){
        return dato;
    }
    
    Nodo* obtenerPadre(){
        return padre;
    }
    
    string obtenerNombreClase() {
        string str(dato.second);
        
        myReplace(str, "public", "");
        myReplace(str, "private", "");
        myReplace(str, "static", "");
        myReplace(str, "class", "");
        str.erase(remove(str.begin(), str.end(), (char)13), str.end());
        str.erase(remove(str.begin(), str.end(), (char)10), str.end());
        str.erase(remove(str.begin(), str.end(), '\t'), str.end());
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    string obtenerNombreMetodo() {
        vector<string> spt = split(dato.second, '(');
        
        myReplace(spt[0], "public", "");
        myReplace(spt[0], "private", "");
        myReplace(spt[0], "static", "");

        myReplace(spt[0], "void", "");
        myReplace(spt[0], "short", "");
        myReplace(spt[0], "int", "");
        myReplace(spt[0], "float", "");
        myReplace(spt[0], "double", "");
        myReplace(spt[0], "long", "");
        myReplace(spt[0], "char", "");
        myReplace(spt[0], "bool", "");

        myReplace(spt[0], "string", ""); //std::string
        myReplace(spt[0], "std", "");
        myReplace(spt[0], "::", "");

        myReplace(spt[0], "unsigned", "");
        myReplace(spt[0], "signed", "");

        spt[0].erase(remove(spt[0].begin(), spt[0].end(), (char)13), spt[0].end());
        spt[0].erase(remove(spt[0].begin(), spt[0].end(), (char)10), spt[0].end());
        spt[0].erase(remove(spt[0].begin(), spt[0].end(), '\t'), spt[0].end());
        spt[0].erase(remove(spt[0].begin(), spt[0].end(), ' '), spt[0].end());

        return spt[0] + "(" + spt[1];
    }

    string obtenerNombreMetodoSinParentesis() {
        string r= obtenerNombreMetodo();
        string r1="";
        int tamR=r.size();
        for(int i=0; i<tamR; i++) {
            if(r[i]=='(') {
                i=tamR;
            }
            else {
                r1+=r[i];
            }
        }
        return r1;
    }
    
vector<Nodo*> hijos;

private:

    idCodigo dato;
    Nodo* padre;

// codigo tomado de http://stackoverflow.com/questions/236129/split-a-string-in-c
vector<string> &split(const string &s, char delim, vector<std::string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
// fin de cita

// codigo tomado de http://stackoverflow.com/questions/1494399/how-do-i-search-find-and-replace-in-a-standard-string
    void myReplace(std::string& str, const std::string& oldStr, const std::string& newStr) {
        size_t pos = 0;
        while((pos = str.find(oldStr, pos)) != std::string::npos) {
            str.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }
// fin cita
};

class ArbolN  {

    friend class Analizador;

public:
    ArbolN();
    ~ArbolN();
    ArbolN(bool, Nodo*);

    Nodo*          agregarRaiz(idCodigo);
    Nodo*          obtenerRaiz();
    
    Nodo*          agregarDato(Nodo*, idCodigo);
    void           modificarDato(idCodigo, idCodigo);
    Nodo*          buscar(idCodigo);
    
    Nodo*          padre(idCodigo);
    
    bool           vacio();
    bool           existe(idCodigo);
    
    int            cantidadNodos();
    int            cantidadNodos(Nodo*);

protected:
    
    Nodo* raiz;
    bool  usado;

    Nodo* buscar(Nodo*, idCodigo);
    Nodo* padre(Nodo*, idCodigo);
    
};

class ArbolAnalisis : public ArbolN  {

public:
    ArbolAnalisis();
    ~ArbolAnalisis();
    
    
    int            altura();
    pair<int, int> anchuraMaxima();
    pair<int, int> anchuraMaximaNodo(Nodo*);
    int            anchuraPromedio();
    
    ArbolN*        subArbol(Nodo*);
    vector<Nodo*>  descendientes(Nodo*);
    int            contarNodosPorId(Nodo*, id);
    int            contarHijosPorId(Nodo*, id);
    void           imprimirArbol(Nodo*);
    bool           sonIguales(Nodo*, Nodo*);
    int            contarBAnidados(Nodo*);
    int            contarNodosSA(Nodo*);
    int            cantidadNodosCon(Nodo*, string);
    int            cantidadNodosConString(Nodo*, string);


private:
    ArbolAnalisis(bool, Nodo*);
    
    int   altura(Nodo*);
    int   anchura(Nodo*, int);
};

#endif // ARBOLN_H
