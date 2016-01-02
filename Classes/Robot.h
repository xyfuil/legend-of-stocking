#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "ActionSprite.h"

class Robot : public ActionSprite
{
public:
	Robot(void);
	~Robot(void);

	virtual bool init();
	CREATE_FUNC(Robot);

	void end();

	float _nextDecisionTime;	// �����˵ľ���ʱ��
};

#endif // _ROBOT_H_