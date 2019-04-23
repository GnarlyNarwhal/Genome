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
#include "../data/GenoImage.h"

#include "GenoTexture2D.h"

GenoTexture2D::GenoTexture2D(uint32 id, uint32 width, uint32 height) :
	GenoTexture(id),
	width(width),
	height(height) {}

GenoTexture2D * GenoTexture2D::create(const GenoTexture2DCreateInfo & info) {
	GenoImage * image = 0;
	uint32      width;
	uint32      height;
	uint8     * data;
	if (info.type == GENO_TEXTURE2D_TYPE_CREATE) {
		width  = info.width;
		height = info.height;
		data   = info.data;
	}
	else {
		GenoImageCreateInfo imageInfo = {};
		imageInfo.type = info.type;
		imageInfo.path = info.texture;

		image = GenoImage::create(imageInfo);

		if (image == 0)
			return 0;
		width  = image->getWidth();
		height = image->getHeight();
		data   = image->getBytes();
	}

	uint32 id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	for (uint32 i = 0; i < info.numParams; ++i) {
		uint32 index = i * 2;
		glTexParameteri(GL_TEXTURE_2D, info.params[index], info.params[index + 1]);
	}

	GenoTexture2D * ret = new GenoTexture2D(id, width, height);

	delete image;

	return ret;
}

uint32 GenoTexture2D::getWidth() const {
	return width;
}

uint32 GenoTexture2D::getHeight() const {
	return height;
}

void GenoTexture2D::bind(uint8 textureNum) const {
	glActiveTexture(GL_TEXTURE0 + textureNum);
	glBindTexture(GL_TEXTURE_2D, id);
}

void GenoTexture2D::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GenoTexture2D::~GenoTexture2D() {}