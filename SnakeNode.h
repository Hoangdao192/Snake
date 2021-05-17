#pragma once
#include "MainFunction.h"

struct SnakeNode
{
    SnakeNode(int x = 0, int y = 0);
    ~SnakeNode();
    int pos_x, pos_y;
    int index;
    SnakeNode* next;
    SnakeNode* previous;
};

class Snake
{
    public:
        Snake();
        ~Snake();
        void push_back(const int x, const int y);
        void pop_back();
        void lengthIncrease(int increase);
        SnakeNode *getHead() {return head; }
        SnakeNode *getTail() {return tail; }
        int getSize() const {return size; }

        void draw();
        void move(char input);
        
    private:
        int size;
        SnakeNode *head;
        SnakeNode *tail;
        int state;
};
