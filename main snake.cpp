#include <iostream>
#include <conio.h> //for input function
#include <windows.h>
using namespace std;
bool gameover;
const short width=40;
const short height=20;
short x,y,fruitX,fruitY,score;
short tailX[100],tailY[100];
short ntail;
enum Edirection{STOP=0,LEFT,RIGHT,UP,DOWN};
Edirection dir;
void setup()
{
    gameover=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%(width);
    fruitY=rand()%height;
    score=0;
}
void draw()
{
    system("cls"); //clear screen
    short i;
    for(i=0;i<width+2;i++)
        cout<<(char)178;
    cout<<endl;
    for(short j=0;j<height;j++)
    {
        for(i=0;i<width+2;i++)
        {
            if(i==0 || i==width+1)
                cout<<(char)178;
            else if(j==y && i==x)
                cout<<"O";
            else if(j==fruitY && i==fruitX)
                cout<<"F";
            else
            {
                bool print=false;
                for(short k=0;k<ntail;k++)
                {
                    if(tailX[k]==i && tailY[k]==j)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
        }
        cout<<endl;
    }
    for(i=0;i<width+2;i++)
        cout<<(char)178;
    cout<<endl;
    cout<<"Score: "<<score<<endl;
}
void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'x':
            gameover=true;
            break;
        }
    }
}
void logic()
{
    short prevX=tailX[0], prevY=tailY[0];
    short prev2X,prev2Y,i;
    tailX[0]=x;
    tailY[0]=y;
    for(i=1;i<ntail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir)
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
    if(x>width || x<1 || y>=height || y<0)
        gameover=true;
    for(i=0;i<ntail;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
            gameover=true;
    }
    if(x==fruitX && y==fruitY)
    {
        score+=10;
        fruitX=rand()%(width);
        fruitY=rand()%height;
        ntail++;
    }
}
int main()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        Sleep(10);
    }
    cout<<"GAME OVER !!!\n";
    return 0;
}
