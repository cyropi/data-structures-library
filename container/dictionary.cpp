

#include <stdexcept>


namespace lasd 
{
	// DictionaryContainer

	template <typename Data>
	bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& traversableContainer)
	{
		bool insertedAll = true;

		traversableContainer.Traverse([this, &insertedAll] (const Data& data) 
										-> void{ if(!(this->Insert(data))) 
												 	insertedAll = false; });
		return insertedAll;
	}



	template <typename Data>
	bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mappableContainer)
	{
		bool insertedAll = true;

		mappableContainer.Map([this, &insertedAll] (Data& data) 
								-> void{ if(!(this->Insert(std::move(data)))) 
											insertedAll = false; });
		return insertedAll;
	}



	template <typename Data>
	bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& traversableContainer)
	{
		bool removedAll = true;

		traversableContainer.Traverse([this, &removedAll] (const Data& data) 
										-> void{ if(!(this->Remove(data))) 
													removedAll = false; });
		return removedAll;
	}



	template <typename Data>
	bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& traversableContainer)
	{
		bool insertedSome = false;

		traversableContainer.Traverse([this, &insertedSome] (const Data& data) 
									    -> void{ if(this->Insert(data)) 
													insertedSome = true; });
		return insertedSome;
	}



	template <typename Data>
	bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mappableContainer)
	{
		bool insertedSome = false;

		mappableContainer.Map([this, &insertedSome] (Data& data) 
								-> void{ if(this->Insert(std::move(data))) 
											insertedSome = true; });
		return insertedSome;
	}



	template <typename Data>
	bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& traversableContainer)
	{
		bool removedSome = false;

		traversableContainer.Traverse([this, &removedSome] (const Data& data) 
									    -> void{ if(this->Remove(data)) 
													removedSome = true; });
		return removedSome;
	}




	// OrderedDictionaryContainer

	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemoveMin() noexcept(false)
	{
		try
		{
			const Data& min = this->Min();
			this->Remove(min);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (RemoveMin): " << e.what() << '\n';
			throw e;
		}
	}



	template <typename Data>
	Data OrderedDictionaryContainer<Data>::MinNRemove() noexcept(false)
	{
		Data minValue;

		try
		{
			const Data& min = this->Min();
			minValue = min;
			this->Remove(min);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (MinNRemove): " << e.what() << '\n';
			throw e;
		}

		return minValue;
	}



	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemoveMax() noexcept(false)
	{
		try
		{
			const Data& max = this->Max();
			this->Remove(max);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (RemoveMax): " << e.what() << '\n';
			throw e;
		}
	}



	template <typename Data>
	Data OrderedDictionaryContainer<Data>::MaxNRemove() noexcept(false)
	{
		Data maxValue;

		try
		{
			const Data& max = this->Max();
			maxValue = max;
			this->Remove(max);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (MaxNRemove): " << e.what() << '\n';
			throw e;
		}

		return maxValue;
	}



	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data& data) noexcept(false)
	{
		try
		{
			const Data& predecessor = this->Predecessor(data);
			this->Remove(predecessor);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (RemovePredecessor): " << e.what() << '\n';
			throw e;
		}
	}



	template <typename Data>
	Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data& data) noexcept(false)
	{
		Data predecessorValue;

		try
		{
			const Data& predecessor = this->Predecessor(data);
			predecessorValue = predecessor;
			this->Remove(predecessor);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (PredecessorNRemove): " << e.what() << '\n';
			throw e;
		}

		return predecessorValue;
	}



	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data& data)
	{
		try
		{
			const Data& successor = this->Successor(data);
			this->Remove(successor);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (RemoveSuccessor): " << e.what() << '\n';
			throw e;
		}
	}



	template <typename Data>
	Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data& data)
	{
		Data successorValue;

		try
		{
			const Data& successor = this->Successor(data);
			successorValue = successor;
			this->Remove(successor);
		}
		catch(const std::length_error& e)
		{
			std::cerr << "Exception occurred in OrderedDictionaryContainer (SuccessorNRemove): " << e.what() << '\n';
			throw e;
		}

		return successorValue;
	}
}
