#include "stack.h"

template <class T>
Stack<T>::Stack(int size){
    this->data = vector<T>(size);
    this->data[0] = 0;
    this->rbp = 0;
    this->rsp = 0;
    this->size = size;
}

template <class T>
void Stack<T>::pop() {
    if(this->rsp < this->size){
        this->rsp--;
    }
    else{
        error("Pilha já vazia");
    }
}

template <class T>
T Stack<T>::top() {
    if(this->rsp > 0){
        return this->data[this->rsp];
    }
    else{
        error("Pilha vazia");
    }
}

template <class T>
void Stack<T>::push(T value) {
    if(this->rsp < this->size){
        this->data[this->rsp++] = value;
    }
    else{
        error("Pilha cheia");
    }
}

//funcao para evitar linker errors
//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
//https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
void test() {
    Stack<int> test = Stack<int>(1);
}