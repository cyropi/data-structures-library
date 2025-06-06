

namespace lasd 
{
/*     template <typename Data>
    SetVec<Data>::SetVec() : vector(DEFAULT_SIZE)
    {}


    template <typename Data>
    SetVec<Data>::SetVec(ulong size) : vector(size)
    {} */


    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& traversableContainer) : vector(traversableContainer.Size())
    {
        //this->vector = Vector<Data>(traversableContainer.Size());
        traversableContainer.Traverse([this](const Data& data) 
                                        -> void{ std::cout << "\n\n\ndata:" << data; this->Insert(data); this->getInfo(); });
    }


    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& mappableContainer) : vector(mappableContainer.Size())
    {
        //this->vector = Vector<Data>(mappableContainer.Size());
        mappableContainer.Map([this](Data& data) 
                                -> void{ this->Insert(std::move(data)); });
    }


    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& setVec) : vector(setVec.Capacity())
    {
        //this->vector = Vector<Data>(setVec.Capacity());

        this->size = setVec.Size();
        this->head = 0;
        this->tail = this->size;

        for (ulong i = 0; i < this->size; ++i)
            this->vector[i] = setVec[i];
    }

/*     template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& setVec)
    : vector(setVec.vector) // Copia il Vector sottostante (che avrà la sua capacità)
    {
       this->size = setVec.size;     // Copia la dimensione logica
      this->head = setVec.head;     // Copia l'head originale
      this->tail = setVec.tail;      // Copia il tail originale
    }
 */

    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data>&& setVec) noexcept 
    {
        std::swap(this->vector, setVec.vector);
        std::swap(this->size, setVec.size);
        std::swap(this->head, setVec.head);
        std::swap(this->tail, setVec.tail);
    }


    template <typename Data>
    SetVec<Data>::~SetVec() 
    {
        this->Clear();
    }


    template<typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& setVec)
    {
        SetVec<Data> tmpSetVec = setVec;
        std::swap(*this, tmpSetVec);

        return *this; 
    }


    template<typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& setVec) noexcept
    {
        std::swap(this->vector, setVec.vector);
        std::swap(this->size, setVec.size);
        std::swap(this->head, setVec.head);
        std::swap(this->tail, setVec.tail);

        return *this; 
    }


/*     // TODO: DA MODIFICARE
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data>& setVec) const noexcept
    {
        return (this->size == setVec.size) && (this->vector == setVec.vector);
    } */

template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& setVec) const noexcept
{
    if (this->size != setVec.size) { // Se le dimensioni sono diverse, non possono essere uguali
        return false;
    }
    // Se le dimensioni sono 0, entrambi sono vuoti e quindi uguali.
    if (this->size == 0) {
        return true;
    }

    // Confronta elemento per elemento in ordine logico
    // Utilizza l'operatore[] di SetVec che gestisce l'aritmetica circolare
    for (ulong i = 0; i < this->size; ++i) {
        if ((*this)[i] != setVec[i]) {
            return false;
        }
    }
    return true;
}

    template <typename Data>
    bool SetVec<Data>::operator!=(const SetVec<Data>& setVec) const noexcept
    {
        return !(*this == setVec);
    }


    template <typename Data>
    const Data& SetVec<Data>::Min() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile prelevare il minimo...");

        return (*this)[0];
    }


    template <typename Data>
    void SetVec<Data>::RemoveMin() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile rimuovere il minimo...");

        this->head = (this->head + 1) % this->Capacity();
        this->size--;
    }


    template <typename Data>
    Data SetVec<Data>::MinNRemove() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile rimuovere il minimo...");

        Data min = this->Min();
        this->RemoveMin();

        return min;
    }


    template <typename Data>
    const Data& SetVec<Data>::Max() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile prelevare il massimo...");

        return (*this)[this->size-1];
    }


    template <typename Data>
    void SetVec<Data>::RemoveMax() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile rimuovere il masssimo...");

        this->tail = (this->tail - 1) % this->Capacity();
        this->size--;
    }


    template <typename Data>
    Data SetVec<Data>::MaxNRemove() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set Vec vuoto! Non è possibile rimuovere il massimo...");

        Data max = this->Max();
        this->RemoveMax();

        return max;
    }


    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& data) const noexcept(false)
    {
        if(data > this->Max())
            return this->Max();

        ulong predecessor_index = this->BinarySearchPredecessor(data);
        return (*this)[predecessor_index];
    }


    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& data) noexcept(false)
    {
        const Data& predecessor = this->Predecessor(data);
        this->Remove(predecessor);
    }


    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& data) noexcept(false)
    {
        Data predecessor = this->Predecessor(data);
        this->Remove(predecessor);

        return predecessor;
    }


    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& data) const noexcept(false)
    {
        if(data < this->Min())
            return this->Min();

        ulong successor_index = this->BinarySearchSuccessor(data);
        return (*this)[successor_index];
    }


    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& data) noexcept(false)
    {
        const Data& successor = this->Successor(data);
        this->Remove(successor);
    }


    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& data) noexcept(false)
    {
        Data successor = this->Successor(data);
        this->Remove(successor);

        return successor;
    }


    template <typename Data>
	bool SetVec<Data>::Insert(const Data& data)
    {
        if(this->size == this->Capacity())
            this->Resize((this->size*2)+1);

        if(this->Empty()) 
        {
            this->vector[this->head] = data;
            this->tail = (this->head + 1) % this->Capacity();
            this->size++;

            return true;
        }

        std::cout << "\n\nMIN: " << this->Min();
        std::cout << "\n\nMAX: " << this->Max();
        
        if(data < this->Min())
        {
            this->head = (this->head - 1 + this->Capacity()) % this->Capacity();
            this->vector[this->head] = data;
            this->size++;

            return true;
        }

        if(data > this->Max())
        {
            this->vector[this->tail] = data;
            this->tail = (this->tail + 1) % this->Capacity();
            this->size++;

            return true;
        } 

        ulong logical_index = this->BinarySearchLowerBound(data);

        if(logical_index < this->Size() && (*this)[logical_index] == data)
            return false;


        if(logical_index <= this->size / 2) 
        {
            std::cout << "\n\nSONO IN SHIFT SX";

            
            //this->head = (this->head - 1 + this->Capacity()) % this->Capacity();

            // Shift left
            for(ulong i = 0; i <= logical_index; i++)
                this->vector[(this->head + i - 1 + this->Capacity()) % this->Capacity()] = this->vector[(this->head + i) % this->Capacity()];

            this->head = (this->head - 1 + this->Capacity()) % this->Capacity();

        } 
        else 
        {
                        std::cout << "\n\nSONO IN SHIFT DX";

for(long i = static_cast<long>(this->size - 1); i >= static_cast<long>(logical_index); i--) {
    this->vector[(this->head + i + 1) % this->Capacity()] = this->vector[(this->head + i) % this->Capacity()];
}

            this->tail = (this->tail + 1) % this->Capacity();
        }

        ulong physical_index = (this->head + logical_index) % this->Capacity(); 
        this->vector[physical_index] = data;
        this->size++;

        return true;
    }


