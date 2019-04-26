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

#include "../gl/GenoGL.h"
#include "GenoInput.h"
#include "GenoMonitor.h"
#include "../audio/GenoAudioDevice.h"

#include "GenoEngine.h"

namespace {
	void errorCallback(int32 code, const char * message);
}

GenoLoopCallback GenoEngine::callback = 0;
GenoLoop * GenoEngine::loop = 0;
GenoEngine::GenoEventPollFunc GenoEngine::getEvents = 0;

void GenoEngine::defaultLoop() {
	GenoInput::update();
	GenoEngine::pollEvents();
	callback();
}

bool GenoEngine::init() {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		std::cerr << "GL Framework failed to initialize!" << std::endl;
		return false;
	}

	getEvents = glfwPollEvents;

	GenoMonitors::init();
	GenoAudioDevices::init();

	return true;
}

bool GenoEngine::initGlew() {
	if (glewInit() != GLEW_NO_ERROR) {
		std::cerr << "GL Extension Wrangler failed to initialize!" << std::endl;
		return false;
	}
	
	return true;
}

void GenoEngine::setLoop(GenoLoopCreateInfo info, bool overrideDefault) {
	delete loop;

	if (!overrideDefault) {
		callback = info.callback;
		info.callback = defaultLoop;
	}

	loop = new GenoLoop(info);
}

void GenoEngine::startLoop() {
	loop->start();
}

void GenoEngine::stopLoop() {
	loop->stop();
}

void GenoEngine::destroy() {
	stopLoop();
	delete loop;
	
	GenoAudioDevices::cleanup();
	GenoMonitors::cleanup();

	glfwTerminate();
}

void GenoEngine::setSwapInterval(uint8 swapInterval) {
	glfwSwapInterval(swapInterval);
}

void GenoEngine::pollEvents() {
	getEvents();
}

void GenoEngine::setPollFunc(bool pollFunc) {
	getEvents = pollFunc ? glfwPollEvents : glfwWaitEvents;
}

GenoLoop * GenoEngine::getLoop() {
	return loop;
}

GenoEngine::GenoEngine() {}
GenoEngine::~GenoEngine() {}

namespace {
	void errorCallback(int32 code, const char * message) {
		std::cerr << "GLFW error " << code << ": " << message << std::endl;
	}
}