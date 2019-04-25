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

#ifndef GNARLY_GENOME_MONITOR
#define GNARLY_GENOME_MONITOR

#include "../GenoInts.h"

#include "../math/linear/GenoVector2.h"
#include "../math/linear/GenoVector3.h"
#include "../gl/GenoGL.h"

#define GENO_MONITOR_SCALE_MILLIMETERS 1.0
#define GENO_MONITOR_SCALE_CENTIMETERS 10.0
#define GENO_MONITOR_SCALE_INCHES      25.4
#define GENO_MONITOR_SCALE_FEET        304.8

class GenoVideoMode final {
	private:
		int32 width;
		int32 height;
		int32 redBits;
		int32 greenBits;
		int32 blueBits;
		int32 refreshRate;

		GenoVideoMode(const GLFWvidmode & videoMode);
		~GenoVideoMode();
	public:
		int32 getWidth() const;
		int32 getHeight() const;
		GenoVector2i getDimensions() const;

		int32 getRedBits() const;
		int32 getGreenBits() const;
		int32 getBlueBits() const;
		GenoVector3i getBitDepth() const;

		int32 getRefreshRate() const;

	friend class GenoMonitor;
};

class GenoMonitor final {
	private:
		GLFWmonitor * monitor;	

		uint32 numVideoModes;
		GenoVideoMode ** videoModes;

		int32 x;
		int32 y;
		int32 width;
		int32 height;
		double sizeX;
		double sizeY;
		const char * name;

		GenoMonitor(GLFWmonitor * monitor);
		~GenoMonitor();
	public:
		int32 getX() const;
		int32 getY() const;
		GenoVector2i getPosition() const;

		int32 getWidth() const;
		int32 getHeight() const;
		GenoVector2i getDimensions() const;

		double getPhysicalWidth(double scale = GENO_MONITOR_SCALE_INCHES) const;
		double getPhysicalHeight(double scale = GENO_MONITOR_SCALE_INCHES) const;
		GenoVector2d getPhysicalDimensions(double scale = GENO_MONITOR_SCALE_INCHES) const;
		double getPhysicalDiagonal(double scale = GENO_MONITOR_SCALE_INCHES) const;

		const char * getName() const;

		uint32 getNumVideoModes() const;
		GenoVideoMode * getDefaultVideoMode() const;
		GenoVideoMode * getVideoMode(uint32 num) const;

	friend class GenoMonitors;
	friend class GenoWindow;
};

class GenoMonitors final {
	private:
		static uint32 numMonitors;
		static GenoMonitor ** monitors;

		GenoMonitors();
		~GenoMonitors();

		static void init();
		static void cleanup();

		////// Callbacks //////

		static void monitorCallback(GLFWmonitor * monitor, int32 event);
	public:
		static uint32 getNumMonitors();
		static GenoMonitor * getPrimaryMonitor();
		static GenoMonitor * getMonitor(uint32 num);

	friend class GenoEngine;
};

#define GNARLY_GENOME_MONITOR_FORWARD
#endif // GNARLY_GENOME_MONITOR