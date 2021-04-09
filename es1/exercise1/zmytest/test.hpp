
#ifndef ZMYTEST_HPP
#define ZMYTEST_HPP
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../container/container.hpp"

namespace lasd
{
  void Menu();

  //Parte vettori
  template<typename Data>
  void riempi(Vector<Data>& v);
  void riempi(Vector<std::string>& v);

  template<typename Data>
  Data& getIndexOf(Vector<Data>& v, int index);


  //Parte liste
  template<typename Data>
  void riempi(List<Data>& list, int dim);

  void riempi(List<std::string>& list, int dim);
}

#endif
