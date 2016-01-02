#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void)
{
	this->_gameLayer = NULL;
	this->_contralLayer = NULL;
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	if(!Scene::init())
		return false;

	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer);

	this->_contralLayer = ContralLayer::create();
	this->addChild(_contralLayer);

	return true;
}
