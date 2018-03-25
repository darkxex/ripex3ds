// Cheuble's sound class

#pragma once
#include <3ds.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
class song {
public:
	u32 dataSize = 0;
	ndspWaveBuf waveBuf;
	u8* data = NULL;
	int chnl = 0;
};
class sound
{
public:
	bool intro;
	sound(string path, int channel, bool toloop, bool _intro);
	sound(string path, int channel = 1, bool toloop = true);
	~sound();
	void play();
	void stop();
	song loadWav(std::string path, int channel, bool toloop);
	song song1;
	song song2;

};
