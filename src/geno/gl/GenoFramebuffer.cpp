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
#include "GenoFramebuffer.h"

const GenoWindow      * GenoFramebuffer::activeWindow = 0;
const GenoFramebuffer * GenoFramebuffer::activeFramebuffer = 0;

void GenoFramebuffer::clear() {
	glClear(activeFramebuffer->clearBits);
}

void GenoFramebuffer::bindDefault() {
	activeWindow->bindFramebuffer();
}

uint32 GenoFramebuffer::getCurrentWidth() {
	return activeFramebuffer->width;
}

uint32 GenoFramebuffer::getCurrentHeight() {
	return activeFramebuffer->height;
}

GenoFramebuffer::GenoFramebuffer() {}

GenoFramebuffer::GenoFramebuffer(const GenoFramebufferCreateInfo & info) :
	width(info.width),
	height(info.height),
	numColorAttachments(info.numColorAttachments),
	depthType(info.depthAttachmentType) {

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	if (numColorAttachments != 0) {
		clearBits |= GL_COLOR_BUFFER_BIT;
		clearRed   = info.clearRed;
		clearGreen = info.clearGreen;
		clearBlue  = info.clearBlue;
		uint32 * colorAttachmentIds = new uint32[numColorAttachments];
		uint32 * drawBuffers        = new uint32[numColorAttachments];
		colorAttachments = new GenoTexture2D*[numColorAttachments];
		glGenTextures(numColorAttachments, colorAttachmentIds);
		for (uint32 i = 0; i < numColorAttachments; ++i) {
			glBindTexture(GL_TEXTURE_2D, colorAttachmentIds[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			for (uint32 j = 0; j < info.numTextureParams; ++j) {
				uint32 index = j * 2;
				glTexParameteri(GL_TEXTURE_2D, info.textureParams[index], info.textureParams[index + 1]);
			}
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorAttachmentIds[i], 0);
			colorAttachments[i] = new GenoTexture2D(colorAttachmentIds[i], width, height);
			drawBuffers[i]      = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(numColorAttachments, drawBuffers);

		delete [] colorAttachmentIds;
		delete [] drawBuffers;
	}
	if (depthType == GENO_FRAMEBUFFER_DEPTH_BUFFER) {
		clearBits |= GL_DEPTH_BUFFER_BIT;
		clearDepth = info.clearDepth;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	}
	else if (depthType == GENO_FRAMEBUFFER_DEPTH_TEXTURE) {
		clearBits |= GL_DEPTH_BUFFER_BIT;
		clearDepth = info.clearDepth;
		uint32 textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		for (uint32 i = 0; i < info.numTextureParams; ++i) {
			uint32 index = i * 2;
			glTexParameteri(GL_TEXTURE_2D, info.textureParams[index], info.textureParams[index + 1]);
		}
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
		depthTexture = new GenoTexture2D(textureId, width, height);
	}

	activeFramebuffer->bind();
}

uint32 GenoFramebuffer::getWidth() const {
	return width;
}

uint32 GenoFramebuffer::getHeight() const {
	return height;
}

const GenoTexture2D * GenoFramebuffer::getColorTexture(uint32 index) const {
	return colorAttachments[index];
}

const GenoTexture2D * GenoFramebuffer::getDepthTexture() const {
	return depthTexture;
}

void GenoFramebuffer::bind() const {
	for (uint32 i = GL_TEXTURE0; i < GL_TEXTURE31; ++i) {
		glActiveTexture(i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	activeFramebuffer = this;
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glClearColor(clearRed, clearGreen, clearBlue, 1);
	glClearDepth(clearDepth);
	glViewport(0, 0, width, height);
}

GenoFramebuffer::~GenoFramebuffer() {
	for (uint32 i = 0; i < numColorAttachments; ++i)
		delete colorAttachments[i];
	delete [] colorAttachments;
	if (depthType == GENO_FRAMEBUFFER_DEPTH_TEXTURE)
		delete depthTexture;
	else if (depthType == GENO_FRAMEBUFFER_DEPTH_BUFFER)
		glDeleteRenderbuffers(1, &depthBuffer);
	glDeleteFramebuffers(1, &id);
}

