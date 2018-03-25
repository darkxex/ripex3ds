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
#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

/* This file is part of Anim3DS!

> Anim3DS is a RipEx Fork with UI and more stuff. 

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

// Libraries Needed
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sys/stat.h>

// SceneManager to go into scenes (We can create splashscreen, titlescreen, gamescreen, endscreen...)
#include "SceneManager.h"

// Settings: We can configure everything from there easily
#include "Settings.h"
#include "pp2d/pp2d.h"

int main()
{
	// We Initialize the services
	srvInit();

	httpcInit(0); // Buffer size when POST/PUT.

	// 
	aptInit();

	// Romfs
	romfsInit();

	// init pp2d environment
	pp2d_init();

	// Sound - We need to dump dsp on the console
	ndspInit();

	// 3DS Stuff (Like Battery)
	ptmuInit();

	// Wifi

	acInit();

	//Creating folders for our homebrew's save. Just rename the last to your Homebrew Name
	mkdir("/3ds", 0777);
	mkdir("/3ds/data", 0777);
	mkdir("/3ds/data/Anim3DS", 0777);

	// set the screen background color
	pp2d_set_screen_color(GFX_TOP, ABGR8(255, 0, 0, 0));
	pp2d_set_screen_color(GFX_BOTTOM, ABGR8(255, 0, 0, 0));
	//consoleInit(GFX_BOTTOM, NULL);

	// We initialize the scene manager. It is created with a singleton so only one instance is created.
	SceneManager::instance()->Start();

	while (aptMainLoop())
	{
		// Update: Check inputs + Draw
		SceneManager::instance()->Update();

		// Every scene is controlled by the SceneManager, so if it goes out, we exit.
		if (SceneManager::instance()->isOut())
		{
			break;
		}
	}

	// We Exit the services and end the program
	romfsExit();
	ndspExit();
	pp2d_exit();
	ptmuExit();
	acExit();
	aptExit();
	httpcExit();
	return 0;
}