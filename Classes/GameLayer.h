#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "Hero.h"
//#include "Stocking.h"
#include "Robot.h"
#include "Bullet.h"
#include "ContralLayer.h"
#include "AtomUtil.h"

class GameLayer : public cocos2d::Layer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();

	void initTiledmap();

	CREATE_FUNC(GameLayer);

	//Hero *_hero;
	Hero *_hero;
	cocos2d::Vector<Robot *> _robots;
	cocos2d::Vector<Bullet *> _bullets;
	cocos2d::TMXTiledMap *_tilemp;

	void initHero();
	void initRobots();
	void addEnemy();
	int _count;

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void addEvents();

	virtual void didChangeDirectorTo(ContralLayer *cot, cocos2d::Point direction, int isRun);
	virtual void isHoldingDirector(ContralLayer *cot, cocos2d::Point direction);
	virtual void simpleDPadTouchEnded(ContralLayer *cot);

	void update(float dt);
	void updateRobots(float dt);
	void updateBullets(float dt);

	void attack();
	void magic();
	void crouch();
	void hurt(cocos2d::Vec2 pos, int dmg);

	void cyclone();
	void cyEnd();
	cocos2d::Sprite *_sp;
	cocos2d::Animation *_cycloneAnimation;
	cocos2d::Action *_cycloneAction;
	bool _cy;
};

#endif // _GAME_LAYER_H_
