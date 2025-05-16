

namespace lasd 
{
    template <typename Data>
    List<Data>::Node::Node(const Data& data)
    {
        this->value = data;
    }


    template <typename Data>
    List<Data>::Node::Node(Data&& data) noexcept
    {
        this->value = std::move(data);
    }


    template <typename Data>
    List<Data>::Node::Node(const Node& node)
    {
        this->value = node.value;
    }


    template <typename Data>
    List<Data>::Node::Node(Node&& node) noexcept
    {
        std::swap(this->value, node.value);
        std::swap(this->next, node.next);
    }


/*     template <typename Data>
    List<Data>::Node::~Node() 
    {
        //delete this->next;
    } */


    template <typename Data>
    bool List<Data>::Node::operator==(const Node& node) const noexcept
    {
        return this->value == node.value ? true : false;
    }

    
    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& node) const noexcept
    {
        return !(*this == node);
    }


    template <typename Data>
    List<Data>::List(const TraversableContainer<Data>& traversableContainer)
    {
        traversableContainer.Traverse([this](const Data& data) 
                                        -> void{ this->InsertAtBack(data); });
    }


    template <typename Data>
    List<Data>::List(MappableContainer<Data>&& mappableContainer)
    {
        mappableContainer.Map([this](Data& data) 
                                -> void{ this->InsertAtBack(std::move(data)); });
    }


    template <typename Data>
    List<Data>::List(const List<Data>& list)
    {
	    if( list.Size() == 0 )
		    return;
            
        this->size = list.Size();
        this->head = new Node(*(list.head));
        this->tail = this->head;

	    Node* cursor = list.head->next;
	    while( cursor != nullptr )
        {
            this->tail->next = new Node(*cursor);
            this->tail = this->tail->next; 
            cursor = cursor->next;
        }
    }


    template <typename Data>
    List<Data>::List(List<Data>&& list) noexcept
    {        
        std::swap(this->size, list.size);
        std::swap(this->head, list.head);
        std::swap(this->tail, list.tail);  
    }
    

