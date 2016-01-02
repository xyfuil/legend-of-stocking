#ifndef _WEL_LAYER_H_
#define _WEL_LAYER_H_

#include "cocos2d.h"
#include "AtomUtil.h"

class WelLayer : public cocos2d::Layer
{
public:
	WelLayer();
	~WelLayer();


	virtual bool init();
	CREATE_FUNC(WelLayer);

	void startCallback(cocos2d::Ref *pSender);
	void exitCallback(cocos2d::Ref *pSender);

	void onEnterTransitionDidFinish();
};

#endif	// _WEL_LAYER_H_