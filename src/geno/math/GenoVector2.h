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

namespace GenoVectorDimensions {
	GenoVectorDimension<0> x;
	GenoVectorDimension<1> y;
}

template <typename T>
class GenoVector<2, T> {
	public:

		T * v;
		
		GenoVector() :
			v(new T[2]()) {}
		
		GenoVector(T * v) noexcept :
			v(v) {}

		explicit GenoVector(T value) :
			v(new T[2] { value, value }) {}

		GenoVector(T x, T y) :
			v(new T[2] { x, y }) {}

		template <typename T2>
		GenoVector(const GenoVector<2, T2> & vector) :
			v(new T[2] {
				(T) vector.v[0],
				(T) vector.v[1]
			}) {}

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

		template <uint32 N>
		T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 2, "GenoVector<2, T> has no dimension z!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 3, "GenoVector<2, T> has no dimension w!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension  < 4, "GenoVector<2, T> has no dimension beyond y!");
			return v[GenoVectorDimensions::GenoVectorDimension<N>::dimension];
		}

		template <uint32 N>
		const T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) const noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 2, "GenoVector<2, T> has no dimension z!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 3, "GenoVector<2, T> has no dimension w!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension  < 4, "GenoVector<2, T> has no dimension beyond y!");
			return v[GenoVectorDimensions::GenoVectorDimension<N>::dimension];
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

		GenoVector<2, T> & set(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			return *this;
		}

		GenoVector<2, T> & translate(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			return *this;
		}

		GenoVector<2, T> & scale(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			return *this;
		}

		GenoVector<2, T> & scale(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			return *this;
		}

		GenoVector<2, T> & setX(T x) {
			v[0] = x;
			return *this;
		}

		GenoVector<2, T> & setY(T y) {
			v[1] = y;
			return *this;
		}

		GenoVector<2, T> & setXY(T x, T y) {
			v[0] = x;
			v[1] = y;
			return *this;
		}

		GenoVector<2, T> & setXY(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			return *this;
		}

		T getX() const {
			return v[0];
		}

		T getY() const {
			return v[1];
		}

		GenoVector<2, T> getXX() const {
			return { v[0], v[0] };
		}

		GenoVector<2, T> getXY() const {
			return { v[0], v[1] };
		}

		GenoVector<2, T> getYX() const {
			return { v[1], v[0] };
		}

		GenoVector<2, T> getYY() const {
			return { v[1], v[1] };
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
GenoVector<2, T> translate(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0]	+ translate.v[0],
		vector.v[1] + translate.v[1]
	};
}

template <typename T>
GenoVector<2, T> & translate(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	return target;
}

template <typename T>
GenoVector<2, T> scale(const GenoVector<2, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale
	};
}

template <typename T>
GenoVector<2, T> & scale(const GenoVector<2, T> & vector, T scale, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	return target;
}

template <typename T>
GenoVector<2, T> scale(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1]
	};
}

template <typename T>
GenoVector<2, T> & scale(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	return target;
}

template <typename T>
GenoVector<2, T> setX(const GenoVector<2, T> vector, T x) {
	return {
		x,
		vector.v[1],
	};
}

template <typename T>
GenoVector<2, T> setX(const GenoVector<2, T> vector, const GenoVector<1, T> set) {
	return {
		   set.v[0],
		vector.v[1],
	};
}

template <typename T>
GenoVector<2, T> setY(const GenoVector<2, T> vector, T y) {
	return {
		vector.v[0],
		y,
	};
}

template <typename T>
GenoVector<2, T> setY(const GenoVector<2, T> vector, const GenoVector<1, T> set) {
	return {
		vector.v[0],
		   set.v[0],
	};
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<2, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << '>';
}

template <typename T> using GenoVector2 = GenoVector<2, T>;

using GenoVector2b  = GenoVector2< int8 >;
using GenoVector2ub = GenoVector2<uint8 >;
using GenoVector2s  = GenoVector2< int16>;
using GenoVector2us = GenoVector2<uint16>;
using GenoVector2i  = GenoVector2< int32>;
using GenoVector2ui = GenoVector2<uint32>;
using GenoVector2l  = GenoVector2< int64>;
using GenoVector2ul = GenoVector2<uint64>;
using GenoVector2f  = GenoVector2<float >;
using GenoVector2d  = GenoVector2<double>;

#define GNARLY_GENOME_VECTOR2_FORWARD
#endif // GNARLY_GENOME_VECTOR2