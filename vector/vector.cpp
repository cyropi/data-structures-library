
//#include "vector.hpp"
#include <algorithm>
#include <stdexcept>


namespace lasd 
{
    // (Vector)

    template<typename Data>
    Vector<Data>::Vector(const ulong size)
    {
        this->size = size;
        this->array = new Data[size];
    } 


    template<typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& traversableContainer) : Vector(traversableContainer.Size())
    {
        ulong i = 0;
        traversableContainer.Traverse([this, &i] (const Data& data)
                                        -> void{ this->array[i++] = data; });
    }

    
    template<typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& mappableContainer) : Vector(mappableContainer.Size())
    {
        ulong i = 0;
        mappableContainer.Map([this, &i] (Data& data)
                                -> void{ this->array[i++] = std::move(data); });
    }


    template<typename Data>
    Vector<Data>::Vector(const Vector<Data>& vector) : Vector(vector.Size())
    {
        std::copy_n(vector.array, this->size, this->array);
    }

    
    template<typename Data>
    Vector<Data>::Vector(Vector<Data>&& vector) noexcept 
    {
        std::swap(this->size, vector.size);
        std::swap(this->array, vector.array); 
    }


    template<typename Data>
    Vector<Data>::~Vector()
    {
        delete[] this->array;
    }


    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector)
    {
        delete[] this->array;

        this->size = vector.size;
        this->array = new int[this->size];

        std::copy_n(vector.array, this->size, this->array);

        return *this;
    }


    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept
    {
        std::swap(this->size, vector.size);
        std::swap(this->array, vector.array);

        return *this; 
    }


    template <typename Data>
    bool Vector<Data>::operator==(const Vector<Data>& vector) const noexcept 
    {
        return LinearContainer<Data>::operator==(vector);
    }


    template <typename Data>
    bool Vector<Data>::operator!=(const Vector<Data>& vector) const noexcept 
    {
        return LinearContainer<Data>::operator!=(vector);
    }


    template<typename Data>
	const Data& Vector<Data>::operator[](ulong index) const noexcept(false)
    {
        if(index > this->size )
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione del vettore.");
        
        return this->array[index];
    }


    template<typename Data>
	Data& Vector<Data>::operator[](ulong index) noexcept(false)
    {
        if(index > this->size )
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione del vettore.");
        
        return this->array[index];
    }


    template<typename Data>
	void Vector<Data>::Resize(ulong newSize)
    {
        if(newSize == 0)
        {
            delete[] this->array;
            this->array = nullptr;
            this->size = 0;

            return;
        }

        ulong limit = (this->size < newSize) ? this->size : newSize;

        Data* tmpArray = new Data[newSize];

        for(ulong i = 0; i < limit; i++)
            std::swap(this->array[i], tmpArray[i]);
          
        std::swap(this->array, tmpArray);
        this->size = newSize;

        delete[] tmpArray;
    }



    /* ************************************************************************** */
    // (SortableVector)

    template<typename Data>
    SortableVector<Data>::SortableVector(const ulong size) : Vector<Data>::Vector(size)
    {}


    template<typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& traversableContainer) : Vector<Data>::Vector(traversableContainer)
    {}


    template<typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& mappableContainer) : Vector<Data>::Vector(std::move(mappableContainer))
    {}


    template<typename Data>
    SortableVector<Data>::SortableVector(const SortableVector<Data>& sortableVector) : Vector<Data>::Vector(sortableVector)
    {}


    template<typename Data>
    SortableVector<Data>::SortableVector(SortableVector<Data>&& sortableVector) : Vector<Data>::Vector(std::move(sortableVector))
    {}


    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& sortableVector) 
    {
        Vector<Data>::operator=(sortableVector);
        return *this;
    }

    
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& sortableVector) noexcept
    {
        Vector<Data>::operator=(std::move(sortableVector));
        return *this;
    }
}
