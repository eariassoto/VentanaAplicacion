#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <list>
#include <string.h>

using namespace std;

typedef char               id;
typedef string             codigo;
typedef pair<char, string> idCodigo;

class Nodo {
    friend class ArbolN;
    friend class Controlador;
    friend class Analizador;

public:

    Nodo(idCodigo d):dato(d), hijos() {
        padre = 0;
    }
    Nodo(idCodigo d, Nodo* np):dato(d), hijos() {
        padre = np;
    }
    ~Nodo() {
    }
    
    string obtenerNombreClase(){
        string str(dato.second);
        myReplace(str, "public", "");
        myReplace(str, "class", "");
        str.erase(remove(str.begin(), str.end(), (char)13), str.end());
        str.erase(remove(str.begin(), str.end(), (char)10), str.end());
        str.erase(remove(str.begin(), str.end(), '\t'), str.end());
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        return str;    
    }

private:

    idCodigo dato;
    vector<Nodo*> hijos;
    Nodo* padre;
    
// codigo tomado de http://stackoverflow.com/questions/1494399/how-do-i-search-find-and-replace-in-a-standard-string
    void myReplace(std::string& str, const std::string& oldStr, const std::string& newStr){
        size_t pos = 0;
        while((pos = str.find(oldStr, pos)) != std::string::npos){
            str.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }
//fin cita
};

class ArbolN  {

    friend class Analizador;

public:
    ArbolN();
    ~ArbolN();

    Nodo*          agregarRaiz(idCodigo);
    Nodo*          obtenerRaiz();
    Nodo*          buscar(idCodigo);
    Nodo*          agregarDato(Nodo*, idCodigo);
    Nodo*          padre(idCodigo);
    vector<Nodo*>  descendientes(Nodo*);
    bool           vacio();
    Nodo*          benjamin();
    bool           existe(idCodigo);
    ArbolN*        subArbol(Nodo*);
    void           modificarDato(idCodigo, idCodigo);
    int            cantidadNodos();
    int            altura();
    pair<int, int> anchuraMaxima();
    pair<int, int> anchuraMaximaNodo(Nodo*);
    int            anchuraPromedio();
    int            contarNodosPorId(Nodo*, id);
    void           imprimirArbol(Nodo* n);


private:
    ArbolN(bool, Nodo*);

    Nodo* raiz;
    bool  usado;

    Nodo* buscar(Nodo*, idCodigo);
    Nodo* padre(Nodo*, idCodigo);
    int   cantidadNodos(Nodo*);
    int   altura(Nodo*);
    int   anchura(Nodo*, int);
};


#endif // ARBOLN_H
