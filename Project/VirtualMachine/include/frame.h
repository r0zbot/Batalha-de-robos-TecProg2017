#ifndef VIRTUALMACHINE_FRAME_H
#define VIRTUALMACHINE_FRAME_H

#include <vector>

using namespace std;

class Frame {

    private:
        int ebp;
        int esp;

        vector<int> data;

    public:
        explicit Frame(int size);

        int back();
        int get(int i) const;

        void alloc (int n);
        void free  (int n);
        void push  (int val);
        void set   (int i, int val);
};

#endif
