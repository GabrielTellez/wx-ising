#ifndef __GT_WX_STATUS_BUTTON_H
#define __GT_WX_STATUS_BUTTON_H

#include <wx/defs.h>
#include <wx/window.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/log.h>
#include <wx/stattext.h>

#include "log-status.hh"

class StatusButton_wx : public wxBitmapButton
{
public:
  StatusButton_wx( wxWindow* parent, wxWindowID id, 
		   const wxBitmap& bitmap, 
		   const wxString& tooltip = wxEmptyString,
		   const wxPoint& pos = wxDefaultPosition,
		   const wxSize& size = wxDefaultSize, 
		   long style = wxBU_AUTODRAW, 
		   const wxValidator& validator = wxDefaultValidator,
		   const wxString& name = "button");
  ~StatusButton_wx();
};

class StatusChoice_wx : public wxChoice
{
public:
  StatusChoice_wx(wxWindow *parent, wxWindowID id, 
		  const wxPoint& pos, const wxSize& size, 
		  int n, const wxString choices[], 
		  const wxString& tooltip=wxEmptyString, 
		  long style = 0, 
		  const wxValidator& validator = wxDefaultValidator, 
		  const wxString& name ="choice") ;
  ~StatusChoice_wx();
};
  
  
class StatusStaticText_wx : public wxStaticText
{
public:
  StatusStaticText_wx(wxWindow* parent, wxWindowID id, 
		      const wxString& label = "", 
		      const wxString& tooltip = "",
		      const wxPoint& pos = wxDefaultPosition, 
		      const wxSize& size = wxDefaultSize, 
		      long style = 0, 
		      const wxString& name = "staticText");

  ~StatusStaticText_wx();
};
  

#endif
