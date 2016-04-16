#include "Hero.h"

bool Hero::init()
{
	Sprite::init();
	//Sprite::initWithFile("c.jpg");
	this->setColor(Color3B(116, 234, 244));
	this->setTextureRect(Rect(0, 0, 20, 20));
	//this->setScaleX(getContentSize().width / getTextureRect().size.width);
	//this->setScaleY(getContentSize().height / getTextureRect().size.height);
	//auto pPhysicsBody = PhysicsBody::createBox(Size(20, 20), PhysicsMaterial(1.0f, 1.0f, 1.0f));
	//pPhysicsBody->setVelocity(Vec2(-400, 0));
	//pPhysicsBody->applyImpulse(Vec2(-400, 0));
	//pPhysicsBody->setDynamic(true);
	//pPhysicsBody->setRotationEnable(false);//ÉèÖÃÐý×ªÎªfalse
	//this->setPhysicsBody(pPhysicsBody);
	return true;
}