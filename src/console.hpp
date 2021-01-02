/*
 * Nigel Scrabble artificial intelligence and analysis.
 * Copyright (C) 2016 by Jonah and Daniel Scheinerman
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

namespace console {

const std::string esc = "\033[";

const std::string black_fg      = esc + "30m";
const std::string red_fg        = esc + "31m";
const std::string green_fg      = esc + "32m";
const std::string yellow_fg     = esc + "33m";
const std::string blue_fg       = esc + "34m";
const std::string purple_fg     = esc + "35m";
const std::string cyan_fg       = esc + "36m";
const std::string white_fg      = esc + "37m";

const std::string black_bg      = esc + "40m";
const std::string red_bg        = esc + "41m";
const std::string green_bg      = esc + "42m";
const std::string yellow_bg     = esc + "43m";
const std::string blue_bg       = esc + "44m";
const std::string purple_bg     = esc + "45m";
const std::string cyan_bg       = esc + "46m";
const std::string white_bg      = esc + "47m";

const std::string bold_on       = esc + "1m";
const std::string bold_off      = esc + "22m";
const std::string blink_on      = esc + "5m";
const std::string blink_off     = esc + "25m";
const std::string underline_on  = esc + "4m";
const std::string underline_off = esc + "24m";
const std::string reverse_on    = esc + "7m";
const std::string reverse_off   = esc + "27m";
const std::string reset         = esc + "0m";

};

#endif
