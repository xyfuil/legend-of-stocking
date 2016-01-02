#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"

typedef enum _ActionState{
	kActionStateNone = 0,
	kActionStateIdle,	// ����״̬
	kActionStateAttack,	// ����״̬
	kActionStateMagic,	// ħ������
	kActionStateWalk,	// ����״̬
	kActionStateRun,	// ����״̬
	kActionStateHurt,	// ����״̬
	kActionStateDead,	// ����״̬
	kActionStateCrouch	// �¶׶���
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

	void idle();	//���ж�������
	void attack();	//������������
	bool magic();
	void hurtWithDamage(int damage);	//���˶���������damage��ʾ�˺�ֵ
	void dead();	//������������
	void walkWithDirection(cocos2d::Point direction);	//���߶���������direction��ʾ���߷���
	void runWithDirection(cocos2d::Point direction);
	void crouch();

	void updateDesiredPosition(float dt);

	BoundingBox createBoundingBoxWithOrigin(cocos2d::Point origin, cocos2d::Size size);
	void transformBoxes();

	virtual void setPosition(cocos2d::Point position);

	//����
	cocos2d::Action *_idleAction;
	cocos2d::Action *_attackAction;
	cocos2d::Action *_magicAction;
	cocos2d::Action *_walkAction;
	cocos2d::Action *_runAction;
	cocos2d::Action *_hurtAction;
	cocos2d::Action *_deadAction;
	cocos2d::Action *_crouchAction;

	ActionState _actionState;	//��ǰ����״̬
	float _walkSpeed;	//��������
	//float _hitPoints;	//����ֵ
	int _hp;
	float _mp;
	float _mpRecover;
	float _damage;	//�˺�ֵ
	float _mDamage;
	cocos2d::Point _velocity;	//�ƶ��ٶ�
	cocos2d::Point _desiredPosition;	//Ҫ����λ��
	float _centerToSides;	//�������ĵ����߾���
	float _centerToBottom;	//�������ĵ��ײ��ľ���

	BoundingBox _hitBox; // ���������
	BoundingBox _attackBox; // �������

	void update(float dt);
};

#endif // _ACTION_SPRITE_H_
