#include <limits>

#include "util.hpp"

void util::init_pairs(){
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
}

int util::value_of(const game::match_type& match){
	for(
		std::size_t column = 0;
		column < match.first.size();
		column++
	){
		for(
			std::size_t row = 0;
			row < std::tuple_size<
				decltype(match.first)::value_type
			>::value;
			row++
		){
			for(
				auto& direction: std::array<std::array<signed, 2>, 4>(
					{
						{
							{-1, 1},
							{0, 1},
							{1, 1},
							{1, 0}
						}
					}
				)
			){
				if(
					!(direction[0] < 0 && column < 3)
				 && !(direction[0] > 0 && column >= match.first.size() - 3)
				 && !(direction[1] < 0 && row < 3)
				 && !(direction[1] > 0 && row >= std::tuple_size<
				        decltype(match.first)::value_type
				    >::value - 3)
				){
					if(
						match.first[column][row]
					 == game::token_type::empty
					 || match.first[column][row]
					 == game::token_type::neutral
					) break;
					else for(unsigned i = 1; i < 4; i++){
						if(
							match.first[column][row]
						 != match.first[
								column + (direction[0] * (signed)i)
							][
								row + (direction[1] * (signed)i)
							]
						) break;
						else if(i == 3) return match.first[column][row]
							== game::token_type::white
							 ? std::numeric_limits<int>::max()
							 : std::numeric_limits<int>::min();
					}
				}
			}
		}
	}
	return 0;
}

bool util::input(game::match_type& match, int ch){
	switch(ch){
	case '1':
		game::advance(match, 0);
		return true;
	case '2':
		game::advance(match, 1);
		return true;
	case '3':
		game::advance(match, 2);
		return true;
	case '4':
		game::advance(match, 3);
		return true;
	case '5':
		game::advance(match, 4);
		return true;
	case '6':
		game::advance(match, 5);
		return true;
	case '7':
		game::advance(match, 6);
		return true;
	default:
		return false;
	}
}

void util::print(const game::match_type& match){
	for(
		std::size_t row
	  = std::tuple_size<game::board_type::value_type>::value - 1;
		row < std::tuple_size<game::board_type::value_type>::value;
		row--
	){
		for(
			std::size_t column = 0;
			column < match.first.size();
			column++
		){
			switch(match.first[column][row]){
			case game::token_type::empty:
				addch('.');
				break;
			case game::token_type::neutral:
				addch('#');
				break;
			case game::token_type::white:
				attron(COLOR_PAIR(1));
				addch('#' | A_BOLD);
				attroff(COLOR_PAIR(1));
				break;
			case game::token_type::colored:
				attron(COLOR_PAIR(2));
				addch('#' | A_BOLD);
				attroff(COLOR_PAIR(2));
				break;
			}
		}
		addch('\n');
	}
}
