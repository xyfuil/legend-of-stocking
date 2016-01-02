#include "Bullet.h"

#define PI 3.1415926

USING_NS_CC;

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Vector<SpriteFrame *> moveFrames;
	for (int i = 0; i < 6; i++){
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("firen_ball_%02d.png", i)->getCString());
		moveFrames.pushBack(frame);
	}
	auto moveAnimation = Animation::createWithSpriteFrames(moveFrames, 0.05f);
	_moveAction = RepeatForever::create(Animate::create(moveAnimation));
	this->_moveAction->retain();

	Vector<SpriteFrame *> brokeFrames;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("firen_ball_broke_%02d.png", i)->getCString());
		brokeFrames.pushBack(frame);
	}
	auto brokeAnimation = Animation::createWithSpriteFrames(brokeFrames, 0.05f);
	_brokeAction = Sequence::create(Animate::create(brokeAnimation), RemoveSelf::create(), NULL);
	this->_brokeAction->retain();

	return true;
}

void Bullet::createShot(Vec2 startPos, float v, float a, float angle, float dela)
{
	initWithSpriteFrameName("firen_ball_none.png");
	this->setPosition(startPos);
	if (v < 0.0f)
	{
		this->setScaleX(-1.0f);
	}
	this->_startPos = startPos;
	this->_v = v;
	this->_a = a;
	this->_angle = angle;
	this->_dela = dela;

	auto action = Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(Bullet::move, this)), NULL);
	this->runAction(action);
}

void Bullet::move()
{
	this->runAction(_moveAction);

	this->scheduleUpdate();
}

void Bullet::broke()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	this->setPositionX(this->getPosition().x + _v * 4.0f);
	this->runAction(_brokeAction);
}

void Bullet::update(float dt)
{
	this->setPositionX(this->getPosition().x + _v);
}