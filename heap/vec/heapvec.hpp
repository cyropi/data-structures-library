
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

#include "../heap.hpp"
#include "../../vector/vector.hpp"


namespace lasd 
{
    template <typename Data>
    class HeapVec : virtual public Heap<Data>,
                    virtual protected Vector<Data>
    {  // Could extend SortableVector<Data>
        private:
            // ...

        protected:
            // using Container::???;
            //SortableVector<Data> sortableVector; 


        public:
            // Default constructor
            HeapVec() = default;


            // Specific constructors
            HeapVec(const ulong);
            HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
            HeapVec(MappableContainer<Data>&&); // A heap obtained from a MappableContainer


            // Copy constructor
            HeapVec(const HeapVec<Data>&);
            // Move constructor
            HeapVec(HeapVec<Data>&&) noexcept;


            // Destructor
            virtual ~HeapVec() = default;
            
            
            // Copy assignment
            HeapVec<Data>& operator=(const HeapVec<Data>&);
            // Move assignment
            HeapVec<Data>& operator=(HeapVec<Data>&&) noexcept;


            // Comparison operators
            bool operator==(const HeapVec<Data>&) const noexcept;
            bool operator!=(const HeapVec<Data>&) const noexcept;


            // Specific member functions (inherited from Heap)
            bool IsHeap() const override; // Override Heap member
            void Heapify() override; // Override Heap member


            // Specific member function (inherited from SortableLinearContainer)
            void Sort() override; // Override SortableLinearContainer member

 
			const Data& operator[](ulong) const noexcept(false) override; // Override LinearContainer member (must throw std::out_of_range when out of range)
			Data& operator[](ulong) noexcept(false) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)


			void Clear() override; // Override ClearableContainer member 


        public:
            // Auxiliary functions, if necessary!
            ulong GetParentIndex(ulong) const noexcept;
            ulong GetLeftChildIndex(ulong) const noexcept;
            ulong GetRightChildIndex(ulong) const noexcept;
            void DecreaseHeapSize(ulong) noexcept;
            void HeapifyDown(ulong,ulong);
            void HeapifyUp(ulong);
    };
}

#include "heapvec.cpp"

#endif
