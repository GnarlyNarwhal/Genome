/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarly Narwhal
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
#include <chrono>

#include "geno/GenoInts.h"
#include "geno/math/GenoVector3.h"
#include "geno/math/GenoVector4.h"
#include "geno/math/GenoMatrix4.h"

int32 main(int32 argc, char ** argv) {

	auto mat = GenoMatrix4f::makeIdentity();

	std::cout << GenoVector3f{ 0, 1, 2 }.rotateXYZ(1, 7, 6) << std::endl;
	std::cout << GenoMatrix4f::makeRotateXYZ(1, 7, 6) * GenoVector4f{ 0, 1, 2, 1 } << std::endl;
	std::cout << mat.rotateXYZ(1, 7, 6) * GenoVector4f{ 0, 1, 2, 1 } << std::endl;

	/////// TIME TRIALS - LEAVE FOR FUTURE USE ///////
/*
	const uint32 NUM_ITERATIONS = 1000000;

	auto mat = GenoMatrix4f::makeIdentity();

	auto begin1 = std::chrono::high_resolution_clock::now();
	
	for (uint32 i = 0; i < NUM_ITERATIONS; ++i)
		mat = GenoMatrix4f::makeOrthographic(1, 8, 7, 6, 4, 2) * GenoMatrix4f::makePerspective(7, 9, 6, 3);
	
	auto end1 = std::chrono::high_resolution_clock::now();

	auto begin2 = std::chrono::high_resolution_clock::now();

	for (uint32 i = 0; i < NUM_ITERATIONS; ++i)
		mat.setOrthographic(1, 8, 7, 6, 4, 2).projectPerspective(7, 9, 6, 3);

	auto end2 = std::chrono::high_resolution_clock::now();
	
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << std::endl;
*/
	//////// DO NOT REMOVE BELOW ////////
	std::cout << "Press enter to continue . . ." << std::endl;
	std::cin.get();

	return 0;
}