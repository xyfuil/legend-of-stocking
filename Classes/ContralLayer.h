#ifndef _CONTRAL_LAYER_
#define _CONTRAL_LAYER_

#include "cocos2d.h"
#include "Button.h"

class SimpleDPadDelegate;

class ContralLayer : public cocos2d::Layer
{
public:
	ContralLayer();
	~ContralLayer();

	cocos2d::SpriteBatchNode *_pad;
	SimpleDPadDelegate *_delegate;

	cocos2d::Sprite *_hero;
	cocos2d::Sprite *_heroHP;
	cocos2d::Sprite *_heroMP;

	Button *_up;
	Button *_left;
	Button *_right;
	Button *_down;
	cocos2d::Vec2 _direction;

	virtual bool init();
	CREATE_FUNC(ContralLayer);

	void getGame(float dt);
	void update(float dt);
	void move();

	bool _lock;
	bool _button[8];
	int _order;	// ¶¯×÷ÐòÁÐ
	long _lastTime;

	void reflashTime();
};

class SimpleDPadDelegate
{
public:
	virtual void didChangeDirectorTo(ContralLayer *cot, cocos2d::Point direction, int isRun) = 0;
	virtual void isHoldingDirector(ContralLayer *cot, cocos2d::Point direction) = 0;
	virtual void simpleDPadTouchEnded(ContralLayer *cot) = 0;
};

#endif	// _CONTRAL_LAYER_