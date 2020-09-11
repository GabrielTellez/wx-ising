#include "monte-carlo-preferences.h"
#include <string>
#include <strstream.h>

#ifdef __BORLANDC__
    #include "wx/wxprec.h"
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/defs.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/dialog.h>
#include <wx/toolbar.h>
#include <wx/choice.h>
#include <wx/event.h>
#endif

#include "basic-lattice.cc"
#include "spin.cc"
#include "status-button.cc"
#include "log-status.cc"
#include "dialogs.cc"
#include "wx-spin.cc"
#include "wx-table-sizer.cc"
#include "wx-lattice.cc"
#include "metropolis.cc"
#include "extra-widgets.cc"
#include "curves_wx.cc"

#if defined(__WXGTK__) || defined (__WXMOTIF__)
#include "bitmaps/start.xpm"
#include "bitmaps/stop.xpm"
#include "bitmaps/fast.xpm"
#include "bitmaps/slow.xpm"
#include "bitmaps/logo.xpm"
#endif

class MonteCarloApp : public wxApp
{
  virtual bool OnInit();
};

class MainFrame: public wxFrame
{
protected:
  wxPanel* mainpanel;
  table_wx* table;
  lattice_wx* lattice;
  metropolis_ising* metropolis_algo;

public:
  MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  
  void OnNew(wxCommandEvent& event);
  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnButtonPressed(wxCommandEvent& event);
  void OnIdle(wxIdleEvent& event);
  void OnStartStop(wxCommandEvent& event);
  void OnFastSlow(wxCommandEvent& event);
  void OnChoiceBC(wxCommandEvent& event);
  void OnChoiceTemp(wxScrollEvent& event);
  void OnChoiceJ(wxScrollEvent& event);
  void update_energy_spin_labels();
protected:
  bool is_running;
  bool is_fast;
  frame_text_wx frm_txt_spin;
  frame_text_wx frm_txt_energy;
  spinctrl_txt_wx* choice_temp;
  spinctrl_txt_wx* choice_coupling;
  DataPlotCurve* m_energy_curve;
  DataPlotCurve* m_spin_curve;
  PlotWindowLabeled* plotwin_energy;
  PlotWindowLabeled* plotwin_spin;

private:
  DECLARE_EVENT_TABLE()
};

enum
{
  ID_Quit = wxID_HIGHEST+1,
  ID_New,
  ID_About,
  ID_StartStop,
  ID_FastSlow,
  ID_CHOICE_BC,
  ID_CHOICE_TEMP,
  ID_CHOICE_J
};

#define MAX_BUTTONS 2500

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(ID_Quit,  MainFrame::OnQuit)
  EVT_MENU(ID_New,  MainFrame::OnNew)
  EVT_MENU(ID_About, MainFrame::OnAbout)
  EVT_COMMAND_RANGE(ID_BUTTON_BASE, ID_BUTTON_BASE+MAX_BUTTONS, wxEVT_COMMAND_BUTTON_CLICKED, MainFrame::OnButtonPressed)
  EVT_IDLE(MainFrame::OnIdle)
  EVT_MENU(ID_StartStop, MainFrame::OnStartStop)
  EVT_MENU(ID_FastSlow, MainFrame::OnFastSlow)
  EVT_CHOICE(ID_CHOICE_BC, MainFrame::OnChoiceBC)
  EVT_SPINCTRL(ID_CHOICE_TEMP, MainFrame::OnChoiceTemp) 
  EVT_SPINCTRL(ID_CHOICE_J, MainFrame::OnChoiceJ) 
END_EVENT_TABLE()



