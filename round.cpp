#include "TXLib.h"

void drawSphere(int x, int y, int R, int N, int r, int g, int b){
    int i;
    for (auto i = 0; i < N; i++){
        txSetFillColor(RGB(i * r / N, g, b));
        txSetColor(RGB(i * r / N, g, b));
        txCircle(x + R * i/(2 * N), y - R * i / (2 * N), R - R * i / N);
        }
}

void moveSphere(int x, int y, int R, int N,int r, int g, int b, int vx, int vy, double dt){

    while (true){
        txBegin();
        drawSphere(x, y, R, N, r, g, b);
        txEnd();
        x = x + vx * dt;
        y = y + vy * dt;
        if ((x >= 800 - R) || (x <= R)){
            vx = -vx;
        }
        if ((y >= 600 - R) || (y <= R)){
            vy = -vy;
        }
        txSetColor(RGB(0,0,0));
        txClear();
        }
}


int main(){
int R = 100;
int N = 100;
int r, g, b;
double dt = 0.1;


txCreateWindow(800,600);

//drawSphere(100,100,R,N,100,50,0);
moveSphere(100,100,R,N,255, 0, 0, 10,10,dt);

return 0;
}
