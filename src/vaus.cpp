#include "vaus.h"

Vaus::Vaus(int vaussize, Texture tex, Vec2i pos, Vec2i size, bool collider, int move) : 
	Sprite(tex, pos, size), current_size(vaussize), movingDirection(move)
{
	has_collider = collider;
}

float Vaus::moveVaus(SDL_Surface *win_surf)
{
	float first = m_pos.x;
	Vec2i move = {direction(), 0};
	m_pos = m_pos.operator+(move);
	if (m_pos.x < 0)
		m_pos.x = 0;
	else if (m_pos.x > ((win_surf->w - m_size.x)))
		m_pos.x = (win_surf->w - m_size.x);

	return (float)m_pos.x - first;
}