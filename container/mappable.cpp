
#include "mappable.hpp"

namespace lasd 
{
	/* ************************************************************************** */
    // (PreOrderMappableContainer)

    template <typename Data>
	inline void PreOrderMappableContainer<Data>::Map(MapFun mapFun)
	{
		PreOrderMap(mapFun);
	}



	/* ************************************************************************** */
	// (PostOrderMappableContainer)

    template <typename Data>
	inline void PostOrderMappableContainer<Data>::Map(MapFun mapFun)
	{
		PostOrderMap(mapFun);
	}
}