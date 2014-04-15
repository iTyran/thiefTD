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

USING_NS_CC;

class GameManager
{
public:
	Vector<Node*> pointsVector;    //路径点集
	static GameManager* getInstance();
    
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
