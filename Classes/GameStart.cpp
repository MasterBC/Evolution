#include "GameStart.h"
#include "GameMain.h"
//#include "Views.h"
bool GameStart::init()
{
	LayerColor::initWithColor(Color4B(239, 216, 86, 255));

	MenuItemImage* item = MenuItemImage::create("play-normal.png", "play-selected.png", [](Ref* ref){
		Scene* reScene = CCTransitionJumpZoom::create(2.0f, GameMain::scene());
		Director::getInstance()->replaceScene(reScene);
		//Director::getInstance()->replaceScene(GameMain::scene());
	});
	item->setPosition(Vec2(0,0));
	Menu* menu = Menu::create(item, NULL);
	log("%f,%f", menu->getPositionX(), menu->getPositionY());
	log("%f,%f", menu->getAnchorPoint().x, menu->getAnchorPoint().y);
	addChild(menu);

	//auto view = Views::getInstance();
	//view->setPosition(0, 0);
	//this->addChild(view);

	return true;
}
Scene* GameStart::scene()
{
	Scene* scene = Scene::create();
	Layer* layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}