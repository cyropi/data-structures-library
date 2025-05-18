

#ifndef SETVEC_HPP
#define SETVEC_HPP

#include "../set.hpp"
#include "../../vector/vector.hpp"



namespace lasd 
{
    template <typename Data>
    class SetVec : virtual public Set<Data>,
                   //virtual public ResizableContainer<Data>,
                   virtual protected Vector<Data>
    {
        private:
            // ...

        protected:
            // using Container::???;
            // ...


        public:
            // Default constructor
            SetVec() = default;


            // Specific constructors
            SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
            SetVec(MappableContainer<Data>&&); // A set obtained from a MappableContainer


            // Copy constructor
            SetVec(const SetVec<Data>&);

            // Move constructor
            SetVec(SetVec<Data>&&) noexcept;


            // Destructor
            virtual ~SetVec();


            // Copy assignment
            SetVec<Data>& operator=(const SetVec<Data>&);

            // Move assignment
            SetVec<Data>& operator=(SetVec<Data>&&);


            // Comparison operators
            bool operator=(const SetVec<Data>&) const noexcept;
            bool operator!=(const SetVec<Data>&) const noexcept;


            // Specific member functions (inherited from OrderedDictionaryContainer)
			const Data& Min() const noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
			void RemoveMin() noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
			Data MinNRemove() noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

			const Data& Max() const noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
			void RemoveMax() noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
			Data MaxNRemove() noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

			const Data& Predecessor(const Data&) const noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
			void RemovePredecessor(const Data&) noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
			Data PredecessorNRemove(const Data&) noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

			const Data& Successor(const Data&) const noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
			void RemoveSuccessor(const Data&) noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
			Data SuccessorNRemove(const Data&) noexcept(false) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)


			// Specific member functions (inherited from DictionaryContainer)
			bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
			bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
			bool Remove(const Data&) override; // Override DictionaryContainer member


			// Specific member functions (inherited from LinearContainer)
			const Data& operator[](ulong) const noexcept(false) override; // Override LinearContainer member (must throw std::out_of_range when out of range)


			// Specific member function (inherited from TestableContainer)
			bool Exists(const Data&) const noexcept override; // Override TestableContainer member


			// Specific member function (inherited from ClearableContainer)
			void Clear() override; // Override ClearableContainer member


        protected:
            // Auxiliary functions, if necessary!
    };
}

#include "setvec.cpp"

#endif
