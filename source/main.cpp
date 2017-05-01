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


	gfxFlushBuffers();

	do {
		ret = httpcOpenContext(&context, HTTPC_METHOD_GET, url, 1);

		gfxFlushBuffers();

		// This disables SSL cert verification, so https:// will be usable
		ret = httpcSetSSLOpt(&context, SSLCOPT_DisableVerify);

		gfxFlushBuffers();

		// Enable Keep-Alive connections (on by default, pending ctrulib merge)
		// ret = httpcSetKeepAlive(&context, HTTPC_KEEPALIVE_ENABLED);
		// printf("return from httpcSetKeepAlive: %"PRId32"\n",ret);
		// gfxFlushBuffers();

		// Set a User-Agent header so websites can identify your application
		ret = httpcAddRequestHeaderField(&context, "User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.81 Safari/537.36");

		gfxFlushBuffers();

		// Tell the server we can support Keep-Alive connections.
		// This will delay connection teardown momentarily (typically 5s)
		// in case there is another request made to the same server.
		ret = httpcAddRequestHeaderField(&context, "Connection", "Keep-Alive");

		gfxFlushBuffers();

		ret = httpcBeginRequest(&context);
		if(ret!=0){
			httpcCloseContext(&context);
			if(newurl!=NULL) free(newurl);
			return ret;
		}

		ret = httpcGetResponseStatusCode(&context, &statuscode);
		if(ret!=0){
			httpcCloseContext(&context);
			if(newurl!=NULL) free(newurl);
			return ret;
		}

		if ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308)) {
			if(newurl==NULL) newurl = (char*) malloc(0x1000); // One 4K page for new URL
			if (newurl==NULL){
				httpcCloseContext(&context);
				return -1;
			}
			ret = httpcGetResponseHeader(&context, "Location", newurl, 0x1000);
			url = newurl; // Change pointer to the url that we just learned
			printf("redirecting to url: %s\n",url);
			httpcCloseContext(&context); // Close this context before we try the next
		}
	} while ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308));

	if(statuscode!=200){

		httpcCloseContext(&context);
		if(newurl!=NULL) free(newurl);
		return -2;
	}

	// This relies on an optional Content-Length header and may be 0
	ret=httpcGetDownloadSizeState(&context, NULL, &contentsize);
	if(ret!=0){
		httpcCloseContext(&context);
		if(newurl!=NULL) free(newurl);
		return ret;
	}


	gfxFlushBuffers();

	// Start with a single page buffer
	buf = (u8*)malloc(0x1000);
	if(buf==NULL){
		httpcCloseContext(&context);
		if(newurl!=NULL) free(newurl);
		return -1;
	}

	do {
		// This download loop resizes the buffer as data is read.
		ret = httpcDownloadData(&context, buf+size, 0x1000, &readsize);
		size += readsize;
		if (ret == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING){
				lastbuf = buf; // Save the old pointer, in case realloc() fails.
				buf = (u8*) realloc(buf, size + 0x1000);
				if(buf==NULL){
					httpcCloseContext(&context);
					free(lastbuf);
					if(newurl!=NULL) free(newurl);
					return -1;
				}
			}
	} while (ret == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

	if(ret!=0){
		httpcCloseContext(&context);
		if(newurl!=NULL) free(newurl);
		free(buf);
		return -1;
	}

	// Resize the buffer back down to our actual final size
	lastbuf = buf;
	buf = (u8*) realloc(buf, size);
	if(buf==NULL){ // realloc() failed.
		httpcCloseContext(&context);
		free(lastbuf);
		if(newurl!=NULL) free(newurl);
		return -1;
	}

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


 consoleSelect(&bottomScreen);
 cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
       cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
   cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
        cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;

	// Try the following for redirection to the above URL.
	// ret=http_download("http://tinyurl.com/hd8jwqx");

	gfxFlushBuffers();


    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

u32 kDown = hidKeysDown();
         consoleSelect(&bottomScreen);

if ( kDown & KEY_RIGHT  ){

        if (arrayselect < arraychapter.size() - 1)
       { consoleClear();
         arrayselect++;
         cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
     cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
        cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
           cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;



}
       	}

       	if ( kDown & KEY_LEFT){

        if (arrayselect > 0 )
       { consoleClear();
       arrayselect--;
       cout << "\x1b[47;30mUse las flechas para elegir.\x1b[0m" << endl;
       cout << "\x1b[47;30mPresiona A para lanzar el episodio.\x1b[0m" << endl;
             cout <<  arrayselect << "/" <<  arraychapter.size() - 1<< endl;
                      cout <<"Nombre: \n" << arraychapter[arrayselect].substr(arraychapter[arrayselect].rfind("/")+1) << endl;
cout << "Enlace: \n" << arraychapter[arrayselect]  << endl;


}
       	}




         if(hidKeysDown() & KEY_A){
                consoleClear();
             ret=http_download(arraychapter[arrayselect].c_str());

     int val1=    content.find("gdrive");
     int val2 = content.find('"',val1);

       string gdrive = content.substr(val1,val2 - val1);
       gdrive = "http://s3.animeflv.com/check.php?server=" + gdrive;



content = "";
ret=http_download(gdrive.c_str());
val1 = content.find("http");
val2 = content.find('"',val1);

gdrive = content.substr(val1,val2 - val1);
 consoleSelect(&bottomScreen);
cout << gdrive << endl;
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
