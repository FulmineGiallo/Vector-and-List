#include <iostream>
#include <string.h>
#include <string>
#include <typeinfo>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../container/container.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>    // std::shuffle

namespace lasd
{

    std::string chars {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
    std::random_device rd;
    std::mt19937 generator(rd());
    std::string rand_str (int length)
    {
      std::string output (chars);
      std::shuffle(output.begin(), output.end(), generator);
      return output.substr(0, length);
    }

    //CONTROLLARE
  template<typename Data>
  Data getIndexOf(Vector<Data>& v, int index)
  {
    return v[index];
  }

  void riempi(Vector<std::string>& v)
  {
       for(unsigned int i=0; i < v.Size(); i++)
       {
         v[i] =  rand_str(v.Size());
       }
  }
  template<typename Data>
  void riempi(Vector<Data>& v)
  {
    Data dataRandom;
    srand ((unsigned int)time(NULL));
    std::string type_name();

    for(unsigned int i = 0; i < v.Size(); i++)
    {
       dataRandom = (Data)rand() / 100 + 1;
       v[i] = dataRandom;

       if(typeid(v[0]).name() == "d")
       {
         v[i] = trunc(dataRandom);
       }
    }
  }

  template<typename Data>
  void riempi(List<Data>& list, int dim)
  {
    Data dataRandom;
    srand ((unsigned int)time(NULL));

    for(unsigned int i = 0; i < dim; i++)
    {
       dataRandom = (Data)rand() / 100 + 1;
       list.InsertAtBack(dataRandom);
    }
  }

  void riempi(List<std::string>& list, int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
      list.InsertAtBack(rand_str(dim - 1));
    }
  }

