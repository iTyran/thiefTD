//
//  Enemy.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#include "Enemy.h"
#include "CCVector.h"


bool EnemyBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
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
    return this->pointsVector.at(pointCount);
}

Node* EnemyBase::nextPoint()
{
    int maxCount = this->pointsVector.size();
	pointCount++;
	if (pointCount > maxCount-1){
		pointCount = 0;
    }
    auto node =this->pointsVector.at(pointCount);
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

void EnemyBase::setPointsVector(Vector<Node*> points)
{
    this->pointsVector = points;
}

//--------------Thief------------------

bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    pointCount = 0;
    setRunSpeed(6);
    
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft");
    
	runAction(Animate::create(animationRight) );

    schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
	return true;
}


