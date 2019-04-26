/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarly Narwhal
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include "AL\al.h"

#include "GenoAudioBuffer.h"

void GenoAudioBuffer::clean() {
	if (buffer)
		alDeleteBuffers(1, &buffer);
}

GenoAudioBuffer::GenoAudioBuffer(uint32 format, uint32 size, uint8 data[], uint32 frequency) {
	clean();
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, size, frequency);
}

GenoAudioBuffer::GenoAudioBuffer(GenoWavFile * wavFile) {
	bufferData(wavFile->getFormat(), wavFile->getSize(), wavFile->getData(), wavFile->getSampleRate());
}

GenoAudioBuffer::GenoAudioBuffer(const char * path) {
	GenoWavFile * file = new GenoWavFile(path);
	loadWav(file);
	delete file;
}

void GenoAudioBuffer::bufferData(uint32 format, uint32 size, uint8 data[], uint32 frequency) {
	clean();
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, size, frequency);
}

void GenoAudioBuffer::loadWav(GenoWavFile * wavFile) {
	bufferData(wavFile->getFormat(), wavFile->getSize(), wavFile->getData(), wavFile->getSampleRate());
}

void GenoAudioBuffer::loadWav(const char * path) {
	GenoWavFile * file = new GenoWavFile(path);
	loadWav(file);
	delete file;
}

uint32 GenoAudioBuffer::getBuffer() {
	return buffer;
}

GenoAudioBuffer::~GenoAudioBuffer() {
	clean();
}