#include "GameLayer.h"
#include "GameScene.h"
#include "Explode.h"
#include "WelScene.h"

USING_NS_CC;

GameLayer::GameLayer(void)
{
	this->_hero = NULL;
	this->_tilemp = NULL;
	_count = 0;
	_cy = false;
}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
	if(!Layer::init())
		return false;

	this->initTiledmap();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/stocking.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/cyclone.plist");

	this->initHero();

	addEvents();

	this->scheduleUpdate();

	//this->initRobots();

	//AudioEngine::play2d("music/game.mp3", true, 0.5f);
	criadx2le::playCueById(1);

	Vector<SpriteFrame *> cycloneFrames;
	for (int i = 0; i < 10; i++){
		auto frame = SpriteFrameCache::getInstance()->spriteFrameByName(String::createWithFormat("freeze_ww_%02d.png", i + 1)->getCString());
		cycloneFrames.pushBack(frame);
	}
	_cycloneAnimation = Animation::createWithSpriteFrames(cycloneFrames, 0.05f);
	_cycloneAction = Sequence::create(Spawn::create(Animate::create(_cycloneAnimation), MoveBy::create(0.5f, Vec2(_hero->getScaleX() * 240.0f, 0.0f)), NULL), CallFunc::create(CC_CALLBACK_0(GameLayer::cyEnd, this)), RemoveSelf::create(), NULL);
	_cycloneAction->retain();

	return true;
}

void GameLayer::initTiledmap()
{
	//std::string file = "image/ditu.tmx";
    //auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
    //_tilemp = cocos2d::TMXTiledMap::createWithXML(str->getCString(),"");
	_tilemp = cocos2d::TMXTiledMap::create("image/ditu.tmx");
	this->addChild(_tilemp);

	auto prt = ParticleSystemQuad::create("partical/mahoujin.plist");
	prt->setTag(5);
	prt->setPosition(Vec2(880.0f, 100.0f));
	prt->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->addChild(prt, prt->getPositionY());
}

void GameLayer::initHero()
{
	//this->_hero = Hero::create();
	this->_hero = Hero::create();
	this->addChild(this->_hero);

	this->_hero->setPosition(Point(this->_hero->_centerToSides, 80));
	this->_hero->_desiredPosition = this->_hero->getPosition();

	this->_hero->idle();
}

void GameLayer::initRobots()
{
	for (int i = 0; i < 10; i++)
	{
		auto robot = Robot::create();
		this->addChild(robot);
		this->_robots.pushBack(robot);

		int minX = 240 + robot->_centerToSides;
		int maxX = this->_tilemp->getMapSize().width * this->_tilemp->getTileSize().width - robot->_centerToSides;
		int minY = robot->_centerToBottom;
		int maxY = 3 * this->_tilemp->getTileSize().height + robot->_centerToBottom;
		robot->setScaleX(-1.0);
		robot->setPosition(Point((rand() % (maxX - minX + 1)) + minX, (rand() % (maxY - minY + 1)) + minY));
		robot->_desiredPosition = robot->getPosition();
		robot->idle();
	}
}

void GameLayer::addEnemy()
{
	if ((CCRANDOM_0_1() < 0.01f) && (_robots.size() < 6) && (_count <= 10))
	{
		_count++;
		auto robot = Robot::create();
		this->addChild(robot);
		this->_robots.pushBack(robot);

		int minX = 880.0f - 60.0f;
		int maxX = 880.0f + 60.0f;
		int minY = 100.0f - 30.0f;
		int maxY = 100.0f + 30.0f;
		robot->setScaleX(-1.0);
		robot->setPosition(Point((rand() % (maxX - minX + 1)) + minX, (rand() % (maxY - minY + 1)) + minY));
		robot->_desiredPosition = robot->getPosition();
		robot->idle();

		if (_count > 10)
		{
			this->removeChildByTag(5);
		}
	}

	if ((_robots.size() == 0) && (_count > 10))
	{
		if (_hero->getBoundingBox().containsPoint(Vec2(880.0f, 100.0f)))
		{
			criadx2le::stopAll();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f,WelScene::create()));
		}
	}
}

