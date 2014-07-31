//
//  GameManager.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#ifndef __thiefTD__GameManager__
#define __thiefTD__GameManager__

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"


USING_NS_CC;

class GameManager
{
public:
    
    Vector<EnemyBase*> enemyVector;
    Vector<Sprite*> bulletVector;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;
    
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(std::string, curBgName, CurBgName);
    
    bool init();
	void clear();
    
	static GameManager* getInstance();
    
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
