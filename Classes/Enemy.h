//
//  Enemy.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#ifndef __thiefTD__Enemy__
#define __thiefTD__Enemy__

#include <iostream>

#include "cocos2d.h"
#include "PlayLayer.h"


USING_NS_CC;
class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    void changeDirection(float dt);
    Node* currPoint();
    Node* nextPoint();
    void runFllowPoint();
    void setPointsVector(Vector<Node*> points);
    
private:
    Vector<Node*> pointsVector;
    
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(int, currHp, CurrHp);
    
};

class Thief : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Thief* createThief(Vector<Node*> points);
    
};


#endif /* defined(__thiefTD__Enemy__) *///;
