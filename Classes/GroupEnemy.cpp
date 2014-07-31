//
//  GroupEnemy.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-17.
//
//

#include "GroupEnemy.h"
USING_NS_CC;


bool GroupEnemy::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    return true;
}

GroupEnemy* GroupEnemy::initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp, int type3Total, int type3Hp)
{
    this->type1Total = type1Total;
    this->type2Total = type2Total;
    this->type3Total = type3Total;
    this->type1Hp = type1Hp;
    this->type2Hp = type2Hp;
    this->type3Hp = type3Hp;
    this->enemyTotal = type1Total + type2Total + type3Total;
    this->isFinishedAddGroup = false;
    return this;
}

