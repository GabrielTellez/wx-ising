#ifndef __GT_WX_SPIN_H
#define __GT_WX_SPIN_H

#include "spin.hh"
#include "status-button.hh"
#include <wx/defs.h>
#include <wx/window.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>

#if defined(__WXGTK__) || defined (__WXMOTIF__)
#include "bitmaps/spinup.xpm"
#include "bitmaps/spindown.xpm"
#endif

class ising_spin_wx : public basic_ising_spin
{
public:
  wxBitmap up_pixmap;
  wxBitmap down_pixmap;
  StatusButton_wx* m_p_spin_button;

public:
  ising_spin_wx(wxWindow *parent, wxWindowID id=-1, 
		const wxString& tooltip=wxEmptyString);
  ising_spin_wx(int spin, 
		wxWindow *parent, wxWindowID id=-1,
		const wxString& tooltip=wxEmptyString);
  void update_spin_button(); 
  void flip();
  bool set_value(int spin);
  StatusButton_wx* get_button();
  virtual ~ising_spin_wx();
};


#endif