void GameLayer::attack()
{
	if (this->_hero->_actionState != kActionStateDead)
	{
		Robot *robot = NULL;

		this->_hero->attack();

		for (int i = 0; i < this->_robots.size(); i++)
		{
			robot = this->_robots.at(i);
			if (fabsf(_hero->getPositionY() - robot->getPositionY()) < 10 && robot->_actionState != kActionStateDead)
			{
				if (_hero->_attackBox.actual.intersectsRect(robot->_hitBox.actual))
				{
					int dmg = int(CCRANDOM_0_1() * _hero->_damage / 2.0f + _hero->_damage / 2.0f) + 1;
					robot->hurtWithDamage(dmg);
					//hurt(robot->getPosition(), dmg);
				}
			}

		}
	}
}

void GameLayer::magic()
{
	if (this->_hero->magic())
	{
		auto bullet = Bullet::create();
		this->_bullets.pushBack(bullet);
		bullet->createShot(_hero->getPosition() + Vec2(_hero->getScaleX() * 36.0f, -5.0f), _hero->getScaleX() * 5.0f, 0.0f, 0.0f, 0.0f);
		this->addChild(bullet, 200 - bullet->getPositionY());
	}
}

void GameLayer::crouch()
{
	this->_hero->crouch();
}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	/*
	float distanceSQ = ccpDistanceSQ(touches[0]->getLocation(), Point(64, 64));
	if(distanceSQ > 64 * 64)
	{
		Robot *robot = NULL;

		this->_hero->attack();

		for (int i = 0; i < this->_robots.size(); i++)
		{
			robot = this->_robots.at(i);
			if(fabsf(_hero->getPositionY() - robot->getPositionY()) < 10 && robot->_actionState != kActionStateDead)
			{
				if (_hero->_attackBox.actual.intersectsRect(robot->_hitBox.actual))
				{
					robot->hurtWithDamage(_hero->_damage);
				}
			}

		}
	}
	*/
}

void GameLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	//log("TouchedMoved...");
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
}

void GameLayer::addEvents()
{
	//单点触屏事件对象 绑定回调函数
	auto eventTouch = EventListenerTouchAllAtOnce::create();
	eventTouch->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
	eventTouch->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
	eventTouch->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);

	//注册事件对象
	auto dispather = Director::getInstance()->getEventDispatcher();
	dispather->addEventListenerWithSceneGraphPriority(eventTouch, this);
}

void GameLayer::didChangeDirectorTo(ContralLayer *cot, Point direction, int isRun)
{
	if (isRun == 0)
	{
		this->_hero->walkWithDirection(direction);
	}
	else
	{
		this->_hero->runWithDirection(direction);
	}
}

void GameLayer::isHoldingDirector(ContralLayer *cot, Point direction)
{
	this->_hero->walkWithDirection(direction);
}

void GameLayer::simpleDPadTouchEnded(ContralLayer *cot)
{
	if ((this->_hero->_actionState == kActionStateWalk) || (this->_hero->_actionState == kActionStateRun) || (this->_hero->_actionState == kActionStateCrouch))
	{
		if (this->_hero->_actionState == kActionStateCrouch)
		{
			this->_hero->_mpRecover = 0.02f;
			this->_hero->removeChildByTag(0);
		}
		this->_hero->idle();
	}

}

