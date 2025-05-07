
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP


/* ************************************************************************** */
#include "testable.hpp"
#include "mappable.hpp"


/* ************************************************************************** */
namespace lasd 
{
    /* ************************************************************************** */
    template <typename Data>
    class DictionaryContainer : virtual public TestableContainer<Data>
    {   
        private:


        protected:


        public:
            // Destructor
            virtual ~DictionaryContainer() = default;


            /* ************************************************************************ */
            // Copy assignment
            DictionaryContainer& operator=(const DictionaryContainer&) = delete; 
            // Move assignment
            DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; 

            /* ************************************************************************ */

            // Comparison operators
            bool operator==(const DictionaryContainer&) const noexcept = delete; 
            bool operator!=(const DictionaryContainer&) const noexcept = delete; 


            /* ************************************************************************ */
            // Specific member functions
            virtual bool Insert(const Data&) = 0; // Copy of the value
            virtual bool Insert(Data&&) = 0; // Move of the value
            virtual bool Remove(const Data&) = 0;

            inline bool InsertAll(const TraversableContainer<Data>&);  // Copy of the value; From TraversableContainer; True if all are inserted
            inline bool InsertAll(MappableContainer<Data>&&);  // Move of the value; From MappableContainer; True if all are inserted
            inline bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

            inline bool InsertSome(const TraversableContainer<Data>&);  // Copy of the value; From TraversableContainer; True if all are inserted
            inline bool InsertSome(MappableContainer<Data>&&);  // Move of the value; From MappableContainer; True if all are inserted
            inline bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed
    };



    /* ************************************************************************** */
    template <typename Data>
    class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>
    {
        private:


        protected:


        public:
        // Destructor
        virtual ~OrderedDictionaryContainer() = default;


        /* ************************************************************************ */
        // Copy assignment
        OrderedDictionaryContainer& operator=(const OrderedDictionaryContainer&) = delete; 
        // Move assignment
        OrderedDictionaryContainer& operator=(OrderedDictionaryContainer&&) = delete; 


        /* ************************************************************************ */
        // Comparison operators
        bool operator==(const OrderedDictionaryContainer&) const noexcept = delete; 
        bool operator!=(const OrderedDictionaryContainer&) const noexcept = delete; 


        /* ************************************************************************ */
        // Specific member functions
        virtual const Data& Min() const noexcept(false) = 0; // (concrete function must throw std::length_error when empty)
        // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
        virtual void RemoveMin() noexcept(false) = 0; // (concrete function must throw std::length_error when empty)

        virtual const Data& Max() const noexcept(false) = 0; // (concrete function must throw std::length_error when empty)
        // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
        virtual void RemoveMax() noexcept(false) = 0; // (concrete function must throw std::length_error when empty)


        virtual const Data& Predecessor(const Data&) const noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
        // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
        virtual void RemovePredecessor(Data&) noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
        
        virtual const Data& Successor(const Data&) const noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
        // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
        virtual void RemoveSuccessor(Data&) noexcept(false) = 0; // (concrete function must throw std::length_error when not found)
    };
    /* ************************************************************************** */
}

#include "dictionary.cpp"

#endif