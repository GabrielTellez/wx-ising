#ifndef __SPIN_H
#define __SPIN_H
template<class SpinType>
class basic_spin 
{
private:
  SpinType m_spin;
public:
  basic_spin();
  basic_spin(SpinType spin);
  virtual  ~basic_spin();
  virtual SpinType get_value() { return m_spin; }
  virtual bool set_value(SpinType spin);
  virtual bool sanity_check(SpinType spin) {return true;}
  // returns true if spin is between bounds, false otherwise;
  virtual SpinType default_value() { return 0;}
  // return default value for spins
};

class basic_ising_spin : public basic_spin<int>
{
public:
  basic_ising_spin(int spin);
  basic_ising_spin();
  virtual void flip();
  virtual bool sanity_check(int spin); // returns 1 if spin is between bounds,
                                       // 0 otherwise;
  virtual int default_value();
};


#endif
