#ifndef __GT_WX_LOG_STATUS_H
#define __GT_WX_LOG_STATUS_H

#include <wx/event.h>

class LogStatusBar : public wxEvtHandler
{
public:
  LogStatusBar(const wxString& tooltip="", bool clear=true);
  void OnEnterWindow(wxMouseEvent& event);
  void OnLeaveWindow(wxMouseEvent& event);
  void set_tooltip(const wxString& tooltip);
  wxString get_tooltip();

protected:
  wxString m_tooltip;
  bool m_clear_tooltip;

private:
  DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(LogStatusBar, wxEvtHandler)
  EVT_ENTER_WINDOW(LogStatusBar::OnEnterWindow) 
  EVT_LEAVE_WINDOW(LogStatusBar::OnLeaveWindow) 
END_EVENT_TABLE()


#endif
