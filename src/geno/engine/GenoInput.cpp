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

#include "GenoEngine.h"
#include "../gl/GenoFramebuffer.h"

#include "GenoInput.h"

double GenoInput::repeatDelay = GENO_INPUT_DEFAULT_DELAY;
double GenoInput::repeatSpeed = GENO_INPUT_DEFAULT_SPEED;

uint8  GenoInput::keyStates[GLFW_KEY_LAST];
double GenoInput::keyTimes[GLFW_KEY_LAST];
double GenoInput::keyTargets[GLFW_KEY_LAST];

uint8  GenoInput::mouseButtonStates[GLFW_MOUSE_BUTTON_LAST];
double GenoInput::mouseButtonTimes[GLFW_MOUSE_BUTTON_LAST];
double GenoInput::mouseButtonTargets[GLFW_MOUSE_BUTTON_LAST];

GenoVector2d GenoInput::mouseCoords = {};

void GenoInput::update() {
	double delta = GenoEngine::getLoop()->getDelta();
	for (uint32 i = 0; i < GLFW_KEY_LAST; ++i) {
		if (keyStates[i] > GENO_INPUT_UNPRESSED)
			keyTimes[i] += delta;
		if (keyStates[i] == GENO_INPUT_RELEASED || keyStates[i] == GENO_INPUT_PRESSED)
			++keyStates[i];
		if (keyStates[i] == GENO_INPUT_REPEATED)
			keyStates[i] = GENO_INPUT_HELD;
		if (keyStates[i] == GENO_INPUT_HELD && keyTimes[i] >= keyTargets[i]) {
			keyStates[i] = GENO_INPUT_REPEATED;
			keyTargets[i] += repeatSpeed;
		}
	}
	for (uint32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
		if (mouseButtonStates[i] > GENO_INPUT_UNPRESSED)
			mouseButtonTimes[i] += delta;
		if (mouseButtonStates[i] == GENO_INPUT_RELEASED || mouseButtonStates[i] == GENO_INPUT_PRESSED)
			++mouseButtonStates[i];
		if (mouseButtonStates[i] == GENO_INPUT_REPEATED)
			mouseButtonStates[i] = GENO_INPUT_HELD;
		if (mouseButtonStates[i] == GENO_INPUT_HELD && mouseButtonTimes[i] >= mouseButtonTargets[i]) {
			mouseButtonStates[i] = GENO_INPUT_REPEATED;
			mouseButtonTargets[i] += repeatSpeed;
		}
	}
}

void GenoInput::setRepeatSpeed(double speed) {
	GenoInput::repeatSpeed = speed;
}

void GenoInput::setRepeatDelay(double delay) {
	GenoInput::repeatDelay = delay;
}

void GenoInput::setRepeat(double delay, double speed) {
	GenoInput::repeatDelay = delay;
	GenoInput::repeatSpeed = speed;
}

uint8 GenoInput::getKeyState(uint16 key) {
	return keyStates[key];
}

double GenoInput::getKeyDuration(uint16 key) {
	return keyTimes[key];
}

uint8 GenoInput::getMouseButtonState(uint8 key) {
	return mouseButtonStates[key];
}

double GenoInput::getMouseButtonDuration(uint8 key) {
	return mouseButtonTimes[key];
}

GenoVector2d GenoInput::getRawMouseCoords() {
	return mouseCoords;
}

GenoVector2f GenoInput::getMouseCoords(GenoCamera2D * camera) {
	return (GenoVector2f) mouseCoords / GenoVector2f(GenoFramebuffer::getCurrentWidth(), GenoFramebuffer::getCurrentHeight()) * camera->getDimensions() + camera->position;
}

GenoInput::GenoInput() {}
GenoInput::~GenoInput() {}

////// CALLBACKS //////

void GenoInput::keyCallback(GLFWwindow * window, int32 key, int32 scancode, int32 action, int32 mods) {
	if (key != GLFW_KEY_UNKNOWN) {
		if (action == GLFW_PRESS)
			keyStates[key] = GENO_INPUT_PRESSED;
		else if (action == GLFW_RELEASE) {
			keyStates[key] = GENO_INPUT_RELEASED;
			keyTimes[key] = 0;
			keyTargets[key] = repeatDelay;
		}
	}
}

void GenoInput::mouseButtonCallback(GLFWwindow * window, int32 button, int32 action, int32 mods) {
	if (button != GLFW_KEY_UNKNOWN) {
		if (action == GLFW_PRESS)
			mouseButtonStates[button] = GENO_INPUT_PRESSED;
		else if (action == GLFW_RELEASE) {
			mouseButtonStates[button] = GENO_INPUT_RELEASED;
			mouseButtonTimes[button] = 0;
			mouseButtonTargets[button] = repeatDelay;
		}
	}
}

void GenoInput::cursorPositionCallback(GLFWwindow * window, double x, double y) {
	mouseCoords.v[0] = x;
	mouseCoords.v[1] = y;
}