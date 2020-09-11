#include "basic-lattice.hh"

template <class TypeContent>
inline basic_lattice<TypeContent>::basic_lattice() :
  m_lattice(),
  m_dimension(1),
  m_dimensions(1,1) ,
  m_boundary_conditions(periodic)
{}

template <class TypeContent>
inline basic_lattice<TypeContent>::basic_lattice(int dimension, 
						 vector<int> dimensions, 
						 boundary_conditions_type bc) :
  m_lattice(),
  m_dimension(dimension),
  m_dimensions(dimensions),
  m_boundary_conditions(bc)
{
  if((get_dimensions().end()-get_dimensions().begin())>m_dimension) {
    cerr << "basic_lattice::basic_lattice(): Lattice incorrectly initialized. Using default lattice: 1D, one site\n";
    vector<int> tmp(1,1);
    set_dimensions(tmp);
  } 
  m_lattice.reserve(get_number_elements());
}


template <class TypeContent>
inline 
void basic_lattice<TypeContent>::set_dimensions(vector<int> dimensions)
{
  m_dimensions=dimensions;
  m_dimension=m_dimensions.end()-m_dimensions.begin();
}

template <class TypeContent>
inline vector<int> basic_lattice<TypeContent>::get_dimensions()
{ return m_dimensions; }

template <class TypeContent>
inline int basic_lattice<TypeContent>::get_dimension()
{ return m_dimension; }

template <class TypeContent>
inline int basic_lattice<TypeContent>::get_number_elements()
{
  int res=1;
  for(int i=0;i<m_dimension;i++) {
    res=res*(get_dimensions()[i]);
  }
  return res;
}

template <class TypeContent>
inline 
void basic_lattice<TypeContent>::set_boundary_conditions(boundary_conditions_type bc)
{
  m_boundary_conditions=bc;
}

template <class TypeContent>
inline 
boundary_conditions_type basic_lattice<TypeContent>::get_boundary_conditions()
{
  return m_boundary_conditions;
}

template <class TypeContent>
inline
vector<int> basic_lattice<TypeContent>::get_coordinates(int site_number)
{
  // return a vector with m_dimension elements: 
  // the cartesian coordinates for the site number site_number
  
  vector<int> coordinates;

  if((site_number>=get_number_elements())||(site_number<0)){
    cerr << "basic_lattice::get_coordinates("<< site_number <<"): site number out of bounds: returning uninitialized coordinates vector\n";
    return coordinates;
  }

  int site_rest=site_number;
  for(int i=0;i<m_dimension;i++) {
    int dime=get_dimensions()[i];
    coordinates.push_back(site_rest%dime);
    site_rest=site_rest/dime;
  }
  return coordinates;
}

template <class ContentType>
inline
int basic_lattice<ContentType>::get_site_number(vector<int> coordinates)
{
  if((coordinates.end()-coordinates.begin())!=m_dimension) {
    cerr << "basic_lattice::get_site_number: incorrect number of coordinates\n";
    return -1;
  }
  int site_num=0;
  for (int i=m_dimension-1;i>=0;i--) {
    if((coordinates[i]>=get_dimensions()[i])||(coordinates[i]<0)) {
      cerr<<"basic_lattice::get_site_number: coordinates["<<i<<"]="
	  << coordinates[i] << ">=" <<get_dimensions()[i]<<endl;
      return -1;
    }
    int the_dims=1;
    if (i>0) {
      the_dims=get_dimensions()[i-1];
    }
    site_num=(coordinates[i]+site_num)*the_dims;
  }
  return site_num;
}

template <class TypeContent>
inline
TypeContent basic_lattice<TypeContent>::operator[] (int site_number)
{
  if((site_number>=get_number_elements())||(site_number<0)){
    cerr << "basic_lattice::operator("<< site_number <<"): site number out of bounds: returning first site\n";
    return m_lattice[0];
  }
  return m_lattice[site_number]; 
}

template <class TypeContent>
inline
TypeContent basic_lattice<TypeContent>::operator[] (vector<int> coordinates)
{
  return operator[](get_site_number(coordinates));
}


template <class TypeContent>
inline 
int 
basic_lattice<TypeContent>::get_neighbours(vector<int> coordinates,
					   vector<TypeContent>& the_neighbours)
{
  // returns the number of neighbours
  // neighbours: vector with iterators to the neighbours

  vector<TypeContent> neighbours;

  if((coordinates.end()-coordinates.begin())!=m_dimension) {
    cerr << "basic_lattice::get_neighbours(vector<int>): incorrect number of coordinates\n";
    return 0;
  }
  int num_neigh=0;

  for(int i=0;i<m_dimension;i++) {

    if((coordinates[i]>=get_dimensions()[i])||(coordinates[i]<0)) {
      cerr<<"basic_lattice::get_neighbours: coordinates["<<i<<"]="
	  << coordinates[i] << ">=" <<get_dimensions()[i]<<endl;
      return 0;
    }
     
    for(int plusminus=-1;plusminus<=1;plusminus+=2) {
      vector<int> neigh_coordinates=coordinates;
      neigh_coordinates[i]+=plusminus;
      if(get_boundary_conditions()==periodic) {
	neigh_coordinates[i]=(neigh_coordinates[i])%(get_dimensions()[i]);
	if(neigh_coordinates[i]==-1) {
	  neigh_coordinates[i]=get_dimensions()[i]-1;
	}
	num_neigh++;
	neighbours.push_back(operator[](neigh_coordinates));	    
      } else {
	if((neigh_coordinates[i]<get_dimensions()[i])
	   &&(neigh_coordinates[i]>=0)) {
	  num_neigh++;
	  neighbours.push_back(operator[](neigh_coordinates));	    
	}
	
      }
    }
  }
  the_neighbours=neighbours;
  return num_neigh;
}

template <class TypeContent>
inline 
int 
basic_lattice<TypeContent>::get_neighbours(int site_number,
					   vector<TypeContent>& the_neighbours)
{
  return get_neighbours(get_coordinates(site_number), the_neighbours);
}

template <class TypeContent>
inline 
void
basic_lattice<TypeContent>::push_back(TypeContent object)
{
  m_lattice.push_back(object);
}

template <class TypeContent>
inline
vector<TypeContent>* basic_lattice<TypeContent>::get_lattice_vector()
{
  return &m_lattice;
}


