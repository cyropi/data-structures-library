

#include <stdexcept>
#include "pqheap.hpp"


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
    {}


    template <typename Data>
    PQHeap<Data>::PQHeap(MappableContainer<Data>&& mappableContainer) : heapVec(std::move(mappableContainer))
    {}


    template <typename Data>
    PQHeap<Data>::PQHeap(const PQHeap<Data>& pqHeap) : heapVec(pqHeap.Capacity())
    {
        this->size = pqHeap.size;

        for (ulong i = 0; i < this->size; ++i)
            this->heapVec[i] = pqHeap[i];
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
    bool PQHeap<Data>::operator==(const PQHeap<Data>& pQHeap) const noexcept
    {
        return !(*this == pQHeap);
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
}
