

#ifndef LIST_HPP
#define LIST_HPP

#include "../container/linear.hpp"


namespace lasd 
{
	template <typename Data>
	class List : virtual public MutableLinearContainer<Data>,
				 virtual public ClearableContainer
	{
		private:

		protected:
			// using Container::???;

			struct Node 
			{
				// Data
				Data value;
				struct Node* next = nullptr;

				
				Node() = default;


				// Specific constructors
				Node(const Data&);
				Node(Data&&) noexcept;


				// Copy constructor
				Node(const Node&); 
				// Move constructor
				Node(Node&&) noexcept; 


				// Destructor
				virtual ~Node() = default;


				// Comparison operators
				bool operator==(const Node&) const noexcept;
				bool operator!=(const Node&) const noexcept;
			};

 			Node* head = nullptr;
			Node* tail = nullptr;


		public:
			// Default constructor
			List() = default;


			// Specific constructor
			List(const TraversableContainer<Data>&); // A list obtained from a TraversableContainer
			List(MappableContainer<Data>&&); // A list obtained from a MappableContainer


			// Copy constructor
			List(const List<Data>&); 

			// Move constructor
			List(List<Data>&&) noexcept; 


			// Destructor
			virtual ~List();


			// Copy assignment
			List<Data>& operator=(const List<Data>&); 

			// Move assignment
			List<Data>& operator=(List<Data>&&) noexcept; 


			// Comparison operators
			bool operator==(const List<Data>&) const noexcept;
			bool operator!=(const List<Data>&) const noexcept;


			// Specific member functions
			void InsertAtFront(const Data&); // Copy of the value
			void InsertAtFront(Data&&); //  Move of the value
			void RemoveFromFront() noexcept(false); // (must throw std::length_error when empty)
			Data FrontNRemove() noexcept(false); // (must throw std::length_error when empty)

			void InsertAtBack(const Data&); // Copy of the value
			void InsertAtBack(Data&&); //  Move of the value
			void RemoveFromBack() noexcept(false); // (must throw std::length_error when empty)
			Data BackNRemove() noexcept(false); // (must throw std::length_error when empty)			


			// Specific member functions (inherited from MutableLinearContainer)
			Data& operator[](ulong) noexcept(false) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
			Data& Front() noexcept(false) override; // Override MutableLinearContainer member (must throw std::length_error when empty)
			Data& Back() noexcept(false) override; // Override MutableLinearContainer member (must throw std::length_error when empty)


			// Specific member functions (inherited from LinearContainer)
			const Data& operator[](ulong) const noexcept(false) override;  // Override LinearContainer member (must throw std::out_of_range when out of range)
			const Data& Front() const noexcept(false) override; // Override LinearContainer member (must throw std::length_error when empty)
			const Data& Back() const noexcept(false) override; // Override LinearContainer member (must throw std::length_error when empty)


			// Specific member function (inherited from MappableContainer)
			using typename MappableContainer<Data>::MapFun;
			void Map(MapFun) override; // Override MappableContainer member

			// Specific member function (inherited from PreOrderMappableContainer)
			void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

			// Specific member function (inherited from PostOrderMappableContainer)
			void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member


			// Specific member function (inherited from TraversableContainer)
			using typename TraversableContainer<Data>::TraverseFun;
			void Traverse(TraverseFun) const override; // Override TraversableContainer member

			// Specific member function (inherited from PreOrderTraversableContainer)
			void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

			// Specific member function (inherited from PostOrderTraversableContainer)
			void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member


			// Specific member function (inherited from ClearableContainer)
			void Clear() override; // Override ClearableContainer member


		protected:
			// Auxiliary functions, if necessary!
/* 			void PreOrderTraverse(TraverseFun,Node *) const;
 			void PostOrderTraverse(TraverseFun, Node *) const;

  			void PreOrderMap(MapFun,Node *);
  			void PostOrderMap(MapFun,Node *); */

	};
}

#include "list.cpp"

#endif
