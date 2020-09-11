#include "monte-carlo.hh"

IMPLEMENT_APP(MonteCarloApp)

bool MonteCarloApp::OnInit()
{
  MainFrame *frame = new MainFrame( "Ising Metropolis Monte Carlo simulation", wxPoint(50,50), wxSize(450,340) );
  frame->Show( TRUE );
  SetTopWindow( frame );
  return TRUE;
}

// MainFrame constructor ctor

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
  wxFrame((wxFrame *)NULL, -1, title, pos, size),
  mainpanel(new wxPanel(this,-1)),
  table(new table_wx(10,10)),
  lattice(new lattice_wx(mainpanel, table, 10, 10, 
			 "Push button to flip spin")),
  metropolis_algo(new metropolis_ising((basic_lattice<basic_ising_spin*>*)
				       lattice,0.5,1.0)),
  is_running(false),
  is_fast(false),
  frm_txt_spin(mainpanel,"Spin","               "),
  frm_txt_energy(mainpanel,"Energy","               "),
  choice_temp(new spinctrl_txt_wx(mainpanel,ID_CHOICE_TEMP,
				  "100*Beta=",
				  50,0,1000, 
				  "Set the inverse temperature beta")),
  choice_coupling(new spinctrl_txt_wx(mainpanel,ID_CHOICE_J,
				      "100*J=",
				      100,-500,500, 
				      "Set the coupling constant J")),
  m_energy_curve(new DataPlotCurve( 0,  -200, 200 )),
  m_spin_curve(new DataPlotCurve( 0,  -200, 200 )),
  plotwin_energy(new PlotWindowLabeled(mainpanel, -1,
				       wxPoint(-1,-1), wxSize(-1,-1), 
				       wxPLOT_DEFAULT,
				       "Energy")),
  plotwin_spin(new PlotWindowLabeled(mainpanel, -1, 
				       wxPoint(-1,-1), wxSize(-1,-1), 
				       wxPLOT_DEFAULT,
				       "Total Spin"))
{
  // Icon
  SetIcon(wxICON(logo));

  // Menu

  wxMenu *menuFile = new wxMenu;
  menuFile->Append( ID_New, "&New\tAlt-N", "Start new simulation" );  
  menuFile->Append( ID_Quit, "E&xit\tAlt-X", "Quit the application" );  

  //  menuFile->AppendSeparator();

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append( ID_About, "&About...\tCtrl-A", "Copyright notice" );
  
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append( menuFile, "&File" );
  menuBar->Append( menuHelp, "&Help" );
  
  SetMenuBar( menuBar );

  // Status bar
  
  CreateStatusBar();
  SetStatusText( "Ising Metropolis simulation" );

  // Toolbar

  wxToolBar* toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL );
  toolbar->SetMargins( 4, 4 );
  toolbar->SetToolBitmapSize(wxSize(20,20));
  wxBitmap start_bitmap(wxBITMAP(start));
  wxBitmap stop_bitmap(wxBITMAP(stop));
  int currentX=5;
  int width=20;
  toolbar->AddTool(ID_StartStop, start_bitmap, stop_bitmap, TRUE, currentX, -1,
		   (wxObject*) NULL, "Start/Stop", 
		   "Starts or stops the simulation");
  wxBitmap fast_bitmap(wxBITMAP(fast));
  wxBitmap slow_bitmap(wxBITMAP(slow));
  currentX+=width+5;
  toolbar->AddTool(ID_FastSlow, slow_bitmap, fast_bitmap, TRUE, currentX, -1,
		   (wxObject*) NULL, "Fast/Slow", 
		   "Run the simulation faster or slower: do one run or step each time");

#ifdef __GT_USE_TOOLBAR__
  wxString choices_str[]={ "Periodic", "Fixed", "Free" };
  StatusChoice_wx *choice_bc = 
    new StatusChoice_wx(toolbar, ID_CHOICE_BC,
			wxPoint(-1,-1), 
			wxSize(-1,-1),
			3, choices_str,
			"Set boundary conditions type");
  choice_bc->SetSelection(0);
  toolbar->AddControl(choice_bc);

#endif // use toolbar
  toolbar->Realize();

  // Main Panel

  wxBoxSizer* topsizer = new wxBoxSizer (wxHORIZONTAL);
  wxBoxSizer* vbox = new wxBoxSizer (wxVERTICAL);
#ifndef __GT_USE_TOOLBAR__
  // Boundary Conditions choice in panel
  wxString choices_str[]={ "Periodic", "Fixed", "Free" };
  StatusChoice_wx *choice_bc = 
    new StatusChoice_wx(mainpanel, ID_CHOICE_BC,
			wxPoint(-1,-1), 
			wxSize(-1,-1),
			3, choices_str,
			"Set boundary conditions type");
  choice_bc->SetSelection(0);
  vbox->Add(choice_bc,0,wxGROW);
