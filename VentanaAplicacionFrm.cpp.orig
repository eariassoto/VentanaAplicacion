///-----------------------------------------------------------------
///
/// @file      VentanaAplicacionFrm.cpp
/// @author    user
/// Created:   11/7/2014 9:29:58 PM
/// @section   DESCRIPTION
///            VentanaAplicacionFrm class implementation
///
///------------------------------------------------------------------

#include "VentanaAplicacionFrm.h"
//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// VentanaAplicacionFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(VentanaAplicacionFrm,wxFrame)
    ////Manual Code Start
    ////Manual Code End

    EVT_CLOSE(VentanaAplicacionFrm::OnClose)
    EVT_ACTIVATE(VentanaAplicacionFrm::VentanaAplicacionFrmActivate)

    EVT_STC_MODIFIED(ID_TXTCODIGO,VentanaAplicacionFrm::txtCodigoModified)
    EVT_BUTTON(ID_BTNANALIZAR,VentanaAplicacionFrm::btnAnalizarClick)
END_EVENT_TABLE()
////Event Table End

VentanaAplicacionFrm::VentanaAplicacionFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
    : wxFrame(parent, id, title, position, size, style)
{
    CreateGUIControls();
}

VentanaAplicacionFrm::~VentanaAplicacionFrm()
{
}

void VentanaAplicacionFrm::CreateGUIControls()
{
    //Do not add custom code between
    //GUI Items Creation Start and GUI Items Creation End
    //wxDev-C++ designer will remove them.
    //Add the custom code before or after the blocks
    ////GUI Items Creation Start

    WxMenuBar1 = new wxMenuBar();

    arbol = new wxTreeCtrl(this, ID_ARBOL, wxPoint(364, 241), wxSize(360, 175), wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_HIDE_ROOT, wxDefaultValidator, _("arbol"));

    txtCodigo = new wxStyledTextCtrl(this, ID_TXTCODIGO, wxPoint(5, 108), wxSize(352, 308), 0,  _("txtCodigo"));
    txtCodigo->SetFocus();

    WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("y de clic en el botón analizar."), wxPoint(16, 77), wxDefaultSize, 0, _("WxStaticText3"));
    WxStaticText3->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false));

    WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Introduzca o escriba el código que desea analizar"), wxPoint(15, 51), wxDefaultSize, 0, _("WxStaticText2"));
    WxStaticText2->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false));

    WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Bienvenid@ al analizador de código"), wxPoint(15, 10), wxDefaultSize, 0, _("WxStaticText1"));
    WxStaticText1->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false));

    txtAreaRes = new wxTextCtrl(this, ID_TXTAREARES, wxEmptyString, wxPoint(363, 14), wxSize(359, 219), wxTE_READONLY | wxTE_MULTILINE, wxDefaultValidator, _("txtAreaRes"));
    txtAreaRes->SetMaxLength(0);
    txtAreaRes->SetInsertionPointEnd();

    btnAnalizar = new wxButton(this, ID_BTNANALIZAR, _("Analizar"), wxPoint(9, 424), wxSize(75, 25), 0, wxDefaultValidator, _("btnAnalizar"));

    SetTitle(_("VentanaAplicacion"));
    SetIcon(wxNullIcon);
    SetSize(8,8,745,500);
    Center();

    ////GUI Items Creation End

    archivo = new wxMenu;
    archivo->Append(wxID_SAVE, wxT("&Guardar Reporte"));
    archivo->Append(wxID_EXIT, wxT("&Salir"));

    demos = new wxMenu;
    demos->Append(7, wxT("&Persona"));
    
    WxMenuBar1->Append(archivo, wxT("&Archivo"));
    WxMenuBar1->Append(demos, wxT("&Demos"));
    SetMenuBar(WxMenuBar1);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(VentanaAplicacionFrm::OnQuit));
    Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(VentanaAplicacionFrm::OnSave));
    Connect(7, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(VentanaAplicacionFrm::OnPersona));

}

void VentanaAplicacionFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void VentanaAplicacionFrm::OnSave(wxCommandEvent& WXUNUSED(event))
{
    if(txtAreaRes->GetValue() != "") {
        txtAreaRes->SaveFile("reporte.txt", wxTEXT_ALIGNMENT_DEFAULT);
        wxMessageDialog* dial = new wxMessageDialog(NULL,
                wxT("El reporte se ha generado correctamente."), wxT("Guardar Reporte"), wxOK);
        dial->ShowModal();
        system( "notepad.exe reporte.txt" );
    } else {
        wxMessageDialog* dial = new wxMessageDialog(NULL,
                wxT("Aun no has analizado ningun codigo. Escribe codigo en el editor para generar el analisis."), wxT("Guardar Reporte"), wxOK);
        dial->ShowModal();
    }
}

void VentanaAplicacionFrm::OnPersona(wxCommandEvent& WXUNUSED(event))
{
    txtCodigo->Clear();
    txtCodigo->AppendText("public class Persona{\n\tstring nombre;\n\tstring apellido;\n\tint edad;\n\tstring getNombre(){\n\t\treturn nombre;\n\t}\n\tint getEdad(){\n\t\treturn nombre;\n\t}\n}\npublic class Auto{\n\tvoid conducir(Persona p){\n\t\tvroomvroom(p);\n\t}\n}");
}

void VentanaAplicacionFrm::SetControlador(Controlador* c)
{
    this->controlador = c;
}

void VentanaAplicacionFrm::OnClose(wxCloseEvent& event)
{
    Destroy();
}

/*
 * VentanaAplicacionFrmActivate
 */
void VentanaAplicacionFrm::VentanaAplicacionFrmActivate(wxActivateEvent& event)
{
    // insert your code here
}


/*
 * btnAnalizarClick
 */
void VentanaAplicacionFrm::btnAnalizarClick(wxCommandEvent& event)
{
    // insert your code here
    const char* codigo = txtCodigo->GetValue().ToStdString().c_str();
    controlador->SetArbol(arbol, txtAreaRes, codigo);
}

/*
 * txtCodigoModified
 */
void VentanaAplicacionFrm::txtCodigoModified(wxStyledTextEvent& event)
{
}
