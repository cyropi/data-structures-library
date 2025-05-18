
#include "setlst.hpp"

namespace lasd 
{
    template <typename Data>
    SetLst<Data>::SetLst(const TraversableContainer<Data>& traversableContainer)
    {
        traversableContainer.Traverse([this](const Data& data) 
                                        -> void{ this->Insert(data); });
    }


    template <typename Data>
    SetLst<Data>::SetLst(MappableContainer<Data>&& mappableContainer)
    {
        mappableContainer.Map([this](Data& data) 
                                -> void{ this->Insert(std::move(data)); });
    }


    template <typename Data>
    SetLst<Data>::SetLst(const SetLst<Data>& setLst) : List<Data>::List(setLst)
    {}


    template <typename Data>
    SetLst<Data>::SetLst(SetLst<Data>&& setLst) noexcept : List<Data>::List(std::move(setLst))
    {}
    

    template <typename Data>
    SetLst<Data>::~SetLst() 
    {
        this->Clear();
    }


    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& setLst)
    {
        List<Data>::operator=(setLst);
        return *this;
    }


    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& setLst) noexcept 
    {
        List<Data>::operator=(std::move(setLst));
        return *this;
    }


    template <typename Data>
    bool SetLst<Data>::operator==(const SetLst<Data>& setLst) const noexcept 
    {
        return List<Data>::operator==(setLst);
    }

    
    template <typename Data>
    bool SetLst<Data>::operator!=(const SetLst<Data>& setLst) const noexcept 
    {
        return !(*this == setLst);
    }


    template <typename Data>
    const Data& SetLst<Data>::Min() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il minimo...");

        return List<Data>::Front();
    }


    template <typename Data>
    void SetLst<Data>::RemoveMin() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il minimo...");

        return List<Data>::RemoveFromFront();
    }


    template <typename Data>
    Data SetLst<Data>::MinNRemove() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il minimo...");

        return List<Data>::FrontNRemove();
    }


    template <typename Data>
    const Data& SetLst<Data>::Max() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il massimo...");

        return List<Data>::Back();
    }


    template <typename Data>
    void SetLst<Data>::RemoveMax() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il massimo...");

        return List<Data>::RemoveFromBack();
    }


    template <typename Data>
    Data SetLst<Data>::MaxNRemove() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Set List vuota! Non è possibile prelevare il massimo...");

        return List<Data>::BackNRemove();
    }


    template <typename Data>
    const Data& SetLst<Data>::Predecessor(const Data& data) const noexcept(false)
    {
        if(data > this->Max())
            return this->Max();

        Node* current = this->head;
        Data* predecessor = nullptr;
        while(current != nullptr && current->value < data)
        {
            predecessor = &(current->value);
            current = current->next; 
        }

        if(predecessor == nullptr)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set List...");
        
        return *predecessor;
    }
    

    template <typename Data>
    void SetLst<Data>::RemovePredecessor(const Data& data) noexcept(false)
    {
        if(data > this->Max())
        {
            this->RemoveFromBack();
            return;
        }

        Node* current = this->head;
        Node* predecessor = nullptr;
        Node* prevPredecessor = nullptr;
        while(current != nullptr && current->value < data)
        {
            prevPredecessor = predecessor;
            predecessor = current;
            current = current->next; 
        }

        if(predecessor == nullptr)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set List...");
        
        if(predecessor == this->head)
        {
            this->RemoveFromFront();
            return;
        }
        
        prevPredecessor->next = predecessor->next;
        delete predecessor;
        this->size--;
    }


    template <typename Data>
    Data SetLst<Data>::PredecessorNRemove(const Data& data) noexcept(false)
    {
        Data removedPredecessor;

        if(data > this->Max())
        {
            removedPredecessor = this->BackNRemove();
            return removedPredecessor;
        }

        Node* current = this->head;
        Node* predecessor = nullptr;
        Node* prevPredecessor = nullptr;
        while(current != nullptr && current->value < data)
        {
            prevPredecessor = predecessor;
            predecessor = current;
            current = current->next; 
        }

        if(predecessor == nullptr)
            throw std::length_error("Non è stato possibile trovare il predecessore nel Set List...");
        
        if(predecessor == this->head)
        {
            removedPredecessor = this->FrontNRemove();
            return removedPredecessor;
        }
        
        prevPredecessor->next = predecessor->next;
        removedPredecessor = predecessor->value;
        delete predecessor;
        this->size--;

        return removedPredecessor;
    }


    template <typename Data>
    const Data& SetLst<Data>::Successor(const Data& data) const noexcept(false)
    {
        if(data < this->Min())
            return this->Min();

        Node* current = this->head;
        while(current != nullptr && current->value <= data)
        {
            current = current->next; 
        }

        if(current == nullptr)
            throw std::length_error("Non è stato possibile trovare il successore nel Set List...");
        
        return current->value;
    }


    template <typename Data>
    void SetLst<Data>::RemoveSuccessor(const Data& data) noexcept(false)
    {
        if(data < this->Min())
        {
            this->RemoveFromFront();
            return;
        }
        
        Node* current = this->head;
        Node* previous = nullptr;
        while(current != nullptr && current->value <= data)
        {
            previous = current;
            current = current->next;  
        }

        if(current == nullptr)
            throw std::length_error("Non è stato possibile trovare il successore nel Set List...");
        
        if(current == this->tail)
        {
            this->RemoveFromBack();
            return;
        }
        
        previous->next = current->next;
        delete current;
        this->size--;
    }


    template <typename Data>
    Data SetLst<Data>::SuccessorNRemove(const Data& data) noexcept(false)
    {
        Data removedSuccessor;

        if(data < this->Min())
        {
            removedSuccessor = this->FrontNRemove();
            return removedSuccessor;
        }
        
        Node* current = this->head;
        Node* previous = nullptr;
        while(current != nullptr && current->value <= data)
        {
            previous = current;
            current = current->next;  
        }

        if(current == nullptr)
            throw std::length_error("Non è stato possibile trovare il successore nel Set List...");
        
        if(current == this->tail)
        {
            removedSuccessor = this->BackNRemove();
            return removedSuccessor;
        }
        
        previous->next = current->next;
        removedSuccessor = current->value;
        delete current;
        this->size--;

        return removedSuccessor;
    }

    
    template <typename Data>
    bool SetLst<Data>::Insert(const Data& data)
    {
        if (this->Empty() || data < this->Min())
        {
            this->InsertAtFront(data);
            return true;
        }

        if (data > this->Max())
        {
            this->InsertAtBack(data);
            return true;
        }


        Node* current = this->head;
        Node* previous = nullptr;
        while (current != nullptr)
        {
            if (data == current->value)
            {
                return false;
            }
            else if (data < current->value)
            {
                Node* temp = new Node(data);
                previous->next = temp;
                temp->next = current;
                this->size++;
                
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }


    template <typename Data>
    bool SetLst<Data>::Insert(Data&& data)
    {
        if (this->Empty() || data < this->Min())
        {
            this->InsertAtFront(std::move(data));
            return true;
        }

        if (data > this->Max())
        {
            this->InsertAtBack(std::move(data));
            return true;
        }


        Node* current = this->head;
        Node* previous = nullptr;
        while (current != nullptr)
        {
            if (data == current->value)
            {
                return false;
            }
            else if (data < current->value)
            {
                Node* temp = new Node(std::move(data));
                previous->next = temp;
                temp->next = current;
                this->size++;
                
                return true;
            }
            
            previous = current;
            current = current->next;
        }

        return false;
    }


    template <typename Data>
    bool SetLst<Data>::Remove(const Data &data)
    {
        if (this->Empty()) 
            return false;

        if (data == this->Min()) 
        {
            this->RemoveFromFront();
            return true;
        }

        if (data == this->Max()) 
        {
            this->RemoveFromBack();
            return true;
        }


        Node* current = this->head->next;
        Node* previous = this->head;

        while (current->next != nullptr) 
        {
            if (data == current->value) 
            {
                previous->next = current->next;
                delete current;
                this->size--;

                return true;
            } 
            else if (data < current->value) 
            {
                return false;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }


    template <typename Data>
    bool SetLst<Data>::Exists(const Data &data) const noexcept
    {
        if(data < this->Min() || data > this->Max())
            return false;     

        Node* current = this->head;
        while(current != nullptr)
        {
            if(data == current->value)
                return true;

            current = current->next;
        }

        return false;
    }
}
