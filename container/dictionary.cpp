

//#include "dictionary.hpp"
#include "mappable.hpp"
#include <utility>
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
	void OrderedDictionaryContainer<Data>::RemoveMin()
	{
		const Data& min = this->Min();
		this->Remove(min);
	}


	template <typename Data>
	Data OrderedDictionaryContainer<Data>::MinNRemove()
	{
		const Data& min = this->Min();
		Data minValue = min;
		this->Remove(min);

		return minValue;
	}


	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemoveMax()
	{
		const Data& max = this->Max();
		this->Remove(max);
	}


	template <typename Data>
	Data OrderedDictionaryContainer<Data>::MaxNRemove()
	{
		const Data& max = this->Max();
		Data maxValue = max;
		this->Remove(max);

		return maxValue;
	}


	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data& data)
	{
		const Data& predecessor = this->Predecessor(data);
		this->Remove(predecessor);
	}


	template <typename Data>
	Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data& data)
	{
		const Data& predecessor = this->Predecessor(data);
		Data predecessorValue = predecessor;
		this->Remove(predecessor);

		return predecessorValue;
	}


	template <typename Data>
	void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data& data)
	{
		const Data& successor = this->Successor(data);
		this->Remove(successor);
	}


	template <typename Data>
	Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data& data)
	{
		const Data& successor = this->Successor(data);
		Data successorValue = successor;
		this->Remove(successor);

		return successorValue;
	}
}
