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
#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include "Settings.h"

#include "sound.h"
#include "scene.h"
#include "SceneManager.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <cstddef>
#include <inttypes.h>
#include <iostream>
#include <3ds.h>
#include <Vector>
#include <cstddef>  
#include <algorithm>
#include "pp2d/pp2d.h"

class GameScreen : public Scene
{

public:

	enum MENU_TYPE 
	{ 
		MAIN,					// Main menú (Banner + 3 options)
		LAST_ANIMES,			// List of latest animes
		ANIME_SELECTED,			// Choosing an anime (You can d-pad up and down for changing the episode)
		ANIME_READY_TO_WATCH,	// Just press A for watching the anime
		SEARCHING,				// Search menu (By name and by url)
		SELECTING_SEARCH,		// Choose by 3 best searched animes
		FAVOURITES				// Choose from favourites
	};

public:

	GameScreen(std::string * last);				// Constructor
	~GameScreen();								// Destructor
	void Start(std::string * last);				// initialize
	void Draw();								// Draw
	void CheckInputs();							// CheckInput
	void Update();								// Update

private:

	float m_offset;						// Offset for 3D
	float m_listOffset;
	Result m_internetServiceInitialized;
	sound * m_bgm, *m_sfx;				// Sounds
	std::string content = "";			// URL stuff
	std::string chapterSelected = "";	
	std::string chapterToShow = "";
	std::vector<std::string> arraychapter;
	std::string m_debugString = "";
	std::string * m_lastWatched;
	int arrayselect;
	int arraycount;
	int off;
	MENU_TYPE menu_status;
	touchPosition touch;
	Result ret = 0;
	bool m_haveInternet;
	bool m_initializedList;
	bool m_goingOut;
	bool m_fromSearching;
	int m_chapterNumber;
	int m_chapterMaxNumber;
	int m_debugValue;
private:

	Result http_download(const char *url);
	void InitializeViewer();
	void ToggleWifi();
	void InitAnimeList();
	void OtherEpisode(bool prev, bool go_to_one = false);
	void SearchByName(std::string mybuf);
	void SearchByURL(std::string mybuf);
	void SearchLastWatched(std::string mybuf);
};

#endif