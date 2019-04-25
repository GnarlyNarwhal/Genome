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

#ifndef GNARLY_GENOME_INPUT
#define GNARLY_GENOME_INPUT

#include "../GenoInts.h"

#include "../gl/GenoGL.h"
#include "../math/linear/GenoVector2.h"
#include "../engine/GenoCamera2D.h"

#define GENO_INPUT_RELEASED  0x00
#define GENO_INPUT_UNPRESSED 0x01
#define GENO_INPUT_PRESSED   0x02
#define GENO_INPUT_HELD      0x03
#define GENO_INPUT_REPEATED  0x04

#define GENO_INPUT_DEFAULT_DELAY 0.3
#define GENO_INPUT_DEFAULT_SPEED 0.05

class GenoInput final {
	private:
		GenoInput();
		~GenoInput();

		static double repeatDelay;
		static double repeatSpeed;

		static uint8 keyStates[GLFW_KEY_LAST];
		static double keyTimes[GLFW_KEY_LAST];
		static double keyTargets[GLFW_KEY_LAST];

		static uint8 mouseButtonStates[GLFW_MOUSE_BUTTON_LAST];
		static double mouseButtonTimes[GLFW_MOUSE_BUTTON_LAST];
		static double mouseButtonTargets[GLFW_MOUSE_BUTTON_LAST];

		static GenoVector2d mouseCoords;

		////// CALLBACKS //////

		static void cursorPositionCallback(GLFWwindow * window, double x, double y);
		static void keyCallback(GLFWwindow * window, int32 key, int32 scancode, int32 action, int32 mods);
		static void mouseButtonCallback(GLFWwindow * window, int32 button, int32 action, int32 mods);
	public:
		static void update();

		static void setRepeatDelay(double delay);
		static void setRepeatSpeed(double speed);
		static void setRepeat(double delay, double speed);

		static uint8 getKeyState(uint16 key);
		static double getKeyDuration(uint16 key);

		static uint8 getMouseButtonState(uint8 mouseButton);
		static double getMouseButtonDuration(uint8 mouseButton);

		static GenoVector2d getRawMouseCoords();
		static GenoVector2f getMouseCoords(GenoCamera2D * camera);

	friend class GenoWindow;
};

#define GNARLY_GENOME_INPUT_FORWARD
#endif // GNARLY_GENOME_INPUT