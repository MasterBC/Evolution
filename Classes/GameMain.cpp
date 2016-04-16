#include "GameMain.h"
 
bool GameMain::init()
{
	
	srand((unsigned)time(NULL));
	LayerColor::init();

	return true;
}
void GameMain::onEnter()
{
	LayerColor::onEnter();
}
void GameMain::onEnterTransitionDidFinish()
{
	LayerColor::onEnterTransitionDidFinish();

	scheduleUpdate();
	addBackground();
	addBlock();
	addHero();
	addTouchListener();

	//addHazard();
}
void GameMain::addBackground()
{
	auto sprite = Sprite::create("background.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	sprite->setScaleX(winSize.width / sprite->getContentSize().width);
	sprite->setScaleY(winSize.height / sprite->getContentSize().height);
	addChild(sprite);
}
void GameMain::addHero()
{
	Hero* hero = Hero::create();
	hero->initWithFile("01.png");
	m_pSpriteHero = hero;
	hero->setPosition(winSize.width / 2 + 50, winSize.height / 2);
	addChild(hero);
	//schedule([&](float dt){
	//	if (abs(m_pSpriteHero->getPositionX() - winSize.width / 2) < 1.0f)
	//	{
	//		if (m_pSpriteHero->getPositionX() - m_pSpriteHero->getContentSize().width / 2 > winSize.width / 2)
	//		{
	//			//m_pSpriteHero->getPhysicsBody()->setDynamic(true);
	//			//m_pSpriteHero->getPhysicsBody()->resetForces();
	//			getScene()->getPhysicsWorld()->setGravity(Vec2(-98.0f, 0));
	//			m_pSpriteHero->getPhysicsBody()->setVelocity(Vec2(-1000, 0));
	//			//m_pSpriteHero->getPhysicsBody()->applyImpulse(Vec2(-1000, 0));
	//			//m_pSpriteHero->setPositionX(winSize.width / 2 - 18);
	//		}
	//		else
	//		{
	//			//m_pSpriteHero->getPhysicsBody()->setDynamic(true);
	//			//m_pSpriteHero->getPhysicsBody()->resetForces();
	//			getScene()->getPhysicsWorld()->setGravity(Vec2(98.0f, 0));
	//			m_pSpriteHero->getPhysicsBody()->setVelocity(Vec2(1000,0));
	//			//m_pSpriteHero->getPhysicsBody()->applyImpulse(Vec2(-1000, 0));
	//			//m_pSpriteHero->setPositionX(winSize.width / 2 - 18);
	//		}
	//	}
	//	log("%f", m_pSpriteHero->getPositionX() - m_pSpriteHero->getContentSize().width / 2 - winSize.width / 2);
	//}, "check Hero");

}
void GameMain::addBlock()
{
	
	m_pSpriteCurSpr = NULL;
	m_pSpriteNextSpr = NULL;
	schedule([&](float dt){

		if (m_pSpriteCurSpr == NULL)//创建第一个block
		{
			//srand((float)time(0));
			float dy = (float)((rand() % (960 - 800)) +800);////产生480到960之间的随机数
			float dist = (float)((rand() % (48 - 45)) + 45);//产生40到45之间的随机数
			PhysicsBody* body = PhysicsBody::createBox(Size(16, dy), PhysicsMaterial(1.0f, 0.0f, 0.0f));
			body->setGravityEnable(false);
			Sprite* spr1 = Sprite::create("block.png");
			spr1->setScaleX(40 / spr1->getContentSize().width);
			spr1->setScaleY(dy / spr1->getContentSize().height);
			//spr1->setTextureRect(Rect(0, 0, 16, dy));
			//spr1->setContentSize(Size(16, dy));

			log("winSize  %f,%f", winSize.width, winSize.height);
			log("spr1 %f,%f", spr1->getContentSize().width, spr1->getContentSize().height);

			addChild(spr1);
			m_pSpriteCurSpr = spr1;
			spr1->setPosition(winSize.width / 2, 0);
			spr1->setAnchorPoint(Vec2(0.5, 0));

			spr1->setPhysicsBody(body);
			//body->setVelocity(Vec2(0, -100));//速度
			body->setRotationEnable(false);

			m_blockVector.pushBack(spr1);

		}
		//如果当前block的最高处低于窗体的最高处则创建一个block
		else if (abs(m_pSpriteCurSpr->getPositionY() + m_pSpriteCurSpr->getContentSize().height - winSize.height) < 5.0f)
			//else if (abs((m_pSpriteCurSpr->getPositionY()) + winSize.height - m_pSpriteCurSpr->getContentSize().height) < 2.0f)
		{
			//srand((float)time(0));
			float dy = (float)((rand() % (960 - 800)) + 800);////产生480到960之间的随机数
			float dist = (float)((rand() % (48 - 45)) + 45);//产生40到45之间的随机数
			PhysicsBody* body = PhysicsBody::createBox(Size(16, dy), PhysicsMaterial(1.0f, 0.0f, 0.0f));
			body->setGravityEnable(false);
			Sprite* spr1 = Sprite::create("block.png");
			spr1->setScaleX(40 / spr1->getContentSize().width);
			spr1->setScaleY(dy / spr1->getContentSize().height);
			//spr1->setContentSize(Size(16, dy));
			//spr1->setTextureRect(Rect(0, 0, 16, dy));
			addChild(spr1);
			m_pSpriteNextSpr = spr1;

			log("winSize  %f,%f", winSize.width, winSize.height);
			log("spr1 %f,%f", spr1->getContentSize().width, spr1->getContentSize().height);

			spr1->setPosition(winSize.width / 2, m_pSpriteCurSpr->getPositionY() + m_pSpriteCurSpr->getContentSize().height + dist);
			spr1->setAnchorPoint(Vec2(0.5, 0));

			spr1->setPhysicsBody(body);


			//body->setVelocity(Vec2(0, -100));//速度
			body->setRotationEnable(false);//设置旋转为false

			m_blockVector.pushBack(spr1);
		}
		if (m_pSpriteCurSpr->getPositionY() + m_pSpriteCurSpr->getContentSize().height < 0)
		{

			m_blockVector.eraseObject(m_pSpriteCurSpr);
			m_pSpriteCurSpr->removeFromParentAndCleanup(true);
			//removeChild(m_pSpriteCurSpr, true);
			m_pSpriteCurSpr = m_pSpriteNextSpr;
		}

	}, "CreateBlock");
}
void GameMain::addHazard()
{
	auto triangle = Sprite::create("a.png");
	triangle->setPosition(winSize.width / 2, winSize.height / 2);
	Point points[3] = { Point(-84.00000, -61.50000), Point(-5.00000, 73.50000), Point(72.00000, -60.50000) };
	auto body = PhysicsBody::createPolygon(points, 3);
	triangle->setPhysicsBody(body);
	addChild(triangle);
}
void GameMain::addTouchListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch*, Event* event)->bool{
		m_lbeginTime = getCurrentTime();
		m_bMoving = true;
		return true;
	};
	listener->onTouchEnded = [&](Touch* touch,Event* event){

		m_bMoving = false;
		m_lendTime = getCurrentTime();
		long time = m_lendTime - m_lbeginTime;

		if (!flag)
		{
			flag = true;
			if (time > 0 && time < 110)
			{
				if (m_pSpriteHero->getPositionX()>winSize.width / 2)
				{
					auto actionBegin = MoveBy::create(0.3f, Point(60, 0));
					auto actionEnd = actionBegin->reverse();
					m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&]{flag = false; }), NULL));
				}
				else if (m_pSpriteHero->getPositionX()<winSize.width / 2)
				{
					auto actionBegin = MoveBy::create(0.3f, Point(-60, 0));
					auto actionEnd = actionBegin->reverse();
					m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&]{flag = false; }), NULL));
				}
			}
			else if (time >= 110)
			{
				if (m_pSpriteHero->getPositionX()>winSize.width / 2)
				{
					auto actionBegin = MoveBy::create(0.3f, Point(110, 0));
					auto actionEnd = actionBegin->reverse();
					m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&]{flag = false; }), NULL));
				}
				else if (m_pSpriteHero->getPositionX() < winSize.width / 2)
				{
					auto actionBegin = MoveBy::create(0.3f, Point(-110, 0));
					auto actionEnd = actionBegin->reverse();
					m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&]{flag = false; }), NULL));
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameMain::update(float dt)
{
	if (m_pSpriteCurSpr != NULL)
	{
		m_pSpriteCurSpr->setPosition(winSize.width / 2, m_pSpriteCurSpr->getPositionY() - 3);
	}
	if (m_pSpriteNextSpr != NULL)
	{
		m_pSpriteNextSpr->setPosition(winSize.width / 2, m_pSpriteNextSpr->getPositionY() - 3);
	}
	if (m_pSpriteHero != NULL && m_pSpriteCurSpr != NULL && m_pSpriteNextSpr != NULL)
	{

		if (((m_pSpriteHero->getPositionY() - m_pSpriteHero->getContentSize().height / 2) > (m_pSpriteCurSpr->getPositionY() + m_pSpriteCurSpr->getContentSize().height)) && ((m_pSpriteHero->getPositionY() + m_pSpriteHero->getContentSize().height / 2) < m_pSpriteNextSpr->getPositionY()))
		{
			if (!flag)
			{
				flag = true;
				//if (m_pSpriteHero->getPositionX() == (winSize.width / 2 + 18))
				if (m_pSpriteHero->getPositionX() > (winSize.width / 2))
				{
					auto action = MoveTo::create(0.2f, Point(winSize.width / 2 - 18, winSize.height / 2));
					m_pSpriteHero->runAction(Sequence::create(action, CallFunc::create([&]() {flag = false; }), NULL));
					//m_pSpriteHero->setPositionX(winSize.width / 2 - 18);
					//Sleep(20);
				}
				//else if (m_pSpriteHero->getPositionX() == (winSize.width / 2 - 18))
				else if (m_pSpriteHero->getPositionX() < (winSize.width / 2))
				{
					auto action = MoveTo::create(0.2f, Point(winSize.width / 2 + 18, winSize.height / 2));
					m_pSpriteHero->runAction(Sequence::create(action, CallFunc::create([&]() {flag = false; }), NULL));
					//m_pSpriteHero->runAction(MoveTo::create(0.2f, Point(winSize.width / 2 + 18, winSize.height / 2)));
					//m_pSpriteHero->setPositionX(winSize.width / 2 + 18);
					//Sleep(20);
				}
			}
		}
		if (m_bMoving && !flag && m_pSpriteHero != NULL)
		{
			flag = true;
			if (m_pSpriteHero->getPositionX() > winSize.width / 2)
			{
				auto actionBegin = MoveBy::create(0.3f, Point(110, 0));
				auto actionEnd = actionBegin->reverse();
				m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&] {flag = false; }), NULL));
			}
			else if (m_pSpriteHero->getPositionX() < winSize.width / 2)
			{
				auto actionBegin = MoveBy::create(0.3f, Point(-110, 0));
				auto actionEnd = actionBegin->reverse();
				m_pSpriteHero->runAction(Sequence::create(actionBegin, actionEnd, CallFunc::create([&] {flag = false; }), NULL));
			}
		}
	}
}
Scene* GameMain::scene()
{
	Scene* scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(-98.0f, 0));
	Layer* layer = GameMain::create();
	scene->addChild(layer);
	return scene;
}

void GameMain::onExit()
{
	Layer::onExit();

}

