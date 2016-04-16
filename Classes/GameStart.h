#ifndef __GameStart_H__
#define __GameStart_H__
#include "cocos2d.h"
USING_NS_CC;
class GameStart : public LayerColor
{
public:
	CREATE_FUNC(GameStart);
	bool init();
	static Scene* scene();
};
#endif
