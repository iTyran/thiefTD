//
//  TowerPanleLayer.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#ifndef __thiefTD__TowerPanleLayer__
#define __thiefTD__TowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;

typedef enum
{
    ARROW_TOWER = 0,
    DECELERATE_TOWER = 1,
	MULTIDIR_TOWER,
	ANOTHER
} TowerType;

class TowerPanleLayer: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerPanleLayer);
    
    bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
    
    CC_SYNTHESIZE(TowerType, chooseTowerType, ChooseTowerType);
    
private:
    
    Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
};


#endif /* defined(__thiefTD__TowerPanleLayer__) */
