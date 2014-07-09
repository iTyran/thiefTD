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

USING_NS_CC;

class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    virtual void changeDirection(float dt){};
    virtual void enemyExpload(){};
    Node* currPoint();
    Node* nextPoint();
    void runFllowPoint();
    void setPointsVector(Vector<Node*> points);
	void createAndSetHpBar();
private:
    Vector<Node*> pointsVector;
    
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    Animation *animationExplode;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(int, currHp, CurrHp);
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
	Sprite* sprite;
    Sprite* hpBgSprite;
};



#endif /* defined(__thiefTD__Enemy__) *///;
