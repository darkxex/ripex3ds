/* This file is part of Anime3DS!

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

#include "SplashScreen.h"

// * Constructor 
SplashScreen::SplashScreen() : Scene()
{
	Start();
}

// * Destructor
SplashScreen::~SplashScreen()
{
	m_SFX->stop();
	delete m_SFX;
	pp2d_free_texture(TEXTURE_SPRITESHEET);
	printf("Deleted Splash Screen Object");
}

// * Start - We initialize the variables
void SplashScreen::Start()
{
	m_scTimer = 0;
	m_splashOpacity = 0;
	m_sfxSplash = false;
	m_goToGame = false;
	pp2d_load_texture_png(TEXTURE_SPRITESHEET, IMG_SPRITES);
	m_SFX = new sound(SND_SFX_SPLASH, 2, false);
}

// * Draw the images every frame
void SplashScreen::Draw()
{
	// Top Screen
	pp2d_begin_draw(GFX_TOP);
	pp2d_draw_texture_part_blend(TEXTURE_SPRITESHEET, 0, 0, 0, 0, TOP_WIDTH, HEIGHT, RGBA8(255, 255, 255, m_splashOpacity));

	// Bottom Screen
	pp2d_draw_on(GFX_BOTTOM);
	pp2d_draw_texture_part_blend(TEXTURE_SPRITESHEET, 0, 0, 0, HEIGHT, BOTTOM_WIDTH, HEIGHT, RGBA8(255, 255, 255, m_splashOpacity));
	pp2d_end_draw();
}

// * Update game stuff (SplashScreen opacity)
void SplashScreen::Update()
{
	switch (m_splashOpeningState)
	{
	case OPENING:

		m_splashOpacity += 3;

		if (m_splashOpacity >= 255)
		{
			m_splashOpacity = 255;
			m_splashOpeningState = STAY;

			if (!m_sfxSplash)
			{
				m_sfxSplash = true;
				m_SFX->play();
			}
		}

		break;
	case STAY:

		m_scTimer += 5;

		if (m_scTimer >= 300)
		{
			m_splashOpeningState = ENDING;
		}

		break;
	case ENDING:

		m_splashOpacity -= 3;

		if (m_splashOpacity <= 0)
		{
			m_goToGame = true;
		}
		break;
	}

	if (m_goToGame)
	{
		GoToGame();
	}
}

// * We go to the game
void SplashScreen::GoToGame()
{
	SceneManager::instance()->setActualScene(SceneManager::GAME);
	delete(this);
}

// * We check the inputs
void SplashScreen::CheckInputs()
{
	hidScanInput();

	// Pressing select we exit
	if ((hidKeysDown() & KEY_SELECT))
	{
		SceneManager::instance()->exitGame();
	}

	if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH))
	{
		m_goToGame = true;
	}
}