

namespace lasd 
{
    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& traversableContainer)
    {
        traversableContainer.Traverse([this](const Data& data) 
                                        -> void{ this->Insert(data); });
    }


    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& mappableContainer)
    {
        mappableContainer.Map([this](Data& data) 
                                -> void{ this->Insert(std::move(data)); });
    }


    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& setVec)
    {
        this->vector(setVec.vector);
        this->size = setVec.size;
        this->head = setVec.head;
        this->tail = setVec.tail;
    }


    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data>&& setVec) noexcept
    {
        this->vector(std::move(setVec.vector));
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
        this->vector = setVec.vector;
        this->size = setVec.size;
        this->head = setVec.head;
        this->tail = setVec.tail;    

        return *this; 
    }


    template<typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& setVec) noexcept
    {
        this->vector = std::move(setVec.vector);
        std::swap(this->size, setVec.size);
        std::swap(this->head, setVec.head);
        std::swap(this->tail, setVec.tail);

        return *this; 
    }


    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data>& setVec) const noexcept
    {
        return (this->size == setVec.size) && (this->vector == setVec.vector);
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

        return (*this)[head];
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

        return (*this)[tail];
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

        ulong predecessor_index = this->BinarySearchLowerBound(data);
        return (*this)[predecessor_index];
    }


    template <typename Data>
    const Data& SetVec<Data>::operator[](ulong index) const noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione del Set Vec...");
        
        return this->vector[(this->head + index) % Capacity()];
    }


    template <typename Data>
    bool SetLst<Data>::Exists(const Data &data) const noexcept
    {
        ulong index = BinarySearch(data);
        return index != this->size ? true : false;
    }


    template <typename Data>
    ulong SetVec<Data>::Capacity() const noexcept
    {
        return this->vector.Size();
    }


    template <typename Data>
    ulong SetVec<Data>::BinarySearch(const Data& data) const noexcept
    {
        ulong start = 0;
        ulong end = this.Empty() ? 0 : this->size - 1;
        
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
        ulong end = this.Empty() ? 0 : this->size - 1;

        ulong* predecessor_index = nullptr;
        
        while(start <= end)
        {
            ulong middle = (start + end) / 2;

            if(data > (*this)[middle])
            {
                predecessor_index = &middle;
                start = middle + 1;
            }
            else
                end = middle - 1;
        }

        if(predecessor_index == nullptr)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set Vec...");


        return *predecessor_index;
    }


    template <typename Data>
    ulong SetVec<Data>::BinarySearchUpperBound(const Data& data) const noexcept(false)
    {
        ulong start = 0;
        ulong end = this.Empty() ? 0 : this->size - 1;

        ulong* successor_index = nullptr;
        
        while(start <= end)
        {
            ulong middle = (start + end) / 2;

            if(data > (*this)[middle])
                start = middle + 1;
            else
            {
                successor_index = &middle;
                end = middle - 1;
            }
        }

        if(successor_index == nullptr)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set Vec...");


        return *predecessor_index;
    }
}
