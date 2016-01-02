#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "cocos2d.h"

class Button : public cocos2d::Sprite
{
public:
	Button();
	~Button();

	virtual bool init();
	CREATE_FUNC(Button);
	
	bool isInSprite(cocos2d::Touch *touch);

	int _tag;
	bool isInTouch;
	bool isInMove;
	bool _isDouble;
	long touchBeginTime;
	cocos2d::Point _direction;	//·½Ïò

	void addEvents(char *s, int tag);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif	// _BUTTON_H_