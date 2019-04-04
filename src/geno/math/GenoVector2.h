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

#ifndef GNARLY_GENOME_VECTOR3_FORWARD
#define GNARLY_GENOME_VECTOR3_FORWARD

template <typename T>
class GenoVector<3, T>;

#endif // GNARLY_GENOME_VECTOR3_FORWARD

#ifndef GNARLY_GENOME_VECTOR4_FORWARD
#define GNARLY_GENOME_VECTOR4_FORWARD

template <typename T>
class GenoVector<4, T>;

#endif // GNARLY_GENOME_VECTOR4_FORWARD

#ifndef GNARLY_GENOME_VECTOR2
#define GNARLY_GENOME_VECTOR2

#include <ostream>
#include <cmath>

#include "GenoVector.h"
#include "GenoVector3.h"
#include "GenoVector4.h"

template <typename T>
class GenoVector<2, T> {
	private:
		GenoVector(T * v) noexcept :
			v(v) {}

		T * steal() noexcept {
			T * ret = v;
			v = 0;
			return ret;
		}
	public:
		T * v;
		
		GenoVector() :
			v(new T[2]()) {}
		
		explicit GenoVector(T value) :
			v(new T[2] { value, value }) {}

		GenoVector(T x, T y) :
			v(new T[2] { x, y }) {}

		GenoVector(const GenoVector<2, T> & vector) :
			v(new T[2] {
				vector.v[0],
				vector.v[1]
			}) {}

		GenoVector(GenoVector<2, T> && vector) noexcept :
			v(vector.v) {
			vector.v = 0;
		}

		GenoVector<2, T> & operator=(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			return *this;
		}

		GenoVector<2, T> & operator=(GenoVector<2, T> && vector) noexcept {
			delete[] v;
			v = vector.v;
			vector.v = 0;
			return *this;
		}

		GenoVector<2, T> & operator+=(const GenoVector<2, T> & vector) {
			v[0] += vector.v[0];
			v[1] += vector.v[1];
			return *this;
		}

		GenoVector<2, T> & operator-=(const GenoVector<2, T> & vector) {
			v[0] -= vector.v[0];
			v[1] -= vector.v[1];
			return *this;
		}

		GenoVector<2, T> & operator*=(T scalar) {
			v[0] *= scalar;
			v[1] *= scalar;
			return *this;
		}

		GenoVector<2, T> & operator*=(const GenoVector<2, T> & vector) {
			v[0] *= vector.v[0];
			v[1] *= vector.v[1];
			return *this;
		}

		GenoVector<2, T> & operator/=(T scalar) {
			v[0] /= scalar;
			v[1] /= scalar;
			return *this;
		}

		GenoVector<2, T> & operator/=(const GenoVector<2, T> & vector) {
			v[0] /= vector.v[0];
			v[1] /= vector.v[1];
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
				v[1] * v[1]
			);
		}

		T getLengthSquared() const {
			return (
				v[0] * v[0] +
				v[1] * v[1]
			);
		}
		
		GenoVector<2, T> & negate() {
			v[0] = -v[0];
			v[1] = -v[1];
			return *this;
		}

		GenoVector<2, T> & project(const GenoVector<2, T> & projection) {
			T scalar = dot(*this, projection) / projection.getLengthSquared();
			v[0] /= scalar;
			v[1] /= scalar;
			return *this;
		}

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <typename T>
GenoVector<2, T> operator-(const GenoVector<2, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1]
	};
}

template <typename T>
GenoVector<2, T> operator+(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	return {
		left.v[0] + right.v[0],
		left.v[1] + right.v[1]
	};
}

template <typename T>
GenoVector<2, T> operator-(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	return {
		left.v[0] - right.v[0],
		left.v[1] - right.v[1]
	};
}

template <typename T>
GenoVector<2, T> operator*(T left, const GenoVector<2, T> & right) {
	return {
		left * right.v[0],
		left * right.v[1]
	};
}

template <typename T>
GenoVector<2, T> operator*(const GenoVector<2, T> & left, T right) {
	return {
		left.v[0] * right,
		left.v[1] * right
	};
}

template <typename T>
GenoVector<2, T> operator*(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	return {
		left.v[0] * right.v[0],
		left.v[1] * right.v[1]
	};
}

template <typename T>
GenoVector<2, T> operator/(const GenoVector<2, T> & left, T right) {
	return {
		left.v[0] / right,
		left.v[1] / right
	};
}

template <typename T>
GenoVector<2, T> operator/(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	return {
		left.v[0] / right.v[0],
		left.v[1] / right.v[1]
	};
}

template <typename T>
GenoVector<3, T> operator|(T left, const GenoVector<2, T> & right) {
	return {
		left,
		right.v[0],
		right.v[1]
	};
}

template <typename T>
GenoVector<3, T> operator|(const GenoVector<2, T> & left, T right) {
	return {
		left.v[0],
		left.v[1],
		right
	};
}

template <typename T>
GenoVector<4, T> operator|(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	std::cout << "asdf" << std::endl;
	return {
		left.v[0],
		left.v[1],
		right.v[0],
		right.v[1]
	};
}

template <typename T>
GenoVector<2, T> negate(const GenoVector<2, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1]
	};
}

template <typename T>
GenoVector<2, T> & negate(const GenoVector<2, T> & vector, GenoVector<2, T> & target) {
	target.v[0] = -vector.v[0];
	target.v[1] = -vector.v[1];
	return target;
}

template <typename T>
T dot(const GenoVector<2, T> & left, const GenoVector<2, T> & right) {
	return (
		left.v[0] * right.v[0] +
		left.v[1] * right.v[1]
	);
}

template <typename T>
GenoVector<2, T> project(const GenoVector<2, T> & vector, const GenoVector<2, T> & projection) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	return {
		scalar * projection.v[0],
		scalar * projection.v[1]
	};
}

template <typename T>
GenoVector<2, T> & project(const GenoVector<2, T> & vector, const GenoVector<2, T> & projection, GenoVector<2, T> & target) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	target.v[0] = scalar * projection.v[0];
	target.v[1] = scalar * projection.v[1];
	return target;
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<2, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << '>';
}

template <typename T> using GenoVector2 = GenoVector<2, T>;

using GenoVector2b  = GenoVector<2,  int8 >;
using GenoVector2ub = GenoVector<2, uint8 >;
using GenoVector2s  = GenoVector<2,  int16>;
using GenoVector2us = GenoVector<2, uint16>;
using GenoVector2i  = GenoVector<2,  int32>;
using GenoVector2ui = GenoVector<2, uint32>;
using GenoVector2l  = GenoVector<2,  int64>;
using GenoVector2ul = GenoVector<2, uint64>;
using GenoVector2f  = GenoVector<2, float >;
using GenoVector2d  = GenoVector<2, double>;

#define GNARLY_GENOME_VECTOR2_FORWARD
#endif // GNARLY_GENOME_VECTOR2