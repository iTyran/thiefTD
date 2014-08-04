//
//  SuccessfulScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__SuccessfulScene__
#define __thiefTD__SuccessfulScene__

#include <iostream>
#include "cocos2d.h"

class SuccessfulScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
     
    void menuNextCallback(Ref* pSender);  
	void menuCloseCallback(Ref* pSender); 
	CREATE_FUNC(SuccessfulScene); 
private:

}; 
#endif /* defined(__thiefTD__SuccessfulScene__) */
