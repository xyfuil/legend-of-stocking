#include "Explode.h"

#define PI 3.1415926

USING_NS_CC;

Explode::Explode()
{
}


Explode::~Explode()
{
}

bool Explode::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	initWithSpriteFrameName("firen_exp_00.png");
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	Vector<SpriteFrame *> ExplodeFrames;
	for (int i = 0; i < 11; i++){
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("firen_exp_%02d.png", i)->getCString());
		ExplodeFrames.pushBack(frame);
	}
	auto ExplodeAnimation = Animation::createWithSpriteFrames(ExplodeFrames, 0.05f);
	auto ExplodeAction = Sequence::create(Animate::create(ExplodeAnimation), RemoveSelf::create(), NULL);
	this->stopAllActions();
	this->runAction(ExplodeAction);

	return true;
}
