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
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <fstream>
#include <sstream>
#include <sys/unistd.h>
#include "SplashScreen.h"
#include "Game.h"

class SceneManager
{
public:

	enum SCENES { SPLASH, GAME };			// Scenes: Splashcreen, Gamescreen

	static SceneManager* instance();		// Property to get the singleton instance

	void setActualScene(SCENES _scene);		// Method to set a new scene (E.G: SplashScreen -> GameScreen)
	void Start();							// Method for initialization
	void Update();							// Method called every frame. It calls to scene Draw, Update and CheckInput functions
	bool isOut();							// Method that returns if we are exiting the game from scene (normal exiting)
	void exitGame();						// Method to exit the game (Out = true)
	void ReadData();						// Method for reading data from our save
	void SaveDataAndExit();					// Method that saves our data to the .sav and exits
	void SaveData();						// Method that saves our data to the .sav
private:

	SceneManager() {};  // Private so that it can  not be called
	static SceneManager* Instance;	// Singleton Instance

	std::string m_lastWatched;						// Variable saved in our .sav
	bool m_out;										// if we ended or not the program
	Scene* m_actualScene;							// Scene running
};

#endif