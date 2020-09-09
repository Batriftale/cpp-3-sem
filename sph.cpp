#include "TXLib.h"

void drawSphere(int x, int y, int R, int N, int r, int g, int b){
    
    COLORREF color = txGetFillColor();
    COLORREF border = txGetColor();
    
    for (auto i = 0; i < N; i++){
        txSetFillColor(RGB(i * r / N, g, b));
        txSetColor(RGB(i * r / N, g, b));
        txCircle(x + R * i / (2 * N), y - R * i / (2 * N), R - R * i / N);
        }
    
    txSetFillColor(color);
    txSetColor(border);
}



int main(){
    int R = 100;
    int N = 100;
    int r = 100;
    int g = 0;
    int b = 0;
    int x = 200;
    int y = 200;
    double dt = 0.1;
    float vx = 100;
    float vy = 100;


    txCreateWindow(800, 600);
    txSetFillColor(RGB(0, 0, 0));
    
    
    while (true){
    
        txClear();
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
    
        
        }


    return 0;
}
