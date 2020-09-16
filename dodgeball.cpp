#include "TXLib.h"
#include "iostream"
#include "cmath"

using namespace std;

bool isCollidedTwoSpheres(int x1, int x2, int y1, int y2, int R){
     if (((x1 - x2) * (x1 - x2) +  (y1 - y2) * (y1 - y2)) <= (4 * R * R)){

        return true;
    }
    return false;
}


void moveSphere(double* currentX, double* currentY, double vx, double vy, double dt){

    *currentX += vx * dt;
    *currentY += + vy * dt;
}


void controlSphere(double currentX, double currentY, double* vx, double* vy){

    if (txMouseButtons() > 0){

        double xCoord = txMouseX();
        double yCoord = txMouseY();

        double xDifference = xCoord - currentX;
        double yDifference = yCoord - currentY;
        double distanceDifference = sqrt(pow(xDifference, 2) + pow(yDifference, 2));
        double xDifferenceNormal = xDifference / distanceDifference;
        double yDifferenceNormal =  yDifference / distanceDifference;

        double speedModule = sqrt((*vx * *vx) + (*vy * *vy));

        double changedSpeedX = xDifferenceNormal * speedModule;
        double changedSpeedY = yDifferenceNormal * speedModule;

        *vx = changedSpeedX;
        *vy = changedSpeedY;

    }
}


void checkCollision(double x, double y, int R, double* vx, double* vy){

    if ((x >= 800 - R) || (x <= R)){
            *vx = -*vx;
        }
    if ((y >= 600 - R) || (y <= R)){
            *vy = -*vy;
        }
}

void drawSphere(int x, int y, int R, int N, int r, int g, int b){

    COLORREF color = txGetFillColor();
    COLORREF border = txGetColor();
    for (auto i = 0; i < N; i++){
        txSetFillColor(RGB(i * r / N, i * g / N, i * b / N));
        txSetColor(RGB(i * r / N, i * g / N, i * b / N));
        txCircle(x + R * i/(2 * N), y - R * i / (2 * N), R - R * i / N);
        }
    txSetFillColor(color);
    txSetColor(border);
}

int main(){

    int R = 50;
    int N = 50;

    int redPlayer = 100;
    int greenPlayer = 0;
    int bluePlayer = 0;
    int redEnemy = 0;
    int greenEnemy = 0;
    int blueEnemy = 100;

    double xPlayer = 100;
    double yPlayer = 100;
    double xEnemy = 500;
    double yEnemy = 500;
    double previousX, previousY;

    double dt = 1;

    double speedXPlayer = 10;
    double speedYPlayer = 10;
    double speedXEnemy = 5;
    double speedYEnemy = -10;

    double distance = 0;


    txCreateWindow(800, 600);
    txSetFillColor(RGB(10, 10, 10));



    while (not isCollidedTwoSpheres(xPlayer, xEnemy, yPlayer, yEnemy, R)){

        txClear();
        txBegin();
        drawSphere(xPlayer, yPlayer, R, N, redPlayer, greenPlayer, bluePlayer);
        drawSphere(xEnemy, yEnemy, R, N, redEnemy, greenEnemy, blueEnemy);
        txEnd();

        controlSphere(xPlayer, yPlayer, &speedXPlayer, &speedYPlayer);

        previousX = xPlayer;
        previousY = yPlayer;

        moveSphere(&xPlayer, &yPlayer, speedXPlayer, speedYPlayer, dt);
        moveSphere(&xEnemy, &yEnemy, speedXEnemy, speedYEnemy, dt);

        distance += sqrt(pow(xPlayer-previousX, 2) + pow(yPlayer - previousY, 2));

        checkCollision(xPlayer, yPlayer, R, &speedXPlayer, &speedYPlayer);
        checkCollision(xEnemy, yEnemy, R, &speedXEnemy, &speedYEnemy);
    }

    cout << "Your score is " << distance;

    return 0;

}


