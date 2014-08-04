//
//  LevelScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__LevelScene__
#define __thiefTD__LevelScene__

#include <iostream>
#include "cocos2d.h"

class LevelScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
    CREATE_FUNC(LevelScene);
    void menuCloseCallback(Ref* pSender);
    static LevelScene *getInstance();
    
private:
    static LevelScene *instance;
}; 
#endif /* defined(__thiefTD__LevelScene__) */
