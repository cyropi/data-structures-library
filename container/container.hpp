
#ifndef CONTAINER_HPP
#define CONTAINER_HPP


/* ************************************************************************** */
namespace lasd 
{
	/* ************************************************************************** */
	class Container 
	{
		private:


		protected:
			unsigned long size = 0;

			/* ************************************************************************ */
			// Default constructor
			Container() = default;


		public:
			// Destructor
			virtual ~Container() = default;


			/* ************************************************************************ */
			// Copy assignment
			Container& operator=(const Container&) = delete; 
			// Move assignment
			Container& operator=(Container&&) noexcept = delete; 


			/* ************************************************************************ */
			// Comparison operators
			Container& operator==(const Container&) const noexcept = delete;
			Container& operator!=(const Container&) const noexcept = delete;


			/* ************************************************************************ */
			// Specific member functions
			inline virtual bool Empty() const noexcept
			{
				if(size == 0)
					return true;

				return false;
			};
		
			inline virtual unsigned long Size() const noexcept
			{
				return size;
			};
		};



		/* ************************************************************************** */
		class ClearableContainer : virtual public Container
		{
			private:


			protected:


			public:
				// Destructor
				virtual ~ClearableContainer() = default;


				/* ************************************************************************ */
				// Copy assignment
				ClearableContainer& operator=(const Container&) = delete;
				// Move assignment
				ClearableContainer& operator=(Container&&) = delete;


				/* ************************************************************************ */
				// Comparison operators
				ClearableContainer& operator==(const ClearableContainer&) const noexcept = delete;
				ClearableContainer& operator!=(const ClearableContainer&) const noexcept = delete;


				/* ************************************************************************ */
				// Specific member functions
				virtual void Clear() = 0;
		};



		/* ************************************************************************** */
		class ResizableContainer : virtual public ClearableContainer
		{			
			private:


			protected:


			public:
				// Destructor
				virtual ~ResizableContainer() = default;


				/* ************************************************************************ */
				// Copy assignment
				ResizableContainer& operator=(const ResizableContainer&) = delete;
				// Move assignment
				ResizableContainer& operator=(ResizableContainer&&) = delete;


				/* ************************************************************************ */
				// Comparison operators
				ResizableContainer& operator==(const ResizableContainer&) const noexcept = delete;
				ResizableContainer& operator!=(const ResizableContainer&) const noexcept = delete;


				/* ************************************************************************ */
				// Specific member functions
				virtual void Resize(unsigned long) = 0;


				/* ************************************************************************ */
				// Specific member function (inherited from ClearableContainer)
				inline void Clear() override
				{
					Resize(0);
				};
		};
	/* ************************************************************************** */
}

#endif