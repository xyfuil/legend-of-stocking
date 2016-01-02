#include "Stocking.h"

USING_NS_CC;


Stocking::Stocking(void)
{
	this->_centerToBottom = 39.0f;
	this->_centerToSides = 29.0f;
	this->_hp = 120;
	this->_mp = 120;
	this->_damage = 10.0f;
	this->_mDamage = 20.0f;
	this->_walkSpeed = 80;
}


Stocking::~Stocking(void)
{
}

bool Stocking::init()
{
	if(!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
	{
		return false;
	}
	int i;
	
	// 空闲动作
	Vector<SpriteFrame *> idleFrames;
	for(i = 0; i < 4; i++){
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_idle_%02d.png", i)->getCString());
		idleFrames.pushBack(frame);
	}
	auto idleAnimation = Animation::createWithSpriteFrames(idleFrames, 0.2f);
	this->_idleAction = RepeatForever::create(Animate::create(idleAnimation));
	this->_idleAction->retain();

	// 攻击动作
	Vector<SpriteFrame *> attackFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_attack_%02d.png", i)->getCString());
		attackFrames.pushBack(frame);
	}
	auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f);
	this->_attackAction = Sequence::create(Animate::create(attackAnimation), CallFunc::create(CC_CALLBACK_0(ActionSprite::idle, this)), NULL);
	this->_attackAction->retain();

	Vector<SpriteFrame *> magicFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_magic_%02d.png", i)->getCString());
		magicFrames.pushBack(frame);
	}
	auto magicAnimation = Animation::createWithSpriteFrames(magicFrames, 0.2f);
	this->_magicAction = Sequence::create(Animate::create(magicAnimation), CallFunc::create(CC_CALLBACK_0(ActionSprite::idle, this)), NULL);
	this->_magicAction->retain();

	// 行走动作
	Vector<SpriteFrame *> walkFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_walk_%02d.png", i)->getCString());
		walkFrames.pushBack(frame);
		walkFrames.pushBack(frame);
	}
	auto walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.05f);
	this->_walkAction = RepeatForever::create(Animate::create(walkAnimation));
	this->_walkAction->retain();

	// 跑步动作
	Vector<SpriteFrame *> runFrames;
	for (int i = 0; i < 1; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_run_%02d.png", i)->getCString());
		runFrames.pushBack(frame);
		runFrames.pushBack(frame);
	}
	auto runAnimation = Animation::createWithSpriteFrames(runFrames, 0.05f);
	this->_runAction = RepeatForever::create(Animate::create(runAnimation));
	this->_runAction->retain();

	// 受伤动作
	Vector<SpriteFrame *> hurtFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_hurt_%02d.png", i)->getCString());
		hurtFrames.pushBack(frame);
	}
	auto hurtAnimation = Animation::createWithSpriteFrames(hurtFrames, 0.1f);
	this->_hurtAction = Sequence::create(Animate::create(hurtAnimation), CallFunc::create(CC_CALLBACK_0(ActionSprite::idle, this)), NULL);
	this->_hurtAction->retain();

	// 死亡动作
	Vector<SpriteFrame *> deadFrames;
	for (int i = 0; i < 3; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("stocking_knockout_%02d.png", i)->getCString());
		deadFrames.pushBack(frame);
	}
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
	this->_deadAction = Sequence::create(Animate::create(deadAnimation), Blink::create(2.0, 8.0), NULL);
	this->_deadAction->retain();

	this->_hitBox = this->createBoundingBoxWithOrigin(Point(-this->_centerToSides, -this->_centerToBottom),
		Size(this->_centerToSides * 2, this->_centerToBottom * 2));
	this->_attackBox = this->createBoundingBoxWithOrigin(Point(this->_centerToSides, -10),
		Size(20, 20));

	this->scheduleUpdate();

	return true;
}
