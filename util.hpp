#pragma once

#include <ncurses.h>

#include "game.hpp"

namespace util{
	void init_pairs();
	int value_of(const game::match_type& match);
	bool input(game::match_type& match, int ch);
	void print(const game::match_type& match);
};
