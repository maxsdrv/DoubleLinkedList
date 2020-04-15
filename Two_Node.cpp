/*
My own implementation Double Linked List
*/


#include <iostream>
#include <ctime>
#include <array>
#include <cassert>


using namespace std;

template<typename T>
class TwoNode
{
public:
	TwoNode();
	~TwoNode();

	
	void push_back( T data); //add in the end list
	void push_front( T data); //add in start list
	void insert( T data, int index);// add by index
	void pop_front(); // remove from start list
	void pop_back(); //remove from end of list
	void removeAt(int index); // remove by index
	void clear();//clear all list
	
	void sort();// not fully implemented
	int GetSize() { return Size; } // size list
	T& operator[](const int index); //overload []
	

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		friend Node* merge_swap(Node* _first, Node* _second)
		{
			return nullptr;
		}
	

	private:		
	};
	int Size;
	Node<T>* head;
	Node<T>* tail;
	
};



int main()
{
	using std::cout;
	using std::endl;

	srand(time(0));
		TwoNode<int> tw;

		tw.push_back(1);
		tw.push_back(2);
		tw.push_back(3);
		tw.push_back(4);
		tw.push_front(5);

		//tw.sort();
		

		for (int i = 0; i < tw.GetSize(); i++)
		{
			cout << tw[i] << endl;
		}

		cout << "runtime = " << clock() / 1000.0 << endl;

	return 0;
}

template<typename T>
TwoNode<T>::TwoNode()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
TwoNode<T>::~TwoNode()
{
	cout << "Destructor" << endl;
	clear();
}

template<typename T>
void TwoNode<T>::push_back( T data)
{
	if (head == nullptr)
	{
		head = tail = new Node<T>(data, head, tail);
	}
	else if (GetSize() == 1)
	{
		tail = new Node<T>(data, nullptr, tail);
		head->pNext = this->tail;
	}
	else
	{
		Node<T>* temp = tail;
		tail = new Node<T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	Size++;
}

template<typename T>
void TwoNode<T>::push_front(T data)
{
	if (head == nullptr)
	{
		head = tail = new Node<T>(data, head, tail);
	}
	else if (GetSize() == 1)
	{
		head = new Node<T>(data, head);
		tail->pPrev = this->head;
	}
	else
	{
		Node<T>* temp = head;
		head = new Node<T>(data, head);
		temp->pPrev = head;
	}
	
	Size++;
}

template<typename T>
void TwoNode<T>::insert( T data, int index)
{
	if (index == NULL)
	{
		push_front(data);
	}
	else if (index <= GetSize() / 2)
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext, previous);

		previous->pNext = newNode;
		Node<T>* next = newNode->pNext;
		next->pPrev = newNode;

		//newNode->pNext->pPrev = newNode;

		Size++;
	}

	else 
	{
		Node<T>* _next = this->tail;

		for (int i = Size - 1; index < i; i--)
		{
			_next = _next->pPrev;
		}
		
		Node<T>* newNode = new Node<T>(data, _next, _next->pPrev);
		_next->pPrev = newNode;
		Node<T>* _pr_node = newNode->pPrev;
		_pr_node->pNext = newNode;
		
		Size++;
	}
}

template<typename T>
void TwoNode<T>::pop_front()
{

	Node<T>* temp = head;

	head = head->pNext;

	delete temp;
	Size--;
}

template<typename T>
void TwoNode<T>::pop_back()
{
	while (tail != nullptr)
	{
		Node<T>* temp = tail;
		tail = tail->pPrev;

		delete temp;
		Size--;

		break;
	}
	
	
}

template<typename T>
void TwoNode<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == GetSize())
	{
		pop_back();
	}
	else if (index <= GetSize() / 2)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* to_delete = previous->pNext;
		previous->pNext = to_delete->pNext;
		Node<T>* next = to_delete->pNext;
		next->pPrev = previous;
		delete to_delete;
		Size--;
	}
	else
	{
		Node<T>* next = this->tail;
		
		for ( int i = GetSize() - 1; i > index; i--)
		{
			next = next->pPrev;
		}
		Node<T>* to_delete = next->pPrev;
		next->pPrev = to_delete->pPrev;
		Node<T>* p_prev = to_delete->pPrev;
		p_prev->pNext = next;
		Size--;
	}
	

}

template<typename T>
void TwoNode<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
	
}


template<typename T>
void TwoNode<T>::sort()
{
	array<Node<T>*, 32> keys = {};
	auto hook_end = keys.begin();

	while (head != nullptr)
	{
		Node<T>* next = head->pNext;
		head->pNext = nullptr;

		auto hook = keys.begin();
		for ( ; hook != hook_end && *hook != nullptr; ++hook)
		{
			head = merge_swap(head, *hook);
			*hook = nullptr;
		}

		if (hook == hook_end)
			if (hook < keys.end())
				hook = hook_end++;
			else
				--hook;

		assert(*hook == nullptr);
		*hook = head;

		head = next;

	
	}
	


	
}



template<typename T>
T& TwoNode<T>::operator[](const int index)
{

	Node<T>* cur_head = this->head;
	Node<T>* cur_tail = this->tail;

	int count_f_head = 0;
	int count_f_tail = GetSize() - 1; // we say that this is the zero element from the end

	while (cur_head && cur_tail != nullptr)
	{
		if (count_f_head == index)
		{
			return cur_head->data;
		}
		else if (index <= GetSize() / 2)
		{
			cur_head = cur_head->pNext;
			count_f_head++;
		}
		else
		{	
			
			if (count_f_tail == index)
			{
				return cur_tail->data;
			}
			cur_tail = cur_tail->pPrev;
			count_f_tail--;
			
			
		}
	}
	

	
}

