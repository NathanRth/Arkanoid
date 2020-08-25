#include "object.h"

Object::Object(Vec2i pos, Vec2i size,bool collider):
    m_pos(pos), m_size(size), has_collider(collider)
{

}