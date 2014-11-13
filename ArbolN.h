#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <string.h>

using namespace std;

typedef char               id;
typedef string             codigo;
typedef pair<char, string> idCodigo;

struct Nodo {
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

private:

    idCodigo dato;
    vector<Nodo*> hijos;
    Nodo* padre;
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
