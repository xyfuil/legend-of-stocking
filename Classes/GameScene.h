#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "ContralLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

	GameLayer *_gameLayer;
	ContralLayer *_contralLayer;
};

#endif // _GAME_SCENE_H_
