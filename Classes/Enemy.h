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

#include "GameManager.h"

USING_NS_CC;
class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    
    static EnemyBase *create();
    static Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    Node* currPoint();
    Node* nextPoint();
    
    float runSpeed;
    int maxHp;
    int currHp;
    int pointCount;
    GameManager* instance;
};

class EnemyFast : public EnemyBase
{
public:
    static EnemyBase* createEnemy();
};

class EnemySlow : public EnemyBase
{
public:
    static EnemyBase* createEnemy();
};


#endif /* defined(__thiefTD__Enemy__) */
