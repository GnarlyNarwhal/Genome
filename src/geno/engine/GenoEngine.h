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

#ifndef GNARLY_GENOME_LOOP_FORWARD
#define GNARLY_GENOME_LOOP_FORWARD

class GenoLoop;

#endif // GNARLY_GENOME_LOOP_FORWARD

#ifndef GNARLY_GENOME_ENGINE
#define GNARLY_GENOME_ENGINE

#include "../GenoInts.h"

#include "GenoLoop.h"

#define GENO_ENGINE_EVENTS_WAIT false
#define GENO_ENGINE_EVENTS_POLL true

/**
 * The engine
**/
class GenoEngine final {
	private:
		typedef void (*GenoEventPollFunc)();

		static GenoLoopCallback callback;
		static GenoLoop * loop;
		static GenoEventPollFunc getEvents;

		static void defaultLoop();

		GenoEngine();
		~GenoEngine();
	public:

		////// PROGRAM FLOW CONTROL METHODS //////

		/**
		 * Initializes the engine
		**/
		static bool init();

		/**
		 * Initializes glew
		**/
		static bool initGlew();

		/**
		 * Sets the parameters for the loop. Can either override the default loop or run in conjunction with it
		 *
		 * @param info - The loop info struct
		 * @param overrideDefault - Whether or not to override the default loop
		**/
		static void setLoop(GenoLoopCreateInfo info, bool overrideDefault = false);

		/**
		 * Starts the loop
		**/
		static void startLoop();

		/**
		 * Stops the loop
		**/
		static void stopLoop();

		/**
		 * Destroys the engine
		**/
		static void destroy();

		////// UTILITY METHODS //////

		/**
		 * Enables or disabled vsync. Sets the ratio between monitor refresh rate and buffer swap rate.
		**/
		static void setSwapInterval(uint8 interval);

		/**
		 * Polls events (e.g. keyboard, mouse, window changes)
		 *
		 * Calls the currently set getEvent func, either glfwPollEvents() or glfwWaitEvents()
		**/
		static void pollEvents();

		/**
		 * Sets the event polling function
		**/
		static void setPollFunc(bool pollFunc);

		/**
		 * Returns the game loop
		**/
		static GenoLoop * getLoop();
};

#define GNARLY_GENOME_ENGINE_FORWARD
#endif // GNARLY_GENOME_ENGINE