#include "Controlador.h"
#include "Analizador.h"
#include <utility>

Controlador::Controlador() {
    codigo = "";
}

void Controlador::SetArbol(wxTreeCtrl* arbol, wxTextCtrl* txtAreaRes, const char* hilera) {

    Analizador analizador;
    analizador.analizarCodigo(hilera);
    ArbolN arbolN = analizador.obtenerArbol();
/*
    Analizador analizador2;
    analizador2.analizarCodigo(hilera);
    ArbolN arbolN2 = analizador2.arbolAnalizador;
    
    
    txtAreaRes->Clear();
    if(arbolN.sonIguales(arbolN.obtenerRaiz(), arbolN2.obtenerRaiz())){
        txtAreaRes->AppendText("Son iguales\n");
    }
    */
    txtAreaRes->AppendText(analizador.generarAnalisis());
    txtAreaRes->ShowPosition(0);
    
    /*
    
    pair<int, int> anch = arbolN.anchuraMaxima();
    string ancm = "Nivel en el max anidamiento (anch maxima): " + NumberToString(anch.first) + string("\n");
    string ancp = "Anchura Promedio: " + NumberToString(arbolN.anchuraPromedio()) + string("\n");

    
    txtAreaRes->AppendText(alt);
    txtAreaRes->AppendText(ancm);
    txtAreaRes->AppendText(ancp);
    */
    wxTreeItemId rootId;
    if(!arbol->IsEmpty()) {
        arbol->DeleteAllItems();
        rootId = arbol->AddRoot("raiz");
        imprimirArbol2(arbol, rootId, arbolN.obtenerRaiz(), true);
        arbol->ExpandAll();
    }else{
        rootId = arbol->AddRoot("raiz");
        imprimirArbol2(arbol, rootId, arbolN.obtenerRaiz(), true);
        arbol->ExpandAll();
    }
}

void Controlador::imprimirArbol2(wxTreeCtrl* arbol, wxTreeItemId fatherId, Nodo* n, bool esRaiz) {
    wxTreeItemId id;
    if(esRaiz)
        id = arbol->AppendItem(fatherId, "Código Fuente");
    else
        id = arbol->AppendItem(fatherId, n->dato.first);

    vector<Nodo*>::iterator it = n->hijos.begin();
    vector<Nodo*>::iterator itFin = n->hijos.end();
    for(; it!=itFin; it++) {
        imprimirArbol2(arbol, id, (*it), false);
    }

}

void Controlador::imprimirArbol(wxTextCtrl* txtAreaRes, Nodo* n) {
    txtAreaRes->AppendText(n->dato.first);
    vector<Nodo*>::iterator it = n->hijos.begin();
    vector<Nodo*>::iterator itFin = n->hijos.end();
    for(; it!=itFin; it++) {
        imprimirArbol(txtAreaRes, (*it));
    }
}

