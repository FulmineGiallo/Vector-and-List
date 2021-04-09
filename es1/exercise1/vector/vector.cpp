
namespace lasd {

/* ************************************************************************** */

// Costruttore con dimensione in ingresso
template<typename Data>
Vector<Data>::Vector(const unsigned long newsize){
  Elements = new Data[newsize] {};  // le parentesi graffe indicano l'array viene inizializzato
                                    // al valore di default del tipo di dato "Data" (utilizzato
                                    // per "pulire" l'area di memoria, invece di avere valori no-sense)
                                    // OPERAZIONE DI ROBUSTEZZA, a discapito di un maggior costo
  size = newsize;
}

// Costruttore con dati da un'altra struttura LinearContainer<Data> (vettore, lista, ecc.)
template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con){
  size = con.Size(); //recupera la dimensione della struttura in ingresso
  Elements = new Data[size];

  for(unsigned long index = 0; index < size; index++)
  {
    Elements[index] = con[index]; // accedi all'i-esimo elemento della struttura (senza sapere
                                  // quale struttura sia, sappiamo che LinearContainer implementa
                                  // operator[]) in ingresso e copialo nella struttura da costruire
  }
}

// Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec)
{
  Elements = new Data[vec.size];
  std::copy(vec.Elements, vec.Elements + vec.size, Elements); // questa funzione prende in input:
                                                              // puntatore all'origine dell'array da copiare;
                                                              // puntatore al termine dell'array da copiare;
                                                              // puntatore all'origine dell'array destinazione.
  size = vec.size; // impostazione della nuova dimensione
}

// Move constructor >>  semplicemente si scambiano i puntatori delle due strutture e delle due dimensioni
//                      tramite la funzione swap() della libreria std (TEMPO COSTANTE).
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
}

/* ************************************************************************** */

// Destructor
template<typename Data>
Vector<Data>::~Vector(){
  delete[] Elements;
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
  Vector<Data>* tmpvec = new Vector<Data>(vec);
  std::swap(*tmpvec, *this);
  delete tmpvec;
  return *this;
}

// Move Assignment >> identico al costruttore di spostamento, solo che
//                    questa funzione restituisce anche un riferimento alla struttura corrente
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept{
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
  return *this;
}

/* ************************************************************************** */

// Confronto di uguaglianza
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept{
  if(size==vec.size){
    for(unsigned int index = 0; index < size; index++){
      if(Elements[index] != vec.Elements[index]){
        return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
}

// Confronto di differenza >> implementato come complemento del confronto di uguaglianza
template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept{
  return !(*this == vec);
}

/* ************************************************************************** */

// Funzione di ridimensionamento
template<typename Data>
void Vector<Data>::Resize(const unsigned long newsize){
  if(newsize == 0) {  // se la nuova dimensione è 0, svuota il vettore
    Clear();
  }
  else if(size != newsize) { // se la nuova dimensione è diversa da quella corrente
    unsigned long limit;
    limit = (size < newsize) ? size : newsize; // imposta la dimensione più piccola nella variabile limite

    Data* TmpElements = new Data[newsize]{}; // crea un nuovo vettore di tanti elementi "Data" quanto indicato da "newsize"

    for(unsigned long index = 0; index < limit; index++){ // copia degli elementi dalla struttura corrente alla nuova
      std::swap(Elements[index], TmpElements[index]);
    }

    std::swap(Elements, TmpElements); // scambio dei puntatori a tempo costante
    size = newsize; // aggiornamento della dimensione della struttura
    delete[] TmpElements; // eliminazione della struttura di appoggio utilizzata per la copia degli elementi
  }
}

// Funzione di svuotamento >> eliminazione di tutti i dati e aggiornamento della dimensione
template<typename Data>
void Vector<Data>::Clear(){
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

// Funzione di recupero del primo elemento
template<typename Data>
Data& Vector<Data>::Front() const{
  if(size != 0) {       // se la struttura contiene almeno un elemento
    return Elements[0]; // restituisci il primo elemento
  }
  else { //altrimenti, restituisci un errore perché non ci sono elementi nella struttura
      throw std::length_error("Impossibile accedere al primo elemento di un vettore vuoto!");
  }
}

// Funzione di recupero dell'ultimo elemento >> stesso funzionamento di Front()
template<typename Data>
Data& Vector<Data>::Back() const{
  if(size != 0){
    return Elements[size - 1];
  }
  else{
    throw std::length_error("Impossibile accedere all'ultimo elemento di un vettore vuoto!");
  }
}

// Funzione di recupero dell'i-esimo elemento >> stesso funzionamento di Front()
template<typename Data>
Data& Vector<Data>::operator[](const unsigned long index) const{
  if(index < size) {
    return Elements[index];
  }
  else {
    throw std::out_of_range("Impossibile accedere alla posizione " + std::to_string(index) +
                            " in un vettore di dimensione " + std::to_string(size) + "!");
  }
}

/* ************************************************************************** */

// Funzione di map dal primo all'ultimo elemento - ciclo in avanti
template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor fun, void* par){
  for(unsigned long index = 0; index < size; index++){
    fun(Elements[index], par); // applicazione in Pre-Order della funzione passata per parametro ad ogni elemento della struttura
  }
}

// Funzione di map dall'ultimo al primo elemento - ciclo a ritroso
template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor fun, void* par){
  unsigned long index = size;
  while(index>0) {
    fun(Elements[--index], par); // applicazione in Post-Order della funzione passata per parametro ad ogni elemento della struttura
  }
}

/* ************************************************************************** */
// LE FUNZIONI FOLD ASSOLUTAMENTE NON POSSONO MODIFICARE I DATI DELLA STRUTTURA

// Funzione di fold dal primo all'ultimo elemento - ciclo in avanti
template <typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const{
  for(unsigned long index = 0; index<size; index++) {
    fun(Elements[index], par, acc); // applicazione in Pre-Order della funzione passata per parametro ad ogni elemento della struttura
  }
}

// Funzione di fold dall'ultimo al primo elemento - ciclo a ritroso
template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const{
  unsigned long index = size;
  while(index>0) {
    fun(Elements[--index], par, acc); // applicazione in Post-Order della funzione passata per parametro ad ogni elemento della struttura
  }
}

/* ************************************************************************** */

} // close namespace lasd
