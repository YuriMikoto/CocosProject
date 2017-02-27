#include "TutorialScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Tutorial::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Tutorial::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto prevItem =
		MenuItemImage::create("MainMenuScreen/Exit.png",
			"MainMenuScreen/Exit.png",
			CC_CALLBACK_1(Tutorial::prevPage, this));
	//prevItem->setAnchorPoint(cocos2d::Vec2(0, 0));
	//prevItem->setPosition(0, 0);

	auto nextItem = 
		MenuItemImage::create("MainMenuScreen/Play.png",
			"MainMenuScreen/Play.png",
			CC_CALLBACK_1(Tutorial::nextPage, this));
	//nextItem->setAnchorPoint(cocos2d::Vec2(1, 0));
	//nextItem->setPosition(visibleSize.width, 0);

	std::string pg1Text = "OVERVIEW\n\n";
	pg1Text += "In Lancelot, you play as a knight in a jousting championship and will joust\n";
	pg1Text += "\t with other knights.\n\n";
	pg1Text += "The goal of the game is to knock out the other player by using different\n";
	pg1Text += "\t attacks, your shield and simple feints.\n\n";
	pg1Text += "Each player's horse will gallop towards the other side of the field, then\n";
	pg1Text += "\t turn around and gallop in the other direction.\n\n";	
	pg1Text += "This repeats for as long as the match lasts, which ends when one player's\n";
	pg1Text += "\t health has been depleted.\n\n";

	std::string pg2Text = "MOVING\n\n";
	pg2Text += "The up and down arrows on the upper corners of the screen control the\n";
	pg2Text += "\t players' movement speeds.\n\n";
	pg2Text += "Pressing the up arrow will increase your speed, and down will decrease it.\n";
	pg2Text += "\t There are upper and lower limits.\n\n";
	pg2Text += "Each round waits until both players are at the opposite ends of the screen\n";
	pg2Text += "\t before starting the next round.\n\n";

	std::string pg3Text = "ATTACKING\n\n";
	pg3Text += "There are four buttons in each of the screen's lower corners. Three of\n";
	pg3Text += "\t these, 'Wk', 'Med' and 'Hvy', are Attack buttons.\n\n";
	pg3Text += "Each attack type has different properties, from quick and weak pokes to\n";
	pg3Text += "\t lengthy thrusts that deal high damage but leave you vulnerable.\n\n";
	pg3Text += "Experiment with these to get a feel for how each attack works.\n";

	std::string pg4Text = "GUARDING\n\n";
	pg4Text += "The fourth button, 'GRD', commands the player character to enter a\n";
	pg4Text += "\t defensive stance. During this stance, you take half damage from enemy\n";
	pg4Text += "\t attacks.\n\n";
	pg4Text += "Use this when you know the enemy is about to get a hit on you to mitigate\n";
	pg4Text += "\t damage and keep your advantage.\n\n";
	pg4Text += "Note that the guard stance has a fixed duration. Try not to use it too early\n";
	pg4Text += "\t or too late.\n\n";

	std::string pg5Text = "TIPS\n\n";
	pg5Text += "Try to time your guard so that you can instantly counterattack with a light\n";
	pg5Text += "\t attack once it ends. You'll reduce damage and still get a hit off.\n\n";
	pg5Text += "Heavy attacks are obvious, but an idle player is likely to try a light attack.\n";
	pg5Text += "\t Watch the opponent carefully at all times.\n\n";
	pg5Text += "You will not be stunned by damage. If the enemy is low on health and you\n";
	pg5Text += "\t can take a hit, trading blows is a viable strategy.\n\n";
	pg5Text += "Use sudden stops and starts with your movement to feint and keep the\n";
	pg5Text += "\t enemy on their toes, but try not to be too predictable. Surprise is key.\n\n";

	page1 = Label::createWithSystemFont(pg1Text, "Arial", 24);
	page1->setAnchorPoint(cocos2d::Vec2(0, 1));
	page1->setPosition(0, visibleSize.height);
	page2 = Label::createWithSystemFont(pg2Text, "Arial", 24);
	page2->setAnchorPoint(cocos2d::Vec2(0, 1));
	page2->setPosition(0, visibleSize.height);
	page3 = Label::createWithSystemFont(pg3Text, "Arial", 24);
	page3->setAnchorPoint(cocos2d::Vec2(0, 1));
	page3->setPosition(0, visibleSize.height);
	page4 = Label::createWithSystemFont(pg4Text, "Arial", 24);
	page4->setAnchorPoint(cocos2d::Vec2(0, 1));
	page4->setPosition(0, visibleSize.height);
	page5 = Label::createWithSystemFont(pg5Text, "Arial", 24);
	page5->setAnchorPoint(cocos2d::Vec2(0, 1));
	page5->setPosition(0, visibleSize.height);

	//this->addChild(prevItem);
	//this->addChild(nextItem);
	this->addChild(page1);
	this->addChild(page2);
	page2->setVisible(false);
	this->addChild(page3);
	page3->setVisible(false);
	this->addChild(page4);
	page4->setVisible(false);
	this->addChild(page5);
	page5->setVisible(false);

	//auto menu = Menu::create(mainMenuItem, NULL);
	auto menu = Menu::create(prevItem, nextItem, NULL);

	menu->alignItemsHorizontallyWithPadding(visibleSize.width / 4);
	menu->setPosition(visibleSize.width / 2, 50);
	this->addChild(menu);
}

void Tutorial::prevPage(Ref *pSender)
{
	if (currentPage == 1)
	{
		currentPage = 0;
		Director::getInstance()->popScene();
	}
	else
	{
		currentPage--;
	}

	if (currentPage != 0)
	{
		writePage();
	}
}

void Tutorial::nextPage(Ref *pSender)
{
	if (currentPage == 5)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		currentPage++;
	}

	if (currentPage != 0)
	{
		writePage();
	}
}

void Tutorial::writePage()
{
	switch (currentPage) {
	case 1:
		page2->setVisible(false);
		page1->setVisible(true);
		break;
	case 2:
		page1->setVisible(false); 
		page3->setVisible(false);
		page2->setVisible(true);
		break;
	case 3:
		page2->setVisible(false);
		page4->setVisible(false);
		page3->setVisible(true);
		break;
	case 4:
		page3->setVisible(false);
		page5->setVisible(false);
		page4->setVisible(true);
		break;
	case 5:
		page4->setVisible(false);
		page5->setVisible(true);
		break;
	}
}

void Tutorial::menuCloseCallback(Ref* pSender)
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
