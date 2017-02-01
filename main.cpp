#include <limits>
#include <ncurses.h>

#include "game.hpp"
#include "util.hpp"

bool running = true;
game::match_type match = {
	{},
	game::turn_type::white
};

bool init(){
	initscr();
	noecho();
	curs_set(0);
	if(has_colors()){
		start_color();
		util::init_pairs();
	}
	else return false;
	return true;
};

bool input(){
	auto ch = getch();
	switch(ch){
	case 'q':
		running = false;
		return true;
	default:
		return util::input(match, ch);
	}
};

void print(){
	clear();
	util::print(match);
	refresh();
};

void quit(){
	endwin();
}

int main(){
	if(!init()) return 1;
	else while(running){
		print();
		while(!input());
		// TODO Remove
		if(util::value_of(match) != 0)
			running = false;
	}
	quit();
}
