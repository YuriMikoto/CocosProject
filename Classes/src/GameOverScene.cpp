#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuTitle =
		MenuItemImage::create("GameOverScreen/Game_Over.png",
			"GameOverScreen/Game_Over.png");
	auto retryItem =
		MenuItemImage::create("GameOverScreen/Replay.png",
			"GameOverScreen/Replay.png",
			CC_CALLBACK_1(GameOver::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/Menu.png",
			"GameOverScreen/Menu.png",
			CC_CALLBACK_1(GameOver::activateMainMenuScene, this));
	auto menu = Menu::create(menuTitle, retryItem, mainMenuItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);
}

void GameOver::activateGameScene(cocos2d::Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::menuCloseCallback(Ref* pSender)
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
