#include "ContralLayer.h"
#include "GameScene.h"

USING_NS_CC;

ContralLayer::ContralLayer()
{
	_lock = false;
	for (size_t i = 0; i < 8; i++)
	{
		_button[i] = false;
	}
	_order = 0;
}


ContralLayer::~ContralLayer()
{
}

static inline long millisecondNow()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	log(now.tv_sec * 1000 + now.tv_usec / 1000);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool ContralLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_lastTime = millisecondNow();

	auto side = Sprite::createWithSpriteFrameName("s.png");
	side->setAnchorPoint(Vec2(0.0f, 0.0f));
	side->setPosition(Vec2(0.0f, 0.0f));
	side->setScaleX(20.0f);
	this->addChild(side);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			auto statu = Sprite::createWithSpriteFrameName("status.png");
			statu->setAnchorPoint(Vec2(0.0f, 0.0f));
			statu->setPosition(Vec2(200.0f * i, 480.0f - (j + 1) * 60.0f));
			this->addChild(statu);
		}
	}

	_hero = Sprite::createWithSpriteFrameName("stocking.png");
	_hero->setAnchorPoint(Vec2(0.0f, 0.0f));
	_hero->setPosition(Vec2(10.0f, 480.0f - 53.0f));
	this->addChild(_hero);

	_heroHP = Sprite::createWithSpriteFrameName("hp.png");
	_heroHP->setAnchorPoint(Vec2(0.0f, 0.0f));
	_heroHP->setPosition(Vec2(65.0f, 480.0f - 25.0f));
	this->addChild(_heroHP); 
	
	_heroMP = Sprite::createWithSpriteFrameName("mp.png");
	_heroMP->setAnchorPoint(Vec2(0.0f, 0.0f));
	_heroMP->setPosition(Vec2(65.0f, 480.0f - 45.0f));
	this->addChild(_heroMP);

	_right = Button::create();
	_right->addEvents("right.png", 1);
	_right->setPosition(Vec2(48.0f + 128.0f, 0.0f + 96.0f));
	this->addChild(_right);

	_left = Button::create();
	_left->addEvents("left.png", 3);
	_left->setPosition(Vec2(-48.0f + 128.0f, 0.0f + 96.0f));
	this->addChild(_left);

	_up = Button::create();
	_up->addEvents("up.png", 2);
	_up->setPosition(Vec2(0.0f + 128.0f, 48.0f + 96.0f));
	this->addChild(_up);

	_down = Button::create();
	_down->addEvents("down.png", 4);
	_down->setPosition(Vec2(0.0f + 128.0f, -48.0f + 96.0f));
	this->addChild(_down);

	auto A = Button::create();
	A->addEvents("A.png", 5);
	A->setPosition(Vec2(636.0f, 36.0f));
	this->addChild(A);

	auto B = Button::create();
	B->addEvents("B.png", 6);
	B->setPosition(Vec2(660.0f, 96.0f));
	this->addChild(B);

	auto C = Button::create();
	C->addEvents("C.png", 7);
	C->setPosition(Vec2(720.0f, 120.0f));
	this->addChild(C);

	this->schedule(schedule_selector(ContralLayer::getGame), 1.0f / 60.0f);

	return true;
}

void ContralLayer::getGame(float dt)
{
	if ((GameScene *)this->getParent() == NULL)
	{
		return;
	}
	else
	{
		this->unschedule(schedule_selector(ContralLayer::getGame));
		this->_delegate = ((GameScene *)this->getParent())->_gameLayer;
		this->scheduleUpdate();
	}
}

void ContralLayer::update(float dt)
{
	if (millisecondNow() - _lastTime > 500)
	{
		_order = 0;
		//_lastTime = millisecondNow();
	}

	move();

	if (!_lock)
	{
		for (size_t i = 5; i < 8; i++)
		{
			if (_button[i])
			{
				switch (i)
				{
					case 5:
						((GameScene *)this->getParent())->_gameLayer->magic();
						break;
					case 6:
						if ((_order == 41) || (_order == 43))
						{
							((GameScene *)this->getParent())->_gameLayer->cyclone();
							_order = 0;
						}
						else
						{
							((GameScene *)this->getParent())->_gameLayer->attack();
						}
						break;
					case 7:
						((GameScene *)this->getParent())->_gameLayer->crouch();
						break;
					default:
						break;
				}
				this->_lock = true;
				break;
			}
		}
	}
}

void ContralLayer::move()
{
	if ((_button[1]) || (_button[3]))
	{
		if (_button[1])
		{
			if (_button[2])
			{
				_direction = Vec2(1.0f, 1.0f);
			}
			else if (_button[4])
			{
				_direction = Vec2(1.0f, -1.0f);
			}
			else
			{
				_direction = Vec2(1.0f, 0.0f);
			}
		}
		else
		{
			if (_button[2])
			{
				_direction = Vec2(-1.0f, 1.0f);
			}
			else if (_button[4])
			{
				_direction = Vec2(-1.0f, -1.0f);
			}
			else
			{
				_direction = Vec2(-1.0f, 0.0f);
			}
		}
		if (_button[1])
		{
			if (_right->_isDouble)
			{
				this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), _direction, 1);
			}
			else
			{
				this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), _direction, 0);
			}
		}
		else
		{
			if (_left->_isDouble)
			{
				this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), _direction, 1);
			}
			else
			{
				this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), _direction, 0);
			}
		}
	}
	else if ((_button[2]) || (_button[4]))
	{
		if (_button[2])
		{
			this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), Vec2(0.0f, 1.0f), 0);
		}
		else
		{
			this->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), Vec2(0.0f, -1.0f), 0);
		}
	}
	else
	{
		//log("stop");
	}
}

void ContralLayer::reflashTime()
{
	_lastTime = millisecondNow();
	//log("%d", _order);
}
