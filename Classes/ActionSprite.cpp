#include "ActionSprite.h"

USING_NS_CC;

ActionSprite::ActionSprite(void)
{
	this->_actionState = kActionStateNone;
}


ActionSprite::~ActionSprite(void)
{
}

void ActionSprite::update(float dt)
{
	if (_mp < 120.0f)
	{
		_mp += _mpRecover;
	}
}

void ActionSprite::idle()
{
	if(this->_actionState!=kActionStateIdle){
		this->stopAllActions();
		this->runAction(this->_idleAction);
		this->_actionState = kActionStateIdle;
		this->_velocity = Vec2(0.0f, 0.0f);
	}
}

void ActionSprite::attack()
{
	if(this->_actionState == kActionStateIdle || this->_actionState == kActionStateAttack || this->_actionState == kActionStateWalk)
	{
		this->stopAllActions();
		this->_actionState = kActionStateAttack;
		this->runAction(this->_attackAction);
	}
}

bool ActionSprite::magic()
{
	if ((this->_actionState == kActionStateIdle || this->_actionState == kActionStateWalk) && this->_mp >= 10.0f)
	{
		this->stopAllActions();
		this->_actionState = kActionStateMagic;
		this->_mp -= 10.0f;
		this->runAction(this->_magicAction);

		return true;
	}

	return false;
}

void ActionSprite::walkWithDirection(Point direction)
{
	if(this->_actionState == kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(this->_walkAction);
		this->_actionState = kActionStateWalk;
	}

	if(this->_actionState == kActionStateWalk)
	{
		this->_velocity = Point(direction.x * this->_walkSpeed, direction.y * this->_walkSpeed);
		if(this->_velocity.x > 0)
		{
			this->setScaleX(1.0);
		}
		if(this->_velocity.x < 0)
		{
			this->setScaleX(-1.0);
		}
	}

}

void ActionSprite::runWithDirection(Point direction)
{
	if (this->_actionState == kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(this->_runAction);
		this->_actionState = kActionStateRun;
	}

	if (this->_actionState == kActionStateRun)
	{
		this->_velocity = Point(direction.x * this->_walkSpeed * 1.5f, direction.y * this->_walkSpeed * 1.2f);
		if (this->_velocity.x > 0)
		{
			this->setScaleX(1.0);
		}
		if (this->_velocity.x < 0)
		{
			this->setScaleX(-1.0);
		}
	}

}

void ActionSprite::hurtWithDamage(int damage)
{
	if(this->_actionState != kActionStateDead)
	{
		this->stopAllActions();
		this->_actionState = kActionStateHurt;
		this->runAction(_hurtAction);

		this->_hp -= damage;

		if(_hp <= 0)
		{
			this->dead();
		}

	}

}

void ActionSprite::dead()
{
	this->stopAllActions();
	this->runAction(_deadAction);
	this->_hp = 0;
	this->_actionState = kActionStateDead;
}

void ActionSprite::crouch()
{
	this->stopAllActions();
	this->runAction(_crouchAction);
	this->_mpRecover *= 5.0f;
	this->_actionState = kActionStateCrouch;

	auto prt = ParticleSystemQuad::create("partical/Phoenix.plist");
	prt->setTag(0);
	prt->setPosition(Vec2(42.0f, 24.0f));
	this->addChild(prt, -1);
}

void ActionSprite::updateDesiredPosition(float dt)
{
	if ((this->_actionState == kActionStateWalk) || (this->_actionState == kActionStateRun))
	{
		this->_desiredPosition = this->getPosition() + this->_velocity * dt;
	}

}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(cocos2d::Point origin, cocos2d::Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;

	boundingBox.actual.origin = this->getPosition() + Point(boundingBox.original.origin.x, boundingBox.original.origin.y);
	boundingBox.actual.size = size;

	return boundingBox;
}

void ActionSprite::transformBoxes()
{
	this->_hitBox.actual.origin = this->getPosition() + Point(_hitBox.original.origin.x, _hitBox.original.origin.y);
	_attackBox.actual.origin = this->getPosition() +
		Point(_attackBox.original.origin.x +
		(this->getScaleX() == -1 ? (-_attackBox.original.size.width - _hitBox.original.size.width) : 0),
		_attackBox.original.origin.y);
}

void ActionSprite::setPosition(Point position)
{
	Sprite::setPosition(position);
	this->transformBoxes();
}