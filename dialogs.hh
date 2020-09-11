#include <wx/dialog.h>
#include "extra-widgets.hh"

class NewDialog : public wxDialog
{
public:
  NewDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
	    int actualx, int actualy,
	    const wxPoint& pos = wxDefaultPosition,
	    const wxSize& size = wxDefaultSize, 
	    long style = wxDEFAULT_DIALOG_STYLE, const wxString& name =
	    "dialogBox");
  spinctrl_txt_wx* x_size;
  spinctrl_txt_wx* y_size;

};

