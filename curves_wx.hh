#ifndef __GT_CURVES_WX
#define __GT_CURVES_WX

#include <vector.h>
#include <wx/pen.h>
#include <wx/plot.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/menu.h>

enum
{
  ID_MENU_CLEAR_GRAPH=wxID_HIGHEST+100
};


class DataPlotCurve : public wxPlotCurve
{
public:
  DataPlotCurve(int offsetY, double startY, double endY);
  
  virtual wxInt32 GetStartX();
  virtual wxInt32 GetEndX();
  virtual double GetY( wxInt32 x );

  void push_back(double data);
  void clear_data();

protected:
  int m_currentX;
  vector<double> m_data;
  
};


class PlotWindowLabeled : public wxPanel
{
public:
  PlotWindowLabeled(wxWindow* parent, wxWindowID id,
		    const wxPoint& pos=wxDefaultPosition, 
		    const wxSize& size = wxDefaultSize, 
		    int flags=wxPLOT_DEFAULT,
		    const wxString& label=wxEmptyString,
		    const wxPoint& label_pos=wxPoint(-1,-1),
		    const wxSize& label_size = wxDefaultSize, 
		    long label_style = 0, wxWindowID plotwin_id=-1) ;
  wxStaticText* get_the_label();
  wxPlotWindow* get_plot_window();
  void refresh_plot_window();
  void OnRightButtonDown(wxMouseEvent& event);
  void OnClear(wxCommandEvent& event);

protected:
  wxStaticText* m_label;
  wxPlotWindow* m_plot_window;
  wxMenu* m_context_menu;
private:
  DECLARE_EVENT_TABLE()
};
  
BEGIN_EVENT_TABLE(PlotWindowLabeled, wxPanel)
  EVT_RIGHT_DOWN(PlotWindowLabeled::OnRightButtonDown)
  EVT_MENU(ID_MENU_CLEAR_GRAPH, PlotWindowLabeled::OnClear)
END_EVENT_TABLE()


#endif
