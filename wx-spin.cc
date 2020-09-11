#include "wx-spin.hh"

inline
ising_spin_wx::ising_spin_wx(wxWindow* parent,
			     wxWindowID id, const wxString& tooltip) :
  basic_ising_spin(),
  up_pixmap(wxBITMAP(spinup)),
  down_pixmap(wxBITMAP(spindown)),
  m_p_spin_button(new StatusButton_wx(parent, id, up_pixmap, tooltip))
{
  update_spin_button();
}

inline
ising_spin_wx::ising_spin_wx(int spin, 
			     wxWindow *parent, wxWindowID id,
			     const wxString& tooltip) :
  basic_ising_spin(spin),
  up_pixmap(wxBITMAP(spinup)),
  down_pixmap(wxBITMAP(spindown)),
  m_p_spin_button(new StatusButton_wx(parent, id, up_pixmap, tooltip))
{
  update_spin_button();
}

inline
void ising_spin_wx::update_spin_button() 
{
  if(get_value()==1) {
    m_p_spin_button->SetBitmapLabel(up_pixmap);
    m_p_spin_button->SetBitmapFocus(up_pixmap);
    m_p_spin_button->SetBitmapDisabled(up_pixmap);
    m_p_spin_button->SetBitmapSelected(up_pixmap);
  } else {
    m_p_spin_button->SetBitmapLabel(down_pixmap);
    m_p_spin_button->SetBitmapFocus(down_pixmap);
    m_p_spin_button->SetBitmapDisabled(down_pixmap);
    m_p_spin_button->SetBitmapSelected(down_pixmap);
  }
  get_button()->Refresh();
}

inline
void ising_spin_wx::flip() 
{ 
  basic_ising_spin::flip();
  update_spin_button();
}

inline
bool ising_spin_wx::set_value(int spin)
{
  if(basic_ising_spin::set_value(spin)) {
    update_spin_button();
    return true;
  } else {
    return false;
  }
}

inline
StatusButton_wx* ising_spin_wx::get_button() 
{ 
  return m_p_spin_button; 
} 

inline
ising_spin_wx::~ising_spin_wx()
{
  m_p_spin_button->Destroy();
}




