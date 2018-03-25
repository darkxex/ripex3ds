<<<<<<< HEAD
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
=======
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <iostream>
#include <3ds.h>
#include <Vector>
using namespace std;
string content = "";
Result http_download(const char *url)
{
	Result ret=0;
	httpcContext context;
	char *newurl=NULL;
	u8* framebuf_top;
	u32 statuscode=0;
	u32 contentsize=0, readsize=0, size=0;
	u8 *buf, *lastbuf;

 //programacion es mode 0
 //buscar es mode 1

	gfxFlushBuffers();
>>>>>>> afb6aca12b2f2c3c9fa29e07450550a1649680a7

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

<<<<<<< HEAD
	//Creating folders for our homebrew's save. Just rename the last to your Homebrew Name
	mkdir("/3ds", 0777);
	mkdir("/3ds/data", 0777);
	mkdir("/3ds/data/Anim3DS", 0777);
=======
		if ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308)) {
			if(newurl==NULL) newurl = (char*) malloc(0x1000); // One 4K page for new URL
			if (newurl==NULL){
				httpcCloseContext(&context);
				return -1;
			}
			ret = httpcGetResponseHeader(&context, "Location", newurl, 0x1000);
			url = newurl; // Change pointer to the url that we just learned
			//printf("redirecting to url: %s\n",url);
			httpcCloseContext(&context); // Close this context before we try the next
		}
	} while ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308));
>>>>>>> afb6aca12b2f2c3c9fa29e07450550a1649680a7

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

<<<<<<< HEAD
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
=======
     //printf("%s", buf);
     content = reinterpret_cast<char*>(buf);


	gfxFlushBuffers();

	//if(size>(240*400*3*2))size = 240*400*3*2;

	//framebuf_top = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	//memcpy(framebuf_top, buf, size);

	//gfxFlushBuffers();
	//gfxSwapBuffers();

	//framebuf_top = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	//memcpy(framebuf_top, buf, size);

	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();

	httpcCloseContext(&context);
	free(buf);
	if (newurl!=NULL) free(newurl);

	return 0;
}


int main() {
     int modeapp = 0;
  Result ret=0;
	gfxInitDefault();
	httpcInit(0); // Buffer size when POST/PUT.


PrintConsole topScreen, bottomScreen;

	//Initialize console for both screen using the two different PrintConsole we have defined
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);


	ret=http_download("http://animeflv.net/");
     int vval1= content.find("ltimos episodios");
     int vval2 = content.find("ltimos animes",vval1);

       content = content.substr(vval1,vval2 - vval1);

         int val1 = 1;
				        int val2;
				        int val0 = 0;
int arrayselect = 0;
int arraycount = 0;
vector<string> arraychapter;
consoleSelect(&topScreen);
cout << "Lista de Episodios de Hoy:" << endl;
 while(val0 != -1){
val0= content.find("/ver/",val1);
if(val0 == -1){break;}

 val1 =  content.find("/ver/",val1);
 val2 = (content.find('"',val1));
 string gdrive = "http://animeflv.net"+ content.substr(val1,val2 - val1);


arraychapter.push_back(gdrive);
cout << arraycount<< ". "<< gdrive.substr(gdrive.rfind("/")+1) << endl;
arraycount++;
val1++;
}
cout << endl<< "Buscar Serie = R" <<endl << "Lista de Ep. = L" << endl;


 consoleSelect(&bottomScreen);
 cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
       cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
   cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
        cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
//cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;

	// Try the following for redirection to the above URL.
	// ret=http_download("http://tinyurl.com/hd8jwqx");

	gfxFlushBuffers();


    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

u32 kDown = hidKeysDown();
         consoleSelect(&bottomScreen);
if (modeapp == 0)
    {if ( kDown & KEY_UP  ){

        if (arrayselect < arraychapter.size() - 1)
       { consoleClear();
         arrayselect++;
         cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
     cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
        cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
           cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
//cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;



}
       	}

       	if ( kDown & KEY_DOWN){

        if (arrayselect > 0 )
       { consoleClear();
       arrayselect--;
       cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
       cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
             cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
                      cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
//cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;


}
       	}
}



  	if ( kDown & KEY_R){

        modeapp = 1;

         consoleClear();
           cout << "Por implementar."<<endl;
       	}

  	if ( kDown & KEY_L){

        modeapp = 0;

         consoleClear();
          cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
     cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
        cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
           cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
       	}

         if(hidKeysDown() & KEY_A){
                consoleClear();
             ret=http_download(arraychapter[arrayselect].c_str());

     int val1=    content.find("ok.ru/videoembed/");
     int val2 = content.find('"',val1);

       string gdrive = content.substr(val1,val2 - val1);
       gdrive = "https://" + gdrive;



content = "";
//ret=http_download(gdrive.c_str());
//val1 = content.find(":360");
//val1 = content.find("http",val1);
//val2 = content.find('"',val1);

//gdrive = content.substr(val1,val2 - val1);
 consoleSelect(&bottomScreen);
//cout << gdrive << endl;
	// Try the following for redirection to the above URL.
	// ret=http_download("http://tinyurl.com/hd8jwqx");
consoleSelect(&topScreen);
 consoleClear();
	cout << "VIDEO EXTRAIDO: PRESIONA START PARA CONTINUAR." << endl;
APT_PrepareToStartSystemApplet(APPID_WEB);
APT_StartSystemApplet(APPID_WEB, gdrive.c_str(), 1024, 0);

	gfxFlushBuffers();

            }



        if(hidKeysDown() & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
>>>>>>> afb6aca12b2f2c3c9fa29e07450550a1649680a7
