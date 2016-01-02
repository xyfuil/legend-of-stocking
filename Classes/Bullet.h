#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();

	virtual bool init();
	CREATE_FUNC(Bullet);

	cocos2d::Vec2 _startPos;
	float _v;
	float _a;
	float _angle;
	float _dela;

	cocos2d::Action *_moveAction;
	cocos2d::Action *_brokeAction;

	void createShot(cocos2d::Vec2 startPos, float v, float a, float angle, float dela);
	void move();
	void broke();
	void update(float dt);
};

#endif	// _BULLET_H_
