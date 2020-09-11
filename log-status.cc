#include "log-status.hh"

LogStatusBar::LogStatusBar(const wxString& tooltip, bool clear) :
  m_tooltip(tooltip),
  m_clear_tooltip(clear)
{}

wxString LogStatusBar::get_tooltip()
{
  return m_tooltip;
}

void LogStatusBar::set_tooltip(const wxString& tooltip)
{
  m_tooltip=tooltip;
}

void LogStatusBar::OnEnterWindow(wxMouseEvent& event)
{
  wxLogStatus(m_tooltip);
  event.Skip();
}

void LogStatusBar::OnLeaveWindow(wxMouseEvent& event)
{
  if(m_clear_tooltip) {
    wxLogStatus("");
  }
  event.Skip();
}

