#ifndef Queue_H
#define Queue_H

template<typename T>
class MyQueue
{
	struct Node
	{
		T data;
		Node* next;
		Node(const T& value)
		{
			data = value;
			next = nullptr;
		}
	};

private:
	int size;
	Node* head, *tail;

public:
	MyQueue();
	~MyQueue();

	void push(const T & value);
	void pop();

	const bool empty() const;
	T & front() const;
};

#endif

template<typename T>
inline MyQueue<T>::MyQueue()
{
	head = tail = nullptr;
	size = 0;
}

template<typename T>
inline MyQueue<T>::~MyQueue()
{
	while (size > 0)
	{
		Node* element = head;
		head = head->next;
		delete element;
		size--;
	}
	head = tail = nullptr;
}

template<typename T>
inline const bool MyQueue<T>::empty() const
{
	return size == 0;
}

template<typename T>
inline void MyQueue<T>::push(const T & value)
{
	Node* element = new Node(value);

	if (size == 0)
		head = tail = element;
	else
		tail = tail->next = element;
	size++;
}

template<typename T>
inline void MyQueue<T>::pop()
{
	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* element = head;
		head = head->next;
		delete element;
		element = nullptr;
	}

	size--;
}

template<typename T>
inline T & MyQueue<T>::front() const
{
	if (size > 0)
		return head->data;
}