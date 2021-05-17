#include "Game.h"
#include "SnakeNode.h"
#include "SnakeFood.h"

const int BORDER_WIDTH = 50;
const int BORDER_HEIGHT = 20;

void drawBorder();
void createSnake();

void update(char input, bool &game_over);
void draw();

bool checkColisionBorder();
bool checkColisionSelf();
void createSnakeFood();
bool snakeEatFood();
void drawFood();

void drawPoint();

int point = 0;
int speed = 150;

Snake snake;
vector<SnakeFood> snake_food;

void MainGame()
{
    createSnake();
    bool gameover = false;

    int i = 0;
    char input = 'd';
    while (!gameover)
    {
        gotoXY(1,1);
        cout << "";
        
        delay(speed);
        if (kbhit()) 
        {
            input = getchar();
            playMusic("click.wav");
        }
        update(input, gameover);
        draw();
    }

    gotoXY(BORDER_WIDTH, BORDER_HEIGHT+5);
    
}

void drawBorder()
{
    //  Draw up border
    gotoXY(1,1);
    for (int col = 1; col <= BORDER_WIDTH; ++col)
    {
        cout << "\033[37;47m" << "-" << "\033[0m";
    }

    //  Draw left and right border
    for (int row = 1; row <= BORDER_HEIGHT; ++row)
    {
        gotoXY(1, row);
        cout << "\033[37;47m" << "--" << "\033[0m";
        gotoXY(BORDER_WIDTH, row);
        cout << "\033[37;47m" << "--" << "\033[0m";
    }

    //  Draw bottom border
    gotoXY(1,BORDER_HEIGHT);
    for (int col = 1; col <= BORDER_WIDTH; ++col)
    {
        cout << "\033[37;47m" << "-" << "\033[0m";
    }
    cout << endl << endl;
}

void createSnake()
{
    snake.push_back(20,10);
    snake.lengthIncrease(3);
    createSnakeFood();
}

void update(char input, bool &game_over)
{
    snake.move(input);
    if (checkColisionBorder() || checkColisionSelf()) game_over = true;    
    if (snakeEatFood()) createSnakeFood();
}

void draw()
{
    clearScreen();
    drawBorder();
    snake.draw();
    drawFood();
    drawPoint();
}

bool checkColisionBorder()
{
    int snake_x = snake.getHead()->pos_x;
    int snake_y = snake.getHead()->pos_y;

    if (snake_x <= 2 || snake_y == 1) return true;
    if (snake_x > BORDER_WIDTH-2 || snake_y == BORDER_HEIGHT) return true;

    return false;
}

bool checkColisionSelf()
{
    
    SnakeNode *snake_head = snake.getHead();
    if (snake_head == NULL) 
    {
        cout << "Error: there is no snake";
        return true;
    }

    SnakeNode *body = snake_head->next;

    while (body != NULL)
    {
        if (snake_head->pos_x == body->pos_x && snake_head->pos_y == body->pos_y)
        {
            return true;
        }
        body = body->next;
    }

    return false;
}

void createSnakeFood()
{
    srand((int) time(nullptr));
    bool create_food_ok = false;

    int food_x;
    int food_y;

    while(!create_food_ok)
    {
        food_x = 3 + rand()%(BORDER_WIDTH-4);
        food_y = 2 + rand()%(BORDER_HEIGHT-2);

        SnakeNode *current = snake.getHead();
        //  Kiểm tra xem food có trùng với vị trí của rắn không
        bool no_dupplicate = true;
        while (current != NULL)
        {
            if (food_x == current->pos_x && food_y == current->pos_y)
            {
                no_dupplicate = false;
                break;
            }
            current = current->next;
        }

        if(no_dupplicate) break;
    }

    SnakeFood temp(food_x, food_y, 10);
    snake_food.push_back(temp);
}

bool snakeEatFood()
{
    bool ate = false;
    SnakeNode *head = snake.getHead();
    for (int i = 0; i < snake_food.size(); ++i)
    {
        if (head->pos_x == snake_food[i].getX() && head->pos_y == snake_food[i].getY())
        {
            playMusic("eat.wav");
            ate = true;
            point += snake_food[i].getPoint();
            if (point % 50 == 0) speed -= 10;
            snake.lengthIncrease(1);
            snake_food.erase(snake_food.begin() + i);
        }
    }
    return ate;
}

void drawFood()
{
    for (int i = 0; i < snake_food.size(); ++i)
    {
        snake_food[i].draw();
    }
}

void drawPoint()
{
    gotoXY(BORDER_WIDTH + 5, 1);
    cout << "LENGTH: " << snake.getSize();
    gotoXY(BORDER_WIDTH + 5, 2);
    cout << "SPEED: " << speed;
    gotoXY(BORDER_WIDTH + 5, 3);
    cout << "POINT: " << point;
}
