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

#include "GenoVector4.h"
#include "GenoMatrixN.h"

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
			m[0 ] = (T) matrix.m[0 ];
			m[1 ] = (T) matrix.m[1 ];
			m[2 ] = (T) matrix.m[2 ];
			m[3 ] = (T) matrix.m[3 ];
			m[4 ] = (T) matrix.m[4 ];
			m[5 ] = (T) matrix.m[5 ];
			m[6 ] = (T) matrix.m[6 ];
			m[7 ] = (T) matrix.m[7 ];
			m[8 ] = (T) matrix.m[8 ];
			m[9 ] = (T) matrix.m[9 ];
			m[10] = (T) matrix.m[10];
			m[11] = (T) matrix.m[11];
			m[12] = (T) matrix.m[12];
			m[13] = (T) matrix.m[13];
			m[14] = (T) matrix.m[14];
			m[15] = (T) matrix.m[15];
		}

		GenoMatrix(const GenoMatrix<4, 4, T> & matrix) :
			m(new T[4 * 4]) {
			m[0 ] = matrix.m[0 ];
			m[1 ] = matrix.m[1 ];
			m[2 ] = matrix.m[2 ];
			m[3 ] = matrix.m[3 ];
			m[4 ] = matrix.m[4 ];
			m[5 ] = matrix.m[5 ];
			m[6 ] = matrix.m[6 ];
			m[7 ] = matrix.m[7 ];
			m[8 ] = matrix.m[8 ];
			m[9 ] = matrix.m[9 ];
			m[10] = matrix.m[10];
			m[11] = matrix.m[11];
			m[12] = matrix.m[12];
			m[13] = matrix.m[13];
			m[14] = matrix.m[14];
			m[15] = matrix.m[15];
		}

		GenoMatrix(GenoMatrix<4, 4, T> && matrix) noexcept :
			owner(matrix.owner),
			m(matrix.m) {
			matrix.owner = false;
		}

		GenoMatrix<4, 4, T> & operator=(const GenoMatrix<4, 4, T> & matrix) {
			m[0 ] = matrix.m[0 ];
			m[1 ] = matrix.m[1 ];
			m[2 ] = matrix.m[2 ];
			m[3 ] = matrix.m[3 ];
			m[4 ] = matrix.m[4 ];
			m[5 ] = matrix.m[5 ];
			m[6 ] = matrix.m[6 ];
			m[7 ] = matrix.m[7 ];
			m[8 ] = matrix.m[8 ];
			m[9 ] = matrix.m[9 ];
			m[10] = matrix.m[10];
			m[11] = matrix.m[11];
			m[12] = matrix.m[12];
			m[13] = matrix.m[13];
			m[14] = matrix.m[14];
			m[15] = matrix.m[15];
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
		left.m[0 ] + right.m[0 ], left.m[1 ] + right.m[1 ], left.m[2 ] + right.m[2 ], left.m[3 ] + right.m[3 ],
		left.m[4 ] + right.m[4 ], left.m[5 ] + right.m[5 ], left.m[6 ] + right.m[6 ], left.m[7 ] + right.m[7 ],
		left.m[8 ] + right.m[8 ], left.m[9 ] + right.m[9 ], left.m[10] + right.m[10], left.m[11] + right.m[11],
		left.m[12] + right.m[12], left.m[13] + right.m[13], left.m[14] + right.m[14], left.m[15] + right.m[15]
	};
}

template <typename T>
GenoMatrix<4, 4, T> operator-(const GenoMatrix<4, 4, T> & left, const GenoMatrix<4, 4, T> & right) {
	return new T[4 * 4] {
		left.m[0 ] - right.m[0 ], left.m[1 ] - right.m[1 ], left.m[2 ] - right.m[2 ], left.m[3 ] - right.m[3 ],
		left.m[4 ] - right.m[4 ], left.m[5 ] - right.m[5 ], left.m[6 ] - right.m[6 ], left.m[7 ] - right.m[7 ],
		left.m[8 ] - right.m[8 ], left.m[9 ] - right.m[9 ], left.m[10] - right.m[10], left.m[11] - right.m[11],
		left.m[12] - right.m[12], left.m[13] - right.m[13], left.m[14] - right.m[14], left.m[15] - right.m[15]
	};
}

template <typename T>
GenoMatrix<4, 4, T> operator*(const GenoMatrix<4, 4, T> & left, const GenoMatrix<4, 4, T> & right) {
	return new T[4 * 4] {
		left.m[0] * right.m[0 ] + left.m[4] * right.m[1 ] + left.m[8 ] * right.m[2 ] + left.m[12] * right.m[3 ],
		left.m[1] * right.m[0 ] + left.m[5] * right.m[1 ] + left.m[9 ] * right.m[2 ] + left.m[13] * right.m[3 ],
		left.m[2] * right.m[0 ] + left.m[6] * right.m[1 ] + left.m[10] * right.m[2 ] + left.m[14] * right.m[3 ],
		left.m[3] * right.m[0 ] + left.m[7] * right.m[1 ] + left.m[11] * right.m[2 ] + left.m[15] * right.m[3 ],
		left.m[0] * right.m[4 ] + left.m[4] * right.m[5 ] + left.m[8 ] * right.m[6 ] + left.m[12] * right.m[7 ],
		left.m[1] * right.m[4 ] + left.m[5] * right.m[5 ] + left.m[9 ] * right.m[6 ] + left.m[13] * right.m[7 ],
		left.m[2] * right.m[4 ] + left.m[6] * right.m[5 ] + left.m[10] * right.m[6 ] + left.m[14] * right.m[7 ],
		left.m[3] * right.m[4 ] + left.m[7] * right.m[5 ] + left.m[11] * right.m[6 ] + left.m[15] * right.m[7 ],
		left.m[0] * right.m[8 ] + left.m[4] * right.m[9 ] + left.m[8 ] * right.m[10] + left.m[12] * right.m[11],
		left.m[1] * right.m[8 ] + left.m[5] * right.m[9 ] + left.m[9 ] * right.m[10] + left.m[13] * right.m[11],
		left.m[2] * right.m[8 ] + left.m[6] * right.m[9 ] + left.m[10] * right.m[10] + left.m[14] * right.m[11],
		left.m[3] * right.m[8 ] + left.m[7] * right.m[9 ] + left.m[11] * right.m[10] + left.m[15] * right.m[11],
		left.m[0] * right.m[12] + left.m[4] * right.m[13] + left.m[8 ] * right.m[14] + left.m[12] * right.m[15],
		left.m[1] * right.m[12] + left.m[5] * right.m[13] + left.m[9 ] * right.m[14] + left.m[13] * right.m[15],
		left.m[2] * right.m[12] + left.m[6] * right.m[13] + left.m[10] * right.m[14] + left.m[14] * right.m[15],
		left.m[3] * right.m[12] + left.m[7] * right.m[13] + left.m[11] * right.m[14] + left.m[15] * right.m[15]
	};
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoMatrix<4, 4, T> & matrix) {
	return stream << '[' << matrix.m[0] << ", " << matrix.m[4] << ", " << matrix.m[8 ] << ", " << matrix.m[12] << "]\n"
		             "[" << matrix.m[1] << ", " << matrix.m[5] << ", " << matrix.m[9 ] << ", " << matrix.m[13] << "]\n"
		             "[" << matrix.m[2] << ", " << matrix.m[6] << ", " << matrix.m[10] << ", " << matrix.m[14] << "]\n"
		             "[" << matrix.m[3] << ", " << matrix.m[7] << ", " << matrix.m[11] << ", " << matrix.m[15] << "]\n";
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