
#include "mappable.hpp"


namespace lasd 
{
	/* ************************************************************************** */
    // (PreOrderMappableContainer)

    template <typename Data>
	void PreOrderMappableContainer<Data>::Map(MapFun mapFun)
	{
		PreOrderMap(mapFun);
	}



	/* ************************************************************************** */
	// (PostOrderMappableContainer)

    template <typename Data>
	void PostOrderMappableContainer<Data>::Map(MapFun mapFun)
	{
		PostOrderMap(mapFun);
	}
	
	/* ************************************************************************** */
}
