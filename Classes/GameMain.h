#ifndef __GameMain_H__
#define __GameMain_H__
#include "Hero.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <time.h>
USING_NS_CC;
class GameMain : public LayerColor
{
public:
	CREATE_FUNC(GameMain);
	void addBackground();
	void addBlock();
	void addHero();
	void addTouchListener();
	void addHazard();
	bool init();
	void onEnter();
	void onEnterTransitionDidFinish();
	void onExit();

	static Scene* scene();
	Scene* getScene()
	{
		return (Scene*)getParent();
	}
	long getCurrentTime()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	void update(float dt);
	Sprite* m_pSpriteCurSpr;
	Sprite* m_pSpriteNextSpr;
	Hero* m_pSpriteHero;
	Vector<Sprite*> m_blockVector;
	long m_lbeginTime;
	long m_lendTime;
	bool flag = false;
	bool m_bMoving = false;
	Size winSize = Director::getInstance()->getWinSize();
};

#endif