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

#ifndef GNARLY_GENOME_TIME
#define GNARLY_GENOME_TIME

#include "../GenoInts.h"

enum GenoTimeScale : uint32 { seconds = 1, milliseconds = 1000, microseconds = 1000000, nanoseconds = 1000000000 };

class GenoTime final {
	public:

		/**
		 * Returns the time since the initialization of the engine
		 *
		 * @param scale - The time scale in which to return the time
		**/
		static double getTime(GenoTimeScale scale = milliseconds);
	
		/**
		 * Sleeps the current thread for the specified amount of time
		 *
		 * @param scale - The time scale of the time provided
		**/
		static void sleep(double time, GenoTimeScale scale = milliseconds);

		/**
		 * Sleeps the current thread until the specified time
		 *
		 * @param scale - The time scale of the time provided
		**/
		static void sleepUntil(double time, GenoTimeScale scale = milliseconds);
};

#define GNARLY_GENOME_TIME_FORWARD
#endif // YOUR_DEFINE_HERE