#include "Robot.h"
#include "GameLayer.h"

USING_NS_CC;

Robot::Robot(void)
{
	this->_centerToBottom = 39.0f;
	this->_centerToSides = 29.0f;
	this->_hp = 100;
	this->_damage = 10;
	this->_walkSpeed = 80;

	this->_nextDecisionTime = 0;
}


Robot::~Robot(void)
{
}

bool Robot::init()
{
	if(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png"))
	{
		return false;
	}

	// 空闲动作
	Vector<SpriteFrame *> idleFrames;
	for (int i = 0; i < 4; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("robot_idle_%02d.png", i)->getCString());
		idleFrames.pushBack(frame);
	}
	auto idleAnimation = Animation::createWithSpriteFrames(idleFrames, 0.1f);
	this->_idleAction = RepeatForever::create(Animate::create(idleAnimation));
	this->_idleAction->retain();

	// 攻击动作
	Vector<SpriteFrame *> attackFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("robot_attack_00_%02d.png", i)->getCString());
		attackFrames.pushBack(frame);
	}
	auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.05f);
	this->_attackAction = Sequence::create(Animate::create(attackAnimation), CallFunc::create(CC_CALLBACK_0(Robot::idle, this)), NULL);
	this->_attackAction->retain();

	// 行走动作
	Vector<SpriteFrame *> walkFrames;
	for (int i = 0; i < 6; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("robot_walk_%02d.png", i)->getCString());
		walkFrames.pushBack(frame);
	}
	auto walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.1f);
	this->_walkAction = RepeatForever::create(Animate::create(walkAnimation));
	this->_walkAction->retain();

	// 受伤动作
	Vector<SpriteFrame *> hurtFrames;
	for (int i = 0; i < 2; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("robot_hurt_%02d.png", i)->getCString());
		hurtFrames.pushBack(frame);
	}
	auto hurtAnimation = Animation::createWithSpriteFrames(hurtFrames, 0.1f);
	this->_hurtAction = Sequence::create(Animate::create(hurtAnimation), CallFunc::create(CC_CALLBACK_0(ActionSprite::idle, this)), NULL);
	this->_hurtAction->retain();

	// 死亡动作
	Vector<SpriteFrame *> deadFrames;
	for (int i = 0; i < 5; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("robot_knockout_%02d.png", i)->getCString());
		deadFrames.pushBack(frame);
	}
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
	this->_deadAction = Sequence::create(Animate::create(deadAnimation), Blink::create(2.0, 8.0), CallFunc::create(CC_CALLBACK_0(Robot::end, this)), RemoveSelf::create(), NULL);
	this->_deadAction->retain();

	this->_hitBox = this->createBoundingBoxWithOrigin(Point(-this->_centerToSides, -this->_centerToBottom),
		Size(this->_centerToSides * 2, this->_centerToBottom * 2));
	this->_attackBox = this->createBoundingBoxWithOrigin(Point(this->_centerToSides, -5),
		Size(25, 20));

	return true;
}

void Robot::end()
{
}