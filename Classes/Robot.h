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

	float _nextDecisionTime;	// 机器人的抉择时间
};

#endif // _ROBOT_H_