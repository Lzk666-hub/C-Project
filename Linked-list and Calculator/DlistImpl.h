//
// Created by 12077 on 2021/7/20.
//

#ifndef P5_DLISTIMPL_H
#define P5_DLISTIMPL_H

#include "Dlist.h"
#include "Instr.h"

using namespace std;
// EFFECTS: returns true if list is empy, false otherwise
template<class T>
bool Dlist<T>::isEmpty() const {
    return !first;
}

// MODIFIES this
// EFFECTS inserts o at the front of the list
template<class T>
void Dlist<T>::insertFront(T *op) {
    node* ptr= new node;
    ptr->op=op;
    ptr->next=first;
    ptr->prev= nullptr;
    if(isEmpty()){
        first=ptr;
        last=ptr;
    } else{
        first->prev=ptr;
        first=ptr;
    }
}


// MODIFIES this
// EFFECTS inserts o at the back of the list
template<class T>
void Dlist<T>::insertBack(T *op) {
    node* ptr= new node;
    ptr->op=op;
    ptr->next= nullptr;
    ptr->prev= last;
    if(isEmpty()){
        first=ptr;
        last=ptr;
    } else{
        last->next=ptr;
        last=ptr;
    }
}


// MODIFIES this
// EFFECTS removes and returns first object from non-empty list
//         throws an instance of EmptyList if empty
template<class T>
T * Dlist<T>::removeFront() {
    if(isEmpty()){
        EmptyList emptyList;
        throw emptyList;
    } else{
        node* vic=first;
        T* quit=first->op;
        first=first->next;
        if(!first){
            last= nullptr;
        } else{
            first->prev= nullptr;
        }
        delete vic;
        return quit;
    }
}



// MODIFIES this
// EFFECTS removes and returns last object from non-empty list
//         throws an instance of EmptyList if empty
template<class T>
T * Dlist<T>::removeBack() {
    if(isEmpty()){
        EmptyList emptyList;
        throw emptyList;
    } else{
        node* vic=last;
        T* quit=last->op;
        last=last->prev;
        if(!last){
            first= nullptr;
        } else{
            last->next= nullptr;
        }
        delete vic;
        return quit;
    }
}



// EFFECT: called by destructor/operator= to remove and destroy
//         all list elements

template<class T>
void Dlist<T>::removeAll() {
    while (!isEmpty()){
        delete removeFront();
    }
}

// EFFECT: called by copy constructor/operator= to copy elements
//         from a source instance l to this instance
template<class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    node* newNode=l.first;
    while (newNode){
        T* it= new T(*(newNode->op));
        insertBack(it);
        newNode=newNode->next;
    }
}

// constructor
template<class T>
Dlist<T>::Dlist() :first(nullptr), last(nullptr){}


// copy constructor
template<class T>
Dlist<T>::Dlist(const Dlist &l): first(nullptr), last(nullptr) {
    copyAll(l);
}


// assignment operator
template<class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l) {
    if(!isEmpty()){
        removeAll();
    } else{
        copyAll(l);
    }
    return *this;
}

// destructor
template<class T>
Dlist<T>::~Dlist<T>() {
    removeAll();
}


class stack {
public:

    //EFFECTS: push in a instruction at the head of the list
    void push(int& data){
        int* add = new int;
        *add = data;
        dlist->insertBack(add);
    }
//EFFECTS: delete one instruction at the head of the list
    int pop(){
        int* add = dlist->removeBack();
        int ret = *add;
        delete add;
        return (ret);
    }

    //EFFECTS: output the numbers in the stack one by one
    void showInfo(){
        stack staNew;
        while (!isEmpty()) {
            int tmp = this->pop();
            staNew.push(tmp);
        }
        while (!staNew.isEmpty()) {
            int tmp = staNew.pop();
            cout << tmp << " ";
            this->push(tmp);
        }
        cout << endl;
    }

    // EFFECTS: returns true if list is empty, false otherwise
    bool isEmpty(){
        return dlist->isEmpty();
    }

    // constructor
    stack(){
        dlist = new Dlist<int>;
    }

// assignment operator
    stack(const stack& l){
        dlist = new Dlist<int>;
    }

// destructor
    ~stack(){
        delete dlist;
    }

protected:
    Dlist<int>* dlist;
};


class queue {
public:
    //EFFECTS: push in a instruction at the end of the list
    void push(Instr data){
        auto* add= new Instr;
        *add = data;
        dblist->insertBack(add);
    }

    //EFFECTS: delete one instruction at the head of the list
    Instr pop(){
        Instr* add = dblist->removeFront();
        Instr ret = *add;
        delete add;
        return (ret);
    }

    //EFFECTS: output the instructions in the queue one by one
    void showInfo(){
        queue queNew;
        while (!isEmpty()) {
            queNew.push(this->pop());
        }
        while (!queNew.isEmpty()) {
            Instr tmp = queNew.pop();
            cout << tmp << " ";
            this->push(tmp);
        }
        cout << endl;
    }
    // EFFECTS: returns true if list is empty, false otherwise
    bool isEmpty(){
        return dblist->isEmpty();
    }

    // constructor
    queue(){
        dblist = new Dlist<Instr>;
    }


// destructor
    ~queue(){
        delete dblist;
    }

protected:
    Dlist<Instr>* dblist;
};




#endif //P5_DLISTIMPL_H
