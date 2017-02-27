#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

   /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	* ISSUES:																							*
	*	> Cannot read certain files; seems to be files that were added to the Resources folder later on.*
	*	This includes the in-game background, and several buttons. Reused main menu buttons for Tutorial*
	*	scene to partially get around this. This also prevented the addition of spritesheet animations.	*
	*	> Error in LevelLoader.cpp prevents JSON loading from working; leaving it out.					*
	*	> Could not deploy onto Android, so sticking with Win32 build.									*
	*	> Failure to read files becomes much more common in a Release build, to the point that the main *
	*	menu screen is completely blank and the player cannot progress past it. Sticking to Debug build.*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto pauseItem =
		MenuItemImage::create("GameScreen/PauseButton.png",
			"GameScreen/PauseButton.png",
			CC_CALLBACK_1(GameScreen::activatePauseScene, this));

	//Creating buttons for Player 1's controls.
	auto p1UpButton =
		MenuItemImage::create("GameScreen/SpeedUpButton.png",
			"GameScreen/SpeedUpButton.png",
			CC_CALLBACK_0(GameScreen::p1SpeedUp, this));
	auto p1DownButton =
		MenuItemImage::create("GameScreen/SpeedDownButton.png",
			"GameScreen/SpeedDownButton.png",
			CC_CALLBACK_0(GameScreen::p1SpeedDown, this));
	auto p1LightButton =
		MenuItemImage::create("GameScreen/LightAttackButton.png",
			"GameScreen/LightAttackButton.png",
			CC_CALLBACK_0(GameScreen::p1LAttack, this));
	auto p1MediumButton =
		MenuItemImage::create("GameScreen/MedAttackButton.png",
			"GameScreen/MedAttackButton.png",
			CC_CALLBACK_0(GameScreen::p1MAttack, this));
	auto p1HeavyButton =
		MenuItemImage::create("GameScreen/HeavyAttackButton.png",
			"GameScreen/HeavyAttackButton.png",
			CC_CALLBACK_0(GameScreen::p1HAttack, this));
	auto p1GuardButton =
		MenuItemImage::create("GameScreen/GuardButton.png",
			"GameScreen/GuardButton.png",
			CC_CALLBACK_0(GameScreen::p1Guard, this));

	//Creating buttons for Player 2's controls.
	auto p2UpButton =
		MenuItemImage::create("GameScreen/SpeedUpButton.png",
			"GameScreen/SpeedUpButton.png",
			CC_CALLBACK_0(GameScreen::p2SpeedUp, this));
	auto p2DownButton =
		MenuItemImage::create("GameScreen/SpeedDownButton.png",
			"GameScreen/SpeedDownButton.png",
			CC_CALLBACK_0(GameScreen::p2SpeedDown, this));
	auto p2LightButton =
		MenuItemImage::create("GameScreen/LightAttackButton.png",
			"GameScreen/LightAttackButton.png",
			CC_CALLBACK_0(GameScreen::p2LAttack, this));
	auto p2MediumButton =
		MenuItemImage::create("GameScreen/MedAttackButton.png",
			"GameScreen/MedAttackButton.png",
			CC_CALLBACK_0(GameScreen::p2MAttack, this));
	auto p2HeavyButton =
		MenuItemImage::create("GameScreen/HeavyAttackButton.png",
			"GameScreen/HeavyAttackButton.png",
			CC_CALLBACK_0(GameScreen::p2HAttack, this));
	auto p2GuardButton =
		MenuItemImage::create("GameScreen/GuardButton.png",
			"GameScreen/GuardButton.png",
			CC_CALLBACK_0(GameScreen::p2Guard, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	p1YPosition = (visibleSize.height / 2) + origin.y + (visibleSize.height / 20);
	p2YPosition = (visibleSize.height / 2) + origin.y - (visibleSize.height / 20);

	pauseItem->setPosition(Point(visibleSize.width / 2, visibleSize.height - pauseItem->getContentSize().height));

	//Placing Player 1's buttons.
	p1UpButton->setPosition(Point(p1UpButton->getContentSize().width * 1.5, visibleSize.height - p1UpButton->getContentSize().height));
	p1DownButton->setPosition(Point(p1DownButton->getContentSize().width * 1.5, p1UpButton->getPosition().y - p1DownButton->getContentSize().height));
	p1MediumButton->setPosition(Point(p1MediumButton->getContentSize().width, p1DownButton->getPosition().y - (p1MediumButton->getContentSize().height * 5)));
	p1LightButton->setPosition(Point(p1LightButton->getContentSize().width, p1MediumButton->getPosition().y - p1LightButton->getContentSize().height));
	p1HeavyButton->setPosition(Point(p1HeavyButton->getContentSize().width * 2, p1MediumButton->getPosition().y));
	p1GuardButton->setPosition(Point(p1GuardButton->getContentSize().width * 2, p1LightButton->getPosition().y));

	//Placing Player 2's buttons.
	p2UpButton->setPosition(Point(visibleSize.width - p2UpButton->getContentSize().width * 1.5, visibleSize.height - p2UpButton->getContentSize().height));
	p2DownButton->setPosition(Point(visibleSize.width - p2DownButton->getContentSize().width * 1.5, p2UpButton->getPosition().y - p2DownButton->getContentSize().height));
	p2MediumButton->setPosition(Point(visibleSize.width - p2MediumButton->getContentSize().width * 2, p2DownButton->getPosition().y - (p2MediumButton->getContentSize().height * 5)));
	p2LightButton->setPosition(Point(visibleSize.width - p2LightButton->getContentSize().width * 2, p2MediumButton->getPosition().y - p2LightButton->getContentSize().height));
	p2HeavyButton->setPosition(Point(visibleSize.width - p2HeavyButton->getContentSize().width, p2MediumButton->getPosition().y));
	p2GuardButton->setPosition(Point(visibleSize.width - p2GuardButton->getContentSize().width, p2LightButton->getPosition().y));

	auto menu = Menu::create(pauseItem, 
		p1UpButton, p1DownButton, p1LightButton, p1MediumButton, p1HeavyButton, p1GuardButton, 
		p2UpButton, p2DownButton, p2LightButton, p2MediumButton, p2HeavyButton, p2GuardButton,
		NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	addBackGroundSprite(visibleSize, origin);
	addPlayers(visibleSize, origin);

	//Defining the locations of the HP display labels.
	p1HPPos = Vec2(visibleSize.width * 3 / 10, visibleSize.height * 4 / 5);
	p2HPPos = Vec2(visibleSize.width * 7 / 10, visibleSize.height * 4 / 5);

	//Defining the HP display labels themselves.
	p1HP = Label::createWithSystemFont("", "Arial", 48);
	p1HP->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	p1HP->setPosition(p1HPPos);
	this->addChild(p1HP, 2);

	p2HP = Label::createWithSystemFont("", "Arial", 48);
	p2HP->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	p2HP->setPosition(p2HPPos);
	this->addChild(p2HP, 2);

	this->scheduleUpdate();

	return true;
}

void GameScreen::update(float dt)
{
	handleMove(dt);
	handleAtk(dt);
	displayHP();
	checkGameOver();

	if (p1->isAttacking())
	{
		handleCollision(p1, p2);
	}
	if (p2->isAttacking())
	{
		handleCollision(p2, p1);
	}
}

void GameScreen::handleMove(float dt)
{
	if (p1->isStopped() && p2->isStopped())
	{//If both players have reached their ends of the board, both turn around and start moving again.
		p1->getMoving();
		p1->setScale(p1->getScale() * -1);
		p2->getMoving();
		p2->setScale(p2->getScale() * -1);
		p2->setPosition(p1->getPosition(), p2YPosition);
	}

	if (!p1->isStopped())
	{//Player 1 moves as long as it has room to on the current round.
		p1->update(dt);
		if (!p1->getDirection())
		{//Direction it moves depends on the direction it's facing.
			p1->setPosition(p1->getPosition(), p1YPosition);
		}
		else
		{
			p1->setPosition(p1->getPosition(), p2YPosition);
		}
	}

	if (!p2->isStopped())
	{//Player 1 moves as long as it has room to on the current round.
		p2->update(dt);
		if (!p2->getDirection())
		{//Direction it moves depends on the direction it's facing.
			p2->setPosition(p2->getPosition(), p1YPosition);
		}
		else
		{
			p2->setPosition(p2->getPosition(), p2YPosition);
		}
	}

	//Display guarding.
	if (p1->isGuarding())
	{
		p1->setOpacity(127);
	}
	else
	{
		p1->setOpacity(255);
	}

	if (p2->isGuarding())
	{
		p2->setOpacity(127);
	}
	else
	{
		p2->setOpacity(255);
	}
}

void GameScreen::handleAtk(float dt)
{
	if (p1->isAttacking())
	{//If P1 is attacking at all...
		if (p1->getAtkType() == 1)
		{//Light attack uses the quarter of the sprite closest to the tip.
			p1Lance->setTextureRect(cocos2d::Rect(lanceWidth * 3 / 4, 0,
									lanceWidth / 4, lanceHeight));
		}
		else if (p1->getAtkType() == 2)
		{//Medium attack uses the half of the sprite closest to the tip.
			p1Lance->setTextureRect(cocos2d::Rect(lanceWidth / 2, 0,
									lanceWidth / 2, lanceHeight));
		}
		else if (p1->getAtkType() == 3)
		{//Heavy attack uses the full sprite.
			p1Lance->setTextureRect(cocos2d::Rect(0, 0,
									lanceWidth, lanceHeight));
		}

		if (!p1->getDirection())
		{//Rotates and places the sprite depending on the direction the attacker is facing.
			p1Lance->setRotation(0.f);
			p1Lance->setPosition(p1->getPosition() + (p1->getContentSize().width / 2), p1YPosition);
		}
		else
		{
			p1Lance->setRotation(180.f);
			p1Lance->setPosition(p1->getPosition() - (p1->getContentSize().width / 2), p2YPosition);
		}
	}
	else
	{//If not attacking, place the lance sprite somewhere way off screen.
		p1Lance->setPosition(-500, -500);
	}

	if (p2->isAttacking())
	{//If P2 is attacking at all...
		if (p2->getAtkType() == 1)
		{//Light attack uses the quarter of the sprite closest to the tip.
			p2Lance->setTextureRect(cocos2d::Rect(lanceWidth * 3 / 4, 0,
									lanceWidth / 4, lanceHeight));
		}
		else if (p2->getAtkType() == 2)
		{//Medium attack uses the half of the sprite closest to the tip.
			p2Lance->setTextureRect(cocos2d::Rect(lanceWidth / 2, 0,
									lanceWidth / 2, lanceHeight));
		}
		else if (p2->getAtkType() == 3)
		{//Heavy attack uses the full sprite.
			p2Lance->setTextureRect(cocos2d::Rect(0, 0,
									lanceWidth, lanceHeight));
		}

		if (!p2->getDirection())
		{//Rotates and places the sprite depending on the direction the attacker is facing.
			p2Lance->setRotation(0.f);
			p2Lance->setPosition(p2->getPosition() + (p2->getContentSize().width / 2), p1YPosition);
		}
		else
		{
			p2Lance->setRotation(180.f);
			p2Lance->setPosition(p2->getPosition() - (p2->getContentSize().width / 2), p2YPosition);
		}
	}
	else
	{//If not attacking, place the lance sprite somewhere way off screen.
		p2Lance->setPosition(-500, -500);
	}
}

void GameScreen::handleCollision(Player* attacker, Player* defender)
{
	if (!attacker->getDirection())
	{//If facing right.
		if (attacker->getAtkType() == 1)
		{//Light attack has short range and low damage.
			float atkPos = attacker->getPosition();
			float defPos = defender->getPosition();
			float atkWidth = attacker->getContentSize().width;
			if (defender->getPosition() < attacker->getPosition() + (lanceWidth / 4) + attacker->getContentSize().width &&
				defender->getPosition() > attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 20;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
		else if (attacker->getAtkType() == 2)
		{//Medium attack has moderate range and damage.
			if (defender->getPosition() < attacker->getPosition() + (lanceWidth / 2) + attacker->getContentSize().width &&
				defender->getPosition() > attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 50;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
		else if (attacker->getAtkType() == 3)
		{//Heavy attack has long range and high damage.
			if (defender->getPosition() < attacker->getPosition() + lanceWidth + attacker->getContentSize().width &&
				defender->getPosition() > attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 75;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
	}
	else
	{//If facing left.
		if (attacker->getAtkType() == 1)
		{//Light attack has short range and low damage.
			if (defender->getPosition() > attacker->getPosition() - (lanceWidth / 4) - attacker->getContentSize().width &&
				defender->getPosition() < attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 20;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
		else if (attacker->getAtkType() == 2)
		{//Medium attack has moderate range and damage.
			if (defender->getPosition() > attacker->getPosition() - (lanceWidth / 2) - attacker->getContentSize().width &&
				defender->getPosition() < attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 50;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
		else if (attacker->getAtkType() == 3)
		{//Heavy attack has long range and high damage.
			if (defender->getPosition() > attacker->getPosition() - lanceWidth - attacker->getContentSize().width &&
				defender->getPosition() < attacker->getPosition())
			{//Collision detected; deal damage.
				float damage = 75;
				if (defender->isGuarding())
				{
					damage *= 0.5;
				}
				defender->setHP(defender->getHP() - damage);
				attacker->cancelAttack();
			}
		}
	}
}

void GameScreen::displayHP()
{//Shows both players' HP totals, rounded down for ease of viewing.
	std::string p1HPDisplay = std::to_string(static_cast<int>(p1->getHP())) + "% HP";
	p1HP->setString(p1HPDisplay);

	std::string p2HPDisplay = std::to_string(static_cast<int>(p2->getHP())) + "% HP";
	p2HP->setString(p2HPDisplay);
}

void GameScreen::checkGameOver()
{
	if (p1->getHP() <= 0)
	{
		activateGameOverScene(this);
	}
	else if (p2->getHP() <= 0)
	{
		activateGameOverScene(this);
	}
}

void GameScreen::p1SpeedUp()
{ p1->changeSpeed(1); }

void GameScreen::p1SpeedDown()
{ p1->changeSpeed(0); }

void GameScreen::p1LAttack()
{ p1->attack(1); }

void GameScreen::p1MAttack()
{ p1->attack(2); }

void GameScreen::p1HAttack()
{ p1->attack(3); }

void GameScreen::p1Guard()
{ p1->guard(); }

//Player 2's Commands
void GameScreen::p2SpeedUp()
{ p2->changeSpeed(1); }

void GameScreen::p2SpeedDown()
{ p2->changeSpeed(0); }

void GameScreen::p2LAttack()
{ p2->attack(1); }

void GameScreen::p2MAttack()
{ p2->attack(2); }

void GameScreen::p2HAttack()
{ p2->attack(3); }

void GameScreen::p2Guard()
{ p2->guard(); }

void GameScreen::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameScreen::activateGameOverScene(Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScreen::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin) 
{ 
	//std::shared_ptr<GameData> ptr = GameData::sharedGameData(); 
	//auto backgroundSprite = Sprite::create(ptr->m_backgroundTextureFile); 
	auto backgroundSprite = Sprite::create("GameScreen/Background.jpg");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y)); 
	this->addChild(backgroundSprite, -1); 
}

void GameScreen::addPlayers(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	p1 = Player::create(0, visibleSize, origin);
	p1->setPosition(p1->getPosition(), p1YPosition);
	this->addChild(p1, 1);

	p1Lance = Sprite::create("GameScreen/Lance.png");
	lanceWidth = p1Lance->getContentSize().width; //Records the dimensions of the base "lance" sprite.
	lanceHeight = p1Lance->getContentSize().height;
	p1Lance->setAnchorPoint(Vec2(0, 1)); //Just because it's what I'm used to.
	p1Lance->setPosition(0, 0);
	this->addChild(p1Lance, 1);

	p2 = Player::create(1, visibleSize, origin);
	p2->setPosition(p2->getPosition(), p2YPosition);
	p2->setScale(p2->getScale() * -1);
	this->addChild(p2, 1);

	p2Lance = Sprite::create("GameScreen/Lance.png");
	p2Lance->setAnchorPoint(Vec2(0, 1)); //Just because it's what I'm used to.
	p2Lance->setPosition(0, 0);
	this->addChild(p2Lance, 1);
}

void GameScreen::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
