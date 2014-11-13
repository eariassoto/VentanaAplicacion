#include "Controlador.h"
#include "Analizador.h"
#include <utility>
#include <sstream>

//citado de http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
template <typename T>
string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}
//fin cita

Controlador::Controlador() {
    codigo = "";
}

void Controlador::SetArbol(wxTreeCtrl* arbol, wxTextCtrl* txtAreaRes, const char* hilera) {
    if(!arbol->IsEmpty()) {
        arbol->DeleteAllItems();
    }
    wxTreeItemId rootId = arbol->AddRoot("raiz");

    Analizador analizador;
    //char* hilera="public class Clase{int a;int b;int x;char c;void metodo(){Syso;while(){Syso();}}void metodo2(){}}";
    analizador.analizarCodigo(hilera);

    ArbolN arbolN = analizador.arbolAnalizador;
    imprimirArbol2(arbol, rootId, arbolN.obtenerRaiz(), true);
    arbol->ExpandAll();

    txtAreaRes->Clear();
    txtAreaRes->AppendText("Análisis del código:\n");
    string met = "Cantidad de metodos: " + NumberToString(arbolN.contarNodosPorId(arbolN.obtenerRaiz(), 'M')) + string("\n");
    string atr = "Cantidad de atributos: " + NumberToString(arbolN.contarNodosPorId(arbolN.obtenerRaiz(), 'A')) + string("\n");
    string alt = "Profundidad del código (altura del arbol): " + NumberToString(arbolN.altura()) + string("\n");

    pair<int, int> anch = arbolN.anchuraMaxima();
    string ancm = "Nivel en el max anidamiento (anch maxima): " + NumberToString(anch.first) + string("\n");
    string ancp = "Anchura Promedio: " + NumberToString(arbolN.anchuraPromedio()) + string("\n");

    txtAreaRes->AppendText(met);
    txtAreaRes->AppendText(atr);
    txtAreaRes->AppendText(alt);
    txtAreaRes->AppendText(ancm);
    txtAreaRes->AppendText(ancp);
    
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

void Controlador::SetCodigo(wxString str) {
    codigo = str;
    cout << codigo << endl;
}