  void Menu()
  {
        int scelta, type = 0;
        int index = 0;
        int x = -1;
        int n = 0; //dimensione struttura

        //Scelta struttura da utilizzare Lista o Vettore
        std::cout << "Benvenuto Utente, ti trovi nel esercizio 1 di - LASD" << std::endl;

        std::cout << "Scegli una struttura da utillizzare: " << std::endl << "1) Vettore" << std::endl << "2) Lista" << std::endl;
        std::cin  >>  scelta;
        std::cout << "Che tipo di dati vuoi utilizzare? "<< std::endl << "1) Int" << std::endl << "2) Double" << std::endl << "3) Float" << std::endl << "4) String" << std::endl;
        std::cin  >> type;
        std::cout << "Inserisci la sua dimensione " << std::endl;
        std::cin  >> n;

        Vector<int>         v1(n);
        Vector<double>      v2(n);
        Vector<float>       v3(n);
        Vector<std::string> v4(n);
        List<int>           l1;
        List<double>        l2;
        List<float>         l3;
        List<std::string>   l4;

        if( scelta == 1) // Scelta Vettore
        {
          if(type == 1) // INT
          {
              riempi(v1);
          }
          if(type == 2)// DOUBLE
          {
              riempi(v2);
          }
          if(type == 3)// FLOAT
          {
              riempi(v3);
          }
          if(type == 4)// STRING
          {
              riempi(v4);
          }
        }
        if( scelta == 2) // Scelta Lista
        {
          if(type == 1) // INT
          {
              riempi(l1, n);
          }
          if(type == 2)// DOUBLE
          {
              riempi(l2, n);
          }
          if(type == 3)// FLOAT
          {
              riempi(l3, n);
          }
          if(type == 4)// STRING
          {
              riempi(l4, n);
          }
        }

        if( scelta == 1)
          while( x != 0)
          {
            std::cout << "Benvenuto nel menu delle funzioni del vettore, puoi utilizzare le seguenti funzionalità:" << std::endl;
            std::cout << "1)Ottieni il primo elemento" << std::endl;
            std::cout << "2)Ottieni l'elemento in posizione che vuoi" << std::endl;
            std::cout << "3)Ottieni l'ultimo elemento" << std::endl;
            std::cout << "4)Stampa tutto il vettore" << std::endl;
            std::cout << "5)Vuoi cercare un elemento all'interno del vettore?" << std::endl;
            std::cout << "6)Vuoi utilizzare le funzioni FOLD del tuo tipo?" << std::endl;
            std::cout << "7)Funzioni applicabili al tuo tipo: 2n(int), n^2(float), uppercase(string)" << std::endl;
            std::cout << "0)Se vuoi uscire dal programma"<< std::endl;
            std::cin  >> x;

            if(type == 1 && x == 1)
            {
              int first;
              first = v1.Front();
              std::cout<<"Primo elemento[0] =" << first << std::endl;
            }
            if(type == 2 && x == 1)
            {
              double first;
              first = v2.Front();
              std::cout<<"Primo elemento[0] =" << first << std::endl;
            }
            if(type == 3 && x == 1)
            {
              float first;
              first = v3.Front();
              std::cout<<"Primo elemento[0] =" << first << std::endl;
            }
            if(type == 4 && x == 1)
            {
              std::string first;
              first = v4.Front();
              std::cout<<"Primo elemento[0] =" << first << std::endl;
            }
            if(x == 2)
            {
                std::cout << "Inserisci la index da trovare";
                std::cin >> index;
            }
            if(type == 1 && x == 2)
            {
              int first;
              first = getIndexOf(v1,index);
              std::cout<<"Elemento["<<index<<"]"<< "=" << first << std::endl;
            }
            if(type == 2 && x == 2)
            {
              double first;
              first = getIndexOf(v2,index);
              std::cout<<"Elemento["<<index<<"]"<< "=" << first << std::endl;
            }
            if(type == 3 && x == 2)
            {
              float first;
              first = getIndexOf(v3,index);
              std::cout<<"Elemento["<<index<<"]"<< "=" << first << std::endl;
            }
            if(type == 4 && x == 2)
            {
              std::string first;
              first = getIndexOf(v4,index);
              std::cout<<"Elemento["<<index<<"]"<< "=" << first << std::endl;
            }
            if(type == 1 && x == 3)
            {
              int first;
              first = v1.Back();
              std::cout<<"Ultimo elemento["<< v1.Size() - 1 << "=" << first << std::endl;
            }
            if(type == 2 && x == 3)
            {
              double first;
              first = v2.Back();
              std::cout<<"Ultimo elemento["<< v2.Size() - 1 << "=" << first << std::endl;
            }
            if(type == 3 && x == 3)
            {
              float first;
              first = v3.Back();
              std::cout<<"Ultimo elemento["<< v3.Size() - 1 << "=" << first << std::endl;
            }
            if(type == 4 && x == 3)
            {
              std::string first;
              first = v4.Back();
              std::cout<<"Ultimo elemento["<< v4.Size() - 1 << "=" << first << std::endl;
            }
            //PRINT VETTORE
            if(x == 4)
              std::cout << "Ecco il vettore:" << std::endl;
            if(type == 1 && x == 4)
            {
              v1.MapPreOrder([](int& dat, void*){std::cout << dat << std::endl;}, nullptr);
            }
            if(type == 2 && x == 4)
            {
              v2.MapPreOrder([](double& dat, void*){std::cout << dat<< std::endl;}, nullptr);
            }
            if(type == 3 && x == 4)
            {
              v3.MapPreOrder([](float& dat, void*){std::cout << dat<< std::endl;}, nullptr);
            }
            if(type == 4 && x == 4)
            {
              v4.MapPreOrder([](std::string& dat, void*){std::cout << dat<< std::endl;}, nullptr);
            }
            //EXIST ELEMENT
            if(x == 5)
            {
              std::cout << "Che elemento vuoi ricercare all'interno del vettore?" << std::endl;
            }
            bool exist;
            if(type == 1 && x == 5)
            {
              int search_element;
              std::cin  >> search_element;
              exist = v1.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 2 && x == 5)
            {
              double search_element;
              std::cin  >> search_element;
              exist = v2.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 3 && x == 5)
            {
              float search_element;
              std::cin  >> search_element;
              exist = v3.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 4 && x == 5)
            {
              std::string search_element;
              std::cin  >> search_element;
              exist = v4.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            //BEGIN FUNZIONI FOLD VECTOR
            if(type == 1 &&  x == 6)
            {
              std::cout << "1) Somma per gli interi minori di K" << std::endl;
              int k;
              int sum = 0;
              std::cout << "Inserisci K" << std::endl;
              std::cin >> k;
              v1.FoldPreOrder([](const int& dat, const void* k, void* sum)
              {
                if (dat < *((int*)k))
                {
                  *((int*)sum) += dat;
                }
              }, &k, &sum);
              std::cout << "La somma degli interi (minori di " << k << ") e' : " << sum << std::endl;
            }
            if(type == 3 && x == 6)
            {
              float k;
              float prod = 1;
              std::cout << "1) Prodotto per i float maggori di K" << std::endl;
              std::cout << "Inserisci K" << std::endl;
              std::cin  >> k;
              v3.FoldPreOrder([](const float& dat, const void* k, void* prod)
              {
              if (dat > *((float*)k))
                {
                  *((float*)prod) *= dat;
                }
              }, &k, &prod);
              std::cout << "Il prodotto dei float (maggiori di " << k << ") e' : " << prod << std::endl;
            }
            if(type == 4 && x == 6)
            {
              std::string str;
              int k;
              std::cout << "1) Concatena le stringhe con lunghezza minore o uguale a K"<< std::endl;
              std::cout << "Inserisci la stringa" << std::endl;
              std::cin  >> str;
              v4.FoldPreOrder([](const std::string& dat, const void* k, void* str)
              {
                if (dat.size() <= *((int*)k))
                {
                  *((std::string*)str) += dat;
                }
              }, &k, &str);
              std::cout << "Concatenazione delle stringhe (con lunghezza minore o uguale a " << k << ") e' : " << str << std::endl;

            }
            // END FUNZIONI FOLD VECTOR

            //Passo 7)
            if(x == 7 && type == 1)
            {
                v1.MapPreOrder([](int& dat, void*){
                dat=dat*2;
                }, nullptr);
                std::cout << "Funzione 2n (INT) applicata alla tua struttura" << std::endl;
            }
            if( x == 7 && type == 3)
            {
                v3.MapPreOrder([](float& dat, void*){
                dat=dat*dat;
                }, nullptr);
                std::cout << "Funzione n^2 (FLOAT) applicata alla tua struttura" << std::endl;
            }
            if( x == 7 && type == 4)
            {
                v4.MapPreOrder([](std::string& dat, void* _)
                {
                  for (char& c : dat)
                  {
                    c = toupper(c);
                  }
                }, nullptr);
                std::cout << "Funzione uppercase applicata alla struttura" << std::endl;
            }
          }

        if(scelta == 2)
        {
          while( x != 0)
          {
            std::cout << "Benvenuto nel menu delle funzioni della lista, puoi utilizzare le seguenti funzionalità:" << std::endl;
            std::cout << "1)Ottieni il primo elemento" << std::endl;
            std::cout << "2)Ottieni l'elemento in posizione che vuoi" << std::endl;
            std::cout << "3)Ottieni l'ultimo elemento" << std::endl;
            std::cout << "4)Stampa LISTA tramite MAP" << std::endl;
            std::cout << "5)Vuoi cercare un elemento all'interno della lista?" << std::endl;
            std::cout << "6)Vuoi utilizzare le funzioni FOLD del tuo tipo?" << std::endl;
            std::cout << "7)Funzioni applicabili al tuo tipo: 2n(int), n^2(float), uppercase(string)" << std::endl;
            std::cout << "0)Se vuoi uscire dal programma"<< std::endl;
            std::cin  >> x;

            if(type == 1 && x == 1)
            {
              std::cout << l1.Front() << std::endl;
            }
            if(type == 2 && x == 1)
            {
              std::cout << l2.Front() << std::endl;
            }
            if(type == 3 && x == 1)
            {
              std::cout << l3.Front() << std::endl;
            }
            if(type == 4 && x == 1)
            {
              std::cout << l4.Front() << std::endl;
            }

            if(x==2)
            {
              std::cout << "Che posizione vuoi ottenere?" << std::endl;
              std::cin  >> index;
            }
            if(type == 1 && x == 2)
            {
              std::cout << l1[index] << std::endl;
            }
            if(type == 2 && x == 2)
            {
              std::cout << l2[index] << std::endl;
            }
            if(type == 3 && x == 2)
            {
              std::cout << l3[index] << std::endl;
            }
            if(type == 4 && x == 2)
            {
              std::cout << l4[index] << std::endl;
            }

            if(type == 1 && x == 3)
            {
              std::cout << l1.Back() << std::endl;
            }
            if(type == 2 && x == 3)
            {
              std::cout << l2.Back() << std::endl;
            }
            if(type == 3 && x == 3)
            {
              std::cout << l3.Back() << std::endl;
            }
            if(type == 4 && x == 3)
            {
              std::cout << l4.Back() << std::endl;
            }


            if(type == 1 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              l1.MapPreOrder([](int& dat, void*){std::cout << dat << "->" << std::endl;}, nullptr);
            }
            if(type == 2 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              l2.MapPreOrder([](double& dat, void*){std::cout << dat << "->" << std::endl;}, nullptr);
            }
            if(type == 3 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              l3.MapPreOrder([](float& dat, void*){std::cout << dat << "->" << std::endl;}, nullptr);
            }
            if(type == 4 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              l4.MapPreOrder([](std::string& dat, void*){std::cout << dat << "->" << std::endl;}, nullptr);
            }
            //EXIST ELEMENT
            if(x == 5)
            {
              std::cout << "Che elemento vuoi ricercare all'interno della Lista?" << std::endl;
            }
            bool exist;
            if(type == 1 && x == 5)
            {
              int search_element;
              std::cin  >> search_element;
              exist = l1.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 2 && x == 5)
            {
              double search_element;
              std::cin  >> search_element;
              exist = l2.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 3 && x == 5)
            {
              float search_element;
              std::cin  >> search_element;
              exist = l3.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 4 && x == 5)
            {
              std::string search_element;
              std::cin  >> search_element;
              exist = l4.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            //FUNZIONE FOLD
            if(type == 1 &&  x == 6)
            {
              std::cout << "1) Somma per gli interi minori di K" << std::endl;
              int k;
              int sum = 0;
              std::cout << "Inserisci K" << std::endl;
              std::cin >> k;
              l1.FoldPreOrder([](const int& dat, const void* k, void* sum)
              {
                if (dat < *((int*)k))
                {
                  *((int*)sum) += dat;
                }
              }, &k, &sum);
              std::cout << "La somma degli interi (minori di " << k << ") e' : " << sum << std::endl;
            }
            if(type == 3 && x == 6)
            {
              float k;
              float prod = 1;
              std::cout << "1) Prodotto per i float maggori di K" << std::endl;
              std::cout << "Inserisci K" << std::endl;
              std::cin  >> k;
              l3.FoldPreOrder([](const float& dat, const void* k, void* prod)
              {
              if (dat > *((float*)k))
                {
                  *((float*)prod) *= dat;
                }
              }, &k, &prod);
              std::cout << "Il prodotto dei float (maggiori di " << k << ") e' : " << prod << std::endl;
            }
            if(type == 4 && x == 6)
            {
              std::string str;
              int k;
              std::cout << "1) Concatena le stringhe con lunghezza minore o uguale a K"<< std::endl;
              std::cout << "Inserisci la stringa" << std::endl;
              std::cin  >> str;
              l4.FoldPreOrder([](const std::string& dat, const void* k, void* str)
              {
                if (dat.size() <= *((int*)k))
                {
                  *((std::string*)str) += dat;
                }
              }, &k, &str);
              std::cout << "Concatenazione delle stringhe (con lunghezza minore o uguale a " << k << ") e' : " << str << std::endl;

            }
            //END FUNZIONE FOLD
            if(x == 7 && type == 1)
            {
                l1.MapPreOrder([](int& dat, void*){
                dat=dat*2;
                }, nullptr);
                std::cout << "Funzione 2n (INT) applicata alla tua struttura" << std::endl << std::endl;
            }
            if( x == 7 && type == 3)
            {
                l3.MapPreOrder([](float& dat, void*){
                dat=dat*dat;
                }, nullptr);
                std::cout << "Funzione n^2 (FLOAT) applicata alla tua struttura" << std::endl << std::endl;
            }
            if( x == 7 && type == 4)
            {
                l4.MapPreOrder([](std::string& dat, void* _)
                {
                  for (char& c : dat)
                  {
                    c = toupper(c);
                  }
                }, nullptr);
                std::cout << "Funzione uppercase applicata alla struttura" << std::endl << std::endl;
            }
        }
      }
    }
}
