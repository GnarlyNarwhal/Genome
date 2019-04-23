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

#ifndef GNARLY_GENOME_MONITOR_FORWARD
#define GNARLY_GENOME_MONITOR_FORWARD

struct GenoVideoMode;
class GenoMonitor;
class GenoMonitors;

#endif // GNARLY_GENOME_MONITOR_FORWARD

#ifndef GNARLY_GENOME_FRAMEBUFFER_FORWARD
#define GNARLY_GENOME_FRAMEBUFFER_FORWARD

class GenoFramebuffer;

#endif // GNARLY_GENOME_FRAMEBUFFER_FORWARD

#ifndef GNARLY_GENOME_WINDOW
#define GNARLY_GENOME_WINDOW

#include "../GenoInts.h"

#include "GenoMonitor.h"
#include "../gl/GenoGL.h"
#include "../gl/GenoFramebuffer.h"

struct GenoWindowCreateInfo {
	bool            defaultPosition;
	int32           x;
	int32           y;
	uint32          width;
	uint32          height;
	bool            fullscreen;
	GenoMonitor   * monitor;
	GenoVideoMode * videoMode;
	const char    * title;
	uint32          numHints;
	int32         * hints;
	float           clearRed;
	float           clearGreen;
	float           clearBlue;
	bool            depth;
};
 
class GenoWindow {
	private:
		bool fullscreen;

		double cachedX;
		double cachedY;
		int32 cachedWidth;
		int32 cachedHeight;

		GenoMonitor * curMonitor;

		int32 x;
		int32 y;
		int32 width;
		int32 height;
		GLFWwindow * window;

		GenoFramebuffer * framebuffer;

		GenoWindow();

		////// Callbacks //////

		static void positionCallback(GLFWwindow * window, int32 x, int32 y);
		static void sizeCallback(GLFWwindow * window, int32 width, int32 height);
		static void framebufferSizeCallback(GLFWwindow * window, int32 width, int32 height);
		static void windowFocusCallback(GLFWwindow * window, int32 action);
	public:
		static GenoWindow * create(const GenoWindowCreateInfo & info);
		void activate() const;
		void bindFramebuffer() const;
		void swap() const;
		int32 getX() const;
		int32 getY() const;
		GenoVector2i getPosition() const;
		int32 getWidth() const;
		int32 getHeight() const;
		GenoVector2i getDimensions() const;
		bool shouldClose() const;
		void setShouldClose(bool shouldClose);
		void disableFullscreen(GenoMonitor * monitor);
		void disableFullscreen(GenoMonitor * monitor, int32 x, int32 y, int32 width, int32 height);
		void setFullscreen(GenoMonitor * monitor, GenoVideoMode * videoMode);
		void setX(int32 x);
		void setY(int32 y);
		void setPosition(int32 x, int32 y);
		void setPosition(const GenoVector2i & position);
		void setWidth(uint32 width);
		void setHeight(int32 height);
		void setDimensions(int32 width, int32 height);
		void setDimensions(const GenoVector2i & position);
		void maximize();
		void minimize();
		~GenoWindow();
};

#define GNARLY_GENOME_WINDOW_FORWARD
#endif // GNARLY_GENOME_WINDOW