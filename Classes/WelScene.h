#ifndef _WEL_SCENE_H_
#define _WEL_SCENE_H_

#include "cocos2d.h"
#include "AtomUtil.h"

class WelScene : public cocos2d::Scene
{
public:
	WelScene();
	~WelScene();

	virtual bool init();
	CREATE_FUNC(WelScene);

	void onEnterTransitionDidFinish();
};

#endif	// _WEL_SCENE_H_