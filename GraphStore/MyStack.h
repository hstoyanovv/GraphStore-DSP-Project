#ifndef MyStack_H
#define MyStack_H

template<typename T>
class MyStack
{
	struct Node
	{
		T data;
		Node* next;
		Node(const T & value)
		{
			data = value;
			next = nullptr;
		}
	};

private:
	int size;
	Node* head;

public:
	MyStack();
	~MyStack();

	void push(const T & value);
	void pop();

	const bool empty() const;
	T & top() const;
};

#endif

template<typename T>
inline MyStack<T>::MyStack()
{
	size = 0;
	head = nullptr;
}

template<typename T>
inline MyStack<T>::~MyStack()
{
	while (size > 0)
	{
		Node* element = head;
		head = head->next;
		delete element;
		element = nullptr;
		size--;
	}
	head = nullptr;
}

template<typename T>
inline void MyStack<T>::push(const T & value)
{
	Node* element = new Node(value);
	element->next = head;
	head = element;
	size++;
}

template<typename T>
inline void MyStack<T>::pop()
{
	if (size > 0)
	{
		Node* element = head;
		head = head->next;
		delete element;
		size--;
	}
}

template<typename T>
inline const bool MyStack<T>::empty() const
{
	return size == 0;
}

template<typename T>
inline T & MyStack<T>::top() const
{
	if(size > 0)
		return head->data;
}
