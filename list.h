#ifndef LIST
#define LIST

#include <iostream>

template<class T>
class Node {
public:
	T data;
	Node *next, *prev;
	Node(){
		next = prev = 0;
	}
	
    Node(const T& el, Node *n = 0, Node *p = 0){
		data = el; next = n; prev = p;
	}
};

template<class T>
class List {
public:
	List() { head = tail = 0; }
	~List();
	bool isEmpty() const { return head == 0; }
	void pushToHead(const T& el);
	void pushToTail(const T& el);
	T popHead();                      
	T popTail();                      
	bool search(const T& el) const;   
	void print(std::ostream& out = std::cout) const;          
	void printReverse(std::ostream& out = std::cout) const;   

private:
	Node<T> *head, *tail;

	List(const List&) = delete;
	List& operator=(const List&) = delete;
};

#include "list.cpp"

#endif