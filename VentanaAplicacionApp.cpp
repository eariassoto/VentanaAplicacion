//---------------------------------------------------------------------------
//
// Name:        VentanaAplicacionApp.cpp
// Author:      user
// Created:     11/7/2014 9:29:58 PM
// Description:
//
//---------------------------------------------------------------------------

#include "VentanaAplicacionApp.h"
#include "VentanaAplicacionFrm.h"
#include "Controlador.h"

IMPLEMENT_APP(VentanaAplicacionFrmApp)

bool VentanaAplicacionFrmApp::OnInit()
{
    Controlador * controlador = new Controlador();

    VentanaAplicacionFrm* frame = new VentanaAplicacionFrm(NULL);
    SetTopWindow(frame);

    frame->SetControlador(controlador);
    frame->Show();


    return true;
}

int VentanaAplicacionFrmApp::OnExit()
{
    return 0;
}
