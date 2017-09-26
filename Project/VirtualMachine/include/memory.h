#ifndef VIRTUALMACHINE_MEMORY_H
#define VIRTUALMACHINE_MEMORY_H

#include <vector>

using namespace std;

class Memory {

    private:
        int ebp;
        int esp;

        vector<int> data;

    public:
        explicit Memory(int size);

        int back();
        int get(int i) const;

        void alloc (int n);
        void free  (int n);
        void push  (int val);
        void set   (int i, int val);
};

#endif
