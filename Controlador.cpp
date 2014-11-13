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

    txtAreaRes->Clear();
    txtAreaRes->AppendText(analizador.generarAnalisis());
    txtAreaRes->ShowPosition(0);

    wxTreeItemId rootId;
    if(!arbol->IsEmpty()) {
        arbol->DeleteAllItems();
        rootId = arbol->AddRoot("raiz");
        imprimirwxTree(arbol, rootId, arbolN.obtenerRaiz(), true);
        arbol->ExpandAll();
    } else {
        rootId = arbol->AddRoot("raiz");
        imprimirwxTree(arbol, rootId, arbolN.obtenerRaiz(), true);
        arbol->ExpandAll();
    }
}

void Controlador::imprimirwxTree(wxTreeCtrl* arbol, wxTreeItemId fatherId, Nodo* n, bool esRaiz) {
    wxTreeItemId id;
    if(esRaiz)
        id = arbol->AppendItem(fatherId, "Código Fuente");
    else
        id = arbol->AppendItem(fatherId, n->dato.first);

    vector<Nodo*>::iterator it = n->hijos.begin();
    vector<Nodo*>::iterator itFin = n->hijos.end();
    for(; it!=itFin; it++) {
        imprimirwxTree(arbol, id, (*it), false);
    }

}
