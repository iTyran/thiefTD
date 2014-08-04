//
//  LoadLevelInfo.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-12.
//
//

#include "LoadLevelInfo.h"
#include "GameManager.h"

LoadLevelinfo::~LoadLevelinfo()
{
    clearAll();
}

LoadLevelinfo *LoadLevelinfo::createLoadLevelinfo(const std::string& plistpath)
{
    LoadLevelinfo *pRet = new LoadLevelinfo();
    if (pRet && pRet->initPlist(plistpath))
    {
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

bool LoadLevelinfo::initPlist(const std::string& plistpath)
{
    bool bRet = false;
    do
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistpath);
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
        resources = dict["resources"].asValueMap();
        levelInfo = dict["levelInfo"].asValueMap();
        
        bRet = true;
    }
    while (0);
    return bRet;
}

void LoadLevelinfo::clearAll()
{
    resources.clear();
    levelInfo.clear();
}

void LoadLevelinfo::readLevelInfo()
{
	GameManager *instance = GameManager::getInstance();
    
	auto money =   levelInfo["money"].asFloat();
	instance->setMoney(money);
	auto currlevel =   levelInfo["currlevel"].asString();
	instance->setCurrLevelFile(currlevel);
	auto nextlevel =   levelInfo["nextlevel"].asString();
	instance->setNextLevelFile(nextlevel);
    
    ValueMap& groupDict = levelInfo["group"].asValueMap();

	auto groupTotle = groupDict.size();
	instance->setGroupNum(groupTotle);
    
    for (auto iter = groupDict.begin(); iter != groupDict.end(); ++iter)
    {
        ValueMap& group = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;
        auto type1Num = group["type1Num"].asInt();
		auto type2Num = group["type2Num"].asInt();
		auto type3Num = group["type3Num"].asInt();
		auto type1Hp = group["type1Hp"].asInt();
		auto type2Hp = group["type2Hp"].asInt();
		auto type3Hp = group["type3Hp"].asInt();
        
        GroupEnemy* groupEnemy = GroupEnemy::create()->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp, type3Num, type3Hp);
		instance->groupVector.pushBack(groupEnemy);
    }
    
	auto curMapName =   resources["map"].asString();
	instance->setCurMapName(curMapName);
	auto curBgName =   resources["image"].asString();
	instance->setCurBgName(curBgName);
}