
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"


namespace lasd
{
    template <typename Data>
    class PQHeap : virtual public PQ<Data>
    {
        protected:
            HeapVec<Data> heapVec; 
            static const ulong DEFAULT_SIZE = 10;


        public:
            // Default constructor
            PQHeap();


            // Specific constructors
            PQHeap(ulong);
            PQHeap(const TraversableContainer<Data>&);  // A priority queue obtained from a TraversableContainer
            PQHeap(MappableContainer<Data>&&); // A priority queue obtained from a MappableContainer


            // Copy constructor
            PQHeap(const PQHeap<Data>&);
            // Move constructor
            PQHeap(PQHeap<Data>&&) noexcept;


            // Destructor
            virtual ~PQHeap();


            // Copy assignment
            PQHeap<Data>& operator=(const PQHeap<Data>&);
            // Move assignment
            PQHeap<Data>& operator=(PQHeap<Data>&&) noexcept;


            // Comparison operators
            bool operator==(const PQHeap<Data>&) const noexcept;
            bool operator!=(const PQHeap<Data>&) const noexcept;


            // Specific member functions (inherited from PQ)
            const Data& Tip() const noexcept(false) override; // Override PQ member (must throw std::length_error when empty)
            void RemoveTip() noexcept(false) override; // Override PQ member (must throw std::length_error when empty)
            Data TipNRemove() noexcept(false) override; // Override PQ member (must throw std::length_error when empty)

            void Insert(const Data&) override; // Override PQ member (Copy of the value)
            void Insert(Data&&) override; // Override PQ member (Move of the value)

            void Change(ulong, const Data&) override; // Override PQ member (Copy of the value)
            void Change(ulong, Data&&) override; // Override PQ member (Move of the value)


			// Specific member functions (inherited from LinearContainer)
			const Data& operator[](ulong) const noexcept(false) override; // Override LinearContainer member (must throw std::out_of_range when out of range)


			// Specific member function (inherited from ClearableContainer)
			void Clear() override; // Override ClearableContainer member


        protected:
            // Auxiliary functions, if necessary!
            virtual ulong Capacity() const noexcept;
            Data& operator[](ulong) noexcept(false); // (must throw std::out_of_range when out of range)
            void Resize(ulong);
    };
}

#include "pqheap.cpp"

#endif
