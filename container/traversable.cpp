
#include "traversable.hpp"

namespace lasd 
{
    /* ************************************************************************** */
    // (TraversableContainer)

    template <typename Data>
    template <typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        Traverse
        (
            [foldFun, &accumulator] (const Data& data) -> void{ accumulator = foldFun(data, accumulator); }
        );

        return accumulator;
    };


    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data& inputData) const noexcept 
    {
        bool isPresent = false;
        
        Traverse
        (
            [inputData, &isPresent] (const Data& containerData) -> void{ if(inputData == containerData) isPresent = true; }
        );

        return isPresent;
    };



    /* ************************************************************************** */
    // PreOrderTraversableContainer

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        PreOrderTraverse
        (
            [foldFun, &accumulator] (const Data& data) -> void{ accumulator = foldFun(data, accumulator); }
        );

        return accumulator;
    };


    template <typename Data>
    inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFun) const 
    {
        PreOrderTraverse(traverseFun);
    };



    /* ************************************************************************** */
    // PostOrderTraversableContainer

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
    {
        PostOrderTraverse
        (
            [foldFun, &accumulator] (const Data& data) -> void{ accumulator = foldFun(data, accumulator); }
        );

        return accumulator;
    };


    template <typename Data>
    inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFun) const 
    {
        PostOrderTraverse(traverseFun);
    };

    /* ************************************************************************** */
}