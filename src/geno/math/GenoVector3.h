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

#ifndef GNARLY_GENOME_VECTOR4_FORWARD
#define GNARLY_GENOME_VECTOR4_FORWARD

template <typename T>
class GenoVector<4, T>;

#endif // GNARLY_GENOME_VECTOR4_FORWARD

#ifndef GNARLY_GENOME_VECTOR3
#define GNARLY_GENOME_VECTOR3

#include <ostream>
#include <cmath>

#include "GenoVector.h"
#include "GenoVector2.h"
#include "GenoVector4.h"

template <typename T>
class GenoVector<3, T> {
	private:
		GenoVector(T * v) noexcept :
			v(v) {}
	public:
		T * v;

		GenoVector() :
			v(new T[3]()) {}
		
		explicit GenoVector(T value) :
			v(new T[3] { value, value, value }) {}

		GenoVector(T x, T y, T z) :
			v(new T[3] { x, y, z }) {}

		GenoVector(const GenoVector<3, T> & vector) :
			v(new T[3] {
				vector.v[0],
				vector.v[1],
				vector.v[2]
			}) {}

		GenoVector(GenoVector<3, T> && vector) :
			v(vector.v) {
			vector.v = 0;
		}

		GenoVector<3, T> & operator=(const GenoVector<3, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			v[2] = vector.v[2];
			return *this;
		}

		GenoVector<3, T> & operator=(GenoVector<3, T> && vector) {
			delete [] v;
			v = vector.v;
			vector.v = 0;
			return *this;
		}

		GenoVector<3, T> & operator+=(const GenoVector<3, T> & vector) {
			v[0] += vector.v[0];
			v[1] += vector.v[1];
			v[2] += vector.v[2];
			return *this;
		}

		GenoVector<3, T> & operator-=(const GenoVector<3, T> & vector) {
			v[0] -= vector.v[0];
			v[1] -= vector.v[1];
			v[2] -= vector.v[2];
			return *this;
		}

		GenoVector<3, T> & operator*=(T scalar) {
			v[0] *= scalar;
			v[1] *= scalar;
			v[2] *= scalar;
			return *this;
		}

		GenoVector<3, T> & operator*=(const GenoVector<3, T> & vector) {
			v[0] *= vector.v[0];
			v[1] *= vector.v[1];
			v[2] *= vector.v[2];
			return *this;
		}

		GenoVector<3, T> & operator/=(T scalar) {
			v[0] /= scalar;
			v[1] /= scalar;
			v[2] /= scalar;
			return *this;
		}

		GenoVector<3, T> & operator/=(const GenoVector<3, T> & vector) {
			v[0] /= vector.v[0];
			v[1] /= vector.v[1];
			v[2] /= vector.v[2];
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
				v[2] * v[2]
			);
		}

		T getLengthSquared() const {
			return (
				v[0] * v[0] +
				v[1] * v[1] +
				v[2] * v[2]
			);
		}

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <typename T>
GenoVector<3, T> operator-(const GenoVector<3, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1],
		-vector.v[2]
	};
}

template <typename T>
GenoVector<3, T> operator+(const GenoVector<3, T> & left, const GenoVector<3, T> & right) {
	return {
		left.v[0] + right.v[0],
		left.v[1] + right.v[1],
		left.v[2] + right.v[2]
	};
}

template <typename T>
GenoVector<3, T> operator-(const GenoVector<3, T> & left, const GenoVector<3, T> & right) {
	return {
		left.v[0] - right.v[0],
		left.v[1] - right.v[1],
		left.v[2] - right.v[2]
	};
}

template <typename T>
GenoVector<3, T> operator*(T left, const GenoVector<3, T> & right) {
	return {
		left * right.v[0],
		left * right.v[1],
		left * right.v[2]
	};
}

template <typename T>
GenoVector<3, T> operator*(const GenoVector<3, T> & left, T right) {
	return {
		left.v[0] * right,
		left.v[1] * right,
		left.v[2] * right
	};
}

template <typename T>
GenoVector<3, T> operator*(const GenoVector<3, T> & left, const GenoVector<3, T> & right) {
	return {
		left.v[0] * right.v[0],
		left.v[1] * right.v[1],
		left.v[2] * right.v[2]
	};
}

template <typename T>
GenoVector<3, T> operator/(const GenoVector<3, T> & left, T right) {
	return {
		left.v[0] / right,
		left.v[1] / right,
		left.v[2] / right
	};
}

template <typename T>
GenoVector<3, T> operator/(const GenoVector<3, T> & left, const GenoVector<3, T> & right) {
	return {
		left.v[0] / right.v[0],
		left.v[1] / right.v[1],
		left.v[2] / right.v[2]
	};
}

template <typename T>
GenoVector<4, T> operator|(T left, const GenoVector<3, T> & right) {
	return {
		left,
		right.v[0],
		right.v[1],
		right.v[2]
	};
}

template <typename T>
GenoVector<4, T> operator|(const GenoVector<3, T> & left, T right) {
	return {
		left.v[0],
		left.v[1],
		left.v[2],
		right
	};
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<3, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << '>';
}

template <typename T> using GenoVector3 = GenoVector<3, T>;

using GenoVector3b  = GenoVector<3,  int8 >;
using GenoVector3nb = GenoVector<3, uint8 >;
using GenoVector3s  = GenoVector<3,  int16>;
using GenoVector3us = GenoVector<3, uint16>;
using GenoVector3i  = GenoVector<3,  int32>;
using GenoVector3ui = GenoVector<3, uint32>;
using GenoVector3l  = GenoVector<3,  int64>;
using GenoVector3ul = GenoVector<3, uint64>;
using GenoVector3f  = GenoVector<3, float >;
using GenoVector3d  = GenoVector<3, double>;

#define GNARLY_GENOME_VECTOR3_FORWARD
#endif // GNARLY_GENOME_VECTOR3