template <typename Data>
bool SetVec<Data>::Insert(Data&& data)
{
    // 1. Gestione della capacità: Se il set è pieno, ridimensiona l'array sottostante.
    //    Assicurati che Resize() gestisca correttamente la copia/move degli elementi
    //    e la linearizzazione/aggiornamento di head e tail nel nuovo array.
    if (this->size == this->Capacity()) {
        this->Resize(this->size * 2 + 1);
    }

    // 2. Caso speciale: Inserimento in un SetVec vuoto.
    //    Qui usiamo std::move per "spostare" 'data' nella posizione dell'array.
    if (this->Empty()) {
        this->vector[this->head] = std::move(data); // <--- Usiamo std::move qui
        this->tail = (this->head + 1) % this->Capacity();
        this->size++;
        return true;
    }

    // 3. Trova l'indice logico dove il nuovo elemento dovrebbe essere inserito.
    //    BinarySearchLowerBound restituisce l'indice del primo elemento maggiore o uguale a 'data'.
    //    NOTA: Qui 'data' è un rvalue, ma per il confronto deve essere trattato come lvalue
    //    (o, se 'Data' ha un operatore di confronto per rvalue, può essere usato direttamente).
    //    Nella maggior parte dei casi, il confronto non consuma l'oggetto.
    ulong logical_index = this->BinarySearchLowerBound(data);

    // 4. Gestione dei duplicati: Se SetVec non permette duplicati, verifica se l'elemento esiste già.
    //    Anche qui, 'data' è trattato come lvalue per il confronto.
    if (logical_index < this->Size() && (*this)[logical_index] == data) {
        return false; // L'elemento esiste già nel set, non inserirlo.
    }

    // 5. Decide la direzione dello shift (sinistra o destra) per ottimizzare le prestazioni.
    if (logical_index < this->size / 2) {
        // Shift a sinistra: spostare gli elementi dall'inizio logico (head) fino
        // a logical_index - 1, di una posizione indietro nell'array fisico.
        // Gli spostamenti intermedi usano std::move.
        for (ulong i = 0; i < logical_index; i++) {
            this->vector[(this->head + i - 1 + this->Capacity()) % this->Capacity()] =
                std::move(this->vector[(this->head + i) % this->Capacity()]); // <--- Usiamo std::move qui
        }
        this->head = (this->head - 1 + this->Capacity()) % this->Capacity();
    } else {
        // Shift a destra: spostare gli elementi da logical_index fino alla fine logica (tail)
        // di una posizione in avanti nell'array fisico.
        // Gli spostamenti intermedi usano std::move.
        for (long i = static_cast<long>(this->size - 1); i >= static_cast<long>(logical_index); i--) {
            this->vector[(this->head + i + 1) % this->Capacity()] =
                std::move(this->vector[(this->head + i) % this->Capacity()]); // <--- Usiamo std::move qui
        }
        this->tail = (this->tail + 1) % this->Capacity();
    }

    // 6. Inserisci il nuovo elemento nella posizione fisica ora liberata.
    //    Usiamo std::move per spostare 'data' nella sua posizione finale.
    ulong physical_index = (this->head + logical_index) % this->Capacity();
    this->vector[physical_index] = std::move(data); // <--- Usiamo std::move qui
    
    // 7. Aggiorna la dimensione del set.
    this->size++;

    return true;
}


    template <typename Data>
	bool SetVec<Data>::Remove(const Data& data)
    {
        if(this->size == this->Capacity())
            this->Resize(this->size*2);

        if(this->Empty() || data < this->Min() || data > this->Max())
            return false;

        ulong logical_index = this->BinarySearch(data);
        
        if(logical_index == this->size)
            return false;

        if(logical_index < size / 2) 
        {
            // Shift right
            for(ulong i = logical_index; i > 0; i--)
                this->vector[(this->head + i) % this->Capacity()] = this->vector[(this->head + i - 1 + this->Capacity()) % this->Capacity()];

            this->head = (this->head + 1) % this->Capacity();
        } 
        else 
        {
            // Shift left
            for(ulong i = logical_index; i < this->size; i++)
                this->vector[(this->head + i) % this->Capacity()] = this->vector[(this->head + i + 1) % this->Capacity()];

            this->tail = (this->tail - 1 + this->Capacity()) % this->Capacity();
        }

        this->size--;

        return true;
    }

    
    template <typename Data>
    const Data& SetVec<Data>::operator[](ulong index) const noexcept(false)
    {        
        if(index >= this->size)
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione del Set Vec...");
        
        return this->vector[(this->head + index) % this->Capacity()];
    }


    template <typename Data>
    bool SetVec<Data>::Exists(const Data &data) const noexcept
    {
        ulong index = BinarySearch(data);
        return index != this->size ? true : false;
    }


    template <typename Data>
    void SetVec<Data>::Clear() 
    {
        this->vector.Clear();
        this->size = 0;
        this->head = 0;
        this->tail = 0;
    }


    template <typename Data>
    void SetVec<Data>::Resize(ulong newCap) 
    {
        if (newCap < this->size)
            newCap = this->size;

        Vector<Data> newVec(newCap);

        for (ulong i = 0; i < this->size; ++i)
            newVec[i] = std::move((*this)[i]); // copia ordinata logica → fisica

    std::swap(this->vector, newVec); // <--- Qui avviene lo scambio
        this->head = 0;
        this->tail = this->size;
    }

