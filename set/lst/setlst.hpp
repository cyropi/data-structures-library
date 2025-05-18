

#ifndef SETLST_HPP
#define SETLST_HPP

#include "../set.hpp"
#include "../../list/list.hpp"


namespace lasd 
{
	template <typename Data>
	class SetLst : virtual public Set<Data>,
				   virtual public List<Data>
	{ 
		private:
			// ...

		protected:
			// using Container::???;
			using typename List<Data>::Node;
			//using List<Data>::Clear;


		public:
			// Default constructor
			SetLst() = default;


			// Specific constructors
			SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
			SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer


			// Copy constructor
			SetLst(const SetLst<Data>&);

			// Move constructor
			SetLst(SetLst<Data>&&) noexcept;


			// Destructor
			virtual ~SetLst();


			// Copy assignment
			SetLst<Data>& operator=(const SetLst<Data>&);

			// Move assignment
			SetLst<Data>& operator=(SetLst<Data>&&) noexcept;


			// Comparison operators
			bool operator==(const SetLst<Data>&) const noexcept;
			bool operator!=(const SetLst<Data>&) const noexcept;


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
			//const Data& operator[](ulong) const noexcept(false) override; // Override LinearContainer member (must throw std::out_of_range when out of range)


			// Specific member function (inherited from TestableContainer)
			bool Exists(const Data&) const noexcept override; // Override TestableContainer member


			// Specific member function (inherited from ClearableContainer)
			//void Clear() override; // Override ClearableContainer member


		protected:
			// Auxiliary functions, if necessary!

	};
}

#include "setlst.cpp"

#endif
