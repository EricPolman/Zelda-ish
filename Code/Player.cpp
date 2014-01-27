#include "Player.h"
#include "Boomerang.h"
#include "ShopItem.h"

std::ostringstream sstream;
Player::Player(std::string a_tilesheetName, float a_fX, float a_fY)
	: Entity(a_tilesheetName, a_fX, a_fY)
{
	m_pSprite->LoadSpritesheet(a_tilesheetName, 48, 48, 9, 13);

	m_type = PLAYER;
	
	m_pSprite->AddAnimation("0_idle", Vector2i(1,0), Vector2i(8,0));
	m_pSprite->AddAnimation("1_idle", Vector2i(1,1), Vector2i(8,1));
	m_pSprite->AddAnimation("2_idle", Vector2i(1,2), Vector2i(8,2));
	m_pSprite->AddAnimation("3_idle", Vector2i(1,3), Vector2i(8,3));

	m_pSprite->AddAnimation("0_walk", Vector2i(1,0), Vector2i(8,0));
	m_pSprite->AddAnimation("1_walk", Vector2i(1,1), Vector2i(8,1));
	m_pSprite->AddAnimation("2_walk", Vector2i(1,2), Vector2i(8,2));
	m_pSprite->AddAnimation("3_walk", Vector2i(1,3), Vector2i(8,3));
	
	m_pSprite->AddAnimation("0_slash", Vector2i(0,4), Vector2i(6,4));
	m_pSprite->AddAnimation("1_slash", Vector2i(0,5), Vector2i(5,5));
	m_pSprite->AddAnimation("2_slash", Vector2i(0,6), Vector2i(5,6));
	m_pSprite->AddAnimation("3_slash", Vector2i(0,7), Vector2i(5,7));

	m_pSprite->AddAnimation("0_throw_boomerang", Vector2i(7,4), Vector2i(8,4));
	m_pSprite->AddAnimation("1_throw_boomerang", Vector2i(7,5), Vector2i(8,5));
	m_pSprite->AddAnimation("2_throw_boomerang", Vector2i(7,6), Vector2i(8,6));
	m_pSprite->AddAnimation("3_throw_boomerang", Vector2i(7,7), Vector2i(8,7));
	
	m_pSprite->AddAnimation("0_walk_noweapons", Vector2i(1,9), Vector2i(8,9));
	m_pSprite->AddAnimation("1_walk_noweapons", Vector2i(1,10), Vector2i(8,10));
	m_pSprite->AddAnimation("2_walk_noweapons", Vector2i(1,11), Vector2i(8,11));
	m_pSprite->AddAnimation("3_walk_noweapons", Vector2i(1,12), Vector2i(8,12));

	m_pSprite->AddAnimation("0_idle_noweapons", Vector2i(1,9), Vector2i(8,9));
	m_pSprite->AddAnimation("1_idle_noweapons", Vector2i(1,10), Vector2i(8,10));
	m_pSprite->AddAnimation("2_idle_noweapons", Vector2i(1,11), Vector2i(8,11));
	m_pSprite->AddAnimation("3_idle_noweapons", Vector2i(1,12), Vector2i(8,12));

	m_bHasBoomerang = false;
	m_bHasSwordAndShield = false;
	m_pCurrentBoomerang = 0;

	m_pSprite->AddAnimation("die", Vector2i(0,8), Vector2i(7,8));
	m_pSprite->AddAnimation("die_idle", Vector2i(7,8), Vector2i(7,8));

	m_iRupees = 0;
}

void Player::Spawn()
{
	m_pWorld->PlacePlayer();
	m_state = ALIVE;
	m_fRespawnTimer = 0;
	m_direction = UP;
	m_bDirectionChanged = false;
	sstream << m_direction;
	m_pSprite->PlayAnimation(sstream.str()+"_idle"+(m_bHasSwordAndShield ? "" : "_noweapons"), true);
	m_pSprite->m_fAnimationSpeed = 6;
	sstream.str("");

	m_collisionRect.x = 17;
	m_collisionRect.y = 23;
	m_collisionRect.height = 10;
	m_collisionRect.width = 14;

	m_playerState = PLAYER_IDLE;
	INVULNERABLE_TIME = 1;
	m_fInvulnerabilityTimer = 0;
	m_bInvulnerable = false;

	m_iHealth = 10;
	
	m_pCurrentSwordSlash = 0;
}

Player::~Player()
{
	Entity::~Entity();
}

