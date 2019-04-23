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

#include "GenoMonitor.h"

GenoVideoMode::GenoVideoMode(const GLFWvidmode & videoMode) :
	width(videoMode.width),
	height(videoMode.height),
	redBits(videoMode.redBits),
	greenBits(videoMode.greenBits),
	blueBits(videoMode.blueBits),
	refreshRate(videoMode.refreshRate) {}

int32 GenoVideoMode::getWidth() const {
	return width;
}

int32 GenoVideoMode::getHeight() const {
	return height;
}

GenoVector2i GenoVideoMode::getDimensions() const {
	return { width, height };
}

int32 GenoVideoMode::getRedBits() const {
	return redBits;
}

int32 GenoVideoMode::getGreenBits() const {
	return greenBits;
}

int32 GenoVideoMode::getBlueBits() const {
	return blueBits;
}

GenoVector3i GenoVideoMode::getBitDepth() const {
	return { redBits, greenBits, blueBits };
}

int32 GenoVideoMode::getRefreshRate() const {
	return refreshRate;
}

GenoVideoMode::~GenoVideoMode() {}

GenoMonitor::GenoMonitor(GLFWmonitor * monitor) :
	monitor(monitor) {
	int32 count;
	const GLFWvidmode * vidmodes = glfwGetVideoModes(monitor, &count);
	numVideoModes = count;
	videoModes = new GenoVideoMode*[numVideoModes];
	for (uint32 i = 0; i < count; ++i)
		videoModes[i] = new GenoVideoMode(vidmodes[i]);

	GenoVideoMode * videoMode = videoModes[numVideoModes - 1];
	width  = videoMode->getWidth();
	height = videoMode->getHeight();
	glfwGetMonitorPos(monitor, &x, &y);
	int32 physicalWidth;
	int32 physicalHeight;
	glfwGetMonitorPhysicalSize(monitor, &physicalWidth, &physicalHeight);
	sizeX = physicalWidth;
	sizeY = physicalHeight;
	name = glfwGetMonitorName(monitor);
}

int32 GenoMonitor::getX() const {
	return x;
}

int32 GenoMonitor::getY() const {
	return y;
}

GenoVector2i GenoMonitor::getPosition() const {
	return { x, y };
}

int32 GenoMonitor::getWidth() const {
	return width;
}

int32 GenoMonitor::getHeight() const {
	return height;
}

GenoVector2i GenoMonitor::getDimensions() const {
	return { width, height };
}

double GenoMonitor::getPhysicalWidth(double scale) const {
	return sizeX / scale;
}

double GenoMonitor::getPhysicalHeight(double scale) const {
	return sizeY / scale;
}

GenoVector2d GenoMonitor::getPhysicalDimensions(double scale) const {
	return { sizeX / scale, sizeY / scale };
}

double GenoMonitor::getPhysicalDiagonal(double scale) const {
	return sqrt(sizeX * sizeX + sizeY * sizeY) / scale;
}
const char * GenoMonitor::getName() const {
	return name;
}

uint32 GenoMonitor::getNumVideoModes() const {
	return numVideoModes;
}

GenoVideoMode * GenoMonitor::getDefaultVideoMode() const {
	return videoModes[numVideoModes - 1];
}

GenoVideoMode * GenoMonitor::getVideoMode(uint32 num) const {
	return videoModes[num];
}

GenoMonitor::~GenoMonitor() {
	for (uint32 i = 0; i < numVideoModes; ++i)
		delete videoModes[i];
	delete [] videoModes;
}

uint32 GenoMonitors::numMonitors = 0;
GenoMonitor ** GenoMonitors::monitors = 0;

uint32 GenoMonitors::getNumMonitors() {
	return numMonitors;
}

void GenoMonitors::init() {
	int32 count;
	GLFWmonitor ** glfwMonitors = glfwGetMonitors(&count);
	numMonitors = count;

	monitors = new GenoMonitor*[numMonitors];

	for (uint32 i = 0; i < numMonitors; ++i)
		monitors[i] = new GenoMonitor(glfwMonitors[i]);

	glfwSetMonitorCallback(monitorCallback);
}

GenoMonitor * GenoMonitors::getPrimaryMonitor() {
	return monitors[0];
}

GenoMonitor * GenoMonitors::getMonitor(uint32 num) {
	return monitors[num];
}

void GenoMonitors::cleanup() {
	for (uint32 i = 0; i < numMonitors; ++i)
		delete monitors[i];
	delete [] monitors;
}

void GenoMonitors::monitorCallback(GLFWmonitor * monitor, int32 event) {
	if (event == GLFW_DISCONNECTED) {
		bool found = false;
		for (uint32 i = 0; i < numMonitors - 1; ++i) {
			if (found)
				monitors[i] = monitors[i + 1];
			else if (monitors[i]->monitor == monitor) {
				delete monitors[i];
				monitors[i] = monitors[i + 1];
			}
		}
		if (!found)
			delete monitors[numMonitors - 1];
	}
	else {
		GenoMonitor * gMonitor = new GenoMonitor(monitor);

		GenoMonitor ** target = new GenoMonitor*[++numMonitors];

		int32 count;
		GLFWmonitor ** monitors = glfwGetMonitors(&count);

		for (uint32 i = 0; i < count; ++i) {
			bool found = false;
			for (uint32 j = 0; j < numMonitors - 1; ++j) {
				if (GenoMonitors::monitors[j]->monitor == monitors[i]) {
					found = true;
					target[i] = GenoMonitors::monitors[j];
				}
			}
			if (!found)
				target[i] = gMonitor;
		}

		delete [] GenoMonitors::monitors;
		GenoMonitors::monitors = target;
	}
}

GenoMonitors::GenoMonitors() {}
GenoMonitors::~GenoMonitors() {}