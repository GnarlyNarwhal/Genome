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

#include <iostream>

#include <AL\al.h>

#include "GenoAudioSource.h"

GenoAudioSource::GenoAudioSource() {
	alGenSources(1, &source);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_DIRECTION, 0, 0, 0);
}

GenoAudioSource::GenoAudioSource(GenoAudioBuffer * buffer) {
	alGenSources(1, &source);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_DIRECTION, 0, 0, 0);
	alSourcei(source, AL_BUFFER, buffer->getBuffer());
}

void GenoAudioSource::setBuffer(GenoAudioBuffer * buffer) {
	alSourcei(source, AL_BUFFER, buffer->getBuffer());
}

void GenoAudioSource::play() {
	alSourcePlay(source);
}

void GenoAudioSource::stop() {
	alSourceStop(source);
}

void GenoAudioSource::pause() {
	alSourcePause(source);
}

void GenoAudioSource::loop(bool loop) {
	alSourcei(source, AL_LOOPING, loop);
}

GenoAudioSource::~GenoAudioSource() {
	alDeleteSources(1, &source);
}
