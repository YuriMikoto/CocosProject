#include "Player.h"
USING_NS_CC;

Player::Player(bool id, cocos2d::Size const & visibleSize, cocos2d::Point const & origin) : playerID(id), direction(id)
{
	p1DefaultX = (visibleSize.width * 1/10) + origin.x;
	p2DefaultX = (visibleSize.width * 9/10) + origin.x;

	if (playerID == 0)
	{
		xPosition = p1DefaultX;
	}
	else
	{
		xPosition = p2DefaultX;
	}
}

Player * Player::create(bool id, cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	Player * pSprite = new Player(id, visibleSize, origin);
	if (id == 0)
	{
		if (pSprite->initWithFile("GameScreen/Player1.png")) //ptr->m_p1TextureFile
		{
			return pSprite;
		}
	}
	else
	{
		if (pSprite->initWithFile("GameScreen/Player2.png")) //ptr->m_p2TextureFile
		{
			return pSprite;
		}
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Player::update(float dt)
{
	if (direction == 0)
	{//0, P1's side, moves right.
		xPosition += speed * dt;

		if (xPosition >= p2DefaultX)
		{
			xPosition = p2DefaultX;
			direction = 1;
			speed = INITIAL_SPEED;
			roundEnd = true;
		}
	}
	else
	{//1, P2's side, moves left.
		xPosition -= speed * dt;

		if (xPosition <= p1DefaultX)
		{
			xPosition = p1DefaultX;
			direction = 0;
			speed = INITIAL_SPEED;
			roundEnd = true;
		}
	}

	if (atkTimer > 0)
	{
		atkTimer -= dt * 24;
	}
	if (atkTimer <= 6 && atkTimer > 0)
	{
		attacking = true;
	}
	if (atkTimer <= 0)
	{
		attacking = false;
		atkType = 0;
	}

	if (grdTimer > 0)
	{
		grdTimer -= dt * 24;
	}
	if (grdTimer <= 0)
	{
		guarding = false;
	}
}

void Player::changeSpeed(bool direction)
{
	if (direction == 0)
	{//0 reduces speed.
		speed -= SPEED_INTERVAL;
		if (speed < MIN_SPEED)
		{
			speed = MIN_SPEED;
		}
	}
	else
	{//1 increases it.
		speed += SPEED_INTERVAL;
		if (speed > MAX_SPEED)
		{
			speed = MAX_SPEED;
		}
	}
}

void Player::attack(byte type)
{
	if (!atkType && !guarding)
	{//Can only attack if you're not already attacking or guarding.
		atkType = type;
		switch (type) {
		case 1:
			atkTimer = 7;
			break;
		case 2:
			atkTimer = 12;
			break;
		case 3:
			atkTimer = 18;
			break;
		}
	}
}

void Player::cancelAttack()
{//Ends the player's attack so that it only ever hits once.
	attacking = false;
	atkType = 0;
}

void Player::guard()
{
	if (!atkType && !guarding)
	{//Cannot guard while attacking, and cannot extend guard time by mashing the button.
		grdTimer = 30;
		guarding = true;
	}
}

bool Player::isStopped()
{
	return roundEnd;
}

void Player::getMoving()
{
	roundEnd = false;
}

bool Player::isAttacking()
{
	return attacking;
}

byte Player::getAtkType()
{
	return atkType;
}

bool Player::isGuarding()
{
	return guarding;
}

float Player::getHP()
{
	return health;
}

void Player::setHP(float value)
{
	health = value;
}

float Player::getPosition()
{
	return xPosition;
}

bool Player::getDirection()
{
	return direction;
}