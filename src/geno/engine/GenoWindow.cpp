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

#include "GenoInput.h"

#include "GenoWindow.h"

GenoWindow::GenoWindow() {}

GenoWindow * GenoWindow::create(const GenoWindowCreateInfo & info) {
	GenoWindow * ret = new GenoWindow();

	bool visible = true;
	for (uint32 i = 0; i < info.numHints; ++i) {
		uint32 index = i * 2;
		if (info.hints[index] == GLFW_VISIBLE)
			visible = info.hints[index + 1];
		else
			glfwWindowHint(info.hints[index], info.hints[index + 1]);
	}
	glfwWindowHint(GLFW_VISIBLE, false);

	GenoMonitor * monitor = info.monitor;
	GenoVideoMode * vidMode = info.videoMode;

	if (monitor == 0)
		monitor = GenoMonitors::getPrimaryMonitor();

	int32 width = info.width;
	int32 height = info.height;
	if (width == 0)
		width = monitor->getWidth() * 0.5;
	if (height == 0)
		height = monitor->getHeight() * 0.5;
	if (info.fullscreen) {
		if (vidMode == 0)
			vidMode = monitor->getDefaultVideoMode();

		glfwWindowHint(GLFW_RED_BITS,     vidMode->getRedBits());
		glfwWindowHint(GLFW_GREEN_BITS,   vidMode->getGreenBits());
		glfwWindowHint(GLFW_BLUE_BITS,    vidMode->getBlueBits());
		glfwWindowHint(GLFW_REFRESH_RATE, vidMode->getRefreshRate());
	}

	GLFWwindow * window;
	window = glfwCreateWindow(width, height, info.title, 0, 0);

	if (window == 0) {
		delete ret;
		return 0;
	}

	int32 x = 0;
	int32 y = 0;
	if (info.defaultPosition) {
		glfwGetWindowPos(window, &x, &y);
		double rx = (double) x / (double) GenoMonitors::getPrimaryMonitor()->getWidth();
		double ry = (double) y / (double) GenoMonitors::getPrimaryMonitor()->getHeight();
		x = rx * monitor->getWidth();
		y = ry * monitor->getHeight();
		glfwSetWindowPos(window, x, y);
	}
	else
		glfwSetWindowPos(window, info.x + monitor->getX(), info.y + monitor->getY());

	ret->cachedX = (double) x / (double) monitor->getWidth();
	ret->cachedY = (double) y / (double) monitor->getHeight();
	ret->cachedWidth = width;
	ret->cachedHeight = height;

	glfwGetWindowSize(window, &width, &height);

	glfwSetWindowPosCallback(window, positionCallback);
	glfwSetWindowSizeCallback(window, sizeCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowFocusCallback(window, windowFocusCallback);

	glfwSetCursorPosCallback(window, GenoInput::cursorPositionCallback);
	glfwSetKeyCallback(window, GenoInput::keyCallback);
	glfwSetMouseButtonCallback(window, GenoInput::mouseButtonCallback);

	ret->curMonitor = monitor;

	ret->x       = x;
	ret->y       = y;
	ret->width   = width;
	ret->height  = height;
	ret->window  = window;

	uint32 clearBits = GL_COLOR_BUFFER_BIT;

	if (info.depth) {
		glEnable(GL_DEPTH_TEST);
		clearBits |= GL_DEPTH_BUFFER_BIT;
	}

	int32 frameWidth;
	int32 frameHeight;
	glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
	
	GenoFramebuffer * framebuffer = new GenoFramebuffer();
	framebuffer->id         = 0;
	framebuffer->width      = frameWidth;
	framebuffer->width      = frameHeight;
	framebuffer->clearRed   = info.clearRed;
	framebuffer->clearGreen = info.clearGreen;
	framebuffer->clearBlue  = info.clearBlue;
	framebuffer->clearBits  = clearBits;

	ret->framebuffer = framebuffer;

	if (GenoFramebuffer::activeFramebuffer == 0)
		GenoFramebuffer::activeFramebuffer = framebuffer;

	glfwSetWindowUserPointer(window, ret);

	if (vidMode != 0)
		ret->setFullscreen(monitor, vidMode);

	glfwShowWindow(window);
	
	return ret;
}

void GenoWindow::activate() const {
	glfwMakeContextCurrent(window);
	glfwFocusWindow(window);
}

void GenoWindow::bindFramebuffer() const {
	framebuffer->bind();
}

void GenoWindow::swap() const {
	glfwSwapBuffers(window);
}

int32 GenoWindow::getX() const {
	return x;
}

int32 GenoWindow::getY() const {
	return y;
}

GenoVector2i GenoWindow::getPosition() const {
	return { x, y };
}

int32 GenoWindow::getWidth() const {
	return width;
}

int32 GenoWindow::getHeight() const {
	return height;
}

GenoVector2i GenoWindow::getDimensions() const {
	return { width, height };
}

bool GenoWindow::shouldClose() const {
	return glfwWindowShouldClose(window);
}

void GenoWindow::setShouldClose(bool shouldClose) {
	glfwSetWindowShouldClose(window, shouldClose);
}

void GenoWindow::disableFullscreen(GenoMonitor * monitor) {
	glfwSetWindowMonitor(window, 0, monitor->getX() + cachedX * monitor->getWidth(), monitor->getY() + cachedY * monitor->getHeight(), cachedWidth, cachedHeight, 0);
	fullscreen = false;
}

void GenoWindow::disableFullscreen(GenoMonitor * monitor, int32 x, int32 y, int32 width, int32 height) {
	glfwSetWindowMonitor(window, 0, x + monitor->getX(), y + monitor->getY(), width, height, 0);
	fullscreen = false;
}

void GenoWindow::setFullscreen(GenoMonitor * monitor, GenoVideoMode * videoMode) {
	if (!fullscreen) {
		cachedX = (double) x / (double) curMonitor->getWidth();
		cachedY = (double) y / (double) curMonitor->getHeight();
		cachedWidth = width;
		cachedHeight = height;
	}
	glfwSetWindowMonitor(window, monitor->monitor, monitor->getX() + 1, monitor->getY() + 1, videoMode->getWidth(), videoMode->getHeight(), videoMode->getRefreshRate());
	fullscreen = true;
}

void GenoWindow::setX(int32 x) {
	glfwSetWindowPos(window, x, y);
}

void GenoWindow::setY(int32 y) {
	glfwSetWindowPos(window, x, y);
}

void GenoWindow::setPosition(int32 x, int32 y) {
	glfwSetWindowPos(window, x, y);
}

void GenoWindow::setPosition(const GenoVector2i & position) {
	glfwSetWindowPos(window, position.v[0], position.v[1]);
}

void GenoWindow::setWidth(uint32 width) {
	glfwSetWindowSize(window, width, height);
}

void GenoWindow::setHeight(int32 height) {
	glfwSetWindowSize(window, width, height);
}

void GenoWindow::setDimensions(int32 width, int32 height) {
	glfwSetWindowSize(window, width, height);
}

void GenoWindow::setDimensions(const GenoVector2i & position) {
	glfwSetWindowSize(window, position.v[0], position.v[1]);
}

void GenoWindow::maximize() {
	glfwMaximizeWindow(window);
}

void GenoWindow::minimize() {
	glfwIconifyWindow(window);
}

GenoWindow::~GenoWindow() {
	glfwDestroyWindow(window);
}

void GenoWindow::positionCallback(GLFWwindow * window, int32 x, int32 y) {
	GenoWindow * win = reinterpret_cast<GenoWindow *>(glfwGetWindowUserPointer(window));
	win->x = x;
	win->y = y;

	int32 cx = win->x + win->width  / 2;
	int32 cy = win->y + win->height / 2;
	for (uint32 i = 0; i < GenoMonitors::getNumMonitors(); ++i) {
		GenoMonitor * cur = GenoMonitors::getMonitor(i);
		if (cx >= cur->getX() && cy >= cur->getY() && cx < cur->getX() + cur->getWidth() && cy < cur->getY() + cur->getHeight())
			win->curMonitor = cur;
	}
}

void GenoWindow::sizeCallback(GLFWwindow * window, int32 width, int32 height) {
	GenoWindow * win = reinterpret_cast<GenoWindow *>(glfwGetWindowUserPointer(window));
	win->width  = width;
	win->height = height;

	int32 cx = win->x + win->width  / 2;
	int32 cy = win->y + win->height / 2;
	for (uint32 i = 0; i < GenoMonitors::getNumMonitors(); ++i) {
		GenoMonitor * cur = GenoMonitors::getMonitor(i);
		if (cx >= cur->getX() && cy >= cur->getY() && cx < cur->getX() + cur->getWidth() && cy < cur->getY() + cur->getHeight())
			win->curMonitor = cur;
	}
}

void GenoWindow::framebufferSizeCallback(GLFWwindow * window, int32 width, int32 height) {
	GenoWindow * win = reinterpret_cast<GenoWindow *>(glfwGetWindowUserPointer(window));
	GenoFramebuffer * framebuffer = win->framebuffer;
	framebuffer->width  = width;
	framebuffer->height = height;
	if (GenoFramebuffer::activeFramebuffer == framebuffer)
		glViewport(0, 0, width, height);
}

void GenoWindow::windowFocusCallback(GLFWwindow * window, int32 action) {
	if (action == GLFW_TRUE) {
		GenoWindow * win = reinterpret_cast<GenoWindow *>(glfwGetWindowUserPointer(window));
		GenoFramebuffer::activeWindow = win;
	}
}