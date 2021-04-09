
#include "zlasdtest/test.hpp"
#include "vector/vector.hpp"
#include "list/list.hpp"
#include "zmytest/test.hpp"
/* ************************************************************************** */

#include <iostream>
using namespace lasd;
/* **************************************************************************
void FoldAdd(const double& dat, const void* _, void* acc) {
  *((double*) acc) += dat;
}
*/

int main()
{
  int scelta = - 1;
  while(scelta != 0)
  {
    std::cout << "Ciao Benevenuto nel ES1 - Guarracino Carmine - Matricola: N86003420" << std::endl;
    std::cout << "1)Test Professore Mogavero Fabio" << std::endl;
    std::cout << "2)Menu utente" << std::endl;
    std::cout << "0) Per uscire dal programma" << std::endl;
    std::cin  >> scelta;
    if(scelta == 1)
      lasdtest();
    if(scelta == 2)
      Menu();
  }


  return 0;
}
