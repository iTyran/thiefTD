//
//  GroupEnemy.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-17.
//
//

#ifndef __thiefTD__GroupEnemy__
#define __thiefTD__GroupEnemy__

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"

class GroupEnemy: public cocos2d::Node
{
public:
    
    virtual bool init();
    GroupEnemy* initGroupEnemy(int type1Total, int type1Hp, int type2Total, int type2Hp, int type3Total, int type3Hp );
    CREATE_FUNC(GroupEnemy);
    
    CC_SYNTHESIZE(int, type1Total, Type1Total);
    CC_SYNTHESIZE(int, type2Total, Type2Total);
    CC_SYNTHESIZE(int, type3Total, Type3Total);
    CC_SYNTHESIZE(int, type1Hp, Type1Hp);
    CC_SYNTHESIZE(int, type2Hp, Type2Hp);
    CC_SYNTHESIZE(int, type3Hp, Type3Hp);
    CC_SYNTHESIZE(int, enemyTotal, EnemyTotal);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
};
#endif /* defined(__thiefTD__GroupEnemy__) */
