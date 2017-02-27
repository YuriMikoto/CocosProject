#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "TutorialScene.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void activateGameScene(Ref * pSender);

	void activateTutorialScene(Ref * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __HELLOWORLD_SCENE_H__
