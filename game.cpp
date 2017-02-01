#include <algorithm>
#include <ncurses.h>

#include "game.hpp"

std::vector<game::move_type> game::valid_moves(
	const game::match_type& match
){
	std::vector<game::move_type> moves = {};
	for(
		game::move_type column = 0;
		column < match.first.size();
		column++
	){
		if(
			std::find(
				match.first.at(column).begin(),
				match.first.at(column).end(),
				game::token_type::empty
			) != match.first.at(column).end()
		){
			moves.push_back(column);
		}
	}
	return moves;
}

bool game::advance(
	game::match_type& match,
	move_type move
){
	auto i = std::find(
		match.first.at(move).begin(),
		match.first.at(move).end(),
		game::token_type::empty
	);
	if(i != match.first.at(move).end()){
		switch(match.second){
		case game::turn_type::white:
			*i = game::token_type::white;
			match.second = game::turn_type::colored;
			break;
		case game::turn_type::colored:
			*i = game::token_type::colored;
			match.second = game::turn_type::white;
			break;
		}
		return true;
	}
	else return false;
}
