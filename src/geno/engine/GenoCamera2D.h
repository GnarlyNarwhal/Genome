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

#ifndef GNARLY_GENOME_CAMERA2D
#define GNARLY_GENOME_CAMERA2D

#include "../math/linear/GenoVector2.h"
#include "../math/linear/GenoMatrix4.h"

class GenoCamera2D {
	private:
		float width;
		float height;

		GenoMatrix4f projection;
		GenoMatrix4f view;
		GenoMatrix4f projectionView;
	public:
		GenoVector2f position;
		float rotation;

		GenoCamera2D(float left, float right, float bottom, float top, float near, float far);
		void update();
		void setProjection(float left, float right, float bottom, float top, float near, float far);
		GenoMatrix4f getProjection();
		GenoMatrix4f getView();
		GenoMatrix4f getVPMatrix();
		float getWidth();
		float getHeight();
		GenoVector2f getDimensions();
		~GenoCamera2D();
};

#define GNARLY_GENOME_CAMERA2D_FORWARD
#endif // GNARLY_GENOME_CAMERA2D