#endif // don't use_toolbar
  vbox->Add(choice_temp,0,wxGROW);
  vbox->Add(choice_coupling,0,wxGROW);

  vbox->Add(frm_txt_spin.get_sizer(),0,wxGROW);  
  vbox->Add(frm_txt_energy.get_sizer(),0,wxGROW);  

  topsizer->Add(vbox,0,wxGROW);
  topsizer->Add(table,1,wxGROW);
  
  wxBoxSizer* topvbox = new wxBoxSizer (wxVERTICAL);

  // Show energy and spin
  plotwin_energy->get_plot_window()->SetScrollOnThumbRelease( TRUE );
  plotwin_energy->get_plot_window()->Add(m_energy_curve);
  plotwin_energy->get_plot_window()->SetZoom(1.0/8.0);
  plotwin_spin->get_plot_window()->SetScrollOnThumbRelease( TRUE );
  plotwin_spin->get_plot_window()->Add(m_spin_curve);
  plotwin_spin->get_plot_window()->SetZoom(1.0/8.0);

  wxBoxSizer* hbox_energy_spin = new wxBoxSizer (wxHORIZONTAL);

  hbox_energy_spin->Add(plotwin_energy,1,wxGROW); 
  //  hbox_energy_spin->Fit(plotwin_energy);
  hbox_energy_spin->Add(plotwin_spin,1,wxGROW);  
  //  hbox_energy_spin->Fit(plotwin_spin);

  topvbox->Add(topsizer,1,wxGROW);
  topvbox->Add(hbox_energy_spin,1,wxGROW);

  mainpanel->SetAutoLayout( TRUE );
  mainpanel->SetSizer( topvbox );
  //  mainpanel->Fit( );
  topvbox->Fit( mainpanel );
  //topvbox->SetSizeHints( mainpanel );

  metropolis_algo->update_all();
  update_energy_spin_labels();

  Fit();
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close( TRUE );
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox( "Monte Carlo simulation of Ising spins using Metropolis algorithm\n (c) April 2000 Gabriel Tellez",
		"About Monte Carlo", wxOK | wxICON_INFORMATION );
}

void MainFrame::OnButtonPressed(wxCommandEvent& event)
{
  int button_number=event.m_id - ID_BUTTON_BASE;
  //  cout << "Button " << button_number << " pressed.\n";
  (*lattice)[button_number]->flip();
  metropolis_algo->update_all();
  update_energy_spin_labels();

  //    vector<ising_spin_wx*> neighbours;
  //    int num_neigh=lattice->get_neighbours(button_number,neighbours);
  //    for(int i=0;i<num_neigh;i++) {
  //      neighbours[i]->flip();
  //    }

}

void MainFrame::OnIdle(wxIdleEvent& event)
{
  wxFrame::OnIdle(event);
  if(is_running) {
    if(is_fast) {
      metropolis_algo->one_run();
    } else {
      metropolis_algo->one_step();
    }
    update_energy_spin_labels();
    wxWakeUpIdle();
  }
}

void MainFrame::OnStartStop(wxCommandEvent& event)
{
  is_running=!is_running;
}

void MainFrame::OnFastSlow(wxCommandEvent& event)
{
  is_fast=!is_fast;
}

void MainFrame::OnChoiceBC(wxCommandEvent& event)
{
  lattice->set_boundary_conditions(boundary_conditions_type(event.GetSelection()));
  metropolis_algo->update_all();
  update_energy_spin_labels();
}

void MainFrame::update_energy_spin_labels()
{
  // updates labels

  wxString str; 
  str << metropolis_algo->m_total_spin ;
  frm_txt_spin.set_text(str);
  wxString strene;
  strene << metropolis_algo->m_energy ;
  frm_txt_energy.set_text(strene);

  // update curves
  m_energy_curve->push_back( metropolis_algo->m_energy );
  m_spin_curve->push_back(double(metropolis_algo->m_total_spin));
  plotwin_energy->refresh_plot_window();
  plotwin_spin->refresh_plot_window();
}

void MainFrame::OnChoiceJ(wxScrollEvent& event)
{
  metropolis_algo->set_coupling(double(choice_coupling->get_value())/100.0);
  update_energy_spin_labels();
}

void MainFrame::OnChoiceTemp(wxScrollEvent& event)
{
  metropolis_algo->set_temperature(double(choice_temp->get_value())/100.0);
}

void MainFrame::OnNew(wxCommandEvent& event)
{
  vector<int> dims=lattice->get_dimensions();
  NewDialog* new_dialog = new NewDialog(this, -1,
					"New Simulation",
					dims[0], dims[1],
					wxPoint(100, 100),
					wxDefaultSize,
					wxDIALOG_MODAL |  
					wxDEFAULT_DIALOG_STYLE,
					"New Dialog");
  //  new_dialog->Centre();
  if( new_dialog->ShowModal() == wxID_OK ) {
    int x=new_dialog->x_size->get_value();
    int y=new_dialog->y_size->get_value();
    table->re_init(x, y);
    boundary_conditions_type bc=lattice->get_boundary_conditions();
    double Jcoupling=metropolis_algo->get_coupling();
    double beta=metropolis_algo->get_temperature();
    delete lattice;
    delete metropolis_algo;
    lattice = new lattice_wx(mainpanel, table, x, y, 
			     "Push button to flip spin",bc);
    metropolis_algo=new metropolis_ising((basic_lattice<basic_ising_spin*>*)
					 lattice, beta, Jcoupling);
    table->Layout();
    wxCommandEvent event;
    plotwin_energy->OnClear(event);
    plotwin_spin->OnClear(event);
    Layout();
  } 
}
