//SortedLinkedList.h
//You can modify this file if needed, do not change the name of the class
#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include<iostream>
#include<string>

class LinkedListNode;
class User;

class SortedLinkedList {

private:
    LinkedListNode *head;

public:
    
    SortedLinkedList();
    ~SortedLinkedList();
    bool add(User *u); 
    bool remove(int userId); 
    bool checkIfExist(int userId);  
    LinkedListNode *getPointerTo(int userId);
    LinkedListNode *getPointerTo();
    void print();
};

#endif
