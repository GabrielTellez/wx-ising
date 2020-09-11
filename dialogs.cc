#include "dialogs.hh"

NewDialog::NewDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
		     int actualx, int actualy,
		     const wxPoint& pos,
		     const wxSize& size, 
		     long style, 
		     const wxString& name) :
  wxDialog(parent, id, title, 
	   pos, size, 
	   style, name ),
  x_size(new spinctrl_txt_wx(this, -1, "Width: ", actualx, 1, 50)),
  y_size(new spinctrl_txt_wx(this,-1, "Height: ", actualy, 1, 50))
{
  wxBoxSizer* topvbox = new wxBoxSizer(wxVERTICAL);
  topvbox->Add(10,10,1,wxGROW);
  topvbox->Add(new wxStaticText(this, -1, "Choose new lattice size"), 
	       1, wxALIGN_CENTER);
  wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
  hbox->Add(10, 10, 1, wxGROW);
  hbox->Add(x_size, 0, wxALIGN_CENTER);
  hbox->Add(10, 10, 1, wxGROW);
  hbox->Add(y_size, 0, wxALIGN_CENTER);
  hbox->Add(10, 10, 1, wxGROW);
  topvbox->Add(10,30,1,wxGROW);
  topvbox->Add(hbox,1, wxALIGN_CENTER);
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
  hbox2->Add(new wxButton(this, wxID_OK, "OK", wxPoint(250, 10), 
			  wxSize(80, 30)),
	     0,wxALIGN_CENTER);
  hbox2->Add(10, 10, 1, wxGROW);
  hbox2->Add(new wxButton(this,wxID_CANCEL, "Cancel", 
			  wxPoint(250, 60), wxSize(80, 30)),
	     0,wxALIGN_CENTER);
  topvbox->Add(10,10,1,wxGROW);
  topvbox->Add(hbox2, 1, wxALIGN_CENTER);
  topvbox->Add(10,10,1,wxGROW);
  SetSizer(topvbox);
  SetAutoLayout(TRUE);
  topvbox->SetSizeHints( this );
  topvbox->Fit( this );
}
