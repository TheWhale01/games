#include "pacman.hpp"
#include "AGhost.hpp"

AGhost::AGhost(Colors::Colors const &color, point_t const &pos): _pos(pos), _state(EntityState::Normal), _color(color) {}
AGhost::~AGhost(void) {}
const point_t &AGhost::get_pos(void) const { return _pos; }
const EntityState::EntityState &AGhost::get_state(void) const { return _state; }
const Colors::Colors &AGhost::get_color(void) const { return _color; }
