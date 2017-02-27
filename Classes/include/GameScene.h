#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameData.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Player.h"

class Player;

class GameScreen : public cocos2d::Layer
{
private:
	cocos2d::Vec2 p1HPPos;
	cocos2d::Vec2 p2HPPos;
	cocos2d::Label * p1HP;
	cocos2d::Label * p2HP;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);

	// Called at game over 
	void activateGameOverScene(Ref *pSender);

	Player* p1;
	Player* p2;
	cocos2d::Sprite* p1Lance;
	cocos2d::Sprite* p2Lance;
	float lanceWidth; //Dimensions of the lance. Made drawing different segments much easier.
	float lanceHeight; 

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
	void addPlayers(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	void update(float dt);
	void handleMove(float dt);
	void handleAtk(float dt);
	void handleCollision(Player* attacker, Player* defender);
	void displayHP();
	void checkGameOver();

	float p1YPosition;
	float p2YPosition;

	void p1SpeedUp();
	void p1SpeedDown();
	void p1LAttack();
	void p1MAttack();
	void p1HAttack();
	void p1Guard();

	void p2SpeedUp();
	void p2SpeedDown();
	void p2LAttack();
	void p2MAttack();
	void p2HAttack();
	void p2Guard();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScreen);
};

#endif // __HELLOWORLD_SCENE_H__
