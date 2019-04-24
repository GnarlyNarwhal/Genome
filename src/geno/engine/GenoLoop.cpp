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

#include "../thread/GenoTime.h"

#include "GenoLoop.h"

GenoLoop::GenoLoop(const GenoLoopCreateInfo & info) :
	sanicLoop(false),
	callbackCount(1 + info.numSubLoops),
	looping(false),
	deltas(new double[callbackCount]),
	deltaScales(new double[callbackCount]),
	fps(new uint32[callbackCount]),
	millisPerFrames(new double[callbackCount]),
	callbacks(new GenoLoopCallback[callbackCount]) {

	fps[0] = 0;
	deltas[0] = 0;
	deltaScales[0] = info.deltaScale;
	if (info.targetFps != 0)
		millisPerFrames[0] = 1000 / info.targetFps;
	else {
		sanicLoop = true;
		millisPerFrames[0] = 0;
	}
	callbacks[0] = info.callback;

	for (uint32 i = 1; i < callbackCount; ++i) {
		fps[i] = 0;
		deltas[i] = 0;
		deltaScales[i] = info.subLoops[i - 1].deltaScale;
		if (info.subLoops[i - 1].targetFps != 0)
			millisPerFrames[i] = 1000 / info.subLoops[i - 1].targetFps;
		else
			millisPerFrames[i] = 0;
		callbacks[i] = info.subLoops[i - 1].callback;
	}
}

void GenoLoop::start() {
	uint32 * frames = new uint32[callbackCount];
	double * pastTimes = new double[callbackCount + 1];
	double * truePastTimes = new double[callbackCount + 1];
	double curTime = 0;

	for (uint32 i = 0; i < callbackCount; ++i) {
		frames[i] = 0;
		pastTimes[i] = GenoTime::getTime(milliseconds);
	}
	pastTimes[callbackCount] = GenoTime::getTime(milliseconds);

	looping = true;
	while (looping) {
		curTime = GenoTime::getTime(milliseconds);
		if (curTime - pastTimes[0] > 1000) {
			for (uint32 i = 0; i < callbackCount; ++i) {
				fps[i] = frames[i];
				frames[i] = 0;
			}
			pastTimes[0] += 1000;
		}
		for (uint32 i = 0; i < callbackCount; ++i) {
			if (curTime - pastTimes[i + 1] >= millisPerFrames[i]) {
				callbacks[i]();
				deltas[i] = (curTime - truePastTimes[i + 1]) * deltaScales[i];
				pastTimes[i + 1] += millisPerFrames[i];
				truePastTimes[i + 1] = curTime;
				++frames[i];
			}
		}
		if (!sanicLoop)
			GenoTime::sleepUntil(pastTimes[1] + millisPerFrames[0]);
	}
	
	delete [] truePastTimes;
	delete [] pastTimes;
	delete [] frames;
}

void GenoLoop::stop() {
	looping = false;
}

double GenoLoop::getDelta(uint32 loopIndex) {
	return deltas[loopIndex];
}

uint32 GenoLoop::getFPS(uint32 loopIndex) {
	return fps[loopIndex];
}

void GenoLoop::setFPS(double fps, uint32 loopIndex) {
	millisPerFrames[loopIndex] = 1000 / fps;
}

void GenoLoop::setDeltaScale(double deltaScale, uint32 loopIndex) {
	deltaScales[loopIndex] = deltaScale;
}

void GenoLoop::setCallback(GenoLoopCallback callback, uint32 loopIndex) {
	callbacks[loopIndex] = callback;
}

GenoLoop::~GenoLoop() {
	delete [] deltas;
	delete [] deltaScales;
	delete [] millisPerFrames;
	delete [] callbacks;
}