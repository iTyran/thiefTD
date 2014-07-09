//
//  TowerBase.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#include "TowerBase.h"
#include "GameManager.h"

TowerBase::TowerBase()
:scope(0)
,towerValue(0)
,lethality(0)
,rate(0)
,nearestEnemy(NULL)
{
}

bool TowerBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    scheduleUpdate();
	return true;
}


void TowerBase::checkNearestEnemy()
{
    GameManager *instance = GameManager::getInstance();
    auto enemyVector = instance->enemyVector;
    
	auto currMinDistant = this->scope;
    
    EnemyBase *enemyTemp = NULL;
	for(int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->sprite->getPosition());
        
		if (distance < currMinDistant) {
			currMinDistant = distance;
            enemyTemp = enemy;
		}
	}
    nearestEnemy = enemyTemp;
}






