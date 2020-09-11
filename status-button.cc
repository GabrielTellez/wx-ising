#include "status-button.hh"

////////////////////////////////////////////
//
//  StatusButton_wx implementation
//

StatusButton_wx::StatusButton_wx( wxWindow* parent, wxWindowID id, 
				  const wxBitmap& bitmap, 
				  const wxString& tooltip,
				  const wxPoint& pos,
				  const wxSize& size,
				  long style,
				  const wxValidator& validator,
				  const wxString& name ) :
  wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name)
{
#if defined(__WXMSW__)
  PushEventHandler(new LogStatusBar(tooltip,false));
#else
  PushEventHandler(new LogStatusBar(tooltip,true));
#endif
}

StatusButton_wx::~StatusButton_wx()
{
  PopEventHandler(true);
}

///////////////////////////////////////
//
//   StatusChoice implementation
//

StatusChoice_wx::StatusChoice_wx(wxWindow *parent, wxWindowID id, 
				 const wxPoint& pos, const wxSize& size, 
				 int n, const wxString choices[], 
				 const wxString& tooltip,
				 long style,
				 const wxValidator& validator,
				 const wxString& name) :
  wxChoice(parent, id, pos, size, n, choices, style, validator, name)
{
#if defined(__WXMSW__)
  PushEventHandler(new LogStatusBar(tooltip,false));
#else
  PushEventHandler(new LogStatusBar(tooltip,true));
#endif
}

StatusChoice_wx::~StatusChoice_wx()
{
  PopEventHandler(true);
}

///////////////////////////////////////////////
//
//   StatusStaticText implementation
//

StatusStaticText_wx::StatusStaticText_wx(wxWindow* parent, 
					 wxWindowID id, 
					 const wxString& label, 
					 const wxString& tooltip,
					 const wxPoint& pos,
					 const wxSize& size,
					 long style,
					 const wxString& name ) :
  wxStaticText(parent, id, label, pos, size, style, name)
{
#if defined(__WXMSW__)
  PushEventHandler(new LogStatusBar(tooltip,false));
#else
  PushEventHandler(new LogStatusBar(tooltip,true));
#endif
}

StatusStaticText_wx::~StatusStaticText_wx()
{
  PopEventHandler(true);
}
