#include "ArbolAnalisis.h"

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
    if(res != 0 && res->obtenerDato() == dato) {
        return res;
    } else {
        return 0;
    }
}

Nodo* ArbolN::buscar(Nodo* n, idCodigo dato) {
    Nodo* tmp = n;
    if(tmp->obtenerDato() == dato) {
        return tmp;
    } else {
        if(!tmp->hijos.empty()) {
            vector<Nodo*>::iterator it = tmp->hijos.begin();
            vector<Nodo*>::iterator itFin = tmp->hijos.end();
            while(it != itFin) {
                if( tmp != 0 && tmp->obtenerDato() == dato) {
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
    return res->obtenerPadre();
}

// Asumo que esto no va a recibir un nodo q no este en el arbol
vector<Nodo*> ArbolAnalisis::descendientes(Nodo* n) {
    Nodo* res = buscar(raiz, n->obtenerDato());
    return res->hijos;
}

bool ArbolN::vacio() {
    return usado;
}


bool ArbolN::existe(idCodigo dato) {
    Nodo* res = buscar(raiz, dato);
    if(res != 0 && res->obtenerDato() == dato) {
        return true;
    } else {
        return false;
    }
}



void ArbolN::modificarDato(idCodigo dato1, idCodigo dato2) {
    Nodo* res = buscar(raiz, dato1);
    res->obtenerDato() = dato2;
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

Nodo* ArbolN::obtenerRaiz() {
    return raiz;
}

ArbolAnalisis::ArbolAnalisis() : ArbolN() {
  
}

ArbolAnalisis::ArbolAnalisis(bool b, Nodo* n) : ArbolN(b, n) {

}

ArbolAnalisis::~ArbolAnalisis() {}

ArbolN* ArbolAnalisis::subArbol(Nodo* n) {
    return new ArbolN(true, n);
}


int ArbolAnalisis::altura(Nodo* nodo) {
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

int ArbolAnalisis::altura() {
    return altura(raiz);
}

int ArbolAnalisis::anchura(Nodo* n, int nivel) {
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

pair<int, int> ArbolAnalisis::anchuraMaxima() {
    return anchuraMaximaNodo(raiz);
}

pair<int, int> ArbolAnalisis::anchuraMaximaNodo(Nodo* n) {
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

int ArbolAnalisis::anchuraPromedio() {
    int anchProm = 0;
    int alt = altura(raiz);
    for(int i = 0; i < alt; i++) {
        anchProm += anchura(raiz, i);
    }
    anchProm /= alt;
    return anchProm;
}

int ArbolAnalisis::contarNodosPorId(Nodo* n, id idBuscar) {
    int c = (n->obtenerId() == idBuscar) ? 1 : 0;
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        c += contarNodosPorId(n->hijos[i], idBuscar);
    }
    return c;
}

int ArbolAnalisis::contarHijosPorId(Nodo* n, id idBuscar) {
    int c = 0;
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        if(n->hijos[i]->obtenerId() == idBuscar)
            c++;
    }
    return c;
}

bool ArbolAnalisis::sonIguales(Nodo* n1, Nodo* n2) {
    if(n1->obtenerDato() == n2->obtenerDato()) {
        return true;
    } else {
        if(n1->hijos.size() == n2->hijos.size()) {
            vector<Nodo*>::iterator it1 = n1->hijos.begin();
            vector<Nodo*>::iterator itFin = n1->hijos.end();
            vector<Nodo*>::iterator it2 = n2->hijos.begin();
            bool resultado = true;
            while(resultado == true && it1!=itFin) {
                resultado = sonIguales((*it1), (*it2));
                it1++;
                it2++;
            }
        } else {
            return false;
        }
    }
}

int ArbolAnalisis::contarBAnidados(Nodo* n){
    int c = 0;
    if(n->obtenerId() == 'B'){
        c += 1;     
    }
    vector<Nodo*>::iterator it = n->hijos.begin();
    vector<Nodo*>::iterator itFin = n->hijos.end();
    
    int res = 0, aux = 0;
    
    while(it != itFin) {
        res = contarBAnidados(*it);
        if(res > aux)
            aux = res;
        it++;
    }
    c += aux;
    return c;    
}

int ArbolAnalisis::contarNodosSA(Nodo * n) {
    int c = 1;
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        c += contarNodosSA(n->hijos[i]);
    }
    return c;
}

int ArbolAnalisis::cantidadNodosCon(Nodo * n,string entrada) {
    int c;
    string d2=n->obtenerCodigo();
    if(d2.find(entrada) != string::npos) {
        c=1;
    }
    else {
        c=0;
    }
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        c += cantidadNodosCon(n->hijos[i],entrada);
    }
    return c;

}

int ArbolAnalisis::cantidadNodosConString(Nodo* n, string entrada) {
    int c;
    string d2 = n->obtenerCodigo();
    if(d2.find(entrada) != string::npos) {
        c=1;
    }
    else {
        c=0;
    }
    for(int i = 0, j = n->hijos.size(); i < j; i++) {
        c += cantidadNodosConString(n->hijos[i],entrada);
    }
    return c;

}
