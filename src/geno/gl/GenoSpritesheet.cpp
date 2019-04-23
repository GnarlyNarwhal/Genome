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

#include <iostream>

#include "GenoGL.h"
#include "../data/GenoImage.h"
#include "GenoSpritesheet.h"

GenoSpritesheet::GenoSpritesheet() {}

GenoSpritesheet * GenoSpritesheet::create(const GenoSpritesheetCreateInfo & info) {
	GenoImage * image = 0;
	uint32      width;
	uint32      height;
	uint32      fullWidth;
	uint32      fullHeight;
	uint8     * data;
	if (info.type == GENO_SPRITESHEET_TYPE_CREATE) {
		width      = info.width  / info.numSpritesX;
		height     = info.height / info.numSpritesY;
		fullWidth  = info.width;
		fullHeight = info.height;
		data       = info.data;
	}
	else {
		GenoImageCreateInfo imageInfo = {};
		imageInfo.type = info.type;
		imageInfo.path = info.texture;

		image = GenoImage::create(imageInfo);

		if (image == 0)
			return 0;

		width      = image->getWidth()  / info.numSpritesX;
		height     = image->getHeight() / info.numSpritesY;
		fullWidth  = image->getWidth();
		fullHeight = image->getHeight();
		data       = image->getBytes();
	}
	
	float fractionalWidth  = (float) width  / (float) fullWidth;
	float fractionalHeight = (float) height / (float) fullHeight;
	
	float paddingX  = 0;
	float paddingY  = 0;
	bool  cleanData = false;
	if (info.addPadding) {
		cleanData = true;
		uint32 fullPadWidth  = fullWidth  + info.numSpritesX * 2;
		uint32 fullPadHeight = fullHeight + info.numSpritesY * 2;
		uint32 padWidth  = width  + 2;
		uint32 padHeight = height + 2;
		uint8 * newData = new uint8[fullPadWidth * fullPadHeight * 4];
		uint32 numSprites = info.numSpritesX * info.numSpritesY;
		uint32 numPixels  = padWidth * padHeight;
		for (uint32 i = 0; i < numSprites; ++i) {
			uint32 spriteX = i % info.numSpritesX;
			uint32 spriteY = i / info.numSpritesX;
			uint32 padOffsetX = padWidth  * spriteX;
			uint32 padOffsetY = padHeight * spriteY;
			uint32 offsetX    = width     * spriteX;
			uint32 offsetY    = height    * spriteY;
			for (uint32 j = 0; j < numPixels; ++j) {
				uint32 pixelX  = j % padWidth;
				uint32 pixelY  = j / padWidth;
				uint32 targetX = pixelX == padWidth  - 1 ? pixelX - 2 : (pixelX > 0 ? pixelX - 1 : 0);
				uint32 targetY = pixelY == padHeight - 1 ? pixelY - 2 : (pixelY > 0 ? pixelY - 1 : 0);
				uint32 writeIndex = ((pixelY  + padOffsetY) * fullPadWidth + pixelX  + padOffsetX) * 4;
				uint32 readIndex  = ((targetY + offsetY   ) * fullWidth    + targetX + offsetX   ) * 4;
				newData[writeIndex    ] = data[readIndex    ];
				newData[writeIndex + 1] = data[readIndex + 1];
				newData[writeIndex + 2] = data[readIndex + 2];
				newData[writeIndex + 3] = data[readIndex + 3];
			}
		}
		fullWidth  = padWidth  * info.numSpritesX;
		fullHeight = padHeight * info.numSpritesY;
		data = newData;

		paddingX = 1.0 / (float) fullPadWidth;
		paddingY = 1.0 / (float) fullPadHeight;
	}


	uint32 id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fullWidth, fullHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	for (uint32 i = 0; i < info.numParams; ++i) {
		uint32 index = i * 2;
		glTexParameteri(GL_TEXTURE_2D, info.params[index], info.params[index + 1]);
	}

	GenoSpritesheet * ret = new GenoSpritesheet();
	ret->id               = id;
	ret->width            = width;
	ret->height           = height;
	ret->numSpritesX      = info.numSpritesX;
	ret->numSpritesY      = info.numSpritesY;
	ret->paddingX         = paddingX;
	ret->paddingY         = paddingY;
	ret->fractionalWidth  = fractionalWidth;
	ret->fractionalHeight = fractionalHeight;
	ret->scaleX           = fractionalWidth  - paddingX * 2;
	ret->scaleY           = fractionalHeight - paddingY * 2;

	if (cleanData)
		delete [] data;
	delete image;

	return ret;
}

uint32 GenoSpritesheet::getWidth() const {
	return width;
}

uint32 GenoSpritesheet::getHeight() const {
	return height;
}

GenoMatrix4f GenoSpritesheet::getTransform(uint32 sprite) const {
	return GenoMatrix4f::makeTranslateXY((sprite % numSpritesX) * fractionalWidth  + paddingX,
	                                     (sprite / numSpritesX) * fractionalHeight + paddingY).scaleXY(scaleX, scaleY);
}

GenoMatrix4f GenoSpritesheet::getTransform(uint32 x, uint32 y) const {
	return GenoMatrix4f::makeTranslateXY(x * fractionalWidth  + paddingX,
	                                     y * fractionalHeight + paddingY).scaleXY(scaleX, scaleY);
}

GenoMatrix4f GenoSpritesheet::getTransform(const GenoVector2i & coords) const {
	return GenoMatrix4f::makeTranslateXY(coords.v[0] * fractionalWidth  + paddingX,
	                                     coords.v[1] * fractionalHeight + paddingY).scaleXY(scaleX, scaleY);
}

void GenoSpritesheet::bind(uint8 textureNum) const {
	glActiveTexture(GL_TEXTURE0 + textureNum);
	glBindTexture(GL_TEXTURE_2D, id);
}

void GenoSpritesheet::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GenoSpritesheet::~GenoSpritesheet() {}