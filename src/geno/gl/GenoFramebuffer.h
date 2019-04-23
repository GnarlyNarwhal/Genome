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

#ifndef GNARLY_GENOME_WINDOW_FORWARD
#define GNARLY_GENOME_WINDOW_FORWARD

class GenoWindow;

#endif // GNARLY_GENOME_WINDOW_FORWARD

#ifndef GNARLY_GENOME_FRAMEBUFFER
#define GNARLY_GENOME_FRAMEBUFFER

#include "../GenoInts.h"
#include "../engine/GenoWindow.h"
#include "GenoTexture2D.h"

#define GENO_FRAMEBUFFER_DEPTH_NONE    0x00
#define GENO_FRAMEBUFFER_DEPTH_TEXTURE 0x01
#define GENO_FRAMEBUFFER_DEPTH_BUFFER  0x02

struct GenoFramebufferCreateInfo {
	uint32   width;
	uint32   height;
	uint32   numColorAttachments;
	uint32   depthAttachmentType;
	uint32   numTextureParams;
	uint32 * textureParams;

	float clearRed;
	float clearGreen;
	float clearBlue;
	float clearDepth;
};

class GenoFramebuffer {
	private:
		static const GenoWindow      * activeWindow;
		static const GenoFramebuffer * activeFramebuffer;
		
		uint32 id;
		uint32 width;
		uint32 height;

		uint32 clearBits;
		float clearRed;
		float clearGreen;
		float clearBlue;
		float clearDepth;

		uint32           numColorAttachments;
		GenoTexture2D ** colorAttachments;
		uint32           depthType;
		uint32           depthBuffer;
		GenoTexture2D  * depthTexture;

		GenoFramebuffer();
	public:
		static void clear();
		static void bindDefault();

		static uint32 getCurrentWidth();
		static uint32 getCurrentHeight();

		GenoFramebuffer(const GenoFramebufferCreateInfo & info);
		uint32 getWidth() const;
		uint32 getHeight() const;
		void bind() const;
		const GenoTexture2D * getColorTexture(uint32 index = 0) const;
		const GenoTexture2D * getDepthTexture() const;
		~GenoFramebuffer();

	friend class GenoWindow;
};

#define GNARLY_GENOME_FRAMEBUFFER_FORWARD
#endif // GNARLY_GENOME_FRAMEBUFFER