/* template <typename Data>
void SetVec<Data>::Resize(ulong newCapacity) 
{
    Vector<Data> newvector = Vector<Data>(newCapacity);
    ulong vectorToCopy = (this->size < newCapacity) ? this->size : newCapacity;
    for (ulong i = 0; i < vectorToCopy; ++i) 
    {
        ulong srcIndex = (head + i) % capacity;
        newvector[i] = std::move(vector[srcIndex]);
    }
    vector.Clear();
    vector = newvector;
    head = 0;
    this->tail = this->size;
    size = vectorToCopy;
} */

    template <typename Data>
    ulong SetVec<Data>::Capacity() const noexcept
    {
        return this->vector.Size();
    }


    template <typename Data>
    ulong SetVec<Data>::BinarySearch(const Data& data) const noexcept(false)
    {
        if(this->Empty()) 
            return this->size;

        ulong start = 0;
        ulong end = this->size - 1;
        
        while(start <= end)
        {
            ulong middle = (start + end) / 2;

            if(data == (*this)[middle]) 
                return middle;
            else if(data > (*this)[middle])
                start = middle + 1;
            else
                end = middle - 1;
        }

        return this->size;
    }


    template <typename Data>
    ulong SetVec<Data>::BinarySearchLowerBound(const Data& data) const noexcept(false)
    {
        ulong start = 0;
        ulong end = this->size;
                
        while(start < end)
        {
            ulong middle = (start + end) / 2;

            if(data == (*this)[middle]) 
                return middle;
            else if(data > (*this)[middle])
                start = middle + 1;
            else
                end = middle;
        }

        return start;
    } 


    template <typename Data>
    ulong SetVec<Data>::BinarySearchPredecessor(const Data& data) const noexcept(false)
    {
        ulong start = 0;
        ulong end = this->size;

        ulong predecessor_index = 0;
        bool isPredecessorFound = false;
        
        while(start < end)
        {
            ulong middle = (start + end) / 2;

            if(data > (*this)[middle])
            {
                predecessor_index = middle;
                isPredecessorFound = true;
                start = middle + 1;
            }
            else
                end = middle;
        }

        if(isPredecessorFound == false)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set Vec...");

        return predecessor_index;
    }


    template <typename Data>
    ulong SetVec<Data>::BinarySearchSuccessor(const Data& data) const noexcept(false)
    {
        ulong start = 0;
        ulong end = this->size;

        ulong successor_index = 0;
        bool isSuccessorFound = false;
        
        while(start < end)
        {
            ulong middle = (start + end) / 2;

            if(data >= (*this)[middle])
                start = middle + 1;
            else
            {
                successor_index = middle;
                isSuccessorFound = true;
                end = middle;
            }
        }

        if(isSuccessorFound == false)
            throw std::length_error("Non è stato possibile trovare il successore nel Set Vec...");

        return successor_index;
    }
}
