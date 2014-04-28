//
//  Tower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#include "Tower.h"

TowerBase::TowerBase()
:enemyVector(NULL)
,scope(0)
,nearestEnemy(NULL)
,scopeEnemys(NULL)
{
}

bool TowerBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}


Vector<EnemyBase*> TowerBase::getEnemysWithinScope()
{
    EnemyBase *temp = NULL;
    auto enemyCount = enemyVector.size();
    for(int i = 0; i < enemyCount; i++)
    {
        temp = enemyVector.at(i);
        float distance = this->getPosition().getDistance(temp->sprite->getPosition());
        if(distance < this->scope)
        {
            scopeEnemys.pushBack(temp);
        }
    }
    return scopeEnemys;
}


void TowerBase::checkNearestEnemy()
{
	EnemyBase *enemy = NULL;
	double maxDistant = Director::getInstance()->getWinSize().width;
    auto enemyCount = enemyVector.size();
    
	for(int i = 0; i < enemyCount; i++)
	{
		enemy = enemyVector.at(i);
		double curDistance = this->getPosition().getDistance(enemy->sprite->getPosition());
        
		if (curDistance < maxDistant) {
			maxDistant = curDistance;
		}
	}
	if (maxDistant < this->scope){
        nearestEnemy = enemy;
    }
    else{
        nearestEnemy = NULL;
    }
}

void TowerBase::setEnemyVector(Vector<EnemyBase*> enemys)
{
    enemyVector = enemys;
}


//===============ArrowTower===============//

bool ArrowTower::init()
{
    if (!Sprite::init())
	{
		return false;
	}
    currBullet = NULL;
    setScope(200);
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    arrow = Sprite::createWithSpriteFrameName("arrow.png");
    arrow->setAnchorPoint(Point(0.3f, 0.5f));
    arrow->setPosition(baseplate->getPositionX() , baseplate->getPositionY() + baseplate->getContentSize().height /4  );
    addChild(baseplate);
    addChild(arrow);
    
    schedule(schedule_selector(ArrowTower::rotateAndShoot), 0.8f);
    scheduleUpdate();
	return true;
}

ArrowTower* ArrowTower::createArrowTower(Vector<EnemyBase*> enemys)
{
    ArrowTower *pRet = new ArrowTower();
    if (pRet && pRet->init())
    {
        pRet->setEnemyVector(enemys);
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

Sprite* ArrowTower::createBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setAnchorPoint(Point(0.3f, 0.5f));
    bullet->setPosition(arrow->getPosition());
    bullet->setRotation(arrow->getRotation());
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
        arrow->runAction( Sequence::create(RotateTo::create(rotateDuration, shootDegrees),
                                           CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
                                           NULL));
        
	}
}


void ArrowTower::shoot()
{
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto moveDuration = 2;
        Point shootVector1 = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector1.normalize();
		Point overshotVector = normalizedShootVector * 480;
		Point offscreenPoint = (arrow->getPosition() - overshotVector);
        
        currBullet = createBullet();
        currBullet->setTag(2);
        bulletVector.pushBack(currBullet);
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ArrowTower::removeBullet(Node* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
    bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}


void ArrowTower::update(float dt)
{
    Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    
    for (int i = 0; i < this->bulletVector.size(); i++)
	{
		auto  bullet = bulletVector.at(i);
		auto  bulletRect = Rect(bullet->getPositionX()+bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			auto enemyRect = enemy->sprite->boundingBox();
            
			if (bulletRect.intersectsRect(enemyRect))
			{
                auto currHp = enemy->getCurrHp();
                currHp--;
                enemy->setCurrHp( currHp );
                
				auto currHpPercentage = enemy->getHpPercentage();
                auto offHp = 100 / enemy->getMaxHp();
				currHpPercentage -= offHp;
                enemy->setHpPercentage(currHpPercentage);
				enemy->getHpBar()->setPercentage(currHpPercentage);
                
                if(currHp <= 0)
                {
                    enemyNeedToDelete.pushBack(enemy);
                }
                bulletNeedToDelete.pushBack( bullet);
                log("currHp :  %i",currHp);
				log("currHpPercentage :  %f",currHpPercentage);
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
            enemyTemp->enemyExpload();
            enemyVector.eraseObject(enemyTemp);
		}
        
		enemyNeedToDelete.clear();
	}
	
	for (const auto& bulletTemp : bulletNeedToDelete)
	{
		bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}



