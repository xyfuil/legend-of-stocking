#include "Button.h"
#include "GameScene.h"
#include "ContralLayer.h"
#include "ActionSprite.h"

USING_NS_CC;

Button::Button()
{
	_isDouble = false;
}


Button::~Button()
{
}

bool Button::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

bool Button::isInSprite(Touch *touch)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 reallyPoint = this->getParent()->convertToNodeSpace(touchPoint);
	Rect rect = this->boundingBox();
	if (rect.containsPoint(reallyPoint)){
		return true;
	}

	return false;
}

//    获取当前时间 精确到毫秒数

static inline long millisecondNow()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	log(now.tv_sec * 1000 + now.tv_usec / 1000);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

// 判断是不是 双击
static inline bool isDoubleTouch()
{
	static long lastTouchTime = 0;
	long thisTouchTime = millisecondNow();
	if (abs(thisTouchTime - lastTouchTime)<250)
	{
		lastTouchTime = 0;
		return true;
	}
	else
	{
		lastTouchTime = millisecondNow();
		return false;
	}
}

void  Button::addEvents(char *s, int tag)
{
	switch (tag)
	{
	case 1:
		this->_direction = Point(1, 0);
		break;
	case 2:
		this->_direction = Point(0, 1);
		break;
	case 3:
		this->_direction = Point(-1, 0);
		break;
	case 4:
		this->_direction = Point(0, -1);
		break;
	default:
		this->_direction = Point(0, 0);
		break;
	}
	this->_tag = tag;
	initWithSpriteFrameName(s);
	this->getTexture()->setAliasTexParameters();
	this->setOpacity(192);
	auto eventTouch = EventListenerTouchOneByOne::create();
	eventTouch->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
	eventTouch->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
	eventTouch->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);

	auto dispather = Director::getInstance()->getEventDispatcher();
	dispather->addEventListenerWithSceneGraphPriority(eventTouch, this);
}

bool Button::onTouchBegan(Touch *touch, Event *event)
{
	if (this->isInSprite(touch))
	{
		this->setScale(0.9f);
		this->setOpacity(128);
		isInTouch = true;
		if (this->_tag < 5)
		{
			auto order = ((ContralLayer *)this->getParent())->_order;
			switch (_tag)
			{
			case 1:
				((ContralLayer *)this->getParent())->_order = order * 10 + 1;
				break;
			case 2:
				((ContralLayer *)this->getParent())->_order = order * 10 + 2;
				break;
			case 3:
				((ContralLayer *)this->getParent())->_order = order * 10 + 3;
				break;
			case 4:
				((ContralLayer *)this->getParent())->_order = order * 10 + 4;
				break;
			default:
				break;
			}
			((ContralLayer *)this->getParent())->reflashTime();
			if (isDoubleTouch()) {
				_isDouble = true;
				//log("double touch");
				//((ContralLayer *)this->getParent())->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), this->_direction, 1);
				this->touchBeginTime = millisecondNow();
			}
			else{
				//log("single touch");
				//((ContralLayer *)this->getParent())->_delegate->didChangeDirectorTo((ContralLayer *)this->getParent(), this->_direction, 0);
				//this->singleClickSprite();
				this->touchBeginTime = millisecondNow();
				//this->schedule(schedule_selector(TestSprite::checkLongPress), 2);
			}
		}
		else
		{
			/*
			switch (this->_tag)
			{
			case 4:
				((GameScene *)this->getParent()->getParent())->_gameLayer->magic();
				break;
			case 5:
				((GameScene *)this->getParent()->getParent())->_gameLayer->attack();
				break;
			case 6:
				((GameScene *)this->getParent()->getParent())->_gameLayer->crouch();
				break;
			default:
				break;
			}
			*/
		}
		((ContralLayer *)this->getParent())->_button[_tag] = true;

		return true;
	}
	
	return false; 
}

void Button::onTouchMoved(Touch *touch, Event *event)
{
	Vec2 deltaPoint = touch->getDelta();
	//log("x=%f,y=%f", deltaPoint.x, deltaPoint.y);
	if (fabs(deltaPoint.x)>1 || fabs(deltaPoint.y)>1){
		isInMove = true;
	}
}

void Button::onTouchEnded(Touch *touch, Event *event)
{
	isInTouch = false;
	isInMove = false;
	_isDouble = false;
	//afterLongPress = false;

	//     恢复精灵
	this->setScale(1.0f);
	//this->setPosition(orignalPoint);
	this->setOpacity(192);

	((ContralLayer *)this->getParent())->_delegate->simpleDPadTouchEnded((ContralLayer *)this->getParent());
	if (_tag >= 5)
	{
		((ContralLayer *)this->getParent())->_lock = false;
	}
	((ContralLayer *)this->getParent())->_button[_tag] = false;
}