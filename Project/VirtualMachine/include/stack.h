#ifndef VIRTUALMACHINE_STACK_H
#define VIRTUALMACHINE_STACK_H

#include <vector>
#include <util.h>

using namespace std;

template <class T>
class Stack {
    private:
        int rbp;
        int rsp;
        int size;

        vector<T> data;

    public:
        Stack(int size){
            this->data = vector<T>(size);
            this->data[0] = 0;
            this->rbp = 0;
            this->rsp = 0;
            this->size = size;
        };

        void pop(){
            if(this->rsp < this->size){
                this->rsp--;
            }
            else{
                error("Pilha já vazia");
            }
        };
        void push(T value){
            if(this->rsp < this->size){
                this->data[this->rsp++] = value;
            }
            else{
                error("Pilha cheia");
            }
        };


        T top(){
            if(this->rsp > 0){
                return this->data[this->rsp];
            }
            else {
                error("Pilha vazia");
            }
        };
};
void test();
#endif //VIRTUALMACHINE_STACK_H
