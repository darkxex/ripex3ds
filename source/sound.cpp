// Cheuble's sound class

#include "sound.h"

sound::sound(string path, int channel, bool toloop, bool _intro)
{
	intro = _intro;
	if (_intro) {
		song1 = loadWav(path, channel, false);
		song2 = loadWav(path, channel, true);
	}
	else{ song1 = loadWav(path, channel, toloop); }
}

sound::sound(string path, int channel, bool toloop)
{
	song1 = loadWav(path, channel, toloop);
}

sound::~sound()
{
	song1.dataSize =0;
	song1.data = NULL;
	song1.waveBuf.data_vaddr = 0;
	song1.waveBuf.nsamples = 0;
	song1.waveBuf.looping = false;
	song1.waveBuf.status = 0;
	if (intro) {
		song2.dataSize = 0;
		song2.data = NULL;
		song2.waveBuf.data_vaddr = 0;
		song2.waveBuf.nsamples = 0;
		song2.waveBuf.looping = false;
		song2.waveBuf.status = 0;

	}
	ndspChnWaveBufClear(song1.chnl);
}

void sound::play()
{
	if (intro) {
		DSP_FlushDataCache(song1.data, song1.dataSize);
		ndspChnWaveBufAdd(song1.chnl, &song1.waveBuf);
		DSP_FlushDataCache(song2.data, song2.dataSize);
		ndspChnWaveBufAdd(song2.chnl, &song2.waveBuf);
	}
	else{
		DSP_FlushDataCache(song1.data, song1.dataSize);
		ndspChnWaveBufAdd(song1.chnl, &song1.waveBuf);
	}
}

void sound::stop()
{
	ndspChnWaveBufClear(song1.chnl);
	ndspChnWaveBufClear(song2.chnl);
}

song sound::loadWav(std::string path,int channel,bool toloop)
{
	song snd;
	u32 sampleRate;
	u16 channels;
	u16 bitsPerSample;
	ndspSetOutputMode(NDSP_OUTPUT_STEREO);
	ndspSetOutputCount(2); // Num of buffers

						   // Reading wav file
	FILE* fp = fopen(path.c_str(), "rb");

	if (!fp)
	{
		printf("Could not open the example.wav file.\n");
	}
	char signature[4];

	fread(signature, 1, 4, fp);

	if (signature[0] != 'R' &&
		signature[1] != 'I' &&
		signature[2] != 'F' &&
		signature[3] != 'F')
	{
		printf("Wrong file format.\n");
		fclose(fp);
	}

	fseek(fp, 0, SEEK_END);
	snd.dataSize = ftell(fp);
	fseek(fp, 22, SEEK_SET);
	fread(&channels, 2, 1, fp);
	fseek(fp, 24, SEEK_SET);
	fread(&sampleRate, 4, 1, fp);
	fseek(fp, 34, SEEK_SET);
	fread(&bitsPerSample, 2, 1, fp);

	if (snd.dataSize == 0 || (channels != 1 && channels != 2) ||
		(bitsPerSample != 8 && bitsPerSample != 16))
	{
		printf("Corrupted wav file.\n");
		fclose(fp);
	}

	// Allocating and reading samples
	snd.data = static_cast<u8*>(linearAlloc(snd.dataSize));
	fseek(fp, 44, SEEK_SET);
	fread(snd.data, 1, snd.dataSize, fp);
	fclose(fp);

	fseek(fp, 44, SEEK_SET);
	fread(snd.data, 1, snd.dataSize, fp);
	fclose(fp);
	snd.dataSize /= 2;
	// Find the right format
	u16 ndspFormat;

	if (bitsPerSample == 8)
	{
		ndspFormat = (channels == 1) ?
			NDSP_FORMAT_MONO_PCM8 :
			NDSP_FORMAT_STEREO_PCM8;
	}
	else
	{
		ndspFormat = (channels == 1) ?
			NDSP_FORMAT_MONO_PCM16 :
			NDSP_FORMAT_STEREO_PCM16;
	}

	ndspChnReset(channel);
	ndspChnSetInterp(channel, NDSP_INTERP_NONE);
	ndspChnSetRate(channel, float(sampleRate));
	ndspChnSetFormat(channel, ndspFormat);

	// Create and play a wav buffer
	std::memset(&snd.waveBuf, 0, sizeof(snd.waveBuf));

	snd.waveBuf.data_vaddr = reinterpret_cast<u32*>(snd.data);
	snd.waveBuf.nsamples = snd.dataSize / (bitsPerSample >> 3);
	snd.waveBuf.looping = toloop;
	snd.waveBuf.status = NDSP_WBUF_FREE;
	snd.chnl = channel;
	return snd;
}


