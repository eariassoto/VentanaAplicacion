//---------------------------------------------------------------------------
//
// Name:        VentanaAplicacionApp.h
// Author:      user
// Created:     11/7/2014 9:29:58 PM
// Description:
//
//---------------------------------------------------------------------------

#ifndef __VENTANAAPLICACIONFRMApp_h__
#define __VENTANAAPLICACIONFRMApp_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

class VentanaAplicacionFrmApp : public wxApp
{
public:
    bool OnInit();
    int OnExit();
};

#endif
