#ifndef __CONTROLADOR_H__
#define __CONTROLADOR_H__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif

//Do not add custom headers between
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/treectrl.h>
#include <wx/stc/stc.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
////Header Include End

#include <iostream>
#include <string>
#include "ArbolN.h"

using namespace std;

class Controlador: public wxEvtHandler
{
public:
    Controlador();
    void   SetArbol(wxTreeCtrl*, wxTextCtrl*, const char*);
    void   imprimirArbol(wxTextCtrl*, Nodo*);
    void   imprimirArbol2(wxTreeCtrl*, wxTreeItemId, Nodo*, bool);
    string analizarAtributosMetodos(ArbolN, Nodo*);
    
private:
    wxString codigo;
};

#endif
