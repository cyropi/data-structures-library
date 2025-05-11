
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../container/linear.hpp"


namespace lasd 
{
	template <typename Data>
	class Vector : virtual public MutableLinearContainer<Data>, 
				   virtual public ResizableContainer
	{
		private:

		protected:
			using Container::size;
			Data* array = nullptr;

			using LinearContainer<Data>::operator==;
			using LinearContainer<Data>::operator!=;


		public:
			// Default constructor
			Vector() = default;


			// Specific constructors
			Vector(const ulong); // A vector with a given initial dimension
			Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
			Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer


			// Copy constructor
			Vector(const Vector<Data>&);
			// Move constructor
			Vector(Vector<Data>&&) noexcept;


			// Destructor
			virtual ~Vector();


			// Copy assignment
            Vector<Data>& operator=(const Vector<Data>&); 
			// Move assignment
            Vector& operator=(Vector<Data>&&) noexcept; 


			// Comparison operators
			bool operator==(const Vector<Data>&) const noexcept;
			bool operator!=(const Vector<Data>&) const noexcept;


			// Specific member functions (inherited from LinearContainer)
			const Data& operator[](ulong) const noexcept(false) override;  // Override LinearContainer member (must throw std::out_of_range when out of range)


			// Specific member functions (inherited from MutableLinearContainer)
			Data& operator[](ulong) noexcept(false) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)


			// Specific member function (inherited from ResizableContainer)
			void Resize(ulong) override;


		protected:
			// Auxiliary functions, if necessary!
	};



	template <typename Data>
	class SortableVector : virtual public Vector<Data>, 
						   virtual public SortableLinearContainer<Data>
	{
		private:

		protected:
			using Container::size;


		public:
			// Default constructor
			SortableVector() = default;


			// Specific constructors
			SortableVector(const ulong); // A vector with a given initial dimension
			SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
			SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer


			// Copy constructor
			SortableVector(const SortableVector<Data>&);
			// Move constructor
			SortableVector(SortableVector<Data>&&);


			// Destructor
			virtual ~SortableVector() = default;


			// Copy assignment
    		SortableVector<Data>& operator=(const SortableVector<Data>&);
			// Move assignment
			SortableVector<Data>& operator=(SortableVector<Data>&&) noexcept;


		protected:
			// Auxiliary functions, if necessary!
	};

}

#include "vector.cpp"

#endif
