#ifndef _CRIWARE_H_
#define _CRIWARE_H_

#include "cocos2d.h"

class criware : public cocos2d::Layer
{
public:
	criware();
	~criware();

	virtual bool init();
	CREATE_FUNC(criware);

	void end();
};

#endif	// _CRIWARE_H_