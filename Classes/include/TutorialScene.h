#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"

class Tutorial : public cocos2d::Layer
{
private:
	byte currentPage = 1;

	cocos2d::Label * page1;
	cocos2d::Label * page2;
	cocos2d::Label * page3;
	cocos2d::Label * page4;
	cocos2d::Label * page5;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// Called when main menu is selected.
	void prevPage(Ref *pSender);
	void nextPage(Ref *pSender);
	void writePage();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Tutorial);
};

#endif // __HELLOWORLD_SCENE_H__
