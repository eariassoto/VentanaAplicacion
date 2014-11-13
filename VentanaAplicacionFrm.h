///-----------------------------------------------------------------
///
/// @file      VentanaAplicacionFrm.h
/// @author    user
/// Created:   11/7/2014 9:29:58 PM
/// @section   DESCRIPTION
///            VentanaAplicacionFrm class declaration
///
///------------------------------------------------------------------

#ifndef __VENTANAAPLICACIONFRM_H__
#define __VENTANAAPLICACIONFRM_H__

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
#include "Controlador.h"

////Dialog Style Start
#undef VentanaAplicacionFrm_STYLE
#define VentanaAplicacionFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

using namespace std;

class VentanaAplicacionFrm : public wxFrame
{
private:
    DECLARE_EVENT_TABLE();

public:
    VentanaAplicacionFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("VentanaAplicacion"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = VentanaAplicacionFrm_STYLE);
    virtual ~VentanaAplicacionFrm();
    void VentanaAplicacionFrmActivate(wxActivateEvent& event);
    void WxButton1Click(wxCommandEvent& event);
    void btnAnalizarClick(wxCommandEvent& event);

    void SetControlador(Controlador*);
    void txtCodigoKey(wxStyledTextEvent& event);
    void txtCodigoModified(wxStyledTextEvent& event);

private:
    //Do not add custom control declarations between
    //GUI Control Declaration Start and GUI Control Declaration End.
    //wxDev-C++ will remove them. Add custom code after the block.
    ////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxTreeCtrl *arbol;
		wxStyledTextCtrl *txtCodigo;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxTextCtrl *txtAreaRes;
		wxButton *btnAnalizar;
    ////GUI Control Declaration End
    wxMenu* archivo;
    wxMenu* demos;
    Controlador* controlador;

private:
    //Note: if you receive any error with these enum IDs, then you need to
    //change your old form code that are based on the #define control IDs.
    //#defines may replace a numeric value for the enum names.
    //Try copy and pasting the below block in your old form header files.
    enum
    {
        ////GUI Enum Control ID Start
			ID_ARBOL = 11,
			ID_TXTCODIGO = 10,
			ID_WXSTATICTEXT3 = 8,
			ID_WXSTATICTEXT2 = 7,
			ID_WXSTATICTEXT1 = 6,
			ID_TXTAREARES = 5,
			ID_BTNANALIZAR = 3,
        ////GUI Enum Control ID End
        ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
    };

private:
    void OnClose(wxCloseEvent& event);
    void CreateGUIControls();
    void OnQuit(wxCommandEvent& WXUNUSED(event));
    void OnSave(wxCommandEvent& WXUNUSED(event));
};

#endif
