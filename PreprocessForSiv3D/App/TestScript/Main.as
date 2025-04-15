#include"Functions.h"

int counter = 0;
int inCircleCounter = 0;

Font font(50);

void update(){
    counter++;
    if(inCircle(CIRCLE_R*Random(),CIRCLE_R*Random())){
        inCircleCounter++;
    }        
    font(getPi(counter,inCircleCounter)).drawAt(Scene::Center());

#ifdef CIRCLE_R
    ClearPrint();
    Print << "円の半径は" << CIRCLE_R << "です";
#endif

#undef CIRCLE_R

#ifndef CIRCLE_R
    Print << "CIRCLE_R は #undef されました";
#endif

}
