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

#include "../GenoInts.h"

#ifndef GNARLY_GENOME_MATRIX_FORWARD
#define GNARLY_GENOME_MATRIX_FORWARD

template <uint32 N, uint32 M, typename T>
class GenoMatrix;

#endif // GNARLY_GENOME_MATRIX_FORWARD

#ifndef GNARLY_GENOME_MATRIXN
#define GNARLY_GENOME_MATRIXN

#include <ostream>

#include "GenoVector.h"

template <typename T>
class GenoMatrix<4, 4, T> {

	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] m;
		}
	public:
		T * m;

		GenoMatrix() :
			m(new T[4 * 4]()) {}

		GenoMatrix(T * m, bool owner = true) noexcept :
			owner(owner),
			m(m) {}
		
		GenoMatrix(T a, T b, T c, T d,
				   T e, T f, T g, T h,
				   T i, T j, T k, T l,
				   T m, T n, T o, T p) :
			m(new T[4 * 4] {
				a, e, i, m,
				b, f, j, n,
				c, g, k, o,
				d, h, l, p
			}) {}

		template <typename T2>
		GenoMatrix(const GenoMatrix<4, 4, T2> & matrix) :
			m(new T[4 * 4]) {
			for (uint32 i = 0; i < 4 * 4; ++i)
				m[i] = (T) matrix.m[i];
		}

		GenoMatrix(const GenoMatrix<4, 4, T> & matrix) :
			m(new T[4 * 4]) {
			for (uint32 i = 0; i < 4 * 4; ++i)
				m[i] = matrix.m[i];
		}

		GenoMatrix(GenoMatrix<4, 4, T> && matrix) noexcept :
			owner(matrix.owner),
			m(matrix.m) {
			matrix.owner = false;
		}

		GenoMatrix<4, 4, T> & operator=(const GenoMatrix<4, 4, T> & matrix) {
			for (uint32 i = 0; i < 4 * 4; ++i)
				m[i] = matrix.m[i];
			return *this;
		}

		GenoMatrix<4, 4, T> & operator=(GenoMatrix<4, 4, T> && matrix) {
			clean();
			owner = matrix.owner;
			m = matrix.m;
			matrix.owner = false;
			return *this;
		}

		GenoMatrix<4, 4, T> & operator+=(const GenoMatrix<4, 4, T> & matrix) {
			m[0 ] += matrix.m[0 ];
			m[1 ] += matrix.m[1 ];
			m[2 ] += matrix.m[2 ];
			m[3 ] += matrix.m[3 ];
			m[4 ] += matrix.m[4 ];
			m[5 ] += matrix.m[5 ];
			m[6 ] += matrix.m[6 ];
			m[7 ] += matrix.m[7 ];
			m[8 ] += matrix.m[8 ];
			m[9 ] += matrix.m[9 ];
			m[10] += matrix.m[10];
			m[11] += matrix.m[11];
			m[12] += matrix.m[12];
			m[13] += matrix.m[13];
			m[14] += matrix.m[14];
			m[15] += matrix.m[15];
			return *this;
		}

		GenoMatrix<4, 4, T> & operator-=(const GenoMatrix<4, 4, T> & matrix) {
			m[0 ] -= matrix.m[0 ];
			m[1 ] -= matrix.m[1 ];
			m[2 ] -= matrix.m[2 ];
			m[3 ] -= matrix.m[3 ];
			m[4 ] -= matrix.m[4 ];
			m[5 ] -= matrix.m[5 ];
			m[6 ] -= matrix.m[6 ];
			m[7 ] -= matrix.m[7 ];
			m[8 ] -= matrix.m[8 ];
			m[9 ] -= matrix.m[9 ];
			m[10] -= matrix.m[10];
			m[11] -= matrix.m[11];
			m[12] -= matrix.m[12];
			m[13] -= matrix.m[13];
			m[14] -= matrix.m[14];
			m[15] -= matrix.m[15];
			return *this;
		}

		GenoMatrix<4, 4, T> & operator*=(const GenoMatrix<4, 4, T> & matrix) {
			return *this = *this * matrix;
		}

		GenoVector<4, T> operator[](uint32 index) const noexcept {
			return GenoVector<4, T>(index * 4, false);
		}

		~GenoMatrix() {
			clean();
		}
};

