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

    Analizador analizador;
    analizador.analizarCodigo(hilera);

    ArbolN arbolN = analizador.arbolAnalizador;

    txtAreaRes->Clear();
    txtAreaRes->AppendText("Análisis del código:\n");
    string str;
    
    str = "Profundidad del código (altura del arbol): " + NumberToString(arbolN.altura()) + string("\n");
    txtAreaRes->AppendText(str);
    
    txtAreaRes->AppendText("\nAnálisis por clases:\n");
    
    Nodo* raiz = arbolN.obtenerRaiz();
    vector<Nodo*>::iterator it = raiz->hijos.begin();
    vector<Nodo*>::iterator itFin = raiz->hijos.end();
    
    for(; it!=itFin; it++) {
        str = "Clase " + (*it)->obtenerNombreClase() +":\n"; 
        txtAreaRes->AppendText(str);
        str = analizarAtributosMetodos(arbolN, (*it));
        txtAreaRes->AppendText(str);
        
        pair<int, int> anch = arbolN.anchuraMaximaNodo((*it));
        str = "Nivel de máximo anidamiento: " + NumberToString(anch.first) + " con un ancho de " + NumberToString(anch.second) + string("\n");
        txtAreaRes->AppendText(str);
        
        txtAreaRes->AppendText("\n");
    }
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

string Controlador::analizarAtributosMetodos(ArbolN arbolN, Nodo* n){
    string s = "";
    int atributos, metodos;
    atributos = arbolN.contarNodosPorId(n, 'A');
    metodos = arbolN.contarNodosPorId(n, 'M');   
    if(atributos > metodos){
        s = "Esta clase posee mas atributos que métodos, posiblemente sea una clase contenedora.\n";    
    }else if(atributos == metodos){
        s = "Esta clase posee igual número de métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";  
    }else{
        s = "Esta clase posee mas métodos que atributos, posiblemente sea una clase que modele algún comportamiento.\n";  
    }
    
    return s;
}
