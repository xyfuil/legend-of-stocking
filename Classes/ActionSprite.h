#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"

typedef enum _ActionState{
	kActionStateNone = 0,
	kActionStateIdle,	// 空闲状态
	kActionStateAttack,	// 攻击状态
	kActionStateMagic,	// 魔法攻击
	kActionStateWalk,	// 行走状态
	kActionStateRun,	// 奔跑状态
	kActionStateHurt,	// 受伤状态
	kActionStateDead,	// 死亡状态
	kActionStateCrouch	// 下蹲动作
}ActionState;

typedef struct
{
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
}BoundingBox;


class ActionSprite : public cocos2d::Sprite
{
public:
	ActionSprite(void);
	~ActionSprite(void);

	void idle();	//空闲动作方法
	void attack();	//攻击动作方法
	bool magic();
	void hurtWithDamage(int damage);	//受伤动作方法，damage表示伤害值
	void dead();	//死亡动作方法
	void walkWithDirection(cocos2d::Point direction);	//行走动作方法，direction表示行走方向
	void runWithDirection(cocos2d::Point direction);
	void crouch();

	void updateDesiredPosition(float dt);

	BoundingBox createBoundingBoxWithOrigin(cocos2d::Point origin, cocos2d::Size size);
	void transformBoxes();

	virtual void setPosition(cocos2d::Point position);

	//动作
	cocos2d::Action *_idleAction;
	cocos2d::Action *_attackAction;
	cocos2d::Action *_magicAction;
	cocos2d::Action *_walkAction;
	cocos2d::Action *_runAction;
	cocos2d::Action *_hurtAction;
	cocos2d::Action *_deadAction;
	cocos2d::Action *_crouchAction;

	ActionState _actionState;	//当前动作状态
	float _walkSpeed;	//行走速率
	//float _hitPoints;	//生命值
	int _hp;
	float _mp;
	float _mpRecover;
	float _damage;	//伤害值
	float _mDamage;
	cocos2d::Point _velocity;	//移动速度
	cocos2d::Point _desiredPosition;	//要到的位置
	float _centerToSides;	//精灵中心到两边距离
	float _centerToBottom;	//精灵中心到底部的距离

	BoundingBox _hitBox; // 精灵的身体
	BoundingBox _attackBox; // 精灵的手

	void update(float dt);
};

#endif // _ACTION_SPRITE_H_
