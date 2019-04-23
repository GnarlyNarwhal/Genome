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

#include "GenoGL.h"

#include "GenoVao.h"

GenoVao::GenoVao(uint32 num, float verts[], uint32 count, uint32 indices[]) {
	this->count = count;
	glGenVertexArrays(1, &vao);
	addAttrib(num, 3, verts);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int32), indices, GL_STATIC_DRAW);
}

void GenoVao::addAttrib(uint32 num, int32 stride, float data[]) {
	glBindVertexArray(vao);
	glGenBuffers(1, vbos + attribs);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[attribs]);
	glBufferData(GL_ARRAY_BUFFER, stride * num * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribs, stride, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(attribs);
	++attribs;
}

void GenoVao::render() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

GenoVao::~GenoVao() {
	glDeleteBuffers(attribs, vbos);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
}
