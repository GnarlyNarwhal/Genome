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

#ifndef GNARLY_GENOME_VECTOR_FORWARD
#define GNARLY_GENOME_VECTOR_FORWARD

template <uint32 N, typename T>
class GenoVector;

#endif // GNARLY_GENOME_VECTOR_FORWARD

#ifndef GNARLY_GENOME_VECTOR2_FORWARD
#define GNARLY_GENOME_VECTOR2_FORWARD

template <typename T>
class GenoVector<2, T>;

#endif // GNARLY_GENOME_VECTOR2_FORWARD

#ifndef GNARLY_GENOME_VECTOR3_FORWARD
#define GNARLY_GENOME_VECTOR3_FORWARD

template <typename T>
class GenoVector<3, T>;

#endif // GNARLY_GENOME_VECTOR3_FORWARD

#ifndef GNARLY_GENOME_VECTOR4
#define GNARLY_GENOME_VECTOR4

#include <ostream>
#include <cmath>

#include "GenoVector.h"
#include "GenoVector2.h"

template <typename T>
class GenoVector<4, T> {
	private:
		GenoVector(T * v) noexcept :
			v(v) {}
	public:
		T * v;

		GenoVector() :
			v(new T[4]()) {}

		explicit GenoVector(T value) :
			v(new T[4] { value, value, value, value }) {}

		GenoVector(T x, T y, T z, T w) :
			v(new T[4] { x, y, z, w }) {}

		GenoVector(const GenoVector<4, T> & vector) :
			v(new T[4] {
				vector.v[0],
				vector.v[1],
				vector.v[2],
				vector.v[3]
			}) {}

		GenoVector(GenoVector<4, T> && vector) :
			v(vector.v) {
			vector.v = 0;
		}

		GenoVector<4, T> & operator=(const GenoVector<4, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			v[2] = vector.v[2];
			v[3] = vector.v[3];
			return *this;
		}

		GenoVector<4, T> & operator=(GenoVector<4, T> && vector) {
			delete [] v;
			v = vector.v;
			vector.v = 0;
			return *this;
		}

		GenoVector<4, T> & operator+=(const GenoVector<4, T> & vector) {
			v[0] += vector.v[0];
			v[1] += vector.v[1];
			v[2] += vector.v[2];
			v[3] += vector.v[3];
			return *this;
		}

		GenoVector<4, T> & operator-=(const GenoVector<4, T> & vector) {
			v[0] -= vector.v[0];
			v[1] -= vector.v[1];
			v[2] -= vector.v[2];
			v[3] -= vector.v[3];
			return *this;
		}

		GenoVector<4, T> & operator*=(T scalar) {
			v[0] *= scalar;
			v[1] *= scalar;
			v[2] *= scalar;
			v[3] *= scalar;
			return *this;
		}

		GenoVector<4, T> & operator*=(const GenoVector<4, T> & vector) {
			v[0] *= vector.v[0];
			v[1] *= vector.v[1];
			v[2] *= vector.v[2];
			v[3] *= vector.v[3];
			return *this;
		}

		GenoVector<4, T> & operator/=(T scalar) {
			v[0] /= scalar;
			v[1] /= scalar;
			v[2] /= scalar;
			v[3] /= scalar;
			return *this;
		}

		GenoVector<4, T> & operator/=(const GenoVector<4, T> & vector) {
			v[0] /= vector.v[0];
			v[1] /= vector.v[1];
			v[2] /= vector.v[2];
			v[3] /= vector.v[3];
			return *this;
		}

		T & operator[](uint32 index) noexcept {
			return v[index];
		}

		const T & operator[](uint32 index) const noexcept {
			return v[index];
		}

		double getLength() const {
			return sqrt(
				v[0] * v[0] +
				v[1] * v[1] +
				v[2] * v[2] +
				v[3] * v[3]
			);
		}

		T getLengthSquared() const {
			return (
				v[0] * v[0] +
				v[1] * v[1] +
				v[2] * v[2] +
				v[3] * v[3]
			);
		}

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <typename T>
GenoVector<4, T> operator-(const GenoVector<4, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1],
		-vector.v[2],
		-vector.v[3]
	};
}

template <typename T>
GenoVector<4, T> operator+(const GenoVector<4, T> & left, const GenoVector<4, T> & right) {
	return {
		left.v[0] + right.v[0],
		left.v[1] + right.v[1],
		left.v[2] + right.v[2],
		left.v[3] + right.v[3]
	};
}

template <typename T>
GenoVector<4, T> operator-(const GenoVector<4, T> & left, const GenoVector<4, T> & right) {
	return {
		left.v[0] - right.v[0],
		left.v[1] - right.v[1],
		left.v[2] - right.v[2],
		left.v[3] - right.v[3]
	};
}

template <typename T>
GenoVector<4, T> operator*(T left, const GenoVector<4, T> & right) {
	return {
		left * right.v[0],
		left * right.v[1],
		left * right.v[2],
		left * right.v[3]
	};
}

template <typename T>
GenoVector<4, T> operator*(const GenoVector<4, T> & left, T right) {
	return {
		left.v[0] * right,
		left.v[1] * right,
		left.v[2] * right,
		left.v[3] * right
	};
}

template <typename T>
GenoVector<4, T> operator*(const GenoVector<4, T> & left, const GenoVector<4, T> & right) {
	return {
		left.v[0] * right.v[0],
		left.v[1] * right.v[1],
		left.v[2] * right.v[2],
		left.v[3] * right.v[3]
	};
}

template <typename T>
GenoVector<4, T> operator/(const GenoVector<4, T> & left, T right) {
	return {
		left.v[0] / right,
		left.v[1] / right,
		left.v[2] / right,
		left.v[3] / right
	};
}

template <typename T>
GenoVector<4, T> operator/(const GenoVector<4, T> & left, const GenoVector<4, T> & right) {
	return {
		left.v[0] / right.v[0],
		left.v[1] / right.v[1],
		left.v[2] / right.v[2],
		left.v[3] / right.v[3]
	};
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<4, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << ", " << vector.v[3] << '>';
}

template <typename T> using GenoVector4 = GenoVector<4, T>;

using GenoVector4b  = GenoVector<4,  int8 >;
using GenoVector4ub = GenoVector<4, uint8 >;
using GenoVector4s  = GenoVector<4,  int16>;
using GenoVector4us = GenoVector<4, uint16>;
using GenoVector4i  = GenoVector<4,  int32>;
using GenoVector4ui = GenoVector<4, uint32>;
using GenoVector4l  = GenoVector<4,  int64>;
using GenoVector4ul = GenoVector<4, uint64>;
using GenoVector4f  = GenoVector<4, float >;
using GenoVector4d  = GenoVector<4, double>;

#define GNARLY_GENOME_VECTOR4_FORWARD
#endif // GNARLY_GENOME_VECTOR4