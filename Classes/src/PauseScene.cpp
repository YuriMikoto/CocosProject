#include "PauseScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto resumeItem =
		MenuItemImage::create("PauseScreen/Resume.png",
			"PauseScreen/Resume.png",
			CC_CALLBACK_1(PauseMenu::resume, this));
	auto mainMenuItem =
		MenuItemImage::create("PauseScreen/Quit.png",
			"PauseScreen/Quit.png",
			CC_CALLBACK_1(PauseMenu::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, mainMenuItem, NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);
}

void PauseMenu::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void PauseMenu::activateMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseMenu::retry(Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseMenu::menuCloseCallback(Ref* pSender)
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
