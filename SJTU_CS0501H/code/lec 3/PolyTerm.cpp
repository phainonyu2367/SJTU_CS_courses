#include<iostream>

class PolyTerm {
    private:
        struct Node{
            int coefficient;
            int exponential;
            Node* next;
        };

        Node head = {-1, -1, NULL};
    public:

};