void GameLayer::update(float dt)
{
	addEnemy();
	this->_hero->updateDesiredPosition(dt);

	// 设置英雄位置，保证在地图内部
	float posx = MIN(this->_tilemp->getMapSize().width * this->_tilemp->getTileSize().width -
		this->_hero->_centerToSides, MAX(this->_hero->_centerToSides, this->_hero->_desiredPosition.x));
	float posy = MIN(4 * this->_tilemp->getTileSize().height + this->_hero->_centerToBottom,
		MAX(this->_hero->_centerToBottom, this->_hero->_desiredPosition.y));

	this->_hero->setPosition(Point(posx, posy));

	// 设置地图移动，用移动图层来实现
	int x = MAX(_hero->getPositionX(), 400.0f);
	int y = MAX(_hero->getPositionX(), 160.0f);
	x = MIN(x, (this->_tilemp->getMapSize().width * this->_tilemp->getTileSize().width) - 400.0f);
	y = MIN(y, (this->_tilemp->getMapSize().height * this->_tilemp->getTileSize().height) - 160.0f);

	auto actualPosition = Vec2(x, y);
	auto centerOfView = Vec2(400.0f, 200.0f);
	auto viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);

	for(auto each = _robots.size() - 1; each >= 0; each--)
	{
		this->reorderChild(_robots.at(each), 200 - _robots.at(each)->getPositionY());
	}
	this->_hero->setZOrder(200 - _hero->getPositionY());

	((GameScene *)this->getParent())->_contralLayer->_heroMP->setScaleX(_hero->_mp / 120.0f);

	updateBullets(dt);

	updateRobots(dt);
}

static float GetCurTime()
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec) / 1000;
	return float(millisecs);
}

void GameLayer::updateBullets(float dt)
{
	Bullet *bullet = NULL;
	Robot *robot = NULL;

	for (int i = this->_bullets.size() - 1; i >= 0; i--)
	{
		bullet = this->_bullets.at(i);

		if ((bullet->getPositionX() > 800.0f - this->getPositionX() + bullet->getContentSize().width / 2) || (bullet->getPositionX() < -this->getPositionX() - bullet->getContentSize().width / 2))
		{
			_bullets.erase(i);
			bullet->removeFromParent();
			break;
		}


		for (size_t j = 0; j < _robots.size(); j++)
		{
			robot = this->_robots.at(j);
			if (robot->_actionState != kActionStateDead && (abs(bullet->getZOrder() - robot->getZOrder()) < 20))
			{
				if (bullet->getBoundingBox().containsPoint(robot->getPosition()))
				{
					bullet->setZOrder(robot->getZOrder() + 1);
					int dmg = int(CCRANDOM_0_1() * _hero->_mDamage / 2.0f + _hero->_mDamage / 2.0f) + 1;
					robot->hurtWithDamage(int(dmg));
					if (dmg > 18)
					{
						auto exp = Explode::create();
						exp->setPosition(robot->getPosition() + Vec2(0.0f, -robot->_centerToBottom));
						this->addChild(exp, robot->getZOrder() + 1);
					}

					//hurt(robot->getPosition(), dmg);

					_bullets.erase(i);
					bullet->broke();
					break;
				}
			}
		}
	}

	if (_cy)
	{
		for (size_t i = 0; i < _robots.size(); i++)
		{
			robot = _robots.at(i);
			if (_sp->getBoundingBox().containsPoint(robot->getPosition()) && (abs(robot->getZOrder() - _sp->getZOrder()) < 20))
			{
				if (robot->getPositionX() > _hero->getPositionX())
				{
					robot->setPositionX(robot->getPositionX() + 3.0f);
				}
				else
				{
					robot->setPositionX(robot->getPositionX() - 3.0f);
				}
			}
		}
	}
}