/* template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& other) {
    if (this != &other)
    {
        Clear();
        Node * cur = other.head;
        while (cur != nullptr)
        {
            InsertAtBack(cur->data);
            cur = cur->next;
        }
    }
    return *this; 
    } */


    template <typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& list)
    {        
        List<Data> tmpList = list;
        std::swap(tmpList, *this);
        
        return *this;
    }


    template <typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& list) noexcept 
    {
        std::swap(this->size, list.size);
        std::swap(this->head, list.head);
        std::swap(this->tail, list.tail); 
        
        return *this;
    }


    template <typename Data>
    List<Data>::~List() 
    {
/*         delete this->head;
        //delete this->tail;

        this->head = this->tail = nullptr;
        this->size = 0; */

        this->Clear();
    }


    template <typename Data>
    bool List<Data>::operator==(const List<Data>& list) const noexcept
    {
        if(this->size != list.Size())
            return false;
        
        Node* thisCurrent = this->head;
        Node* thatCurrent = list.head;

        while(thisCurrent != nullptr)
        {
            if(thisCurrent->value != thatCurrent->value)
                return false;
            
            thisCurrent = thisCurrent->next;
            thatCurrent = thatCurrent->next;
        } 

        return true;
    }


    template <typename Data>
    bool List<Data>::operator!=(const List<Data>& list) const noexcept
    {
        return !(*this == list);
    }


    template <typename Data>
    void List<Data>::InsertAtFront(const Data& data)
    {
        Node* newHead = new Node(data);
        newHead->next = this->head;
        this->head = newHead;
        this->size++;

        if(this->tail == nullptr)
            this->tail = this->head;        
    }


    template <typename Data>
    void List<Data>::InsertAtFront(Data&& data)
    {
        Node* newHead = new Node(std::move(data));
        newHead->next = this->head;
        this->head = newHead;
        this->size++;

        if(this->tail == nullptr)
            this->tail = this->head;        
    }


    template <typename Data>
    void List<Data>::RemoveFromFront() noexcept(false)
    {
        if(this->size == 0)
            throw std::length_error("Lista vuota! Non è possibile rimuovere l'elemento in testa...");

        Node* headToRemove = this->head;
        this->head = this->head->next;
        delete headToRemove;   
        this->size--;

        if(this->head == nullptr)
            this->tail = this->head;
    }


    template <typename Data>
    Data List<Data>::FrontNRemove() noexcept(false)
    {
        if(this->size == 0)
            throw std::length_error("Lista vuota! Non è possibile rimuovere l'elemento in testa...");

        Node* headToRemove = this->head;
        this->head = this->head->next;
        Data removedHeadValue = headToRemove->value;
        delete headToRemove;   
        this->size--;

        if(this->head == nullptr)
            this->tail = this->head;

        return removedHeadValue;
    }


    template <typename Data>
    void List<Data>::InsertAtBack(const Data& data)
    {
        Node* newTail = new Node(data);

        if(this->tail != nullptr)
            this->tail->next = newTail;
        else
            this->head = newTail;

        this->tail = newTail;
        this->size++;
    }


    template <typename Data>
    void List<Data>::InsertAtBack(Data&& data)
    {
        Node* newTail = new Node(data);

        if(this->tail != nullptr)
            this->tail->next = newTail;
        else
            this->head = newTail;

        this->tail = newTail;
        this->size++;
    }


    template <typename Data>
    void List<Data>::RemoveFromBack() noexcept(false)
    {
        if(this->size == 0)
            throw std::length_error("Lista vuota! Non è possibile rimuovere l'elemento in coda...");

        if(this->size == 1)
        {
            this->RemoveFromFront();
            return;
        }

        Node* current = this->head;
        while(current->next->next != nullptr)
        {
            current = current->next;
        } 

        delete this->tail;
        this->tail = current;
        this->tail->next = nullptr;
        this->size--;
    }


    template <typename Data>
    Data List<Data>::BackNRemove() noexcept(false)
    {
        if(this->size == 0)
            throw std::length_error("Lista vuota! Non è possibile rimuovere l'elemento in coda...");

        if(this->size == 1)
        {
            Data removedTailValue = this->FrontNRemove();
            return removedTailValue;
        }

        Node* current = this->head;
        while(current->next->next != nullptr)
        {
            current = current->next;
        } 

        delete this->tail;
        this->tail = current;
        this->tail->next = nullptr;
        this->size--;
        Data removedTailValue = current->value;

        return removedTailValue;
    }


    template<typename Data>
	const Data& List<Data>::operator[](ulong index) const noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione della lista...");
        
        Node* current = this->head;
        for(ulong i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }


    template<typename Data>
	const Data& List<Data>::Front() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Lista vuota! Non è possibile prelevare il primo elemento...");

        return this->head->value;
    }


    template<typename Data>
	const Data& List<Data>::Back() const noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Lista vuota! Non è possibile prelevare l'ultimo elemento...");

        return this->tail->value;
    }


    template<typename Data>
	Data& List<Data>::operator[](ulong index) noexcept(false)
    {
        if(index >= this->size)
            throw std::out_of_range("Indice non valido! Sei fuori dal range della dimensione della lista...");
        
        Node* current = this->head;
        for(ulong i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }


    template<typename Data>
	Data& List<Data>::Front() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Lista vuota! Non è possibile prelevare il primo elemento...");

        return this->head->value;
    }

    
    template<typename Data>
	Data& List<Data>::Back() noexcept(false)
    {
        if(this->Empty())
            throw std::length_error("Lista vuota! Non è possibile prelevare l'ultimo elemento...");

        return this->tail->value;
    }


    template <typename Data>
    void List<Data>::Map(MapFun mapFun)
    {
        this->PreOrderMap(mapFun);
    }


    template <typename Data>
    void List<Data>::PreOrderMap(MapFun mapFun)
    {
        Node* current = this->head;
        while(current != nullptr)
        {
            mapFun(current->value);
            current = current->next;
        }
    }


    template <typename Data>
    void List<Data>::PostOrderMap(MapFun mapFun)
    {
        std::function<void(Node*)> postOrderMap = [&](Node* currentNode)
                                                    -> void{ if(currentNode == nullptr) 
                                                                return; 

                                                             postOrderMap(currentNode->next); 
                                                             mapFun(currentNode->value); };

        postOrderMap(this->head);
    }


    template <typename Data>
    void List<Data>::Traverse(TraverseFun traverseFun) const
    {
        this->PreOrderTraverse(traverseFun);
    }


    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun traverseFun) const
    {
        Node* current = this->head;
        while(current != nullptr)
        {
            traverseFun(current->value);
            current = current->next;
        }
    }


    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun traverseFun) const
    {
        std::function<void(Node*)> postOrderTraverse = [&](Node* currentNode)
                                                        -> void{ if(currentNode == nullptr) 
                                                                    return; 

                                                                 postOrderTraverse(currentNode->next); 
                                                                 traverseFun(currentNode->value); };

        postOrderTraverse(this->head);
    }


    template <typename Data>
void List<Data>::Clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

}
