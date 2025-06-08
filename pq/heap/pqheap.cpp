
#include <stdexcept>


namespace lasd 
{    
    template <typename Data>
    PQHeap<Data>::PQHeap() : heapVec(DEFAULT_SIZE)
    {}



    template <typename Data>
    PQHeap<Data>::PQHeap(const ulong size) : heapVec(size)
    {}



    template <typename Data>
    PQHeap<Data>::PQHeap(const TraversableContainer<Data>& traversableContainer) : heapVec(traversableContainer)
    {
        this->size = traversableContainer.Size();
    }



    template <typename Data>
    PQHeap<Data>::PQHeap(MappableContainer<Data>&& mappableContainer) : heapVec(std::move(mappableContainer))
    {
        this->size = mappableContainer.Size();
    }



    template <typename Data>
    PQHeap<Data>::PQHeap(const PQHeap<Data>& pqHeap) : heapVec(pqHeap.size)
    {
        this->size = pqHeap.size;

        for (ulong i = 0; i < this->size; ++i)
            (*this)[i] = pqHeap[i];
    }



    template <typename Data>
    PQHeap<Data>::PQHeap(PQHeap<Data>&& pQHeap) noexcept 
    {
        std::swap(this->heapVec, pQHeap.heapVec);
        std::swap(this->size, pQHeap.size);
    }



    template <typename Data>
    PQHeap<Data>::~PQHeap() 
    {
        this->Clear();
    }



    template<typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& pQHeap)
    {
        PQHeap<Data> tmpPQHeap = pQHeap;
        std::swap(*this, tmpPQHeap);

        return *this; 
    }



    template<typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& pQHeap) noexcept
    {
        std::swap(this->heapVec, pQHeap.heapVec);
        std::swap(this->size, pQHeap.size);

        return *this; 
    }



    template <typename Data>
    bool PQHeap<Data>::operator==(const PQHeap<Data>& pQHeap) const noexcept
    {
        return LinearContainer<Data>::operator==(pQHeap);
    }



    template <typename Data>
    bool PQHeap<Data>::operator!=(const PQHeap<Data>& pQHeap) const noexcept
    {
        return !(*this == pQHeap);
    }



    template <typename Data>
    const Data& PQHeap<Data>::Tip() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("PQHeap is empty! It wasn't possible to fetch the tip element...");

        return (*this)[0];
    }



    template <typename Data>
    void PQHeap<Data>::RemoveTip() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("PQHeap is empty! It wasn't possible to remove the tip element...");

        if(this->size == this->Capacity()/2)
            this->Resize(this->size);

        this->heapVec[0] = this->heapVec[this->size-1];
        this->size--;
        this->heapVec.HeapifyDown(this->size, 0);
    }



    template <typename Data>
    Data PQHeap<Data>::TipNRemove() noexcept(false)
    {
        Data tipValue;

        try
        {
			tipValue = this->Tip();
            this->RemoveTip();
        }
        catch(const std::length_error& e)
        {
            std::cerr << "Exception occurred in PQHeap (TipNRemove): " << e.what() << '\n';
            throw;
        }
        
        return tipValue;    
    }



    template <typename Data>
    void PQHeap<Data>::Insert(const Data& data)
    {
        if(this->size == this->Capacity())
            this->Resize((this->size*2)+1);   

        ulong lastIndex = this->size;
        this->heapVec[lastIndex] = data;

        this->heapVec.HeapifyUp(lastIndex);
        this->size++;
    }



    template <typename Data>
    void PQHeap<Data>::Insert(Data&& data)
    {
        if(this->size == this->Capacity())
            this->Resize((this->size*2)+1);   

        ulong lastIndex = this->size;
        this->heapVec[lastIndex] = std::move(data);

        this->heapVec.HeapifyUp(lastIndex);
        this->size++;
    }



    template <typename Data>
    void PQHeap<Data>::Change(ulong index, const Data& data)
    {
        if(data == (*this)[index])
            return;

        Data oldValue = (*this)[index];
        this->heapVec[index] = data;

        if((*this)[index] < oldValue)
            this->heapVec.HeapifyDown(this->size, index);
        else
            this->heapVec.HeapifyUp(index);
    }



    template <typename Data>
    void PQHeap<Data>::Change(ulong index, Data&& data)
    {
        if(data == (*this)[index])
            return;

        Data oldValue = (*this)[index];
        this->heapVec[index] = std::move(data);

        if((*this)[index] < oldValue)
            this->heapVec.HeapifyDown(this->size, index);
        else
            this->heapVec.HeapifyUp(index);
    }



    template <typename Data>
    const Data& PQHeap<Data>::operator[](ulong index) const noexcept(false)
    {        
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the pqHeap size range...");
        
        return this->heapVec[index];
    }



    template <typename Data>
    void PQHeap<Data>::Clear() 
    {
        this->heapVec.Clear();
        this->size = 0;
    }



    template <typename Data>
    ulong PQHeap<Data>::Capacity() const noexcept
    {
        return this->heapVec.Size();
    }



    template <typename Data>
    Data& PQHeap<Data>::operator[](ulong index) noexcept(false)
    {        
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the pqHeap size range...");
        
        return this->heapVec[index];
    }



    template <typename Data>
    void PQHeap<Data>::Resize(ulong newSize) 
    {
        if(newSize == 0)
        {
            this->Clear();
        }
        else if(this->size != newSize)
        {
            HeapVec<Data> tmpHeapVec = HeapVec<Data>(newSize);

            ulong minSize = (this->size < newSize) ? this->size : newSize;
            for(ulong i = 0; i < minSize; i++)
                tmpHeapVec[i] = std::move((*this)[i]); 

            std::swap(this->heapVec, tmpHeapVec);
        }
    }
} 
