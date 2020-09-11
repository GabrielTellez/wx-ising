#ifndef __GT_WX_LATTICE_H
#define __GT_WX_LATTICE_H
#include "wx-spin.hh"
#include "basic-lattice.hh"
#include "wx-table-sizer.hh"

class lattice_wx : public basic_lattice<ising_spin_wx*>
{
protected:
  table_wx* mp_table;
  wxWindow* m_parent;

public:
  lattice_wx(wxWindow* parent, table_wx* p_table, vector<int> dims, 
	     const wxString& tooltip=wxEmptyString,
	     boundary_conditions_type bc=periodic);
  lattice_wx(wxWindow* parent, table_wx* p_table, int x=4, int y=5,
	     const wxString& tooltip=wxEmptyString,
	     boundary_conditions_type bc=periodic);
  ~lattice_wx();
  void fill_init_lattice(const wxString& tooltip=wxEmptyString);
  void randomize_lattice();
  void sync_table();
};


#endif

