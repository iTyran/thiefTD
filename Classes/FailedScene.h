//
//  FailedScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-12.
//
//

#ifndef __thiefTD__FailedScene__
#define __thiefTD__FailedScene__

#include <iostream>
#include "cocos2d.h"

class FailedScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
    CREATE_FUNC(FailedScene);  
    void menuBackCallback(Ref* pSender);  

}; 
#endif /* defined(__thiefTD__FailedScene__) */
