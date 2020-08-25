#include "ball.h"
#include "staticbrick.h"

#define PI 3.14159265

Ball::Ball(Texture tex, Vec2i pos, Vec2i size, bool collider, bool moving, Vec2f force, Vec2f fpos, float spd) : 
	Sprite(tex, pos, size), isMoving(moving), currentForce(force), fposition(fpos), fspeed(spd)
{
	has_collider = true;
}

long mod(long a, long b)
{
	return (a % b + b) % b;
}

int getPoints(int id)
{
	if (id > 0 && id < 13)
	{
		return id * 10 + 40;
	}
}

bool Ball::moveBall(SDL_Surface *win_surf, Vaus vaus, bool cylindrical, Player *player)
{
	Vec2f move = force(); //chercher le vecteur de force
	if (player->slow() == true)
	{
		move.x = move.x / 2;
		move.y = move.y / 2;
	} //on ralenti la balle

	fposition = fposition.operator+(move); //ajoute ce vecteur à la position float
	int x = (int)fposition.x;			   //cherche les coord x et y entière pour les mettre dans m_pos
	int y = (int)fposition.y;

	m_pos = {x, y}; //m_pos= coord entière de la balle pour l'affichage

	if (m_pos.x < 0 || m_pos.x > (win_surf->w - m_size.x))
	{
		if (cylindrical == false)
			setForce({-1 * force().x, force().y});
		else
		{
			int modulo = mod(m_pos.x, win_surf->w);
			m_pos.x = modulo;
		}
	}

	if (m_pos.y < 0 || m_pos.y > (win_surf->h - m_size.y))
		setForce({force().x, -1 * force().y});

	if(m_pos.y > (win_surf->h - m_size.y) && player->divide()==false)	//touche le bas de l'écran
	{
		player->setLifes(player->lifes() - 1);
		return false;
	}
	else if(m_pos.y > (win_surf->h - m_size.y) && player->divide()==true)	//touche le bas de l'écran
	{
		return false;
	}

	if (m_pos.y > (vaus.pos().y - m_size.y) &&
		m_pos.y < vaus.pos().y &&
		m_pos.x > (vaus.pos().x - m_size.x) &&
		m_pos.x < ((vaus.pos().x + vaus.size().x) - m_size.x) &&
		force().y >= 0.0f)
	{
		if (player->magnet() == true)
		{
			setForce({0.0, 0.0});
		}
		else
		{
			float coeff = ((m_pos.x + m_size.x / 2) - (vaus.pos().x + vaus.size().x / 2)) * (64.0 / (vaus.size().x / 2)); //coeff de distance entre le centre du vaus et la balle
			float cosinus = cos(coeff * PI / 180.0);																	  //cosinus de ce coeff en degré
			float sinus = sin(coeff * PI / 180.0);

			if(player->divide()==true)
				setSpeed(speed()*1.01);
			else
				setSpeed(speed()*1.03);

			setForce({sinus * speed(), -cosinus * speed()}); //on accélère la balle
		}
	}

	return true;
}

bool Ball::destroyBrick(Sprite *it, Player *player, int currentLevel)
{
	if (it->getBrickType() == 13 || it->getBrickType() == 14)
	{
		if (it->getBrickType() == 13 && it->getHitLeft() == 1)
		{
			player->setScore(player->score() + 100 * currentLevel);
			return true;
		}
		else
			it->animate(true);

		if (it->getBrickType() == 13)
			it->setHitLeft(it->getHitLeft() - 1);

		return false;
	}
	else
	{
		player->setScore(player->score() + getPoints(it->getBrickType()));
		return true;
	}
}

Vec2i Ball::checkCollision(std::vector<Sprite *> &levelBricks, Player *player, int currentLevel)
{
	// auto = std::vector<Sprite*>::iterator
	// pour chaque brique
	for (auto it = levelBricks.begin(); it != levelBricks.end(); it++)
	{
		// on calcule les bornes
		int xmin = (*it)->pos().x;
		int ymin = (*it)->pos().y;
		int xmax = (*it)->pos().x + (*it)->size().x;
		int ymax = (*it)->pos().y + (*it)->size().y;

		int ballxMiddle = m_pos.x + (m_size.x / 2);
		int ballyMiddle = m_pos.y + (m_size.y / 2);

		// la ball est dans les bornes ?
		if ((ballxMiddle > xmin && ballxMiddle < xmax) //la balle est dans les bornes x de la brique ?
			&&
			((ballyMiddle > ymin &&
			  m_pos.y < ymax &&
			  force().y <= 0.0f) //touché depuis le bas de la brique
			 ||
			 (ballyMiddle < ymax &&
			  m_pos.y + m_size.y > ymin &&
			  force().y >= 0.0f))) //touché depuis le haut de la brique
		{

			// on fait rebondir dans le sens des y
			setForce({force().x, -1 * force().y});

			if (destroyBrick(*it, player, currentLevel) == true)
			{
				Vec2i brickPos = (*it)->pos();
				levelBricks.erase(it);
				return brickPos;
			}

			return {-1, -1};
		}
		else if ((ballyMiddle > ymin && ballyMiddle < ymax) //la balle est dans les bornes y de la brique ?
				 &&
				 ((ballxMiddle > xmin &&
				   m_pos.x < xmax &&
				   force().x <= 0.0f) //touché depuis la droite de la brique
				  ||
				  (ballxMiddle < xmax &&
				   m_pos.x + m_size.x > xmin &&
				   force().x >= 0.0f))) //touché depuis la gauche de la brique
		{

			// on fait rebondir dans le sens des x
			setForce({-1 * force().x, force().y});

			if (destroyBrick(*it, player, currentLevel) == true)
			{
				Vec2i brickPos = (*it)->pos();
				levelBricks.erase(it);
				return brickPos;
			}

			return {-1, -1};
		}
	}
	return {-1, -1};
}