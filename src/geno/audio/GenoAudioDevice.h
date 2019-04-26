/*******************************************************************************
 *
 * Copyright (c) 2018 Gnarly Narwhal
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

#ifndef GNARLY_GENOME_AUDIO_DEVICE
#define GNARLY_GENOME_AUDIO_DEVICE

#include "../GenoInts.h"
#include "GenoAL.h"
#include "../engine/GenoEngine.h"

class GenoAudioOutputDevice {
	private:
		GenoAudioOutputDevice(ALCdevice * device, const char * name);
		ALCdevice * device;
		ALCcontext * context;
		char * name;

	public:
		void setActive();
		const char * getName();
		~GenoAudioOutputDevice();

	friend class GenoAudioDevices;
};

class GenoAudioDevices final {
	private:
		static int32 numOutputDevices;
		static GenoAudioOutputDevice ** outputDevices;

		GenoAudioDevices();
		~GenoAudioDevices();

		static void init();
		static void cleanup();
	public:
		static uint32 getNumOutputDevices();
		static GenoAudioOutputDevice * getDefaultOutputDevice();
		static GenoAudioOutputDevice * getOutputDevice(uint32 outputDevice);

	friend class GenoEngine;
};

#define GNARLY_GENOME_AUDIO_DEVICE_FORWARD
#endif // GNARLY_GENOME_AUDIO_DEVICE