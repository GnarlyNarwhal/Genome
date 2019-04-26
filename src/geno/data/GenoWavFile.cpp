#include <iostream>
#include <fstream>

#include "../audio/GenoAL.h"

#include "GenoWavFile.h"

#pragma pack(2)

struct GenoWavFileHeader {
	uint32 signature;
	uint32 size;
	uint32 format;
};

struct GenoWavFormatChunk {
	uint32 id;
	uint32 size;
	uint16 format;
	uint16 numChannels;
	uint32 sampleRate;
	uint32 byteRate;
	uint16 blockAlign;
	uint16 bitsPerSample;
};

struct GenoWavSubChunk {
	uint32 id;
	uint32 size;
};

GenoWavFile::GenoWavFile(const char * path) {
	std::ifstream file(path, std::ios::binary);
	if (file) {
		GenoWavFileHeader fileHeader;
		file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));

		if (fileHeader.signature == 0x46464952 && !file.eof()) {
			GenoWavFormatChunk formatChunk;
			file.read(reinterpret_cast<char *>(&formatChunk), sizeof(formatChunk));

			if (formatChunk.id == 0x20746d66 && !file.eof()) {
				GenoWavSubChunk subChunk = GenoWavSubChunk();
				subChunk.size = 0;
				do {
					file.ignore(subChunk.size);
					file.read(reinterpret_cast<char *>(&subChunk), sizeof(subChunk));
				} while (subChunk.id != 0x61746164 && !file.eof());
				if (!file.eof()) {
					data = new uint8[subChunk.size];
					file.read(reinterpret_cast<char *>(data), subChunk.size);
					if (!file.eof()) {
						size = subChunk.size;
						if (formatChunk.numChannels == 1)
							format = formatChunk.bitsPerSample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
						else
							format = formatChunk.bitsPerSample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
						sampleRate = formatChunk.sampleRate;
					}
					else
						delete [] data;
				}
			}
		}
	}
	file.close();
}

uint32 GenoWavFile::getFormat() {
	return format;
}

uint32 GenoWavFile::getSampleRate() {
	return sampleRate;
}

uint32 GenoWavFile::getSize() {
	return size;
}

uint8 * GenoWavFile::getData() {
	return data;
}

GenoWavFile::~GenoWavFile() {
	delete [] data;
}