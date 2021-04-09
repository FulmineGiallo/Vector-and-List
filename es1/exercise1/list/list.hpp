
#ifndef LIST_HPP
#define LIST_HPP
#include "../container/container.hpp"
namespace lasd
{
/* ************************************************************************** */
template <typename Data>
class List: virtual public LinearContainer<Data>, virtual public MappableContainer<Data>, virtual public FoldableContainer<Data>
{

private:

  // ...

protected:

  using LinearContainer<Data>::size;

  struct Node
  {
    Data element;
    struct Node *next = nullptr; // si mette a nullptr, per non far andare in memory leak.
    /* ********************************************************************** */
    //Default Constructor
    Node() = default;
    // Specific constructors
    Node(const Data& value) // costruttore che crea un nuovo nodo.
    {
       element = value;
       next = nullptr;
    }
    /* ********************************************************************** */

    // Copy constructor
    Node(const Node& node)
    {
        element = node.element;
        next = node.next;
    }

    // Move constructor
    Node(Node&& node) noexcept
    {
        std::swap(element, node.element);
        std::swap(next, node.next);
    }

    /* ********************************************************************** */

    // Destructor
     ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    // ...

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };
public:

  Node *testa = nullptr;
  Node *coda  = nullptr;
  Data valueRemoved;
  // Default constructor
  List() = default;
  /* ************************************************************************ */
  // Specific constructor
  List(LinearContainer<Data>& con); // A list obtained from a LinearContainer, costruire una lista partendo da un vettore o una lista (un oggetto di tipo LinearContainer)
  // DONE
  /* ************************************************************************ */

  // Copy constructor
  List(const List&); //DONE

  // Move constructor
  List(List&&) noexcept;  //DONE

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&); //DONE

  // Move assignment
  List& operator=(List&&) noexcept; //DONE

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept; //DONE
  bool operator!=(const List&) const noexcept; //DONE

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data& val); // Copy of the value
  void InsertAtFront(Data&& val) noexcept; // Move of the value

  void RemoveFromFront(); // (must throw std::length_error when empty) rimozione.
  Data FrontNRemove();   // (must throw std::length_error when empty) rimozione con lettura.

  void InsertAtBack(const Data& val); // Copy of the value
  void InsertAtBack(Data&& val) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back()  const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& operator[](const unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member   sx -> dx
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member  dx -> sx

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*,void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
