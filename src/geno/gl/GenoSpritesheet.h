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

#ifndef GNARLY_GENOME_TEXTURE_FORWARD
#define GNARLY_GENOME_TEXTURE_FORWARD

class GenoTexture;

#endif // GNARLY_GENOME_TEXTURE_FORWARD

#ifndef GNARLY_GENOME_SPRITESHEET
#define GNARLY_GENOME_SPRITESHEET

#define GENO_SPRITESHEET_TYPE_CREATE 0x00
#define GENO_SPRITESHEET_TYPE_PNG    0x01
#define GENO_SPRITESHEET_TYPE_BMP    0x02

#include "../GenoInts.h"
#include "../math/linear/GenoMatrix4.h"
#include "../math/linear/GenoVector2.h"
#include "GenoTexture.h"

struct GenoSpritesheetCreateInfo {
	uint32   type;
	bool     addPadding;
	uint32   numSpritesX;
	uint32   numSpritesY;
	uint32   numParams;
	uint32 * params;

	uint32   width;
	uint32   height;
	uint8  * data;

	const char * texture;
};

class GenoSpritesheet : public GenoTexture {
	private:
		uint32 width;
		uint32 height;
		uint32 numSpritesX;
		uint32 numSpritesY;
		
		float paddingX;
		float paddingY;
		float fractionalWidth;
		float fractionalHeight;
		float scaleX;
		float scaleY;

		GenoSpritesheet();
	public:
		static GenoSpritesheet * create(const GenoSpritesheetCreateInfo & info);
		uint32 getWidth() const;
		uint32 getHeight() const;

		GenoMatrix4f getTransform(uint32 sprite) const;
		GenoMatrix4f getTransform(uint32 x, uint32 y) const;
		GenoMatrix4f getTransform(const GenoVector2i & coords) const;

		virtual void bind(uint8 textureNum = 0) const;
		virtual void unbind() const;

		~GenoSpritesheet();
};

#define GNARLY_GENOME_SPRITESHEET_FORWARD
#endif // GNARLY_GENOME_SPRITESHEET