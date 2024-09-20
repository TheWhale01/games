#include "pacman.hpp"
#include "AGhost.hpp"

AGhost::AGhost(void): _state(EntityState::Normal) {}
AGhost::~AGhost(void) {}
const point_t &AGhost::get_pos(void) const { return _pos; }
const EntityState::EntityState &AGhost::get_state(void) const { return _state; }
