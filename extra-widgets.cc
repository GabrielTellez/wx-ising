#include "extra-widgets.hh"


spinctrl_txt_wx::spinctrl_txt_wx(wxWindow* parent, wxWindowID id,
				 const wxString& label,    
				 int value,  
				 int lower,
				 int upper, const wxString& tooltip) :
  wxBoxSizer(wxHORIZONTAL),
  m_label(new StatusStaticText_wx(parent, -1, label, tooltip)),
  m_spinbutton(new wxSpinCtrl(parent, id, wxEmptyString, wxDefaultPosition, 
#if defined(__WXMSW__)
			      wxSize(5,-1)))
#else
			      wxSize(50,-1)))
#endif
{
  m_spinbutton->SetRange(lower, upper);
  m_spinbutton->SetValue(value);

  Add(m_label,0,wxALIGN_LEFT);
#if defined(__WXMSW__)
  Add(m_spinbutton, 4, wxGROW);
#else 
  Add(m_spinbutton, 1, wxGROW);
#endif

#if defined(__WXMSW__)
  m_spinbutton->PushEventHandler(new LogStatusBar(tooltip,false));
#else
  m_spinbutton->PushEventHandler(new LogStatusBar(tooltip,true));
#endif

}

spinctrl_txt_wx::~spinctrl_txt_wx() 
{
  m_spinbutton->PopEventHandler(true);
}

StatusStaticText_wx* spinctrl_txt_wx::get_label()
{
  return m_label;
}

wxSpinCtrl* spinctrl_txt_wx::get_spinctrl()
{ 
  return m_spinbutton;
}

int spinctrl_txt_wx::get_value()
{
  return m_spinbutton->GetValue();
}

// Frame and Text widget

frame_text_wx::frame_text_wx(wxWindow* parent, const wxString& frame_str,
			     const wxString& label_str) :
  wxStaticBox(parent, -1, frame_str),
  m_box_sizer(new wxStaticBoxSizer(this, wxVERTICAL)),
  m_label(new wxStaticText(parent, -1, label_str))
{
  m_box_sizer->Add(m_label,0,wxALIGN_CENTRE);
}

frame_text_wx::~frame_text_wx()
{
}

wxStaticBoxSizer* frame_text_wx::get_sizer()
{
  return m_box_sizer;
}

wxStaticText* frame_text_wx::get_label()
{
  return m_label;
}

void frame_text_wx::set_text(const wxString& str)
{
  m_label->SetLabel(str);
  m_label->Refresh();
}
