#include "spin.hh"

//////////////////////////////////////////
//
//   basic_spin class implementation
//

template<class SpinType>
inline
basic_spin<SpinType>::basic_spin() 
{}


template<class SpinType>
inline
basic_spin<SpinType>::basic_spin(SpinType spin) :
    m_spin(spin)
{
  if(!sanity_check(get_value())) {
    set_value(default_value());
  }
}

template<class SpinType>
inline
basic_spin<SpinType>::~basic_spin() {}

template<class SpinType>
inline
bool basic_spin<SpinType>::set_value(SpinType spin)
{
  if(sanity_check(spin)) {
    m_spin=spin;
    return true;  // OK: changed
  } else {
    return false;  // not OK: not changed
  }
}

////////////////////////////////////////////////
//
//  basic_ising_spin class implementation
//

inline
basic_ising_spin::basic_ising_spin(int spin) :
  basic_spin<int>(spin)
{
  if(!sanity_check(get_value())){
    set_value(default_value());
  }
}

inline
basic_ising_spin::basic_ising_spin() :
  basic_spin<int>(1)
{}

inline
void basic_ising_spin::flip() 
{ 
  set_value(-get_value()); 
}

inline
bool basic_ising_spin::sanity_check(int spin)
{
  return ((spin==1)||(spin==-1));
}

inline
int basic_ising_spin::default_value()
{
  // return default value for spins
  return 1;
}




