

#include <stdexcept>


namespace lasd 
{
    template<typename Data>
    HeapVec<Data>::HeapVec(const TraversableContainer<Data>& traversableContainer) : SortableVector<Data>::SortableVector(traversableContainer)
    {
        this->Heapify();
    }


    template<typename Data>
    HeapVec<Data>::HeapVec(MappableContainer<Data>&& mappableContainer) : SortableVector<Data>::SortableVector(std::move(mappableContainer))
    {
        this->Heapify();
    }


    template<typename Data>
    HeapVec<Data>::HeapVec(const HeapVec<Data>& heapVec) : SortableVector<Data>::SortableVector(heapVec)
    {}


    template<typename Data>
    HeapVec<Data>::HeapVec(HeapVec<Data>&& heapVec) noexcept : SortableVector<Data>::SortableVector(std::move(heapVec))
    {}


    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heapVec) 
    {
        SortableVector<Data>::operator=(heapVec);
        return *this;
    }

    
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heapVec) noexcept
    {
        SortableVector<Data>::operator=(std::move(heapVec));
        return *this;
    }

    
    template <typename Data>
    bool HeapVec<Data>::operator==(const HeapVec<Data>& heapVec)  const noexcept
    {
        return SortableVector<Data>::operator==(heapVec);
    }


    template <typename Data>
    bool HeapVec<Data>::operator!=(const HeapVec<Data>& heapVec)  const noexcept
    {
        return !(*this == heapVec);
    }


    template <typename Data>
    bool HeapVec<Data>::IsHeap() const
    {
        if(this->Empty() || this->size == 1)
            return true;

        for(ulong index = this->size-1; index > 0; index--)
        {
            ulong parentIndex = GetParentIndex(index);
            if((*this)[index] > (*this)[parentIndex])
                return false;
        }

        return true;
    }

    
    template <typename Data>
    void HeapVec<Data>::Heapify()
    {
        if(this->Empty() || this->size == 1)
            return;

        for(long index = static_cast<long>((this->size/2)-1); index >= 0; index--)
            this->MaxHeapify(index);
    }


    template <typename Data>
    void HeapVec<Data>::Sort()
    {
        if(this->Empty() || this->size == 1)
            return;

        if(!(this->IsHeap()))
            this->Heapify();

        ulong tmpSize = this->size;
        for(ulong index = (this->size)-1; index > 0; index--)
        {
            std::swap((*this)[0], (*this)[index]);
            this->size--;
            this->MaxHeapify(0);
        }

        this->size = tmpSize;
    }


    template <typename Data>
    ulong HeapVec<Data>::GetParentIndex(ulong index) const noexcept
    {
        return (index-1)/2;
    }

    
    template <typename Data>
    ulong HeapVec<Data>::GetLeftChildIndex(ulong index) const noexcept
    {
        return (index*2)+1;
    }

    
    template <typename Data>
    ulong HeapVec<Data>::GetRightChildIndex(ulong index) const noexcept
    {
        return (index*2)+2;
    }


    template <typename Data>
    void HeapVec<Data>::MaxHeapify(ulong index)
    {
        ulong leftChildIndex = GetLeftChildIndex(index);
        ulong rightChildIndex = GetRightChildIndex(index);
        ulong max = index;

        if(leftChildIndex < this->size && (*this)[leftChildIndex] > (*this)[index])
            max = leftChildIndex;

        if(rightChildIndex < this->size && (*this)[rightChildIndex] > (*this)[max])
            max = rightChildIndex;

        if(max != index)
        {
            std::swap((*this)[index], (*this)[max]);
            MaxHeapify(max);
        }
    }
}
