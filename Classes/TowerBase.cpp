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
,nearestEnemy(NULL)
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


void TowerBase::checkNearestEnemy()
{
    GameManager *instance = GameManager::getInstance();
    
    auto enemyVector = instance->enemyVector;
    
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







