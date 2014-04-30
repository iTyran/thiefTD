//
//  ArrowTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);
    
    rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(0, baseplate->getContentSize().height /4  );
    addChild(rotateArrow);
    
    schedule(schedule_selector(ArrowTower::rotateAndShoot), 0.8f);
    scheduleUpdate();
	return true;
}


Sprite* ArrowTower::ArrowTowerBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(rotateArrow->getPosition());
    bullet->setRotation(rotateArrow->getRotation());
    addChild(bullet);
    
    return bullet;
}

void ArrowTower::rotateAndShoot(float dt)
{
    checkNearestEnemy();
    if (nearestEnemy != NULL)
	{
		Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		float shootRadians = shootVector.getAngle();
		float shootDegrees = CC_RADIANS_TO_DEGREES(-1 * shootRadians);
        
		float speed = 0.5 / M_PI;
		float rotateDuration = fabs(shootRadians * speed);
        rotateArrow->runAction( Sequence::create(RotateTo::create(rotateDuration, shootDegrees),
                                                 CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
                                                 NULL));
	}
}

void ArrowTower::shoot()
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto moveDuration = 2;
        Point shootVector1 = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector1.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (rotateArrow->getPosition() - overshotVector);
        
        auto currBullet = ArrowTowerBullet();
        instance->bulletVector.pushBack(currBullet);
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ArrowTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}



