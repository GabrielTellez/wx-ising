#include "curves_wx.hh"

////////////////////////////////////////////////////
//
//        DataPlotCurve implementation
//


DataPlotCurve::DataPlotCurve(int offsetY, double startY, double endY) :
  wxPlotCurve(offsetY, startY, endY),
  m_currentX(-1)
{}

wxInt32 DataPlotCurve::GetStartX()
{
  return 0;
}
wxInt32 DataPlotCurve::GetEndX()
{
  return m_currentX;
}
double DataPlotCurve::GetY( wxInt32 x )
{
  if ((x<0)||(x>m_currentX)) {
    cout << "DataPlotCurve(x): x=" << x << 
      " out of bounds (0," << m_currentX <<")\n";
    return 0;
  }
  return m_data[x];
}

void DataPlotCurve::push_back(double data)
{
  m_data.push_back(data);
  m_currentX++;
}

void DataPlotCurve::clear_data()
{
  m_data.erase(m_data.begin(),m_data.end());
  m_currentX=-1;
}

///////////////////////////////////////////////////////
//
//     PlotWindowLabeled
//

PlotWindowLabeled::PlotWindowLabeled(wxWindow* parent, wxWindowID id,
				     const wxPoint& pos, 
				     const wxSize& size, 
				     int flags,
				     const wxString& label,
				     const wxPoint& label_pos,
				     const wxSize& label_size,
				     long label_style, 
				     wxWindowID plotwin_id) :
  wxPanel(parent, id, pos),
  m_label(new wxStaticText(this, -1, label, label_pos, label_size,
			   label_style)),
  m_plot_window(new wxPlotWindow(this, plotwin_id, pos, size, flags)),
  m_context_menu(new wxMenu(label, wxMENU_TEAROFF))
{
  m_plot_window->SetEnlargeAroundWindowCentre( TRUE );
  SetSize(size.GetWidth(), size.GetHeight()+GetCharHeight());
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
  vbox->Add(m_label,0,wxALIGN_CENTER);
  vbox->Add(m_plot_window,1,wxGROW);
  vbox->Layout();
  SetSizer(vbox);
  SetAutoLayout(TRUE);
  vbox->SetSizeHints( this );
  SetBackgroundColour(wxColour("WHITE"));
  m_label->SetBackgroundColour(wxColour("WHITE"));
  Refresh();

  // Set the context menu

  m_context_menu->Append(ID_MENU_CLEAR_GRAPH, "Clear", "Clear graph");

}

wxStaticText* PlotWindowLabeled::get_the_label()
{
  return m_label;
}

wxPlotWindow* PlotWindowLabeled::get_plot_window()
{
  return m_plot_window;
}

void PlotWindowLabeled::refresh_plot_window()
{
  get_plot_window()->SetZoom( get_plot_window()->GetZoom() );
  //  get_plot_window()->RedrawEverything();

  int xend,y;
  get_plot_window()->GetVirtualSize(&xend,&y);
  int xUnit;
  get_plot_window()->GetScrollPixelsPerUnit(&xUnit,&y);
  int x=xend/xUnit; // x size in scroll units
  get_plot_window()->Scroll(x, -1);
}

void PlotWindowLabeled::OnRightButtonDown(wxMouseEvent& event)
{
  PopupMenu(m_context_menu, event.GetPosition());
}

void PlotWindowLabeled::OnClear(wxCommandEvent& event)
{
  DataPlotCurve* curve=(DataPlotCurve*) get_plot_window()->GetCurrent();
  curve->clear_data();
  refresh_plot_window();
}
