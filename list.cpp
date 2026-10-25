#ifndef LIST_CPP
#define LIST_CPP

#include "list.h"

template<class T>
List<T>::~List() {
	for (Node<T> *p; !isEmpty(); ){
		p = head->next;
		delete head;
		head = p;
	}
	tail = 0;
}

template<class T>
void List<T>::pushToHead(const T& el){
	head = new Node<T>(el, head, 0);
	if (tail == 0){
		tail = head;           
	}else{
		head->next->prev = head;   
	}
}

template<class T>
void List<T>::pushToTail(const T& el){
	tail = new Node<T>(el, 0, tail);
	if (head == 0) {
		head = tail;          
	}else{
		tail->prev->next = tail;   
	}
}

template<class T>
T List<T>::popHead(){
	if (isEmpty())
		return T();            

	T el = head->data;
	Node<T> *tmp = head;
	if (head == tail){
		head = tail = 0;       
	}else{
		head = head->next;
		head->prev = 0;
	}
	delete tmp;
	return el;
}

template<class T>
T List<T>::popTail(){
	if (isEmpty())
		return T();            

	T el = tail->data;
	Node<T> *tmp = tail;
	if (head == tail) {
		head = tail = 0;       
	}else{
		tail = tail->prev;
		tail->next = 0;
	}
	delete tmp;
	return el;
}

template<class T>
bool List<T>::search(const T& el) const{
	for (Node<T> *p = head; p != 0; p = p->next) {
        if (p->data == el)
		return true;
	}
	return false;
}

template<class T>
void List<T>::print(std::ostream& out) const {
	if (isEmpty()){
		out << "(empty)";
		return;
	}
	for (Node<T> *p = head; p != 0; p = p->next){
		out << p->data;
		if (p->next != 0)
		out << " ";
	}
}

template<class T>
void List<T>::printReverse(std::ostream& out) const{
	if (isEmpty()){
		out << "(empty)";
		return;
	}
    
    for (Node<T> *p = tail; p != 0; p = p->prev){
		out << p->data;
		if (p->prev != 0)
		out << " ";
	}
}

#endif