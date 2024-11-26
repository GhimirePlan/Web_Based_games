#include "body.h"
#include <iostream>
#include "raymath.h"
std::vector<Vector2> Body::getAxis(){
    Vector2 OX = {1,0};
    Vector2 OY = {0,1};

    Vector2 RX = Vector2Rotate(OX,angle*3.14/180);
    Vector2 RY = Vector2Rotate(OY,angle*3.14/180);
    std::vector<Vector2> axes = {Vector2Normalize(RX),Vector2Normalize(RY)};
    return axes;
}
std::vector<Vector2> Body::getCorners(){
    std::vector<Vector2> axes = getAxis();
    Vector2 X = Vector2Scale(axes[0],(sizex/2));
    Vector2 Y = Vector2Scale(axes[1],(sizey/2));
    std::vector<Vector2> cor = {
        Vector2Add(this->getPos(),Vector2Add(X,Y)),
        Vector2Add(this->getPos(),Vector2Subtract(X,Y)),
        Vector2Subtract(this->getPos(),Vector2Add(X,Y)),
        Vector2Subtract(this->getPos(),Vector2Subtract(X,Y)),

    };
    DrawLine(this->getPos().x,this->getPos().y, cor[3].x,cor[3].y, BLACK);
    DrawLine(this->getPos().x,this->getPos().y, cor[2].x,cor[2].y, BLACK);
    DrawLine(this->getPos().x,this->getPos().y, cor[1].x,cor[1].y, BLACK);
    DrawLine(this->getPos().x,this->getPos().y, cor[0].x,cor[0].y, BLACK);
    //std::cout<<"{"<<getPos().x<<","<<getPos().y<<"}";
    return cor;
}

std::vector<bool> Body::project(Body* b){ 
            std::vector<bool> isColliding; 
            for(int i = 0;i<2;i++){
 bool sign ;
            float maxMag = -__FLT_MAX__;
            float minMag = __FLT_MAX__; 
            float mmmm=__FLT_MAX__;
            float mmim=__FLT_MIN__;
            Vector2 minProj;
            Vector2 maxProj;
                for(int j = 0; j<4;j++){
                    DrawLine(b->getPos().x-(b->getAxis()[i].x*100), (b->getPos().y-b->getAxis()[i].y*100), (b->getPos().x+(b->getAxis()[i].x*100)),(b->getPos().y+b->getAxis()[i].y*100), RED);
                    float dot = b->getAxis()[i].x * (this->getCorners()[j].x-b->getPos().x)+b->getAxis()[i].y * (this->getCorners()[j].y-b->getPos().y);
                    
                    Vector2 proj = {b->getPos().x+(b->getAxis()[i].x*dot),b->getPos().y+(b->getAxis()[i].y*dot)};
                    
                    // DrawLine(b->getPos().x+25,b->getPos().y, b->getPos().x+proj.x+25, b->getPos().y+proj.y, BLUE);
                    Vector2 cp = {proj.x - b->getPos().x, proj.y - b->getPos().y};
                    sign = (cp.x*b->getAxis()[i].x)+(cp.y * b->getAxis()[i].y)>0;
                    float signedMag = Vector2Length(cp) * ((sign)?1:-1);
                    // DrawLine(b->getPos().x,b->getPos().y, b->getPos().x+cp.x, b->getPos().y+cp.y, YELLOW);
                    // DrawLine(b->getPos().x,b->getPos().y, proj.x, proj.y, (j==0)?BROWN:(j==1)?RED:(j==2)?GREEN:BLUE);
                // DrawLine(b->getPos().x,b->getPos().y, b->getPos().x+cp.x, b->getPos().y+cp.y, BROWN);
                    
                    if(signedMag<=minMag){
                        minMag = signedMag;
                        minProj.x = proj.x;
                        minProj.y = proj.y;

                    }
                    // if(signedMag<=minMag){
                    //     //std::cout<<"["<<i<<"]"<<"{"<<cp.x<<","<<cp.y<<"}"<<"mag:"<<cp.Magnitude();
                    //     std::cout<<"["<<i<<"min]"<<signedMag;
                    //     minMag = signedMag;
                    //     minProj = proj;
                    // }
                    if(signedMag>=maxMag){
                        maxMag = signedMag;
                        maxProj.x = proj.x;
                        maxProj.y = proj.y;
                    }
                    // if(cp.Magnitude()<=mmmm){
                    //     mmmm = cp.Magnitude();
                    //     minProj = proj;

                    // }
                    // if(cp.Magnitude()>=mmim){
                    //     mmim = cp.Magnitude();
                    //     maxProj = proj;

                    // }

                }
                DrawPoint3D({minProj.x,minProj.y, 0}, BLACK);
                DrawLine(minProj.x,minProj.y, maxProj.x, maxProj.y, BROWN);
                if(i==0)
                isColliding.push_back((minMag<0&&maxMag>0)||(std::abs(minMag)<b->getBounds().x)||(std::abs(maxMag)<b->getBounds().x));
                else
                isColliding.push_back((minMag<0&&maxMag>0)||(std::abs(minMag)<b->getBounds().y)||(std::abs(maxMag)<b->getBounds().y));
                // isColliding.push_back((minMag<0&&maxMag>0)||(std::abs(minMag)<(i==0)?(b->getBounds().x):(b->getBounds().y))||(std::abs(maxMag)<(i==0)?(b->getBounds().x):b->getBounds().y));
                // std::cout<<"OI: "<<(std::abs(minMag)<((i==0)?b->getBounds().x:b->getBounds().y));
                // if(i==0){
                //     if(2*b->getBounds().x<std::abs(minProj.x-maxProj.x))
                //     isColliding.push_back((b->getPos().x>maxProj.x&&b->getPos().x<minProj.x)||(b->getPos().x<maxProj.x&&b->getPos().x>minProj.x));
                //     else
                //     isColliding.push_back((b->getPos().x+b->getBounds().Rotate(angle).x>maxProj.x&&b->getPos().x+b->getBounds().x>minProj.x)||(b->getPos().x-b->getBounds().x<maxProj.x&&b->getPos().x-b->getBounds().x<minProj.x));
                // }else{
                //     if(2*b->getBounds().y<std::abs(minProj.y-maxProj.y))
                //     isColliding.push_back((b->getPos().y>maxProj.y&&b->getPos().y<minProj.y )||(b->getPos().y<maxProj.y&&b->getPos().y>minProj.y ));
                //     else
                //     isColliding.push_back((b->getPos().y+b->getBounds().y>maxProj.x&&b->getPos().y+b->getBounds().y>minProj.x)||(b->getPos().y-b->getBounds().y<maxProj.x&&b->getPos().y-b->getBounds().y<minProj.x));

                // }
            }
        return isColliding;
}