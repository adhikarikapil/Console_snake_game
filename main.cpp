#include<iostream>
//including the library console input and output
#include<conio.h>
using namespace std;

//Setting the width and height of the map 
const int width = 20;
const int height = 20;
//Setting the coordinates of the snake head and fruit 
//Declaring the enumeration for the direction of the snake head
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool gameOver;

//Setting up the intial stage of the game 
void setup()
{
    gameOver = false;
    //it will make snake in stationary position
    dir = STOP;
    // x and y will place the snake in the map
    x = width / 2;  
    y = height / 2;
    //It will spawn the fruit randomly within the area of width and height
    fruitX = rand() % width;    
    fruitY = rand() % height;
    //starts wih the score 0
    score = 0;
}
void draw()
{
    system("cls");
        
    //Setting up the walls of the map
    for (int i = 0; i < width + 2; i++)
        cout<<"#";
    cout<<endl;
    
    //Setting walls verticalliy and leaving space in between 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout<<"#";     
            //Printing head of the snake 'O'
            if (i == y && j == x)
                cout<< "O";
            //Printing the fruit 'F'
            else if (i == fruitY && j == fruitX)
                cout<<"F";
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k++) 
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print)
            cout<<" ";
            }
            if (j == width -1)
                cout<<"#";
        }
        cout<<endl;
    }

    for (int i = 0; i < width +2; i++)
        cout<<"#";
    cout<<endl;
    cout<<"Score: "<<score<<endl;
}
    
void input()
{
    //_kbhit will return positive if the key is pressed
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break; 
            case 'w':
                dir = UP;
                break; 
            case 's':
                dir = DOWN;
                break; 
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break; 
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }
    if(x == fruitX && y == fruitY)
    {
        score += 1;
        fruitX = rand() % width;    
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
    }
    return 0;
}
