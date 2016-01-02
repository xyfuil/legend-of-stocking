#ifndef _EXPLODE_H_
#define _EXPLODE_H_

#include "cocos2d.h"

class Explode : public cocos2d::Sprite
{
public:
	Explode();
	~Explode();

	virtual bool init();
	CREATE_FUNC(Explode);
};

#endif	// _EXPLODE_H_
