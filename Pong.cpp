

#include <iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>

using namespace std;


enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3,
                    RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cball {
private:
    int x , y ;
    int OGx, OGy;
    eDir direction;
public:
    cball(int posX, int posY) {
        OGx = posX;
        OGy = posY;
        x = posX; y = posY;
        direction = STOP;
    };
    void Reset() {
        x = OGx; y = OGy;
        direction = STOP;
    }
    void changeDirection(eDir d) {
        direction = d;

    }
    void randomDirection() {
        int num = (rand() % 6) + 1;
        direction = (eDir)(num);
  
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }

    void move() {
        switch (direction) {
        case STOP: 
            break;
        case LEFT: 
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--, y--;
            break;
        case DOWNLEFT:
            x--, y++;
            break;
        case UPRIGHT:
            x++, y--;
            break;
        case DOWNRIGHT:
            x++, y++;
            break;
        default: break;
        }
    }
    friend ostream& operator<<(ostream& o, cball c) {
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

class cPaddle {
private:
    int x, y;
    int OGx, OGy;
public:
     cPaddle() {
         
         x = y = 0;
     }
     cPaddle(int posX, int posY) : cPaddle() {
         OGx = posX;
         OGy = posY;
         x = posX; y = posY;
     }
     inline void Reset() { x = OGx; y = OGy; }
     inline int getX() { return x; }
     inline int getY() { return y; }
     inline void moveUP() { y--; }
     inline void moveDOWN() { y++; }

     friend ostream& operator<<(ostream& o, cPaddle p) {
         o << "Paddle [" << p.x << "," << p.y << "]";
         return o;
     }
};

class cGameManeger {
private:
    int width, hight;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cball* ball;
    cPaddle* player1;
    cPaddle* player2;
public:
    cGameManeger(int w, int h) {

        srand(time(NULL));
        quit = false;
        up1 = 'w'; up2 = 'i';
        down1 = 's'; down2 = 'k';
        score1 = score2 = 0;
        width = w; hight = h;
        ball = new cball(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);


    }
    ~cGameManeger() {

        delete ball, player1, player2;
    }
    void scoreUp(cPaddle* player) {
        if (player == player1) {
            score1++;

        }
        else if(player == player2) {
            score2++;
        }

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++) {
            cout << "\xB2";
        }
        cout << endl;

        for (int i = 0; i < hight; i++) {
            for (int j = 0; j < width; j++) {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player1y = player1->getY();
                int player2x = player2->getX();
                int player2y = player2->getY();

                if (j == 0) {
                    cout << "\xB2";

                }

                if (ballx == j && bally == i) {
                    cout << "O";//ball
                }
                else if (player1x == j && player1y == i) {
                    cout << "\xDB";//player1
                }
                else if (player2x == j && player2y == i) {
                    cout << "\xDB";//player2
                }
                else if (player1x == j && player1y + 1 == i) {
                    cout << "\xDB";//player1
                }
                else if (player1x == j && player1y + 2 == i) {
                    cout << "\xDB";//player1
                }
                else if (player1x == j && player1y + 3 == i) {
                    cout << "\xDB";//player1
                }
               
                else if (player2x == j && player2y + 1== i) {
                    cout << "\xDB";//player2
                }
                else if (player2x == j && player2y + 2 == i) {
                    cout << "\xDB";//player2
                }
                else if (player2x == j && player2y + 3 == i) {
                    cout << "\xDB";//player2
                }

                else {
                    cout << " ";
                }

                if (j == width - 1) {
                    cout << "\xB2";

                }

            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) {
            cout << "\xB2";
        }
        cout << endl;


        cout << "player 1 : " << score1 <<endl<< "player 2 : " << score2 << endl;

    }
    void Input() {

        ball->move();
 
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        if (_kbhit()) {
            char current = _getch();
            if (current == up1 && player1y > 0) {
                player1->moveUP();

            }
            if (current == up2 && player2y > 0) {
                player2->moveUP();

            }

            if (current == down1 && (player1y + 4) < hight) {
                player1->moveDOWN();

            }
            if (current == down2 && (player2y + 4) < hight) {
                player2->moveDOWN();

            }

            if (ball->getDirection() == STOP) {
                ball->randomDirection();

            }
            if (current == 'q') {
                quit = true;

            }

        }
    }
    void Logic() {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        //left paddle
        for (int i = 0; i < 4; i++) {
            if (ballx == player1x + 1 && bally == (player1y + i)) {
                ball->changeDirection((eDir)((rand() % 3) + 4));
            }
        }
        //right paddle
        for (int i = 0; i < 4; i++) {
            if (ballx == player2x - 1 && bally == (player2y + i)) {
                ball->changeDirection((eDir)((rand() % 3) + 1));
            }
        }

        if (bally == hight - 1) {
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }
        if (bally ==  0) {
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }
        if (ballx == width - 1) {
            scoreUp(player1);
        }
        if (ballx == 0) {
            scoreUp(player2);
        }
    }
    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{

    cGameManeger c(40, 20);
    c.Run();


    return 0;
}
