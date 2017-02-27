#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameScene.h"

class Player : public cocos2d::Sprite {
private:
	const bool P1 = 0; //ID used for player 1 and the direction P1 begins facing (right).
	const bool P2 = 1; //ID used for player 2 and the direction P2 begins facing (left).

	const float INITIAL_SPEED = 210.f;
	const float MIN_SPEED = 30.f;
	const float MAX_SPEED = 390.f;
	const float SPEED_INTERVAL = 60.f;

	bool playerID;
	bool direction;
	float health = 100;
	float speed = INITIAL_SPEED;
	bool attacking = 0; //If currently able to hit.
	byte atkType = 0; //Which attack is being used.
	float atkTimer = 0; //Time until attack ends.
	bool guarding = false;
	float grdTimer = 0;
	bool roundEnd = false;

	float xPosition;

public:
	Player(bool id, cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	static Player * create(bool id, cocos2d::Size const & visibleSize, cocos2d::Point const & origin);

	void update(float dt);
	void changeSpeed(bool direction);
	void getMoving();
	void attack(byte type);
	void cancelAttack();
	void guard();

	bool isStopped();
	bool isAttacking();
	byte getAtkType();
	bool isGuarding();
	float getHP();
	void setHP(float value);
	float getPosition();
	bool getDirection();

	float p1DefaultX;
	float p2DefaultX;
};

#endif