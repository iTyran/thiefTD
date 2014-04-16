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

bool EnemyBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    
    schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
    
	return true;
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> animFrames;
    
	for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "_%i.png",  i);
        std::string str =  prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}

Node* EnemyBase::currPoint()
{
    return instance->pointsVector.at(pointCount);
}

Node* EnemyBase::nextPoint()
{
    
    int maxCount = instance->pointsVector.size();
	pointCount++;
	if (pointCount > maxCount-1){
		pointCount = 0;
    }
    auto node =instance->pointsVector.at(pointCount);
    return node;
}

void EnemyBase::changeDirection(float dt)
{
    auto curr = currPoint();

    if(curr->getPositionX() >= this->getPosition().x )
    {
        runAction( Animate::create(animationRight->clone()) );
    }
    else
    {
        runAction( Animate::create(animationLeft->clone())  );
    }
}


//--------------EnemyFast------------------

EnemyBase* EnemyFast::createEnemy()
{
    auto enemyFast = EnemyBase::create();
    
    enemyFast->pointCount = 0;
    enemyFast->runSpeed = 6;
    enemyFast->instance = GameManager::getInstance();
    
	enemyFast->animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(enemyFast->animationRight, "runright");
    enemyFast->animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(enemyFast->animationLeft, "runleft");

	enemyFast->runAction(Animate::create(enemyFast->animationRight) );

    return enemyFast;
}

