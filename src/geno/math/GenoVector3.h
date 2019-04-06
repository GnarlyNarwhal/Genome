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
	public:
		T * v;

		GenoVector() :
			v(new T[3]()) {}
		
		GenoVector(T * v) noexcept :
			v(v) {}
		
		explicit GenoVector(T value) :
			v(new T[3] { value, value, value }) {}

		GenoVector(T x, T y, T z) :
			v(new T[3] { x, y, z }) {}

		template <typename T2>
		GenoVector(const GenoVector<3, T2> & vector) :
			v(new T[3] {
				(T) vector.v[0],
				(T) vector.v[1],
				(T) vector.v[2]
			}) {}

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
		
		GenoVector<3, T> & negate() {
			v[0] = -v[0];
			v[1] = -v[1];
			v[2] = -v[2];
			return *this;
		}

		GenoVector<3, T> & project(const GenoVector<3, T> & projection) {
			T scalar = dot(*this, projection) / projection.getLengthSquared();
			v[0] /= scalar;
			v[1] /= scalar;
			v[2] /= scalar;
			return *this;
		}

		GenoVector<3, T> & set(const GenoVector<3, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			v[2] = vector.v[2];
			return *this;
		}

		GenoVector<3, T> & translate(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
			return *this;
		}
		
		GenoVector<3, T> & scale(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[2] *= scale;
			return *this;
		}
		
		GenoVector<3, T> & scale(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
			return *this;
		}

		GenoVector<3, T> & setX(T x) {
			v[0] = x;
			return *this;
		}

		GenoVector<3, T> & setY(T y) {
			v[1] = y;
			return *this;
		}

		GenoVector<3, T> & setZ(T z) {
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setXY(T x, T y) {
			v[0] = x;
			v[1] = y;
			return *this;
		}

		GenoVector<3, T> & setXY(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			return *this;
		}

		GenoVector<3, T> & setXZ(T x, T z) {
			v[0] = x;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setXZ(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[2] = vector.v[1];
			return *this;
		}

		GenoVector<3, T> & setYZ(T y, T z) {
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setYZ(const GenoVector<2, T> & vector) {
			v[1] = vector.v[0];
			v[2] = vector.v[1];
			return *this;
		}

		GenoVector<3, T> & setXYZ(T x, T y, T z) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setXYZ(const GenoVector<3, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			v[2] = vector.v[2];
			return *this;
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
GenoVector<3, T> negate(const GenoVector<3, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1],
		-vector.v[2]
	};
}

template <typename T>
GenoVector<3, T> & negate(const GenoVector<3, T> & vector, GenoVector<3, T> & target) {
	target.v[0] = -vector.v[0];
	target.v[1] = -vector.v[1];
	target.v[2] = -vector.v[2];
	return target;
}

template <typename T>
T dot(const GenoVector<3, T> & left, const GenoVector<3, T> & right) {
	return (
		left.v[0] * right.v[0] +
		left.v[1] * right.v[1] +
		left.v[2] * right.v[2]
	);
}

template <typename T>
GenoVector<3, T> project(const GenoVector<3, T> & vector, const GenoVector<3, T> & projection) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	return {
		scalar * projection.v[0],
		scalar * projection.v[1],
		scalar * projection.v[2]
	};
}

template <typename T>
GenoVector<3, T> & project(const GenoVector<3, T> & vector, const GenoVector<3, T> & projection, GenoVector<3, T> & target) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	target.v[0] = scalar * projection.v[0];
	target.v[1] = scalar * projection.v[1];
	target.v[2] = scalar * projection.v[2];
	return target;
}

template <typename T>
GenoVector<3, T> translate(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0]	+ translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2]
	};
}

template <typename T>
GenoVector<3, T> & translate(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	return target;
}

template <typename T>
GenoVector<3, T> scale(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template <typename T>
GenoVector<3, T> & scale(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template <typename T>
GenoVector<3, T> scale(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2]
	};
}

template <typename T>
GenoVector<3, T> & scale(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	return target;
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<3, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << '>';
}

template <typename T> using GenoVector3 = GenoVector<3, T>;

using GenoVector3b  = GenoVector3< int8 >;
using GenoVector3ub = GenoVector3<uint8 >;
using GenoVector3s  = GenoVector3< int16>;
using GenoVector3us = GenoVector3<uint16>;
using GenoVector3i  = GenoVector3< int32>;
using GenoVector3ui = GenoVector3<uint32>;
using GenoVector3l  = GenoVector3< int64>;
using GenoVector3ul = GenoVector3<uint64>;
using GenoVector3f  = GenoVector3<float >;
using GenoVector3d  = GenoVector3<double>;

#define GNARLY_GENOME_VECTOR3_FORWARD
#endif // GNARLY_GENOME_VECTOR3