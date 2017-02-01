#pragma once

#include <array>
#include <vector>

namespace game{
	constexpr std::size_t rows = 6,
	          columns = 7;
	
	enum class token_type{
		empty,
		neutral,
		white,
		colored
	};
	enum class turn_type{
		white,
		colored
	};	
	using board_type = std::array<
		std::array<
			token_type,
			rows
		>,
		columns
	>;
	using match_type = std::pair<
		board_type,
		turn_type
	>;
	using move_type = std::size_t;

	std::vector<move_type> valid_moves(const match_type& match);	
	bool advance(
		match_type& match,
		move_type move
	);
};
