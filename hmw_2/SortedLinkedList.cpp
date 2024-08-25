#include "User.h"
#include "SortedLinkedList.h"
#include "LinkedListNode.h"

#include<iostream>
#include<string>

using namespace std;

// Implement the functions in the "SortedLinkedList.h"

SortedLinkedList::SortedLinkedList(){
	head = nullptr;
}
SortedLinkedList::~SortedLinkedList(){
	LinkedListNode *current = head;
	while(current != nullptr){
		LinkedListNode *next = current->next;
		delete current;
		current = next; 
	}
	
}
bool SortedLinkedList::add(User *u){
	LinkedListNode *newNode = new LinkedListNode();
	newNode->u = u;
	newNode->next = nullptr;
	
	if (head == nullptr){
		head = newNode;
		return true;
	}
	if (u->getId() == head->u->getId())
		return false;
	if (u->getId() < head->u->getId())
	{
		newNode->next = head;
		head = newNode;
		return true;
	}
	
	LinkedListNode *current = head;
	while (current->next != nullptr && u->getId() >= current->next->u->getId())
	{
		if (current->u->getId() == u->getId())
			return false;
		current = current->next;
	}
	
	newNode->next = current->next;
	current->next = newNode;
	return true;
}
bool SortedLinkedList::remove(int userId){
	if (head == nullptr)
		return false;
	if(head->u->getId() == userId){
		LinkedListNode *temp = head;
		head = head->next;
		delete temp;
		return true;
	}
	LinkedListNode *current = head;
	while(current->next!= nullptr && current->next->u->getId() != userId){
		current = current->next;
	}
	if (current->next != nullptr){
		LinkedListNode *temp = current->next;
		current->next = current->next->next;
		delete temp;
		return true;
	}
	return false;
}
bool SortedLinkedList::checkIfExist(int userId) {
	LinkedListNode *current = head;
	while (current != nullptr) {
		if (current->u->getId() == userId) {
			return true;
        }
        current = current->next;
    }
    return false;
}
LinkedListNode* SortedLinkedList::getPointerTo(int userId){
	LinkedListNode* current = head;
	 while(current!= nullptr){
		if (current->u->getId() == userId){
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
LinkedListNode* SortedLinkedList::getPointerTo(){
	LinkedListNode* current = head;
	return current;
}
void SortedLinkedList::print(){
	LinkedListNode *current = head;
	if (head == nullptr)
	{
		cout << "None" << endl;
	}
	while(current != nullptr){
		cout<< current->u->getId() << ", " << current->u->getName()<<endl;
		current = current->next;
	}
}