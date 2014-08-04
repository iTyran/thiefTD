//
//  LoadingResScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-6-8.
//
//

#ifndef __thiefTD__LoadingResScene__
#define __thiefTD__LoadingResScene__

#include <iostream>
#include "cocos2d.h"
#include "LoadLevelInfo.h"
USING_NS_CC;

class LoadingResScene : public Layer
{
public:

	LoadingResScene();
    CREATE_FUNC(LoadingResScene);
    static Scene * createScene();
	virtual bool init();
    
    ProgressTimer *addProgress();
    void loadResources();
	void transitionScene();
	void loadingCallBack(cocos2d::Texture2D *texture);

private:
    
	ProgressTimer* progressBar;
	int numberOfLoadedRes;
	int totalOfLoadedRes;
};
#endif /* defined(__thiefTD__LoadingResScene__) */
