#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
	LoadingScene();
	~LoadingScene();

	virtual bool init();
	CREATE_FUNC(LoadingScene);
};

#endif	// _LOADING_SCENE_H_