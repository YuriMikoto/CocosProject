#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuTitle =
		MenuItemImage::create("MainMenuScreen/Title.png",
			"MainMenuScreen/Title.png");
	auto playItem =
		MenuItemImage::create("MainMenuScreen/Play.png",
			"MainMenuScreen/Play.png",
			CC_CALLBACK_1(MainMenu::activateGameScene, this));
	auto tutorialItem = //Why can't it find "MainMenuScreen/Tutorial.png"...?
		MenuItemImage::create("MainMenuScreen/Play.png",
			"MainMenuScreen/TutButton.png",
			CC_CALLBACK_1(MainMenu::activateTutorialScene, this));
	auto quitItem =
		MenuItemImage::create("MainMenuScreen/Exit.png",
			"MainMenuScreen/Exit.png",
			CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	auto menu = Menu::create(menuTitle, playItem, tutorialItem, quitItem, NULL);

	// Returns visible size of OpenGL window in points.
	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 8);
	this->addChild(menu);

	return true;
}

void MainMenu::activateGameScene(Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::activateTutorialScene(Ref * pSender)
{
	auto scene = Tutorial::createScene();
	Director::getInstance()->pushScene(scene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
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