template <typename T>
GenoMatrix<4, 4, T> operator+(const GenoMatrix<4, 4, T> & left, const GenoMatrix<4, 4, T> & right) {
	return new T[4 * 4] {
		left[0 ] + right[0 ], left[1 ] + right[1 ], left[2 ] + right[2 ], left[3 ] + right[3 ],
		left[4 ] + right[4 ], left[5 ] + right[5 ], left[6 ] + right[6 ], left[7 ] + right[7 ],
		left[8 ] + right[8 ], left[9 ] + right[9 ], left[10] + right[10], left[11] + right[11],
		left[12] + right[12], left[13] + right[13], left[14] + right[14], left[15] + right[15]
	};
}

template <typename T>
GenoMatrix<4, 4, T> operator-(const GenoMatrix<4, 4, T> & left, const GenoMatrix<4, 4, T> & right) {
	return new T[4 * 4] {
		left[0 ] - right[0 ], left[1 ] - right[1 ], left[2 ] - right[2 ], left[3 ] - right[3 ],
		left[4 ] - right[4 ], left[5 ] - right[5 ], left[6 ] - right[6 ], left[7 ] - right[7 ],
		left[8 ] - right[8 ], left[9 ] - right[9 ], left[10] - right[10], left[11] - right[11],
		left[12] - right[12], left[13] - right[13], left[14] - right[14], left[15] - right[15]
	};
}

template <typename T>
GenoMatrix<4, 4, T> operator*(const GenoMatrix<4, 4, T> & left, const GenoMatrix<4, 4, T> & right) {
	return new T[4 * 4] {
		left[0] * right[0 ] + left[4] * right[1 ] + left[8 ] * right[2 ] + left[12] * right[3 ],
		left[1] * right[0 ] + left[5] * right[1 ] + left[9 ] * right[2 ] + left[13] * right[3 ],
		left[2] * right[0 ] + left[6] * right[1 ] + left[10] * right[2 ] + left[14] * right[3 ],
		left[3] * right[0 ] + left[7] * right[1 ] + left[11] * right[2 ] + left[15] * right[3 ],
		left[0] * right[4 ] + left[4] * right[5 ] + left[8 ] * right[6 ] + left[12] * right[7 ],
		left[1] * right[4 ] + left[5] * right[5 ] + left[9 ] * right[6 ] + left[13] * right[7 ],
		left[2] * right[4 ] + left[6] * right[5 ] + left[10] * right[6 ] + left[14] * right[7 ],
		left[3] * right[4 ] + left[7] * right[5 ] + left[11] * right[6 ] + left[15] * right[7 ],
		left[0] * right[8 ] + left[4] * right[9 ] + left[8 ] * right[10] + left[12] * right[11],
		left[1] * right[8 ] + left[5] * right[9 ] + left[9 ] * right[10] + left[13] * right[11],
		left[2] * right[8 ] + left[6] * right[9 ] + left[10] * right[10] + left[14] * right[11],
		left[3] * right[8 ] + left[7] * right[9 ] + left[11] * right[10] + left[15] * right[11],
		left[0] * right[12] + left[4] * right[13] + left[8 ] * right[14] + left[12] * right[15],
		left[1] * right[12] + left[5] * right[13] + left[9 ] * right[14] + left[13] * right[15],
		left[2] * right[12] + left[6] * right[13] + left[10] * right[14] + left[14] * right[15],
		left[3] * right[12] + left[7] * right[13] + left[11] * right[14] + left[15] * right[15]
	};
}

using GenoMatrix4b  = GenoMatrix<4, 4,  int8 >;
using GenoMatrix4ub = GenoMatrix<4, 4, uint8 >;
using GenoMatrix4s  = GenoMatrix<4, 4,  int16>;
using GenoMatrix4us = GenoMatrix<4, 4, uint16>;
using GenoMatrix4i  = GenoMatrix<4, 4,  int32>;
using GenoMatrix4ui = GenoMatrix<4, 4, uint32>;
using GenoMatrix4l  = GenoMatrix<4, 4,  int8 >;
using GenoMatrix4ul = GenoMatrix<4, 4, uint64>;
using GenoMatrix4f  = GenoMatrix<4, 4, float >;
using GenoMatrix4d  = GenoMatrix<4, 4, double>;

#define GNARLY_GENOME_MATRIXN_FORWARD
#endif // GNARLY_GENOME_MATRIXN