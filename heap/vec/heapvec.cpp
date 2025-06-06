
#include <stdexcept>


namespace lasd 
{
    template<typename Data>
    HeapVec<Data>::HeapVec(const ulong size) : sortableVector(size)
    {
        this->size = size;
        this->Heapify();
    }




    template<typename Data>
    HeapVec<Data>::HeapVec(const TraversableContainer<Data>& traversableContainer) : sortableVector(traversableContainer)
    {
        this->size = traversableContainer.Size();
        this->Heapify();
    }




    template<typename Data>
    HeapVec<Data>::HeapVec(MappableContainer<Data>&& mappableContainer) : sortableVector(std::move(mappableContainer))
    {
        this->size = mappableContainer.Size();
        this->Heapify();
    }




    template<typename Data>
    HeapVec<Data>::HeapVec(const HeapVec<Data>& heapVec) : sortableVector(heapVec.size)
    {
        this->size = heapVec.size;

        for (ulong i = 0; i < this->size; ++i)
            (*this)[i] = heapVec[i];
    }




    template<typename Data>
    HeapVec<Data>::HeapVec(HeapVec<Data>&& heapVec) noexcept
    {
        std::swap(this->size, heapVec.size);
        std::swap(this->sortableVector, heapVec.sortableVector); 
    }




    template <typename Data>
    HeapVec<Data>::~HeapVec() 
    {
        this->Clear();
    }




    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heapVec) 
    {
        HeapVec<Data> tmpHeapVec = heapVec;
        std::swap(tmpHeapVec, *this);

        return *this; 
    }

    


    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heapVec) noexcept
    {
        std::swap(this->size, heapVec.size);
        std::swap(this->sortableVector, heapVec.sortableVector);         
        
        return *this;
    }

    


    template <typename Data>
    bool HeapVec<Data>::operator==(const HeapVec<Data>& heapVec) const noexcept
    {
        return SortableLinearContainer<Data>::operator==(heapVec);
    }




    template <typename Data>
    bool HeapVec<Data>::operator!=(const HeapVec<Data>& heapVec) const noexcept
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
            this->HeapifyDown(this->size, index);
    }




    template <typename Data>
    void HeapVec<Data>::Sort()
    {
        if(this->Empty() || this->size == 1)
            return;

        if(!(this->IsHeap()))
            this->Heapify();

        for(ulong index = (this->size)-1; index > 0; index--)
        {
            std::swap((*this)[0], (*this)[index]);
            this->HeapifyDown(index, 0);
        }
    }




    template<typename Data>
	const Data& HeapVec<Data>::operator[](ulong index) const noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the heapVec size range...");
        
        return this->sortableVector[index];
    }




    template<typename Data>
	Data& HeapVec<Data>::operator[](ulong index) noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the heapVec size range...");
        
        return this->sortableVector[index];
    }




    template<typename Data>
	void HeapVec<Data>::Clear()
    {            
        this->sortableVector.Clear();
        this->size = 0;
    }




    template <typename Data>
    ulong HeapVec<Data>::GetParentIndex(ulong index) const noexcept
    {
        return (static_cast<long>(index)-1)/2;
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
    void HeapVec<Data>::HeapifyDown(ulong endSize, ulong index)
    {
        ulong leftChildIndex = GetLeftChildIndex(index);
        ulong rightChildIndex = GetRightChildIndex(index);
        ulong max = index;

        if(leftChildIndex < endSize && (*this)[leftChildIndex] > (*this)[index])
            max = leftChildIndex;

        if(rightChildIndex < endSize && (*this)[rightChildIndex] > (*this)[max])
            max = rightChildIndex;

        if(max != index)
        {
            std::swap((*this)[index], (*this)[max]);
            HeapifyDown(endSize, max);
        }
    }




    template <typename Data>
    void HeapVec<Data>::HeapifyUp(ulong index)
    {
        while(index > 0 && (*this)[index] > (*this)[this->GetParentIndex(index)])
        {
            std::swap((*this)[index], (*this)[this->GetParentIndex(index)]);
            index = this->GetParentIndex(index);
        }
    }
} 







/* 
#include <stdexcept>
#include "heapvec.hpp"


namespace lasd 
{
    template<typename Data>
    HeapVec<Data>::HeapVec(const ulong size) : SortableVector<Data>::SortableVector(size)
    {
        this->Heapify();
    }


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
        Vector<Data>::operator=(heapVec);
        return *this;
    }

    
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heapVec) noexcept
    {
        Vector<Data>::operator=(std::move(heapVec));
        return *this;
    }

    
    template <typename Data>
    bool HeapVec<Data>::operator==(const HeapVec<Data>& heapVec) const noexcept
    {
        return Vector<Data>::operator==(heapVec);
    }


    template <typename Data>
    bool HeapVec<Data>::operator!=(const HeapVec<Data>& heapVec) const noexcept
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
            this->HeapifyDown(this->size, index);
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
            this->HeapifyDown(index, 0);
        }

        this->size = tmpSize;
    }




    template<typename Data>
	const Data& HeapVec<Data>::operator[](ulong index) const noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the heapVec size range...");
        
        return this->array[index];
    }




    template<typename Data>
	Data& HeapVec<Data>::operator[](ulong index) noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Invalid index! You're out of the heapVec size range...");
        
        return this->array[index];
    }



    template<typename Data>
	void HeapVec<Data>::Clear()
    {            
        return Vector<Data>::Clear();
    }



    template <typename Data>
    ulong HeapVec<Data>::GetParentIndex(ulong index) const noexcept
    {
        return (static_cast<long>(index)-1)/2;
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
    void HeapVec<Data>::DecreaseHeapSize(ulong size) noexcept
    {
        this->size = size;
    }



    template <typename Data>
    void HeapVec<Data>::HeapifyDown(ulong endSize, ulong index)
    {
        ulong leftChildIndex = GetLeftChildIndex(index);
        ulong rightChildIndex = GetRightChildIndex(index);
        ulong max = index;

        if(leftChildIndex < endSize && (*this)[leftChildIndex] > (*this)[index])
            max = leftChildIndex;

        if(rightChildIndex < endSize && (*this)[rightChildIndex] > (*this)[max])
            max = rightChildIndex;

        if(max != index)
        {
            std::swap((*this)[index], (*this)[max]);
            HeapifyDown(endSize, max);
        }
    }



    template <typename Data>
    void HeapVec<Data>::HeapifyUp(ulong index)
    {
        std::cout << "\n\nsono in heapifyUp... index: " << index;
        while(index > 0 && (*this)[index] > (*this)[this->GetParentIndex(index)])
        {
            std::swap((*this)[index], (*this)[this->GetParentIndex(index)]);
            index = this->GetParentIndex(index);
        }
    }
}
 */
