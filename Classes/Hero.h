#ifndef _HERO_H_
#define _HERO_H_

#include "ActionSprite.h"

class Hero : public ActionSprite
{
public:
	Hero(void);
	~Hero(void);

	CREATE_FUNC(Hero);

	virtual bool init();

	void end();
};

#endif // _HERO_H_
