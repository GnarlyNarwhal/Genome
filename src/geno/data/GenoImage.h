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

#ifndef GNARLY_GENOME_IMAGE
#define GNARLY_GENOME_IMAGE

#include "../GenoInts.h"

#define GENO_IMAGE_TYPE_CREATE 0x00
#define GENO_IMAGE_TYPE_PNG    0x01
#define GENO_IMAGE_TYPE_BMP    0x02

struct GenoImageCreateInfo {
	uint32 type;
	
	uint32 width;
	uint32 height;
	uint8  r;
	uint8  g;
	uint8  b;
	uint8  a;

	const char * path;
};

class GenoImage {
	private:
		uint32 width;
		uint32 height;
		uint8 * image;
		
		GenoImage();
	public:
		static GenoImage * create(const GenoImageCreateInfo & info);
		uint32 getWidth() const;
		uint32 getHeight() const;
		uint8 * getBytes();
		const uint8 * getBytes() const;
		~GenoImage();
};

#define GNARLY_GENOME_IMAGE_FORWARD
#endif // GNARLY_GENOME_IMAGE