void Player::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	
	m_position = m_position + m_velocity;
	m_velocity = Vector2();
	Vector2 moveDirection;

	//std::cout << "Player: " << Vector2(m_position + Vector2(m_collisionRect.x, m_collisionRect.y)).ToString() << Vector2(m_collisionRect.width, m_collisionRect.height).ToString() << std::endl;
	
	if(m_pCurrentBoomerang != 0)
	{
		if(m_pCurrentBoomerang->m_state == REMOVED) m_pCurrentBoomerang = 0;
	}

	UpdateDirectionReset();

	if(m_state == EntityState::ALIVE)
	{
		if(m_bInvulnerable)
		{
			if((int)(m_fInvulnerabilityTimer * 10) % 2 == 0)
			{
				m_bIsVisible = false;
			}
			else
			{
				m_bIsVisible = true;
			}
			m_fInvulnerabilityTimer += a_fDeltaTime;
			if(m_fInvulnerabilityTimer > INVULNERABLE_TIME)
			{
				m_fInvulnerabilityTimer = 0;
				m_bInvulnerable = false;
				m_bIsVisible = true;
			}
		}

		switch(m_playerState)
		{
		case PLAYER_IDLE:
		case PLAYER_WALKING:
			if(Input->IsKeyDown(SDLK_w) || Input->IsKeyDown(SDLK_UP))
			{
				if(!m_bDirectionChanged && m_direction != UP)
				{
					ChangeDirection(UP);
				}
				moveDirection.y -= 1;
			}
			if(Input->IsKeyDown(SDLK_s) || Input->IsKeyDown(SDLK_DOWN))
			{
				if(!m_bDirectionChanged && m_direction != DOWN)
				{
					ChangeDirection(DOWN);
				}
				moveDirection.y += 1;
			}
			if(Input->IsKeyDown(SDLK_a) || Input->IsKeyDown(SDLK_LEFT))
			{
				if(!m_bDirectionChanged && m_direction != LEFT)
				{
					ChangeDirection(LEFT);
				}
				moveDirection.x -= 1;
			}
			if(Input->IsKeyDown(SDLK_d) || Input->IsKeyDown(SDLK_RIGHT))
			{
				if(!m_bDirectionChanged && m_direction != RIGHT)
				{
					ChangeDirection(RIGHT);
				}
				moveDirection.x += 1;
			}

			if(moveDirection.x != 0 && moveDirection.y != 0)
			{
				moveDirection.Normalize();
			}
			else if(moveDirection.x == 0 && moveDirection.y == 0)
			{
				sstream << m_direction;
				m_pSprite->PlayAnimation(sstream.str()+"_idle"+(m_bHasSwordAndShield ? "" : "_noweapons"), true);
				sstream.str("");
				m_bDirectionChanged = false;
			}
			m_velocity = moveDirection * a_fDeltaTime * 80;
			//m_velocity = moveDirection * a_fDeltaTime * 600;

			if(m_position.x < -24)
			{
				m_pWorld->ChangeRoom(this, (short)LEFT);
			}
			else if(m_position.x + m_pSprite->GetWidth() > ROOM_WIDTH + 24)
			{
				m_pWorld->ChangeRoom(this, (short)RIGHT);
			}
			else if(m_position.y < -24)
			{
				m_pWorld->ChangeRoom(this, (short)UP);
			}
			else if(m_position.y + m_pSprite->GetHeight() > ROOM_HEIGHT + 24)
			{
				m_pWorld->ChangeRoom(this, (short)DOWN);
			}
			
			if(Input->IsKeyPressed(SDLK_SPACE))
			{
				if(m_bHasSwordAndShield)
					Slash();
			}
			else if(Input->IsKeyPressed(SDLK_e))
			{
				if(m_bHasBoomerang && m_pCurrentBoomerang == 0)
					ThrowBoomerang();
			}
			break;
		case PLAYER_ATTACKING:
			sstream << m_direction;
			//std::string str = sstream.str();
			if(m_pSprite->m_sCurrentAnimation != sstream.str()+"_slash")
			{
				m_playerState = PLAYER_IDLE;
				m_pSprite->PlayAnimation(sstream.str()+"_idle"+(m_bHasSwordAndShield ? "" : "_noweapons"), true);
				m_pCurrentSwordSlash->m_state = REMOVED;
				m_pCurrentSwordSlash = 0;
			}
			sstream.str("");
			break;
		case PLAYER_THROWING_BOOMERANG:
			sstream << m_direction;
			//std::string str = sstream.str();
			if(m_pSprite->m_sCurrentAnimation != sstream.str()+"_throw_boomerang")
			{
				m_playerState = PLAYER_IDLE;
				m_pSprite->PlayAnimation(sstream.str()+"_idle"+(m_bHasSwordAndShield ? "" : "_noweapons"), true);
				m_pSprite->m_fAnimationSpeed = 6;
				switch(m_direction)
				{
				case DOWN:
					m_pCurrentBoomerang = new Boomerang(m_position.x + m_collisionRect.x, m_position.y + m_collisionRect.y + m_collisionRect.height, Vector2(0,1), this);
					break;
				case RIGHT:
					m_pCurrentBoomerang = new Boomerang(m_position.x + m_collisionRect.x + m_collisionRect.width - 18, m_position.y + 16, Vector2(1,0), this);
					break;
				case UP:
					m_pCurrentBoomerang = new Boomerang(m_position.x + m_collisionRect.x, m_position.y + m_collisionRect.y, Vector2(0,-1), this);
					break;
				case LEFT:	
					m_pCurrentBoomerang = new Boomerang(m_position.x + m_collisionRect.x, m_position.y + m_collisionRect.y, Vector2(-1,0), this);
					break;
				}
				//new boomerang here!
			}
			sstream.str("");
			break;
		}
	}
	else if(m_state == DEAD)
	{
		if(m_pSprite->m_sCurrentAnimation != "die")
		{
			if(m_pSprite->m_sCurrentAnimation != "die_idle")
			{
				m_pSprite->PlayAnimation("die_idle", true);
			}
			m_fRespawnTimer += a_fDeltaTime;
			if(m_fRespawnTimer > 2)
				Spawn();
		}
	}
}


