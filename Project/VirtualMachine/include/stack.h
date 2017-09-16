#ifndef VIRTUALMACHINE_STACK_H
#define VIRTUALMACHINE_STACK_H

#include <vector>
#include <string>
#include "util.cpp"

using namespace std;

/*
 * Devido ao uso de templates, os métodos devem ser declarados aqui
 * para evitar linker errors
 * https://stackoverflow.com/questions/648900/c-templates-undefined-reference
 */
template <class T>
class Stack {
    private:
        int rsp;
        int size;

        vector<T> data;

    public:
        Stack(int size){
            this->data = vector<T>(size);
            this->data[0] = 0;
            this->rsp = 0;
            this->size = size;
        };

        void pop(){
            if(this->rsp > 0){
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
                return this->data[this->rsp-1];
            }
            else {
                error("Pilha vazia");
            }
        };

        T getPosition(int pos){
            return this->data[pos];
        }

        int getRsp(){
            return this->rsp;
        }

        int getSize(){
            return this->size;
        }

        void setPosition(int pos, T val){
            this->data[pos] = val;
        }

        void setRsp(int val){
            this->rsp = val;
        }
};
#endif //VIRTUALMACHINE_STACK_H
