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

#include "../../GenoInts.h"

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
#include "GenoVectorDimensions.h"

namespace GenoVectorDimensions {
	extern GenoVectorDimension<0> x;
	extern GenoVectorDimension<1> y;
}

template <typename T>
class GenoVector<2, T> {
	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] v;
		}

	public:
		static GenoVector<2, T> * newArray(uint32 length) {
			T * v = new T[2 * length];
			GenoVector<2, T> * ret = new GenoVector<2, T>[length];
			ret[0] = GenoVector<2, T>(v);
			for (uint32 i = 1; i < length; ++i)
				ret[i] = GenoVector<2, T>(v + i * 2, false);
			return ret;
		}

		T * v;
		
		GenoVector() :
			v(new T[2]()) {}

		GenoVector(T * v, bool owner = true) noexcept :
			owner(owner),
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
			owner(vector.owner),
			v(vector.v) {
			vector.owner = false;
		}

		GenoVector<2, T> & operator=(const GenoVector<2, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			return *this;
		}

		GenoVector<2, T> & operator=(GenoVector<2, T> && vector) noexcept {
			if (owner) {
				clean();
				owner = vector.owner;
				v = vector.v;
				vector.owner = false;
			}
			else {
				v[0] = vector.v[0];
				v[1] = vector.v[1];
			}
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

		T & x() noexcept {
			return v[0];
		}

		const T & x() const noexcept {
			return v[0];
		}

		T & y() noexcept {
			return v[1];
		}

		const T & y() const noexcept {
			return v[1];
		}

		T getLength() const {
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

		GenoVector<2, T> & setLength(T length) {
			auto scalar = length / getLength();
			v[0] *= scalar;
			v[1] *= scalar;
			return *this;
		}

		GenoVector<2, T> & normalize() {
			auto scalar = 1 / getLength();
			v[0] *= scalar;
			v[1] *= scalar;
			return *this;
		}

		T getAngle() const {
			return atan2(v[1], v[0]);
		}
		
		GenoVector<2, T> & setAngle(T angle) {
			auto length = getLength();
			v[0] = cos(angle) * length;
			v[1] = sin(angle) * length;
			return *this;
		}

		GenoVector<2, T> & rotate(T angle) {
			auto   sine = sin(angle);
			auto cosine = cos(angle);
			auto x = v[0];
			v[0] = v[0] * cosine - v[1] *   sine;
			v[1] = x    *   sine - v[1] * cosine;
			return *this;
		}

		GenoVector<2, T> & negate() {
			v[0] = -v[0];
			v[1] = -v[1];
			return *this;
		}

		GenoVector<2, T> & project(const GenoVector<2, T> & projection) {
			auto scalar = dot(*this, projection) / projection.getLengthSquared();
			v[0] /= scalar;
			v[1] /= scalar;
			return *this;
		}

		GenoVector<2, T> & shear(T axisAngle, T shearAngle) {
			auto sinAxis = sin(axisAngle);
			auto cosAxis = cos(axisAngle);
			auto scalar  = v[0] * sinAxis - v[1] * cosAxis;
			     scalar *= tan(shearAngle);
			v[0] += scalar * cosAxis;
			v[1] += scalar * sinAxis;
			return *this;
		}

		GenoVector<2, T> & shear(const GenoVector<2, T> & axis, T shearAngle) {
			auto unitAxis = normalize(axis); 
			auto scalar  = v[0] * unitAxis.v[1] - v[1] * unitAxis.v[0];
			     scalar *= tan(shearAngle);
			v[0] += scalar * unitAxis.v[0];
			v[1] += scalar * unitAxis.v[1];
			return *this;
		}

		GenoVector<2, T> & shear(T axisAngle, const GenoVector<2, T> & shear) {
			auto sinAxis = sin(axisAngle);
			auto cosAxis = cos(axisAngle);
			auto scalar  = v[0] * sinAxis - v[1] * cosAxis;
			     scalar *= shear.v[1] / shear.v[0];
			v[0] += scalar * cosAxis;
			v[1] += scalar * sinAxis;
			return *this;
		}

		GenoVector<2, T> & shear(const GenoVector<2, T> & axis, const GenoVector<2, T> & shear) {
			auto unitAxis = normalize(axis); 
			auto scalar  = v[0] * unitAxis.v[1] - v[1] * unitAxis.v[0];
			     scalar *= shear.v[1] / shear.v[0];
			v[0] += scalar * unitAxis.v[0];
			v[1] += scalar * unitAxis.v[1];
			return *this;
		}

		GenoVector<2, T> & shearX(T angle) {
			v[0] -= v[1] * tan(angle);
			return *this;
		}

		GenoVector<2, T> & shearX(const GenoVector<2, T> & shear) {
			v[0] -= v[1] * shear.v[1] / shear.v[0];
			return *this;
		}

		GenoVector<2, T> & shearY(T angle) {
			v[1] += v[0] * tan(angle);
			return *this;
		}

		GenoVector<2, T> & shearY(const GenoVector<2, T> & shear) {
			v[1] += v[0] * shear.v[1] / shear.v[0];
			return *this;
		}

		GenoVector<2, T> & set(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
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

		GenoVector<2, T> & setXY(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<2, T> & setYX(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<2, T> & translateX(T translateX) {
			v[0] += translateX;
		}

		GenoVector<2, T> & translateY(T translateY) {
			v[1] += translateY;
		}

		GenoVector<2, T> & translateXY(T translateX, T translateY) {
			v[0] += translateX;
			v[1] += translateY;
		}

		GenoVector<2, T> & translateXY(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<2, T> & translateYX(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<2, T> & scaleX(T scaleX) {
			v[0] *= scaleX;
		}

		GenoVector<2, T> & scaleY(T scaleY) {
			v[1] *= scaleY;
		}

		GenoVector<2, T> & scaleXY(T scale) {
			v[0] *= scale;
			v[1] *= scale;
		}

		GenoVector<2, T> & scaleXY(T scaleX, T scaleY) {
			v[0] *= scaleX;
			v[1] *= scaleY;
		}

		GenoVector<2, T> & scaleXY(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<2, T> & scaleYX(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
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

		GenoVector<3, T> getXXX() const {
			return { v[0], v[0], v[0] };
		}

		GenoVector<3, T> getXXY() const {
			return { v[0], v[0], v[1] };
		}

		GenoVector<3, T> getXYX() const {
			return { v[0], v[1], v[0] };
		}

		GenoVector<3, T> getXYY() const {
			return { v[0], v[1], v[1] };
		}

		GenoVector<3, T> getYXX() const {
			return { v[1], v[0], v[0] };
		}

		GenoVector<3, T> getYXY() const {
			return { v[1], v[0], v[1] };
		}

		GenoVector<3, T> getYYX() const {
			return { v[1], v[1], v[0] };
		}

		GenoVector<3, T> getYYY() const {
			return { v[1], v[1], v[1] };
		}

		GenoVector<4, T> getXXXX() const {
			return { v[0], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getXXXY() const {
			return { v[0], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getXXYX() const {
			return { v[0], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getXXYY() const {
			return { v[0], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getXYXX() const {
			return { v[0], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getXYXY() const {
			return { v[0], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getXYYX() const {
			return { v[0], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getXYYY() const {
			return { v[0], v[1], v[1], v[1] };
		}

		GenoVector<4, T> getYXXX() const {
			return { v[1], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getYXXY() const {
			return { v[1], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getYXYX() const {
			return { v[1], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getYXYY() const {
			return { v[1], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getYYXX() const {
			return { v[1], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getYYXY() const {
			return { v[1], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getYYYX() const {
			return { v[1], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getYYYY() const {
			return { v[1], v[1], v[1], v[1] };
		}

		virtual ~GenoVector() noexcept {
			clean();
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
	return {
		left.v[0],
		left.v[1],
		right.v[0],
		right.v[1]
	};
}

template <typename T>
GenoVector<2, T> setLength(const GenoVector<2, T> & vector, T length) {
	auto scalar = length / vector.getLength();
	return {
		vector.v[0] * scalar,
		vector.v[1] * scalar
	};
}

template <typename T>
GenoVector<2, T> & setLength(const GenoVector<2, T> & vector, T length, GenoVector<2, T> & target) {
	auto scalar = length / vector.getLength();
	target.v[0] = vector.v[0] * scalar;
	target.v[1] = vector.v[1] * scalar;
	return target;
}

template <typename T>
GenoVector<2, T> normalize(const GenoVector<2, T> & vector) {
	auto scalar = 1 / vector.getLength();
	return {
		vector.v[0] * scalar,
		vector.v[1] * scalar
	};
}

template <typename T>
GenoVector<2, T> & normalize(const GenoVector<2, T> & vector, GenoVector<2, T> & target) {
	auto scalar = 1 / vector.getLength();
	target.v[0] = vector.v[0] * scalar;
	target.v[1] = vector.v[1] * scalar;
	return target;
}

template <typename T>
GenoVector<2, T> setAngle(const GenoVector<2, T> & vector, T angle) {
	auto length = vector.getLength();
	return {
		cos(angle) * length,
		sin(angle) * length
	};
}

template <typename T>
GenoVector<2, T> & setAngle(const GenoVector<2, T> & vector, T angle, GenoVector<2, T> & target) {
	auto length = vector.getLength();
	target.v[0] = cos(angle) * length;
	target.v[1] = sin(angle) * length;
	return target;
}

template <typename T>
GenoVector<2, T> & rotate(const GenoVector<2, T> & vector, T angle) {
	auto   sine = sin(angle);
	auto cosine = cos(angle);
	return {
		vector.v[0] * cosine - vector.v[1] *   sine,
		vector.v[0] *   sine + vector.v[1] * cosine
	};
}

template <typename T>
GenoVector<2, T> & rotate(const GenoVector<2, T> & vector, T angle, GenoVector<2, T> & target) {
	auto   sine = sin(angle);
	auto cosine = cos(angle);
	target.v[0] = vector.v[0] * cosine - vector.v[1] *   sine;
	target.v[1] = vector.v[0] *   sine + vector.v[1] * cosine;
	return target;
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
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	return {
		scalar * projection.v[0],
		scalar * projection.v[1]
	};
}

template <typename T>
GenoVector<2, T> & project(const GenoVector<2, T> & vector, const GenoVector<2, T> & projection, GenoVector<2, T> & target) {
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	target.v[0] = scalar * projection.v[0];
	target.v[1] = scalar * projection.v[1];
	return target;
}

template <typename T>
GenoVector<2, T> shear(const GenoVector<2, T> & vector, T axisAngle, T shearAngle) {
	auto sinAxis = sin(axisAngle);
	auto cosAxis = cos(axisAngle);
	auto scalar  = vector.v[0] * sinAxis - vector.v[1] * cosAxis;
	     scalar *= tan(shearAngle);
	return {
		vector.v[0] + scalar * cosAxis,
		vector.v[1] + scalar * sinAxis,
	};
}

template <typename T>
GenoVector<2, T> & shear(const GenoVector<2, T> & vector, T axisAngle, T shearAngle, GenoVector<2, T> & target) {
	auto sinAxis = sin(axisAngle);
	auto cosAxis = cos(axisAngle);
	auto scalar  = vector.v[0] * sinAxis - vector.v[1] * cosAxis;
	     scalar *= tan(shearAngle);
	target.v[0]  = vector.v[0] + scalar * cosAxis;
	target.v[1]  = vector.v[1] + scalar * sinAxis;
	return target;
}

template <typename T>
GenoVector<2, T> shearX(const GenoVector<2, T> & vector, T angle) {
	return {
		vector.v[0] - vector.v[1] * tan(angle),
		vector.v[1]
	};
}

template <typename T>
GenoVector<2, T> & shearX(const GenoVector<2, T> & vector, T angle, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] - vector.v[1] * tan(angle);
	target.v[1] = vector.v[1];
	return target;
}

template <typename T>
GenoVector<2, T> shearY(const GenoVector<2, T> & vector, T angle) {
	return {
		vector.v[0],
		vector.v[1] + vector.v[0] * tan(angle)
	};
}

template <typename T>
GenoVector<2, T> & shearY(const GenoVector<2, T> & vector, T angle, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + vector.v[0] * tan(angle);
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

template<typename T>
GenoVector<2, T> setX(const GenoVector<2, T> & vector, T x) {
	return {
		x,
		vector.v[1]
	};
}

template<typename T>
GenoVector<2, T> setY(const GenoVector<2, T> & vector, T y) {
	return {
		vector.v[0],
		y
	};
}

template<typename T>
GenoVector<2, T> setX(const GenoVector<2, T> & vector, T x, GenoVector<2, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	return target;
}

template<typename T>
GenoVector<2, T> setY(const GenoVector<2, T> & vector, T y, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	return target;
}

template<typename T>
GenoVector<2, T> translateX(const GenoVector<2, T> & vector, T translateX) {
	return {
		vector.v[0] + translateX,
		vector.v[1]
	};
}

template<typename T>
GenoVector<2, T> translateY(const GenoVector<2, T> & vector, T translateY) {
	return {
		vector.v[0],
		vector.v[1] + translateY
	};
}

template<typename T>
GenoVector<2, T> translateXY(const GenoVector<2, T> & vector, T translateX, T translateY) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY
	};
}

template<typename T>
GenoVector<2, T> translateXY(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1]
	};
}

template<typename T>
GenoVector<2, T> translateYX(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0]
	};
}

template<typename T>
GenoVector<2, T> translateX(const GenoVector<2, T> & vector, T translateX, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	return target;
}

template<typename T>
GenoVector<2, T> translateY(const GenoVector<2, T> & vector, T translateY, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	return target;
}

template<typename T>
GenoVector<2, T> translateXY(const GenoVector<2, T> & vector, T translateX, T translateY, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	return target;
}

template<typename T>
GenoVector<2, T> translateXY(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<2, T> translateYX(const GenoVector<2, T> & vector, const GenoVector<2, T> & translate, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<2, T> scaleX(const GenoVector<2, T> & vector, T scaleX) {
	return {
		vector.v[0] * scaleX,
		vector.v[1]
	};
}

template<typename T>
GenoVector<2, T> scaleY(const GenoVector<2, T> & vector, T scaleY) {
	return {
		vector.v[0],
		vector.v[1] * scaleY
	};
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale
	};
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, T scaleX, T scaleY) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY
	};
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1]
	};
}

template<typename T>
GenoVector<2, T> scaleYX(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0]
	};
}

template<typename T>
GenoVector<2, T> scaleX(const GenoVector<2, T> & vector, T scaleX, const GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	return target;
}

template<typename T>
GenoVector<2, T> scaleY(const GenoVector<2, T> & vector, T scaleY, const GenoVector<2, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	return target;
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, T scale, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	return target;
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, T scaleX, T scaleY, const GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	return target;
}

template<typename T>
GenoVector<2, T> scaleXY(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<2, T> scaleYX(const GenoVector<2, T> & vector, const GenoVector<2, T> & scale, GenoVector<2, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	return target;
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