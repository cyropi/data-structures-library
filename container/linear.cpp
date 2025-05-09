
#include "linear.hpp"


namespace lasd 
{
    /* ************************************************************************** */
    // (LinearContainer)

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data>& linearContainer) const noexcept
    {
        if(this->size != linearContainer.size)
            return false;

        for(int i = 0; i < this->size; i++)
        {
            if((*this)[i] != linearContainer[i])
                return false;
        }

        return true;
    }


    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& linearContainer) const noexcept
    {
        return !(*this == linearContainer);
    }


    template <typename Data>
	const Data& LinearContainer<Data>::Front() const
    {
        if(this->Empty())
            throw std::length_error("Struttura dati vuota! Non è possibile prelevare il primo elemento...");

        return (*this)[0];
    }


    template <typename Data>
	const Data& LinearContainer<Data>::Back() const
    {
        if(this->Empty())
            throw std::length_error("Struttura dati vuota! Non è possibile prelevare l'ultimo elemento...");

        return (*this)[this->size - 1];
    }


    template <typename Data>
    void LinearContainer<Data>::Traverse(TraverseFun traverseFun) const 
    {
        this->PreOrderTraverse(traverseFun);
    };

        
    template <typename Data>
    void LinearContainer<Data>::PreOrderTraverse(TraverseFun traverseFun) const 
    {
        for(int i = 0; i < this->size; i++)
            traverseFun((*this)[i]);
    };

        
    template <typename Data>
    void LinearContainer<Data>::PostOrderTraverse(TraverseFun traverseFun) const 
    {
        for(int i = this->size-1; i >= 0; i--)
            traverseFun((*this)[i]);
    };
    
    
    
    /* ************************************************************************** */
    // (Mutable Container)

    template <typename Data>
    Data& MutableLinearContainer<Data>::Front()
    {
        if(this->Empty())
            throw std::length_error("Struttura dati vuota! Non è possibile prelevare il primo elemento...");

        return (*this)[0];
    }

    template <typename Data>
    Data& MutableLinearContainer<Data>::Back()
    {
        if(this->Empty())
            throw std::length_error("Struttura dati vuota! Non è possibile prelevare il primo elemento...");

        return (*this)[this->size - 1];
    }


    template <typename Data>
    void MutableLinearContainer<Data>::Map(MapFun mapFun)
    {
        this->PreOrderMap(mapFun);
    }


    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun mapFun)
    {
        for(int i = 0; i < this->size; i++)
            mapFun((*this)[i]);
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun mapFun)
    {
        for(int i = this->size-1; i >= 0; i--)
            mapFun((*this)[i]);
    }

    /* ************************************************************************** */
}
