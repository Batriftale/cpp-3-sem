#include "TXLib.h"
#include "iostream"
#include "cmath"

using namespace std;

void Collision (double* vx2, double* vx3, double* vy2, double* vy3){

        //each mass is 1 unit
        double v_centreX = (*vx2 + *vx3) / 2 ;
        double v_centreY = (*vy2 + *vy3) / 2 ;

        *vx2 = -*vx2 + 2 * v_centreX;
        *vx3 = -*vx3 + 2 * v_centreX;
        *vy2 = -*vy2 + 2 * v_centreY;
        *vy3 = -*vy3 + 2 * v_centreY;
    }

bool isCollidedTwoSpheres(int x1, int x2, int y1, int y2, int R){
        
     if (((x1 - x2) * (x1 - x2) +  (y1 - y2) * (y1 - y2)) <= (4 * R * R)){

        return true;
    }
    return false;
}


void moveSphere(double* currentX, double* currentY, double vx, double vy, double dt){

    *currentX += vx * dt;
    *currentY += vy * dt;
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
    int redEnemy1 = 0;
    int greenEnemy1 = 0;
    int blueEnemy1 = 100;
    int redEnemy2 = 0;
    int greenEnemy2 = 100;
    int blueEnemy2 = 0;

    double xPlayer = 100;
    double yPlayer = 100;
    double xEnemy1 = 500;
    double yEnemy1 = 500;
    double xEnemy2 = 300;
    double yEnemy2 = 100;
    double previousX, previousY;

    double dt = 1;

    double speedXPlayer = 10;
    double speedYPlayer = 10;
    double speedXEnemy1 = 5;
    double speedYEnemy1 = -10;
    double speedXEnemy2 = 2;
    double speedYEnemy2 = 4;

    double distance = 0;


    txCreateWindow(800, 600);
    txSetFillColor(RGB(20, 20, 20));



    while ((not isCollidedTwoSpheres(xPlayer, xEnemy1, yPlayer, yEnemy1, R)) && (not isCollidedTwoSpheres(xPlayer, xEnemy2, yPlayer, yEnemy2, R))){

        txClear();
        txBegin();
        drawSphere(xPlayer, yPlayer, R, N, redPlayer, greenPlayer, bluePlayer);
        drawSphere(xEnemy1, yEnemy1, R, N, redEnemy1, greenEnemy1, blueEnemy1);
        drawSphere(xEnemy2, yEnemy2, R, N, redEnemy2, greenEnemy2, blueEnemy2);
        txEnd();

        controlSphere(xPlayer, yPlayer, &speedXPlayer, &speedYPlayer);

        previousX = xPlayer;
        previousY = yPlayer;

        moveSphere(&xPlayer, &yPlayer, speedXPlayer, speedYPlayer, dt);
        moveSphere(&xEnemy1, &yEnemy1, speedXEnemy1, speedYEnemy1, dt);
        moveSphere(&xEnemy2, &yEnemy2, speedXEnemy2, speedYEnemy2, dt);

        distance += sqrt(pow(xPlayer-previousX, 2) + pow(yPlayer - previousY, 2));

        checkCollision(xPlayer, yPlayer, R, &speedXPlayer, &speedYPlayer);
        checkCollision(xEnemy1, yEnemy1, R, &speedXEnemy1, &speedYEnemy1);
        checkCollision(xEnemy2, yEnemy2, R, &speedXEnemy2, &speedYEnemy2);

        if (isCollidedTwoSpheres(xEnemy1, xEnemy2, yEnemy2, yEnemy2, R)){

            Collision(&speedXEnemy1, &speedXEnemy2, &speedYEnemy2, &speedYEnemy2);
        }


    }

    cout << "Your score is " << distance;

    return 0;

}


