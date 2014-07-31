//
//  GameManager.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
        instance = new GameManager();
	return instance;
}

void GameManager::clear()
{
	enemyVector.clear();
	bulletVector.clear();
	//towerVector.clear();
	groupVector.clear();
}
