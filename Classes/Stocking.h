#ifndef _STOCKING_H_
#define _STOCKING_H_

#include "ActionSprite.h"

class Stocking : public ActionSprite
{
public:
	Stocking(void);
	~Stocking(void);

	CREATE_FUNC(Stocking);

	virtual bool init();
};

#endif // _STOCKING_H_
