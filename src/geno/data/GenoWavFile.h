#ifndef GNARLY_GENOME_WAVFILE
#define GNARLY_GENOME_WAVFILE

#include "../GenoInts.h"

class GenoWavFile {
	private:
		uint32 format, sampleRate, size;
		uint8 * data;

	public:
		GenoWavFile(const char * path);
		uint32 getFormat();
		uint32 getSampleRate();
		uint32 getSize();
		uint8 * getData();
		~GenoWavFile();
};

#define GNARLY_GENOME_WAVFILE_FORWARD
#endif // GNARLY_GENOME_WAVFILE