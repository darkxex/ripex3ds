/* This file is part of Anim3DS!

Copyright (C) 2017 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

#pragma once

// Screen size: Top Screen = 400x240; Bottom Screen: 320x240
#define TOP_WIDTH 400
#define BOTTOM_WIDTH 320
#define HEIGHT 240

// Version of our Homebrew and if we want to set a debugmode for us. We can disable it from here.
#define VERSION "1.0"
#define DEBUGMODE false

// Color definition
#define C_BLACK RGBA8(0, 0, 0, 255)
#define C_WHITE RGBA8(255, 255, 255, 255)
#define C_GREY RGBA8(127, 127, 127, 255)
#define C_RED RGBA8(255, 0, 0, 255)
#define C_BLUE RGBA8(0, 0, 255, 255)
#define C_SECOND_BLUE RGBA8(0, 102, 173, 255)
#define C_SEMI_RED RGBA8(255, 0, 0, 120) 

// Number of chapters shown
#define CHAPTERSHOWN 9