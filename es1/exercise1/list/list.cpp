
namespace lasd
{

/* ****************************************************************************/
template<typename Data>
List<Data>::~List()
{
  Clear();
}

template<typename Data>
List<Data>::List(LinearContainer<Data>& con)
{
  for(unsigned long i = 0; i < con.Size(); i++)
  {
    InsertAtBack(con[i]);
  }
}

template<typename Data>
List<Data>::List(const List& list) //gli passiamo un oggetto Lista, l'oggetto che richiama questo costruttore, copia la lista passata.
{
  //this nuova Lista
  //list è la lista passata da copiare in this
  if(list.size >= 1) // ha almeno un elemento, deve copiare.
  {
    for(unsigned long i = 0; i < list.size; i++)
      InsertAtBack(list[i]);
  }
  /*this.size = list.size; // impostazione della nuova dimensione, viene impostato in InsertAtBack() */
}

// Move constructor
template<typename Data>
List<Data>::List(List&& list) noexcept
{
  std::swap(list.testa, testa);
  std::swap(list.coda, coda);
  std::swap(list.size, size);
}

// Copy assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List& list)
{
  List<Data>* tmplist = new List<Data>(list);
  std::swap(*tmplist, *this);
  delete tmplist;
  return *this;
}

// Move assignment
template<typename Data>
List<Data>& List<Data>::operator=(List&& list) noexcept
{
  std::swap(testa, list.testa);
  std::swap(coda, list.coda);
  std::swap(size, list.size);

  return *this;
}
/**************************************************/
template<typename Data> //copy
void List<Data>::InsertAtFront(const Data& val)
{
  //inserimento in testa
  Node* tmp = new Node(val);
  tmp->next = testa;
  testa = tmp;
  if(size == 0)
    coda = tmp;
  size++;
}
template<typename Data> //move, non si deve creare altra memoria.
void List<Data>::InsertAtFront(Data&& val) noexcept
{
  Node* tmp = new Node();
  std::swap(tmp->element, val);
  tmp->next = testa;
  testa = tmp;
  if(size == 0)
    coda = tmp;
  size++;
}

template<typename Data>
void List<Data>::RemoveFromFront()
{
  if(size > 0) //ci sono elementi nella struttura.
  {
    Node* tmp;
    tmp = testa;
    testa = tmp->next;
    size--;
    delete tmp;
  }
  else //altrimenti, restituisci un errore perché non ci sono elementi nella struttura
  {
    throw std::length_error("Lista VUOTA, non ci sono elementi da eilimanre!");
  }
}
template<typename Data>
Data List<Data>::FrontNRemove()
{
  if(size > 0) //ci sono elementi nella struttura.
  {
    valueRemoved = Front();
    RemoveFromFront();
    return valueRemoved;
  }
  else //altrimenti, restituisci un errore perché non ci sono elementi nella struttura
  {
    throw std::length_error("Lista VUOTA, non ci sono elementi da eliminare!");
  }

}

template<typename Data>
void List<Data>::InsertAtBack(const Data& val) // copy
{
    Node* tmp = new Node(val);
    if(testa == nullptr)
	  {
		  tmp->next = testa;
		  testa = tmp;
      coda = tmp;
    }
    else
    {
      coda->next = tmp;
      coda = tmp;
      tmp->next = nullptr;
    }
    size++;
}
template<typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept //move
{
    Node* tmp = new Node();
    std::swap(tmp->element, val);
    if(testa == nullptr)
	  {
		  tmp->next = testa;
		  testa = tmp;
      coda = tmp;
    }
    else
    {
      coda->next = tmp;
      coda = tmp;
      tmp->next = nullptr;
    }
    size++;
}
template<typename Data>
void List<Data>::Clear()
{
  unsigned long cont = size;
  for(int i = 0; i < cont; i++)
  {
    RemoveFromFront();
  }
  size = 0;
}

template<typename Data>
Data& List<Data>::Front() const
{
  if(testa == nullptr)
    throw std::length_error("Lista vuota");
  else
    return testa->element;
}

template<typename Data>
Data& List<Data>::Back() const
{
  if(testa == nullptr)
    throw std::length_error("Lista vuota");
  else
    return coda->element;
}

// Funzione di recupero dell'i-esimo elemento >> stesso funzionamento di Front()
// Discutere
template<typename Data>
Data& List<Data>::operator[](const unsigned long index) const
{
  Node *tmp = testa;
  int i = 0;
  if(index == 0)
    return Front();
  if(index == size - 1)
    return Back();

  if(index < size)
  {
    while(i != index)
    {
      tmp = tmp->next;
      i++;
    }
    return tmp->element;
  }

  //Oppure
  /*
  if(index < size)
  {
    while(tmp != nullptr && i!= index)
    {
      i++;
      tmp = tmp->next;
    }
    return tmp->element;
  }
  */
  else
  {
    throw std::out_of_range("Impossibile accedere alla posizione " + std::to_string(index) +
                            " in una lista di dimensione " + std::to_string(size) + "!");
  }
}

// Confronto di uguaglianza, da aggiustare
template <typename Data>
bool List<Data>::operator==(const List<Data>& lista) const noexcept
{

  if (size == lista.size)
  {
         Node* l1 = testa;
         Node* l2 = lista.testa;
         while (l1 != nullptr)
         {
             if (l1->element != l2->element)
             {
                 return false;
             }
             l1 = l1->next;
             l2 = l2->next;
         }
         return true;
     }
    else return false;
}

// Confronto di differenza >> implementato come complemento del confronto di uguaglianza
template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& list) const noexcept
{
  return !(*this == list);
}

template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor map, void* support)
{
  Node *tmp = testa;

  while(tmp != nullptr)
  {
    map(tmp->element, support);
    tmp = tmp->next;
  }
}
template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor map, void* support)
{
  for(unsigned long i = size; i > 0; i--)
  {
    map((*this)[i - 1], support);
  }
}

template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fold, const void* accum, void* support) const
{
  Node *tmp = testa;
  while(tmp != nullptr)
  {
    fold(tmp->element, accum, support);
    tmp = tmp->next;
  }
}

template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fold, const void* accum, void* support) const
{
  for(unsigned long i = size; i > 0; i--)
  {
    fold((*this)[i - 1], accum, support);
  }
}
/* ************************************************************************** */
} // close namespace lasd
