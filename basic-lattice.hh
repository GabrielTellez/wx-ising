#ifndef __BASIC_LATTICE_H
#define __BASIC_LATTICE_H
#include <iostream.h>
#include <vector.h>


enum boundary_conditions_type 
{
  periodic=0,
  fixed_bc=1,
  free_bc=2
};


template <class TypeContent>
class basic_lattice 
{
protected:
  vector<TypeContent> m_lattice; // the lattice
  int m_dimension;               // number of dimensions 1D, 2D, 3D, etc...
  vector<int> m_dimensions;      // actual dimensions: width, height, etc...
  boundary_conditions_type  m_boundary_conditions;

public:
  basic_lattice();
  basic_lattice(int dimension, vector<int> dimensions, 
		boundary_conditions_type bc);
  ~basic_lattice() {};
public:
  void set_dimensions(vector<int> dimensions);
  vector<int> get_dimensions();
  int get_dimension();
  int get_number_elements();
  int get_neighbours(int site_number, 
		     vector<TypeContent>& neighbours);
  int get_neighbours(vector<int> coordinates,
		     vector<TypeContent>& neighbours);
  void set_boundary_conditions(boundary_conditions_type bc);
  boundary_conditions_type get_boundary_conditions();
  vector<int> get_coordinates(int site_number);
  int get_site_number(vector<int> coordinates);
  TypeContent operator[] (int site_num); 
  // returns contents of site number: site_num 
  TypeContent operator[] (vector<int> coordinates); 
  // returns content of site with coordinates vector<int> coordinates
  void push_back(TypeContent object);
  vector<TypeContent>* get_lattice_vector(); 
};

#endif

