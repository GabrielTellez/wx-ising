#include "wx-lattice.hh"
#include "button_ids.h"
#include <stdlib.h>
#include <time.h>

lattice_wx::~lattice_wx()
{
  vector<ising_spin_wx*>::iterator ite_begin=get_lattice_vector()->begin();
  vector<ising_spin_wx*>::iterator ite_end=get_lattice_vector()->end()  ;
  while(ite_end!=ite_begin){
    (*ite_begin)->get_button()->Destroy();
    delete *ite_begin;
    ite_begin++;
  }
}

lattice_wx::lattice_wx(wxWindow* parent,
		       table_wx* p_table, vector<int> dims, 
		       const wxString& tooltip,
		       boundary_conditions_type bc) :
  basic_lattice<ising_spin_wx*>(2,dims,bc),
  mp_table(p_table),
  m_parent(parent)
{
  sync_table();
  fill_init_lattice();
  randomize_lattice();
}

lattice_wx::lattice_wx(wxWindow* parent,
		       table_wx* p_table, int x, int y,
		       const wxString& tooltip,
		       boundary_conditions_type bc) :
  basic_lattice<ising_spin_wx*>(),
  mp_table(p_table),
  m_parent(parent)
{
  vector<int> dims(1,x);
  dims.push_back(y);
  set_dimensions(dims);
  set_boundary_conditions(bc);
  sync_table();
  fill_init_lattice(tooltip);
  randomize_lattice();
}
void lattice_wx::randomize_lattice()
{
  srand(time(0));
  int tot_sites=get_number_elements();
  for(int i=0;i<tot_sites;i++) {
    if(double(rand())/double(RAND_MAX)>0.5) {
      operator[](i)->flip();
    }
  }
}

void lattice_wx::fill_init_lattice(const wxString& tooltip)
{
  int current_button_id = ID_BUTTON_BASE;
  for(int y=0;y<get_dimensions()[1];y++) {
    for(int x=0;x<get_dimensions()[0];x++) {      
      vector<int> coordinates;
      coordinates.push_back(x);
      coordinates.push_back(y);
      
      push_back(new ising_spin_wx(m_parent, current_button_id, tooltip));
      current_button_id++;
      mp_table->push_back((operator[](coordinates))->get_button());
    }
  }
}

void lattice_wx::sync_table()
{
  if(!(mp_table->resize(get_dimensions()[0],get_dimensions()[1]))) {
    cerr << "lattice_wx::sync_table(): couldn't resize the table \n";
  }
}
