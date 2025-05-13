
//#include "traversable.hpp"


namespace lasd 
{    
    // TraversableContainer

    template <typename Data>
    template <typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        this->Traverse([foldFun, &accumulator] (const Data& data) 
                        -> void{ accumulator = foldFun(data, accumulator); });

        return accumulator;
    }


    template <typename Data>
    bool TraversableContainer<Data>::Exists(const Data& inputData) const noexcept 
    {
        bool isPresent = false;
        
        this->Traverse([inputData, &isPresent] (const Data& containerData) 
                        -> void{ if(inputData == containerData) isPresent = true; });

        return isPresent;
    }



    // PreOrderTraversableContainer

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        this->PreOrderTraverse([foldFun, &accumulator] (const Data& data) 
                                -> void{ accumulator = foldFun(data, accumulator); });

        return accumulator;
    }


    template <typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFun) const 
    {
        this->PreOrderTraverse(traverseFun);
    }



    // PostOrderTraversableContainer

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        this->PostOrderTraverse([foldFun, &accumulator] (const Data& data) 
                                 -> void{ accumulator = foldFun(data, accumulator); });

        return accumulator;
    }


    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFun) const 
    {
        this->PostOrderTraverse(traverseFun);
    }
}
