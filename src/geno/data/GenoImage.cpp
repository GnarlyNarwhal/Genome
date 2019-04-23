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

#include <fstream>
#include <cstring>

#include <PNG\png.h>

#include "GenoImage.h"

struct GenoBitmapFileHeader {
	uint16 signature;
	uint32 fileSize;
	uint16 res1;
	uint16 res2;
	uint32 offset;
};

struct GenoBitmapInfoHeader {
	uint32 headerSize;
	uint32 width;
	uint32 height;
	uint16 colorPlanes;
	uint16 bitsPerPixel;
	uint32 compression;
	uint32 imageSize;
	uint32 horzRes;
	uint32 vertRes;
	uint32 colorPerPalette;
	uint32 important;
};

GenoImage::GenoImage() {}

GenoImage * GenoImage::create(const GenoImageCreateInfo & info) {
	uint32 width = 0;
	uint32 height = 0;
	uint8 * image = 0;
	switch (info.type) {
		case GENO_IMAGE_TYPE_CREATE: {
			width = info.width;
			height = info.height;
			uint64 size = width * height * 4;
			image = new uint8[size];
			for (int32 i = 0; i < size; i += 4) {
				image[i    ] = info.r;
				image[i + 1] = info.g;
				image[i + 2] = info.b;
				image[i + 3] = info.a;
			}
			break;
		}
		case GENO_IMAGE_TYPE_BMP: {
			std::ifstream file(info.path, std::ios::binary);
			if (file) {
				GenoBitmapFileHeader fileHeader;
				file.read(reinterpret_cast<char *> (&fileHeader), sizeof(fileHeader));

				if (fileHeader.signature == 0x4D42) {
					GenoBitmapInfoHeader infoHeader;
					file.read(reinterpret_cast<char *> (&infoHeader), sizeof(infoHeader));


					width = infoHeader.width;
					height = infoHeader.height;

					image = new uint8[width * height * 4];

					if (infoHeader.bitsPerPixel == 24 && infoHeader.compression == 0) {

						uint8 padding = (4 - (width * 3) % 4) % 4;

						file.seekg(fileHeader.offset);
						int32 lWidth = width * 4;
						int32 lHeight = height * 4;
						for (int32 i = lHeight - 4; i >= 0; i -= 4) {
							for (int32 j = 0; j < lWidth; j += 4) {
								int pixel = j * height + i;
								image[pixel + 3] = file.get();
								image[pixel + 2] = file.get();
								image[pixel + 1] = file.get();
								image[pixel    ] = 0xFF;
							}
							file.seekg(padding, std::ios::cur);
						}
					}
					else
						return 0;
				}
				else
					return 0;
			}
			else
				return 0;
			file.close();
			break;
		}
		case GENO_IMAGE_TYPE_PNG: {
			FILE * fp = fopen(info.path, "rb");

			png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			png_infop info = png_create_info_struct(png);

			png_init_io(png, fp);

			png_read_info(png, info);

			width = png_get_image_width(png, info);
			height = png_get_image_height(png, info);
			png_byte colorType = png_get_color_type(png, info);
			png_byte bitDepth = png_get_bit_depth(png, info);

			if (bitDepth == 16)
				png_set_strip_16(png);

			if (colorType == PNG_COLOR_TYPE_PALETTE)
				png_set_palette_to_rgb(png);

			if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
				png_set_expand_gray_1_2_4_to_8(png);

			if (png_get_valid(png, info, PNG_INFO_tRNS))
				png_set_tRNS_to_alpha(png);

			if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE)
				png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

			if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
				png_set_gray_to_rgb(png);

			png_read_update_info(png, info);

			png_bytep * rowPointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
			for (int y = 0; y < height; y++)
				rowPointers[y] = (png_byte *) malloc(png_get_rowbytes(png, info));

			png_read_image(png, rowPointers);

			image = new uint8[width * height * 4];
			for (int j = 0; j < height; ++j) {
				png_bytep row = rowPointers[j];
				for (int i = 0; i < width; ++i) {
					uint32 pixel = i * 4 + j * width * 4;
					png_bytep px = row + (i * 4);
					image[pixel    ] = px[0];
					image[pixel + 1] = px[1];
					image[pixel + 2] = px[2];
					image[pixel + 3] = px[3];
				}
			}

			png_destroy_read_struct(&png, &info, NULL);
			fclose(fp);
			break;
		}
	}

	GenoImage * ret = new GenoImage();
	ret->width  = width;
	ret->height = height;
	ret->image  = image;

	return ret;
}

uint32 GenoImage::getWidth() const {
	return width;
}

uint32 GenoImage::getHeight() const {
	return height;
}

uint8 * GenoImage::getBytes() {
	return image;
}

const uint8 * GenoImage::getBytes() const {
	return image;
}

GenoImage::~GenoImage() {
	delete [] image;
}