void Player::ChangeDirection(Direction a_direction)
{
	m_direction = a_direction;
	sstream << m_direction;
	m_pSprite->PlayAnimation(sstream.str()+"_walk" + (m_bHasSwordAndShield ? "" : "_noweapons"), true);
	sstream.str("");
	m_bDirectionChanged = true;
}


void Player::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(m_state != DEAD)
	{
		switch(a_pOther->m_type)
		{
		case PICKUP:
			break;
		case SWORD_SLASH:
		case PLAYER_WEAPON:
			break;
		case DESTROYABLE:
		case STATIC:
			a_info.depth.Normalize();
			a_info.depth = a_info.depth * 1.5f;
			
			m_velocity.x += a_info.depth.x;
			m_velocity.y += a_info.depth.y;
			break;
		case ENEMY:
			a_info.depth.Normalize();
			if(m_bInvulnerable)
			{
				a_info.depth = a_info.depth * 1;
			}
			else
			{
				a_info.depth = a_info.depth * 12;
			}
			
			m_velocity.x += a_info.depth.x;
			m_velocity.y += a_info.depth.y;
			DecreaseHealth(1);
		
			break;
		default:
			a_info.depth.Normalize();
			a_info.depth = a_info.depth * 1.5f;
			
			m_velocity.x += a_info.depth.x;
			m_velocity.y += a_info.depth.y;
			break;
		}
	}
}


void Player::Slash()
{
	m_playerState = PLAYER_ATTACKING;
	m_pCurrentSwordSlash = new SwordSlash(m_direction, m_position.x, m_position.y);
	sstream << m_direction;
	m_pSprite->PlayAnimation(sstream.str()+"_slash", false);
	sstream.str("");
}


void Player::ThrowBoomerang()
{
	m_pSprite->m_fAnimationSpeed = 2;
	m_playerState = PLAYER_THROWING_BOOMERANG;
	sstream << m_direction;
	m_pSprite->PlayAnimation(sstream.str()+"_throw_boomerang", false);
	sstream.str("");
}



void Player::UpdateDirectionReset()
{
	switch(m_direction)
	{
	case DOWN:
		if(Input->IsKeyUp(SDLK_s) || Input->IsKeyUp(SDLK_DOWN))
			m_bDirectionChanged = false;
		break;
	case RIGHT:
		if(Input->IsKeyUp(SDLK_d) || Input->IsKeyUp(SDLK_RIGHT))
			m_bDirectionChanged = false;
		break;
	case UP:
		if(Input->IsKeyUp(SDLK_w) || Input->IsKeyUp(SDLK_UP))
			m_bDirectionChanged = false;
		break;
	case LEFT:
		if(Input->IsKeyUp(SDLK_a) || Input->IsKeyUp(SDLK_LEFT))
			m_bDirectionChanged = false;
		break;
	}
}


void Player::AddRupees(int a_iAmount)
{
	m_iRupees += a_iAmount;
}

void Player::DecreaseHealth(int a_iAmount)
{
	if(!m_bInvulnerable && m_state != DEAD)
	{
		if(a_iAmount > 0)
		{
			m_bInvulnerable = true;
			m_fInvulnerabilityTimer = 0;
			m_iHealth -= a_iAmount;
			if(m_iHealth < 1)
			{
				Die();
			}
		}
		else
		{
			m_iHealth -= a_iAmount;
			if(m_iHealth > 10)
				m_iHealth = 10;
		}
	}
}

void Player::Die()
{
	m_pSprite->PlayAnimation("die", false);
	m_pSprite->m_fAnimationSpeed = 2;
	m_state = DEAD;
	if(m_pCurrentBoomerang != 0)
	{
		m_pCurrentBoomerang->m_state = REMOVED;
	}
	if(m_pCurrentSwordSlash != 0)
	{
		m_pCurrentSwordSlash->m_state = REMOVED;
	}
}


void Player::EnableBoomerang()
{
	m_bHasBoomerang = true;
	m_pWorld->PrepareEndGame();
}


void Player::KnockBack(Vector2 a_otherPosition)
{
	Vector2 direction = m_position - a_otherPosition;
	direction.Normalize();
	Move(direction * 2);
}