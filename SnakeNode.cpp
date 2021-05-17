#include "SnakeNode.h"

SnakeNode::SnakeNode(int x, int y)
{
    pos_x = x;
    pos_y = y;
    index = 0;
    next = NULL;
    previous = NULL;
}

SnakeNode::~SnakeNode()
{
    pos_x = 0;
    pos_y = 0;
    index = 0;
    next = NULL;
    previous = NULL;
}

Snake::Snake()
{
    head = NULL;
    tail = NULL;
    size = 0;
    state = MOVE_RIGHT;
}

Snake::~Snake()
{
    if (head == NULL)
    {
        cout << "\nSnake has been deleted already";
        return;
    }

    SnakeNode* current = head;
    SnakeNode* next = current->next;

    while (next != NULL)
    {
        //  Get next Node
        next = current->next;
        //  Delete current Node
        delete current;
        //  Take next Node
        current = next;
    }
}

void Snake::push_back(const int x, const int y)
{
    //  Thêm node cho rắn

    SnakeNode *temp = new SnakeNode(x, y);
    temp->index = size;
    ++size;

    //  Nếu rắn chưa có head thì tạo head và tail
    if (head == NULL)
    {
        temp->previous = NULL;
        head = temp;
        tail = temp;
        return;
    }

    //             before_tail      tail       new
    //                              tail  <-   new.previous
    //                         tail.next  ->   new
    //                            |             |
    //                         before_tail     tail
    temp->previous = tail;
    tail->next = temp;
    tail = temp;
}

void Snake::pop_back()
{
    if (tail == NULL)
    {
        cout << "\nSnake has been deleted already";
        return;
    }

    //      before_tail                 tail
    //      before_tail  ->   temp
    //                                  delete tail
    //    temp  ->  tail
    //    tail.next = NULL              NULL
    --size;
    SnakeNode *temp = tail->previous;
    delete tail;
    tail = temp;
    tail->next = NULL;
}

void Snake::draw()
{
    SnakeNode *current = head;
    while (current != NULL)
    {
        gotoXY(current->pos_x, current->pos_y);
        if (current == head)
            cout << SNAKE_HEAD_COLOR_TEXT.c_str() << "O" << "\033[0m";
        else cout << SNAKE_COLOR_TEXT.c_str() << "O" << "\033[0m";
        current = current->next;
    }
}

void Snake::move(char input)
{
    if (head == NULL)
    {
        cout << "\nError: Cannot move because head = NULL";
        return;
    }

    int old_pos_x = head->pos_x;
    int old_pos_y = head->pos_y;

    switch (input)
    {
        case 'a': 
            if (state == MOVE_RIGHT) break;
            state = MOVE_LEFT;
            break;
        case 'd': 
            if (state == MOVE_LEFT) break;
            state = MOVE_RIGHT;
            break;
        case 's':
            if (state == MOVE_UP) break;
            state = MOVE_DOWN;
            break;
        case 'w':
            if (state == MOVE_DOWN) break;
            state = MOVE_UP;
            break;
    }

    switch (state)
    {
        case MOVE_RIGHT: ++head->pos_x; break;
        case MOVE_LEFT: --head->pos_x; break;
        case MOVE_UP: --head->pos_y; break;
        case MOVE_DOWN: ++head->pos_y; break;
    }
    

    SnakeNode *current = head->next;
    while (current != NULL)
    {
        //  Save temp position
        int temp_pos_x = current->pos_x;
        int temp_pos_y = current->pos_y;

        // Take prev node postion
        current->pos_x = old_pos_x;
        current->pos_y = old_pos_y;

        //  Save old position 
        old_pos_x = temp_pos_x;
        old_pos_y = temp_pos_y;

        current = current -> next;
    }
}

void Snake::lengthIncrease(int increase)
{
    if (tail == NULL)
        {
            cout << "Error: No snake, cannot incresea length";
            return;
        }

    for (int i = 0; i < increase; ++i)
    {
        push_back(tail->pos_x, tail->pos_y);
    }
}