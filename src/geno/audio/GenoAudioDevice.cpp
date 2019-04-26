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

#include <iostream>
#include <cstring>

#include "GenoAudioDevice.h"

GenoAudioOutputDevice::GenoAudioOutputDevice(ALCdevice * device, const char * name) {
	this->device = device;
	context = alcCreateContext(device, 0);
	int32 nameLength = strlen(name);
	this->name = new char[nameLength + 1];
	strcpy(this->name, name);
}

void GenoAudioOutputDevice::setActive() {
	alcMakeContextCurrent(context);
}

const char * GenoAudioOutputDevice::getName() {
	return name;
}

GenoAudioOutputDevice::~GenoAudioOutputDevice() {
	alcDestroyContext(context);
	alcCloseDevice(device);
}

int32 GenoAudioDevices::numOutputDevices = 0;
GenoAudioOutputDevice ** GenoAudioDevices::outputDevices = 0;

void GenoAudioDevices::init() {
	bool enumOk = alcIsExtensionPresent(0, "ALC_ENUMERATION_EXT");
	if (enumOk) {
		numOutputDevices = 0;
		const char * devices = alcGetString(0, ALC_DEVICE_SPECIFIER);
		const char * loop = devices;
		while (*loop) {
			++numOutputDevices;
			loop += strlen(loop) + 1;
		}
		outputDevices = new GenoAudioOutputDevice*[numOutputDevices];
		loop = devices;
		for (int32 i = 0; i < numOutputDevices; ++i) {
			outputDevices[i] = new GenoAudioOutputDevice(alcOpenDevice(loop), loop);
			loop += strlen(loop) + 1;
		}
	}
	else {
		ALCdevice * device = alcOpenDevice(0);
		if(device) {
			numOutputDevices = 1;
			outputDevices = new GenoAudioOutputDevice*[1] { new GenoAudioOutputDevice(device, alcGetString(device, ALC_DEVICE_SPECIFIER)) };
		}
		else {
			numOutputDevices = 0;
			outputDevices = 0;
		}
	}
}

uint32 GenoAudioDevices::getNumOutputDevices() {
	return numOutputDevices;
}

GenoAudioOutputDevice * GenoAudioDevices::getDefaultOutputDevice() {
	return outputDevices[0];
}

GenoAudioOutputDevice * GenoAudioDevices::getOutputDevice(uint32 outputDevice) {
	if(outputDevice >= 0 && outputDevice < numOutputDevices)
		return outputDevices[outputDevice];
	else
		return 0;
}

void GenoAudioDevices::cleanup() {
	for (int32 i = 0; i < numOutputDevices; ++i)
		delete outputDevices[i];
	delete [] outputDevices;
}

GenoAudioDevices::GenoAudioDevices() {}
GenoAudioDevices::~GenoAudioDevices() {}