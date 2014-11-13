#include "ArbolN.h"

ArbolN::ArbolN() {
    usado = false;
}

ArbolN::ArbolN(bool b, Nodo* n) {
    usado = b;
    raiz = n;
}

ArbolN::~ArbolN() {}

Nodo* ArbolN::agregarRaiz(idCodigo d) {
    Nodo* nodo = new Nodo(d);
    this->raiz = nodo;
    this->usado = true;

    return nodo;
}

Nodo* ArbolN::buscar(idCodigo dato) {
    Nodo* res = buscar(raiz, dato);
    if(res != 0 && res->dato == dato) {
        return res;
    } else {
        return 0;
    }
}

Nodo* ArbolN::buscar(Nodo* n, idCodigo dato) {
    Nodo* tmp = n;
    if(tmp->dato == dato) {
        return tmp;
    } else {
        if(!tmp->hijos.empty()) {
            vector<Nodo*>::iterator it = tmp->hijos.begin();
            vector<Nodo*>::iterator itFin = tmp->hijos.end();
            while(it != itFin) {
                if( tmp != 0 && tmp->dato == dato) {
                    return tmp;
                } else {
                    tmp = buscar((*it), dato);
                    it++;
                }
            }
        }
    }
    return 0;
}

Nodo* ArbolN::agregarDato(Nodo* padre, idCodigo dato) {
    Nodo* nuevo = new Nodo(dato, padre);
    padre->hijos.push_back(nuevo);

    return nuevo;
}

Nodo* ArbolN::padre(idCodigo dato) {
    return padre(raiz, dato);
}

// Darth Vader approves
Nodo* ArbolN::padre(Nodo* n, idCodigo dato) {
    Nodo* res = buscar(n, dato);
    return res->padre;
}

// Asumo que esto no va a recibir un nodo q no este en el arbol
vector<Nodo*> ArbolN::descendientes(Nodo* n) {
    Nodo* res = buscar(raiz, n->dato);
    return res->hijos;
}

bool ArbolN::vacio() {
    return usado;
}

Nodo* ArbolN::benjamin() {
    if(usado && !raiz->hijos.empty()) {
        return raiz->hijos[0];
    } else {
        return 0;
    }
}

bool ArbolN::existe(idCodigo dato) {
    Nodo* res = buscar(raiz, dato);
    if(res != 0 && res->dato == dato) {
        return true;
    } else {
        return false;
    }
}

ArbolN* ArbolN::subArbol(Nodo* n) {
    return new ArbolN(true, n);
}

void ArbolN::modificarDato(idCodigo dato1, idCodigo dato2) {
    Nodo* res = buscar(raiz, dato1);
    res->dato = dato2;
}

int ArbolN::cantidadNodos(Nodo* nodo) {
    int c = 1;
    for(int i = 0, j = nodo->hijos.size(); i < j; i++) {
        c += cantidadNodos(nodo->hijos[i]);
    }
    return c;
}

int ArbolN::cantidadNodos() {
    return cantidadNodos(raiz);
}

int ArbolN::altura(Nodo* nodo) {
    int c = 1;
    int aux = 0, aux2;
    for(int i = 0, j = nodo->hijos.size(); i < j; i++) {
        aux2 = altura(nodo->hijos[i]);
        if(aux2 > aux) {
            aux = aux2;
        }
    }
    c += aux;
    return c;
}

int ArbolN::altura() {
    return altura(raiz);
}

int ArbolN::anchura(Nodo* n, int nivel) {
    int c = 0;
    if(n == 0) {
        return 0;
    }
    if(nivel == 1) {
        return 1;
    }
    else if(nivel > 1) {
        for(int i = 0, j = n->hijos.size(); i<j; i++) {
            c += anchura(n->hijos[i], nivel-1);
        }
    }
    return c;
}

pair<int, int> ArbolN::anchuraMaxima() {
    return anchuraMaximaNodo(raiz);
}

pair<int, int> ArbolN::anchuraMaximaNodo(Nodo* n) {
    int anchMax = 0, nivelMax = 0;
    int ancho;
    int alt = altura(n);
    for(int i = 0; i < alt; i++) {
        ancho = anchura(n, i);
        if(ancho > anchMax) {
            nivelMax = i;
            anchMax = ancho;
        }
    }
    return make_pair(nivelMax, anchMax);
}

int ArbolN::anchuraPromedio() {
    int anchProm = 0;
    int alt = altura(raiz);
    for(int i = 0; i < alt; i++) {
        anchProm += anchura(raiz, i);
    }
    anchProm /= alt;
    return anchProm;
}

Nodo* ArbolN::obtenerRaiz() {
    return raiz;
}

int ArbolN::contarNodosPorId(Nodo* n, id idBuscar) {
    int c = (n->dato.first == idBuscar) ? 1 : 0;
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        c += contarNodosPorId(n->hijos[i], idBuscar);
    }
    return c;
}

void ArbolN::imprimirArbol(Nodo* n) {
    cout << n->dato.first << " " << n->dato.second << endl;
    vector<Nodo*>::iterator it = n->hijos.begin();
    vector<Nodo*>::iterator itFin = n->hijos.end();
    cout<<"["<<endl;
    for(; it!=itFin; it++) {
        imprimirArbol((*it));
    }
    cout<<"]"<<endl;
}
