//
//  LevelInfoScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-21.
//
//

#ifndef __thiefTD__Loading__
#define __thiefTD__Loading__

#include <iostream>
#include "cocos2d.h"
#include "LoadLevelInfo.h"
USING_NS_CC;

class LevelInfoScene : public Layer
{
public:

	LevelInfoScene();
    CREATE_FUNC(LevelInfoScene);
    static Scene * createScene();
	bool init();
    void addBackGround();
                                                                                  
    void initLoadInfo(int bigLevel,int smallLevel);
	void menuBackCallback(Ref* pSender);
	void menuStartCallback(Ref* pSender);

private:
	LoadLevelinfo* info;
	std::string fileName;
};
#endif /* defined(__thiefTD__LevelInfoScene__) */
