/*
  Fairy-Stockfish Random, a random mover variant playing engine derived
  from Fairy-Stockfish
  Copyright (C) 2021 Ada Joule
  Copyright (C) 2018-2022 Yohaan Nathan

  Fairy-Stockfish Random is free software: you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Fairy-Stockfish Random is distributed in the hope that it will
  be useful, but WITHOUT ANY WARRANTY; without even the implied
  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RANDOM_SELECT_H_INCLUDED
#define RANDOM_SELECT_H_INCLUDED

// C++ random selector from https://gist.github.com/cbsmith/5538174

#include <random>
#include <iterator>

template <typename RandomGenerator = std::default_random_engine>
struct RandomSelector
{
	//On most platforms, you probably want to use std::random_device("/dev/urandom")()
	RandomSelector(RandomGenerator g = RandomGenerator(std::random_device()()))
		: gen(g) {}

	template <typename Iter>
	Iter select(Iter start, Iter end) {
		std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}

	//convenience function
	template <typename Iter>
	Iter operator()(Iter start, Iter end) {
		return select(start, end);
	}

	//convenience function that works on anything with a sensible begin() and end(), and returns with a ref to the value type
	template <typename Container>
	auto operator()(const Container& c) -> decltype(*begin(c))& {
		return *select(begin(c), end(c));
	}

private:
	RandomGenerator gen;
};

extern RandomSelector<> random_selector;

#endif // #ifndef RANDOM_SELECT_H_INCLUDED