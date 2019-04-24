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

#include "GenoCamera2D.h"

GenoCamera2D::GenoCamera2D(float left, float right, float bottom, float top, float near, float far) :
	width(right - left),
	height(bottom - top),
	projection(GenoMatrix4f::makeOrthographic(left, right, bottom, top, near, far)),
	view(GenoMatrix4f::makeIdentity()),
	projectionView(projection),
	position(),
	rotation(0) {}

void GenoCamera2D::update() {
	view.setTranslateXY(-position).rotateZ(-rotation);
	projectionView = projection * view;
}

void GenoCamera2D::setProjection(float left, float right, float bottom, float top, float near, float far) {
	projection.setOrthographic(left, right, bottom, top, near, far);
}

GenoMatrix4f GenoCamera2D::getProjection() {
	return projection;
}

GenoMatrix4f GenoCamera2D::getView() {
	return view;
}

GenoMatrix4f GenoCamera2D::getVPMatrix() {
	return projectionView;
}

float GenoCamera2D::getWidth() {
	return width;
}

float GenoCamera2D::getHeight() {
	return height;
}

GenoVector2f GenoCamera2D::getDimensions() {
	return { width, height };
}

GenoCamera2D::~GenoCamera2D() {}