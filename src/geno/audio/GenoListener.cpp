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

#include "GenoAL.h"

#include "GenoListener.h"

GenoListener::GenoListener() :
	position(GenoVector3f()),
	velocity(GenoVector3f()),
	at(0, 0, -1),
	up(0, 1, 0),
	gain(1) {}

GenoListener::GenoListener(GenoVector3f position, GenoVector3f velocity, GenoVector3f at, GenoVector3f up, float gain) :
	position(position),
	velocity(velocity),
	at(at),
	up(up),
	gain(gain) {}

void GenoListener::setActive() {
	alListener3f(AL_POSITION, position.x(), position.y(), position.z());
		
	alListener3f(AL_VELOCITY, velocity.x(), velocity.y(), velocity.z());

	float orientation[] = { at.x(), at.y(), at.z(), up.x(), up.y(), up.z() };
	alListenerfv(AL_ORIENTATION, orientation);

	alListenerf(AL_GAIN, gain);
}

void GenoListener::setPosition(GenoVector3f position) {
	this->position = position;
}

void GenoListener::setVelocity(GenoVector3f velocity) {
	this->velocity = velocity;
}

void GenoListener::setOrientation(GenoVector3f at, GenoVector3f up) {
	this->at = at;
	this->up = up;
}

void GenoListener::setGain(float gain) {
	this->gain = gain;
}

GenoListener::~GenoListener() {}