

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "testable.hpp"
#include "mappable.hpp"


namespace lasd 
{
    template <typename Data>
    class DictionaryContainer : virtual public TestableContainer<Data>
    {   
        private:

        protected:

        public:
            // Destructor
            virtual ~DictionaryContainer() = default;


            // Copy assignment
            DictionaryContainer& operator=(const DictionaryContainer&) = delete; 
            // Move assignment
            DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; 


            // Comparison operators
            bool operator==(const DictionaryContainer&) const noexcept = delete; 
            bool operator!=(const DictionaryContainer&) const noexcept = delete; 


            // Specific member functions
            virtual bool Insert(const Data&) = 0; // Copy of the value
            virtual bool Insert(Data&&) = 0; // Move of the value
            virtual bool Remove(const Data&) = 0;

            virtual bool InsertAll(const TraversableContainer<Data>&);  // Copy of the value; From TraversableContainer; True if all are inserted
            virtual bool InsertAll(MappableContainer<Data>&&);  // Move of the value; From MappableContainer; True if all are inserted
            virtual bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

            virtual bool InsertSome(const TraversableContainer<Data>&);  // Copy of the value; From TraversableContainer; True if some are inserted
            virtual bool InsertSome(MappableContainer<Data>&&);  // Move of the value; From MappableContainer; True if some are inserted
            virtual bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if some are removed
    };



    template <typename Data>
    class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>
    {
        private:

        protected:

        public:
            // Destructor
            virtual ~OrderedDictionaryContainer() = default;


            // Copy assignment
            OrderedDictionaryContainer& operator=(const OrderedDictionaryContainer&) = delete; 
            // Move assignment
            OrderedDictionaryContainer& operator=(OrderedDictionaryContainer&&) noexcept = delete; 


            // Comparison operators
            bool operator==(const OrderedDictionaryContainer&) const noexcept = delete; 
            bool operator!=(const OrderedDictionaryContainer&) const noexcept = delete; 


            // Specific member functions
            virtual const Data& Min() const noexcept(false) = 0; // (concrete function must throw std::length_error when empty)
            virtual void RemoveMin() noexcept(false); // (concrete function must throw std::length_error when empty)
            virtual Data MinNRemove() noexcept(false); // (concrete function must throw std::length_error when empty)

            virtual const Data& Max() const noexcept(false) = 0; // (concrete function must throw std::length_error when empty)
            virtual void RemoveMax() noexcept(false); // (concrete function must throw std::length_error when empty)
            virtual Data MaxNRemove() noexcept(false); // (concrete function must throw std::length_error when empty)


            virtual const Data& Predecessor(const Data&) const noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
            virtual void RemovePredecessor(const Data&) noexcept(false); // (concrete function must throw std::length_error when not found)
            virtual Data PredecessorNRemove(const Data&) noexcept(false); // (concrete function must throw std::length_error when not found)
            
            virtual const Data& Successor(const Data&) const noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
            virtual void RemoveSuccessor(const Data&) noexcept(false); // (concrete function must throw std::length_error when not found)
            virtual Data SuccessorNRemove(const Data&) noexcept(false); // (concrete function must throw std::length_error when not found)
    };
}

#include "dictionary.cpp"

#endif
