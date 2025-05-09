
#ifndef LINEAR_HPP
#define LINEAR_HPP


/* ************************************************************************** */
#include "mappable.hpp"


/* ************************************************************************** */
namespace lasd 
{
	/* ************************************************************************** */
	template <typename Data>
	class LinearContainer : virtual public PreOrderTraversableContainer<Data>, PostOrderTraversableContainer<Data>
	{
		private:


		protected:


		public:
			// Destructor
			virtual ~LinearContainer() = default;


			/* ************************************************************************ */
			// Copy assignment
			LinearContainer& operator=(const LinearContainer&) = delete;
			// Move assignment
			LinearContainer& operator=(LinearContainer&&) noexcept = delete;


			/* ************************************************************************ */
			// Comparison operators
			virtual bool operator==(const LinearContainer<Data>&) const noexcept; 
			virtual bool operator!=(const LinearContainer<Data>&) const noexcept;


			/* ************************************************************************ */
			// Specific member functions
			virtual const Data& operator[](ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
			virtual const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
			virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)


			/* ************************************************************************ */
			// Specific member function (inherited from TraversableContainer)
			using typename TraversableContainer<Data>::TraverseFun;
			void Traverse(TraverseFun) const override;


			/* ************************************************************************ */
			// Specific member function (inherited from PreOrderTraversableContainer)
			void PreOrderTraverse(TraverseFun) const override;


			/* ************************************************************************ */
			// Specific member function (inherited from PostOrderTraversableContainer)
			void PostOrderTraverse(TraverseFun) const override;
	};



	/* ************************************************************************** */
	template <typename Data>
	class MutableLinearContainer : virtual public LinearContainer<Data>, PreOrderMappableContainer<Data>, PostOrderMappableContainer<Data>
	{
		private:


		protected:


		public:
			// Destructor
			virtual ~MutableLinearContainer() = default;


			/* ************************************************************************ */
			// Copy assignment
			MutableLinearContainer& operator=(const MutableLinearContainer&) = delete;
			// Move assignment
			MutableLinearContainer& operator=(MutableLinearContainer&&) = delete;


			/* ************************************************************************ */
			// Specific member functions
			virtual Data& operator[](ulong) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)
			virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)
			virtual Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)


			/* ************************************************************************ */
			// Specific member function (inherited from MappableContainer)
			using typename MappableContainer<Data>::MapFun;
			void Map(MapFun) override; 


			/* ************************************************************************ */
			// Specific member function (inherited from PreOrderMappableContainer)
			void PreOrderMap(MapFun) override;


			/* ************************************************************************ */
			// Specific member function (inherited from PostOrderMappableContainer)
			void PostOrderMap(MapFun) override;
	};



	/* ************************************************************************** */
	template <typename Data>
	class SortableLinearContainer : virtual public MutableLinearContainer<Data>
	{
		private:


		protected:


		public:
			// Destructor
			virtual ~SortableLinearContainer() = default;


			/* ************************************************************************ */
			// Copy assignment
			SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;
			// Move assignment
			SortableLinearContainer& operator=(SortableLinearContainer&&) = delete;


			/* ************************************************************************ */
			// Specific member function
			virtual void Sort();


		protected:
			// Auxiliary member functions
	};
	/* ************************************************************************** */
}

//#include "linear.cpp"

#endif
