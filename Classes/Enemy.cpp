//
//  Enemy.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#include "Enemy.h"
#include "CCVector.h"

EnemyBase::EnemyBase():
runSpeed(0)
{
}

EnemyBase::~EnemyBase(){ }

EnemyBase *EnemyBase::create()
{
    EnemyBase *enemyBase = (EnemyBase *)Sprite::create();
    return enemyBase;
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> animFrames;
    
	for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "%i.png",  i);
        std::string str =  prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}

Node* EnemyBase::currPoint()
{
    instance = GameManager::getInstance();
    return instance->pointsVector.at(pointCount);
}

Node* EnemyBase::nextPoint()
{
    instance = GameManager::getInstance();
    int maxCount = instance->pointsVector.size();
	pointCount++;
	if (pointCount > maxCount-1){
		pointCount = 0;
    }
    return instance->pointsVector.at(pointCount);
}


//--------------EnemyFast------------------

EnemyBase* EnemyFast::createEnemy()
{
    auto enemyFast = EnemyBase::create();
	Animation *animation = createAnimation("enemy", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation, "runright");
	Animate *animate = Animate::create(animation);
    
	enemyFast->runAction(CCRepeatForever::create( animate ));
    
    enemyFast->pointCount = 0;
    enemyFast->runSpeed = 6;
    
    return enemyFast;
}

