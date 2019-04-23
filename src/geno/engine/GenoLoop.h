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

#ifndef GNARLY_GENOME_LOOP
#define GNARLY_GENOME_LOOP

// bröther may I have some lööps
//
//      ^..---..^
//     /  @ v @  \
//    /     ^     \
//   .             .
//   || |       | ||
//   '|_|       |_|'
//    \           /
//     \_|_____|_/

#include "../GenoInts.h"

typedef void (*GenoLoopCallback)();

struct GenoSubLoopCreateInfo {
	double targetFps;
	double deltaScale;
	GenoLoopCallback callback;
};

struct GenoLoopCreateInfo {
	double targetFps;
	double deltaScale;
	GenoLoopCallback callback;
	uint32 numSubLoops;
	GenoSubLoopCreateInfo * subLoops;
};

class GenoLoop {
	private:
		bool sanicLoop;
		uint32 callbackCount;
		bool looping;
		uint32 * fps;
		double * deltas;
		double * deltaScales;
		double * millisPerFrames;
		GenoLoopCallback * callbacks;
	public:
		GenoLoop(const GenoLoopCreateInfo & info);
		void start();
		void stop();
		double getDelta(uint32 loopIndex = 0);
		uint32 getFPS(uint32 loopIndex = 0);
		void setFPS(double fps, uint32 loopIndex = 0);
		void setDeltaScale(double scale, uint32 loopIndex = 0);
		void setCallback(GenoLoopCallback callback, uint32 loopIndex = 0);
		~GenoLoop();
};

#define GNARLY_GENOME_LOOP_FORWARD
#endif // GNARLY_GENOME_LOOP