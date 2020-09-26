#include "TXLib.h"
#include "iostream"
#include "cmath"

struct Vector{

    double var1;
    double var2;
};
struct Sphere{

    Vector pos;
    Vector speed;
    int red;
    int green;
    int blue;
    int Radius;

};


void Collision (Sphere *sphere1, Sphere *sphere2){

        //each mass is 1 unit
        double v_centreX = ((*sphere1).speed.var1 + (*sphere2).speed.var1) / 2 ;
        double v_centreY = ((*sphere1).speed.var2 + (*sphere2).speed.var2) / 2 ;

        (*sphere1).speed.var1 = -(*sphere1).speed.var1 + 2 * v_centreX;
        (*sphere2).speed.var1 = -(*sphere2).speed.var1 + 2 * v_centreX;
        (*sphere1).speed.var2 = -(*sphere1).speed.var2 + 2 * v_centreY;
        (*sphere2).speed.var2 = -(*sphere2).speed.var2 + 2 * v_centreY;
    }

bool isCollidedTwoSpheres(Sphere sphere1, Sphere sphere2){
     if ((pow((sphere1.pos.var1 - sphere2.pos.var1), 2) +  pow((sphere1.pos.var2 - sphere2.pos.var2), 2) <= (4 * pow(sphere1.Radius, 2)))){

        return true;
    }
    return false;
}


void moveSphere(Sphere *sphere, double dt){

    (*sphere).pos.var1 += (*sphere).speed.var1 * dt;
    (*sphere).pos.var2 += (*sphere).speed.var2 * dt;
}


void controlSphere(Sphere *sphere){

    if (txMouseButtons() > 0){

        double xCoord = txMouseX();
        double yCoord = txMouseY();

        double xDifference = xCoord - (*sphere).pos.var1;
        double yDifference = yCoord - (*sphere).pos.var2;
        double distanceDifference = sqrt(pow(xDifference, 2) + pow(yDifference, 2));
        double xDifferenceNormal = xDifference / distanceDifference;
        double yDifferenceNormal =  yDifference / distanceDifference;

        double speedModule = sqrt(pow((*sphere).speed.var1, 2) + pow((*sphere).speed.var2, 2));

        double changedSpeedX = xDifferenceNormal * speedModule;
        double changedSpeedY = yDifferenceNormal * speedModule;

        (*sphere).speed.var1 = changedSpeedX;
        (*sphere).speed.var2 = changedSpeedY;

    }
}


void checkCollision(Sphere *sphere){

    if (((*sphere).pos.var1 >= 800 - (*sphere).Radius) || ((*sphere).pos.var1 <= (*sphere).Radius)){
            (*sphere).speed.var1 = -(*sphere).speed.var1;
        }
    if (((*sphere).pos.var2 >= 600 - (*sphere).Radius) || ((*sphere).pos.var2 <= (*sphere).Radius)){
            (*sphere).speed.var2 = -(*sphere).speed.var2;
        }
}

void drawSphere(Sphere sphere, int N){

    COLORREF color = txGetFillColor();
    COLORREF border = txGetColor();
    for (auto i = 0; i < N; i++){
        txSetFillColor(RGB(i * sphere.red / N, i * sphere.green / N, i * sphere.blue / N));
        txSetColor(RGB(i * sphere.red / N, i * sphere.green / N, i * sphere.blue / N));
        txCircle(sphere.pos.var1 + sphere.Radius * i/(2 * N), sphere.pos.var2 - sphere.Radius * i / (2 * N), sphere.Radius - sphere.Radius * i / N);
        }
    txSetFillColor(color);
    txSetColor(border);
}

int main(){

    int N = 50;

    Sphere spherePlayer = {{100, 100}, {10, 10}, 100, 0, 0, 50};
    Sphere sphereEnemy1 = {{500, 500}, {5, -10}, 0, 100, 0, 50};
    Sphere sphereEnemy2 = {{300, 100}, {20, 10}, 0, 0, 100, 50};

    double previousX, previousY;

    double dt = 1;

    double distance = 0;


    txCreateWindow(800, 600);
    txSetFillColor(RGB(20, 20, 20));



    while ((not isCollidedTwoSpheres(spherePlayer, sphereEnemy1)) && (not isCollidedTwoSpheres(spherePlayer, sphereEnemy2))){

        txClear();
        txBegin();
        drawSphere(spherePlayer, N);
        drawSphere(sphereEnemy1, N);
        drawSphere(sphereEnemy2, N);
        txEnd();

        controlSphere(&spherePlayer);

        previousX = spherePlayer.pos.var1;
        previousY = spherePlayer.pos.var2;

        moveSphere(&spherePlayer, dt);
        moveSphere(&sphereEnemy1, dt);
        moveSphere(&sphereEnemy2, dt);

        distance += sqrt(pow(spherePlayer.pos.var1-previousX, 2) + pow(spherePlayer.pos.var2 - previousY, 2));

        checkCollision(&spherePlayer);
        checkCollision(&sphereEnemy1);
        checkCollision(&sphereEnemy2);

        if (isCollidedTwoSpheres(sphereEnemy1, sphereEnemy2)){

            Collision(&sphereEnemy1, &sphereEnemy2);


    }
    }

    std::cout << "Your score is " << distance ;

    return 0;

}


