////////////////////////////////////////
//
//  Metropolis algorithm
//

#ifndef __METROPOLIS_HH
#define __METROPOLIS_HH
#include "basic-lattice.hh"


////////////////////////////////////////////
//
//  Class generic metropolis algorithm
//

template<class TypeContent>
class metropolis
{
  // variables
public:
  basic_lattice<TypeContent>* p_lattice;
  int current_site;
  double beta;
  double m_energy;

  // methods
public:
  metropolis(basic_lattice<TypeContent>* lattice, double beta_value);
  virtual ~metropolis() {}
  bool one_step(int site);
  bool one_step();
  virtual void do_change(int site)=0;
  void one_run(int start_site=0);
  virtual double total_energy()=0;
  virtual double energy_change(int site)=0;
  void set_temperature(double new_beta);
  double get_temperature();
  virtual void update_all();
};

/////////////////////////////////////////////////////
//
//  Class metropolis algorithm for ising spins
//

#include "spin.hh"

class metropolis_ising : public metropolis<basic_ising_spin*>
{
public:
  double J; // coupling constant
  int m_total_spin;
public:
  metropolis_ising(basic_lattice<basic_ising_spin*>* lattice, 
		   double beta_value, 
		   double coupling);
  void set_coupling(double J_val);
  double get_coupling();
  virtual double energy_change(int site);
  virtual void do_change(int site);
  virtual double total_energy();
  int total_spin();
  virtual void update_all();
  double get_nearfield(int site);
};

#endif
