//
//  Thief.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "Thief.h"


bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    setRunSpeed(9);
    setMaxHp(10);
    setCurrHp(10);
    sprite = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft");
    animationExplode= createAnimation("explode", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode");
    
    createAndSetHpBar();
	schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
	return true;
}

Thief* Thief::createThief(Vector<Node*> points)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->runFllowPoint();
        
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
