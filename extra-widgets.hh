#ifndef __GT_EXTRA_WIDGETS_H
#define __GT_EXTRA_WIDGETS_H

#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include "status-button.hh"

class spinctrl_txt_wx : public wxBoxSizer
{
protected:
  StatusStaticText_wx* m_label;
  wxSpinCtrl* m_spinbutton;

public:
  spinctrl_txt_wx(wxWindow* parent, wxWindowID id,
		  const wxString& label,    
		  int value,        
		  int lower,
		  int upper,
		  const wxString& tooltip=wxEmptyString);
  ~spinctrl_txt_wx();

  wxSpinCtrl* get_spinctrl();
  int get_value();
  StatusStaticText_wx* get_label();
};


class frame_text_wx : public wxStaticBox
{
protected:
  wxStaticBoxSizer*  m_box_sizer;
  wxStaticText* m_label;
public:
  frame_text_wx(wxWindow* parent, const wxString& frame_str,const wxString& label_str="");
  ~frame_text_wx();
  wxStaticText* get_label();
  wxStaticBoxSizer* get_sizer();
  void set_text(const wxString& str);
};

#endif
