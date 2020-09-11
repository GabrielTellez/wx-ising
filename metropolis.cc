/////////////////////////////////////////////
//
//  Metropolis algorithm implementation
//
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "metropolis.hh"

////////////////////////////////////////////
//
//  Class generic metropolis algorithm
//

template<class TypeContent>
metropolis<TypeContent>::metropolis(basic_lattice<TypeContent>* lattice, 
		       double beta_value) :
  p_lattice(lattice),
  current_site(0),
  beta(beta_value),
  m_energy(0)
{
  srand(time(0)); // Seed random number generator with current time. 
}

template<class TypeContent>
void metropolis<TypeContent>::set_temperature(double new_beta)
{
  beta=new_beta;
  //  update_all();
}

template<class TypeContent>
void metropolis<TypeContent>::update_all()
{
  total_energy();
}


template<class TypeContent>
double metropolis<TypeContent>::get_temperature()
{
  return beta;
}

template<class TypeContent>
bool metropolis<TypeContent>::one_step()
{
  int site=current_site;
  return one_step(site);
}

template<class TypeContent>
bool metropolis<TypeContent>::one_step(int site)
{
  // One Metropolis Monte Carlo step
  // Returns: true if "spin" changed, false otherwise

  double change_in_energy=energy_change(site);
  current_site=(site+1)%(p_lattice->get_number_elements());

  if(p_lattice->get_boundary_conditions()==fixed_bc) {
    vector<basic_ising_spin*> neighbours;
    if (p_lattice->get_neighbours(site, neighbours)!=2*p_lattice->get_dimension()) {
      // Site on the boundary and fixed boundary conditions: no change
      return false;
    }
  }

  if (change_in_energy>0) {
    double randnum = double(rand())/double(RAND_MAX);
    if(randnum>(double)exp(-beta*change_in_energy)) {
      return false;
    } else {
      do_change(site);
      return true;
    }
  } else {
    do_change(site);
    return true;
  }
}

template<class TypeContent>
void metropolis<TypeContent>::one_run(int start_site)
{
  int number_sites=p_lattice->get_number_elements();
  for (int i=1;i<=number_sites;i++) {
    one_step();
  }
}

/* Pure Virtual
template<class TypeContent>
void metropolis<TypeContent>::do_change(int site) {}


template<class TypeContent>
double metropolis<TypeContent>::total_energy() {return 0;}

template<class TypeContent>
double metropolis<TypeContent>::energy_change(int site) { return 0;}
*/

/////////////////////////////////////////////////////
//
//  Class metropolis algorithm for ising spins
//

metropolis_ising::metropolis_ising(basic_lattice<basic_ising_spin*>* lattice,
				   double beta_value, 
				   double coupling) :
  metropolis<basic_ising_spin*>(lattice, beta_value),
  J(coupling)
{
  total_energy();
  total_spin();
}

void metropolis_ising::set_coupling(double J_val)
{
  J=J_val;
  update_all();
}

void metropolis_ising::update_all()
{
  total_energy();
  total_spin();
}

double metropolis_ising::get_coupling()
{
  return J;
}

double metropolis_ising::energy_change(int site)
{
  return double(2.0)*J*get_nearfield(site)*double((*p_lattice)[site]->get_value());
}

int metropolis_ising::total_spin()
{
  m_total_spin=0;
  int number_sites=p_lattice->get_number_elements();
  for (int i=0;i<number_sites;i++) {
    m_total_spin+=(*p_lattice)[i]->get_value();
  }
  return m_total_spin;
}

void metropolis_ising::do_change(int site)
{
  m_energy+=energy_change(site);
  m_total_spin+=-2*(*p_lattice)[site]->get_value();
  (*p_lattice)[site]->flip();
}

double metropolis_ising::total_energy()
{
  // computes total energy:
  // E= -J sum<i,j> S_i S_j 

  m_energy=0;
  int number_sites=p_lattice->get_number_elements();
  for (int i=0;i<number_sites;i++) {
    m_energy+=double(((*p_lattice)[i]->get_value()))*get_nearfield(i);
  }
  m_energy=-J*m_energy/2.0;
  // divided by 2.0 because we counted twice the terms <i,j>
  return m_energy;
}

double metropolis_ising::get_nearfield(int site)
{
  double near_field=0;
  vector<basic_ising_spin*> neighbours;
  int tot_neighbours=p_lattice->get_neighbours(site, neighbours);
  for(int i=0;i<tot_neighbours;i++) {
    near_field+=double(neighbours[i]->get_value());
  }
  return near_field;
}

