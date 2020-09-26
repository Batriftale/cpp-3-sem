#include "TXLib.h"
#include "iostream"
#include "cmath"

struct Vector{
    double x;
    double y;
};

struct Sphere{
    Vector pos;
    Vector speed;
    int red;
    int green;
    int blue;
    int radius;
};

void collide (Sphere *sphere1, Sphere *sphere2){
        //each mass is 1 unit
        double v_centreX = (sphere1 -> speed.x + sphere2 -> speed.x) / 2 ;
        double v_centreY = (sphere1 -> speed.y + sphere2 -> speed.y) / 2 ;

        sphere1 -> speed.x = -sphere1 -> speed.x + 2 * v_centreX;
        sphere2 -> speed.x = -sphere2 -> speed.x + 2 * v_centreX;
        sphere1 -> speed.y = -sphere1 -> speed.y + 2 * v_centreY;
        sphere2 -> speed.y = -sphere2 -> speed.y + 2 * v_centreY;
}

bool isCollidedTwoSpheres(Sphere sphere1, Sphere sphere2){
     return ((pow((sphere1.pos.x - sphere2.pos.x), 2) +  pow((sphere1.pos.y - sphere2.pos.y), 2) <= (4 * pow(sphere1.radius, 2))));
}
        
void moveSphere(Sphere *sphere, double dt){
    sphere -> pos.x += sphere -> speed.x * dt;
    sphere -> pos.y += sphere -> speed.y * dt;
}

void controlSphere(Sphere *sphere){
    if (txMouseButtons() <= 0){
        return;
    }
    double xCoord = txMouseX();
    double yCoord = txMouseY();

    double xDifference = xCoord - sphere -> pos.x;
    double yDifference = yCoord - sphere -> pos.y;
    double distanceDifference = sqrt(pow(xDifference, 2) + pow(yDifference, 2));
    double xDifferenceNormal = xDifference / distanceDifference;
    double yDifferenceNormal =  yDifference / distanceDifference;

    double speedModule = sqrt(pow(sphere -> speed.x, 2) + pow(sphere -> speed.y, 2));

    double changedSpeedX = xDifferenceNormal * speedModule;
    double changedSpeedY = yDifferenceNormal * speedModule;

    sphere -> speed.x = changedSpeedX;
    sphere -> speed.y = changedSpeedY;
}

void checkCollision(Sphere *sphere, int width, int length){
    if ((sphere -> pos.x >= length - sphere -> radius) || (sphere -> pos.x <= sphere -> radius)){
            sphere -> speed.x = - sphere -> speed.x;
        }
    if ((sphere -> pos.y >= width - sphere -> radius) || (sphere -> pos.y <= sphere -> radius)){
            sphere -> speed.y = - sphere -> speed.y;
        }
}

void drawSphere(Sphere sphere, int detail){
    COLORREF color = txGetFillColor();
    COLORREF border = txGetColor();
    for (auto i = 0; i < detail; i++){
        txSetFillColor(RGB(i * sphere.red / detail, i * sphere.green / detail, i * sphere.blue / detail));
        txSetColor(RGB(i * sphere.red / detail, i * sphere.green / detail, i * sphere.blue / detail));
        txCircle(sphere.pos.x + sphere.radius * i/(2 * detail), sphere.pos.y - sphere.radius * i / (2 * detail), sphere.radius - sphere.radius * i / detail);
        }
    txSetFillColor(color);
    txSetColor(border);
}

int main(){
    int detail = 50;

    Sphere spherePlayer = {{100, 100}, {10, 10}, 100, 0, 0, 50};
    Sphere sphereEnemy1 = {{500, 500}, {5, -10}, 0, 100, 0, 50};
    Sphere sphereEnemy2 = {{300, 100}, {20, 10}, 0, 0, 100, 50};

    double dt = 1;
    double distance = 0;
    int length = 800;
    int width = 600;

    txCreateWindow(length, width);
    txSetFillColor(RGB(20, 20, 20));

    while (true){
        txClear();
        txBegin();
        drawSphere(spherePlayer, detail);
        drawSphere(sphereEnemy1, detail);
        drawSphere(sphereEnemy2, detail);
        txEnd();

        controlSphere(&spherePlayer);

        double previousX = spherePlayer.pos.x;
        double previousY = spherePlayer.pos.y;

        moveSphere(&spherePlayer, dt);
        moveSphere(&sphereEnemy1, dt);
        moveSphere(&sphereEnemy2, dt);

        distance += sqrt(pow(spherePlayer.pos.x - previousX, 2) + pow(spherePlayer.pos.y - previousY, 2));

        checkCollision(&spherePlayer);
        checkCollision(&sphereEnemy1);
        checkCollision(&sphereEnemy2);

        if (isCollidedTwoSpheres(sphereEnemy1, sphereEnemy2)){
            collide(&sphereEnemy1, &sphereEnemy2);
        }
        if ((isCollidedTwoSpheres(spherePlayer, sphereEnemy1)) || (isCollidedTwoSpheres(spherePlayer, sphereEnemy2)){
            break;
        }
    }
    std::cout << "Your score is " << distance ;
    return 0;
}


