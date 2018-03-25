/* This file is part of Speaking Is Hard 3D!

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
#ifndef _SPLASH_SCREEN_H_
#define _SPLASH_SCREEN_H_

#include <sftd.h>
#include <sf2d.h>
#include <sfil.h>

#include "Settings.h"

#include "sound.h"
#include "scene.h"
#include "SceneManager.h"
#include "pp2d/pp2d.h"

class SplashScreen : public Scene
{

public:

	enum SPLASH_STATE { OPENING, STAY, ENDING };

	SplashScreen();						// Constructor
	~SplashScreen();

	void Start() override;
	void Draw() override;
	void CheckInputs() override;
	void Update() override;
	void GoToGame();
private:

	int m_splashOpacity, m_scTimer;
	bool m_sfxSplash, m_goToGame;
	sound * m_SFX;
	SPLASH_STATE m_splashOpeningState;
};

#endif