void GameLayer::updateRobots(float dt)
{
	int alive = 0;	// 当前存活机器人的数量
	int distanceSQ;
	int randomChoice = 0;

	for (size_t i = 0; i < this->_robots.size(); i++)
	{
		auto robot = this->_robots.at(i);
		if (robot->_actionState == kActionStateDead)
		{
			_robots.erase(i);
		}
	}

	for (int i = 0; i < this->_robots.size(); i++)
	{
		auto robot = this->_robots.at(i);
		if (robot->_actionState != kActionStateDead)
		{
			alive++;
			if(_hero->_actionState == kActionStateDead)
			{
				robot->idle();
				continue;
			}
			if (::GetCurTime() > robot->_nextDecisionTime)
			{
				distanceSQ = ccpDistanceSQ(robot->getPosition(), this->_hero->getPosition());
				if (distanceSQ <= 50 * 50)
				{
					robot->_nextDecisionTime = ::GetCurTime() + CCRANDOM_0_1() * 400 + 100;
					randomChoice = int(CCRANDOM_0_1() * 1000) % 3;

					if (randomChoice < 2)
					{
						if (this->_hero->getPositionX() > robot->getPositionX())
						{
							robot->setScaleX(1.0f);
						}
						else
						{
							robot->setScaleX(-1.0f);
						}

						robot->_nextDecisionTime = ::GetCurTime() + CCRANDOM_0_1() * 800 + 200;
						robot->attack();

						// 检测机器人是否攻击到英雄
						if(fabsf(_hero->getPositionY() - robot->getPositionY()) < 10 && 
							_hero->_hitBox.actual.intersectsRect(robot->_attackBox.actual))
						{
							_hero->hurtWithDamage(robot->_damage);
							((GameScene *)this->getParent())->_contralLayer->_heroHP->setScaleX(_hero->_hp / 120.0f);
						}
					}
					else
					{
						robot->idle();
					}
				}
				else if (distanceSQ <= 480 * 480)
				{
					robot->_nextDecisionTime = ::GetCurTime() + CCRANDOM_0_1() * 400 + 100;
					randomChoice = int(CCRANDOM_0_1() * 1000) % 1;

					if (randomChoice == 0)
					{
						Point moveDirection = ccpNormalize(ccpSub(_hero->getPosition(), robot->getPosition())) * 8;
						robot->walkWithDirection(moveDirection);
						robot->updateDesiredPosition(dt);
						float posx = MIN(this->_tilemp->getMapSize().width * this->_tilemp->getTileSize().width -
							robot->_centerToSides, MAX(robot->_centerToSides, robot->_desiredPosition.x));
						float posy = MIN(3 * this->_tilemp->getTileSize().height + robot->_centerToBottom,
							MAX(robot->_centerToBottom, robot->_desiredPosition.y));
						robot->setPosition(Point(posx, posy));
					}
					else
					{
						robot->idle();
					}
				}
			}
		}
	}
}

void GameLayer::hurt(Vec2 pos, int dmg)
{
	char str[3];
	sprintf(str, "%d", dmg);
	auto hurt = Label::createWithTTF(str, "font.ttf", dmg + 4);
	hurt->setPosition(pos);
	this->addChild(hurt, 200);

	if (dmg > 18)
	{
		hurt->enableOutline(Color4B(255, 0, 0, 255), 1);
	}
	else
	{
		hurt->enableOutline(Color4B(255, 128, 0, 255), 1);
	}

	auto action = Sequence::create(MoveBy::create(0.5f, Vec2(0.0f, 6.0f)), RemoveSelf::create(), NULL);
	hurt->runAction(action);
}

void GameLayer::cyclone()
{
	_cy = true;
	_sp = Sprite::createWithSpriteFrameName("freeze_ww_01.png");
	_sp->setPosition(_hero->getPosition());
	auto action = Sequence::create(Spawn::create(Animate::create(_cycloneAnimation), MoveBy::create(0.5f, Vec2(_hero->getScaleX() * 240.0f, 0.0f)), NULL), CallFunc::create(CC_CALLBACK_0(GameLayer::cyEnd, this)), RemoveSelf::create(), NULL);
	this->addChild(_sp, _hero->getZOrder());

	_sp->runAction(action);
}

void GameLayer::cyEnd()
{
	_cy = false;
}
