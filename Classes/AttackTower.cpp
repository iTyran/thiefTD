//
//  AttackTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "AttackTower.h"
#include "GameManager.h"

bool AttackTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);
	setTowerValue(200);
    setLethality(1);
    setRate(2);
    tower= Sprite::createWithSpriteFrameName("attackTower.png");
    this->addChild(tower);
    
    schedule(schedule_selector(AttackTower::shoot), 0.8f);
	return true;
}


Sprite* AttackTower::AttackTowerBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
    this->addChild(bullet);
    
    return bullet;
}

void AttackTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = AttackTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(AttackTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void AttackTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}