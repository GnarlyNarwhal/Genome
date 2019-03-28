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
class GenoVector3;

#endif // GNARLY_GENOME_VECTOR3_FORWARD

#ifndef GNARLY_GENOME_VECTOR2
#define GNARLY_GENOME_VECTOR2

#include <ostream>

#include "GenoVector.h"
#include "GenoVector3.h"

template <typename T>
class GenoVector2 : public GenoVector<2, T> {
	private:
		typedef GenoVector<2, T> GenoVector;

		GenoVector2(T * newV) :
			GenoVector(newV) {}
	public:
		GenoVector2() :
			GenoVector() {}
		
		GenoVector2(const T & x) :
			GenoVector(new T[2] { x, T() }) {}

		GenoVector2(const T & x, const T & y) :
			GenoVector(new T[2] { x, y }) {}

		GenoVector2(const GenoVector2<T> & vector) :
			GenoVector(vector) {}

		GenoVector2(GenoVector2<T> && vector) noexcept :
			GenoVector(vector) {}

		GenoVector2<T> & operator=(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator=(GenoVector2<T> && vector) noexcept {
			GenoVector::operator=(vector);
			return *this;
		}

		GenoVector2<T> & operator+=(const GenoVector2<T> & vector) {
			GenoVector::v[0] += vector.v[0];
			GenoVector::v[1] += vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator-=(const GenoVector2<T> & vector) {
			GenoVector::v[0] -= vector.v[0];
			GenoVector::v[1] -= vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator*=(const T & scalar) {
			GenoVector::v[0] *= scalar;
			GenoVector::v[1] *= scalar;
			return *this;
		}

		GenoVector2<T> & operator*=(const GenoVector2<T> & vector) {
			GenoVector::v[0] *= vector.v[0];
			GenoVector::v[1] *= vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator/=(const T & scalar) {
			GenoVector::v[0] /= scalar;
			GenoVector::v[1] /= scalar;
			return *this;
		}

		GenoVector2<T> & operator/=(const GenoVector2<T> & vector) {
			GenoVector::v[0] /= vector.v[0];
			GenoVector::v[1] /= vector.v[1];
			return *this;
		}

		GenoVector2<T> operator-() const {
			return { -GenoVector::v[0],
			         -GenoVector::v[1] };
		}

		GenoVector2<T> operator+(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] + vector.v[0],
			         GenoVector::v[1] + vector.v[1] };
		}

		GenoVector2<T> operator-(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] - vector.v[0],
			         GenoVector::v[1] - vector.v[1] };
		}
		
		GenoVector2<T> operator*(const T & scalar) const {
			return { GenoVector::v[0] * scalar,
			         GenoVector::v[1] * scalar };
		}

		GenoVector2<T> operator*(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] * vector.v[0],
			         GenoVector::v[1] * vector.v[1] };
		}
		
		GenoVector2<T> operator/(const T & scalar) const {
			return { GenoVector::v[0] / scalar,
			         GenoVector::v[1] / scalar };
		}
		
		GenoVector2<T> operator/(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] / vector.v[0],
			         GenoVector::v[1] / vector.v[1] };
		}

		bool operator==(const GenoVector2<T> & vector) const {
			return GenoVector::v[0] == vector.v[0]
			    && GenoVector::v[1] == vector.v[1];
		}

		bool operator!=(const GenoVector2<T> & vector) const {
			return GenoVector::v[0] != vector.v[0]
			    || GenoVector::v[1] != vector.v[1];
		}

		GenoVector2<T> getNegate() const {
			return { -GenoVector::v[0],
			         -GenoVector::v[1] };
		}

		GenoVector2<T> & negate() {
			GenoVector::v[0] = -GenoVector::v[0];
			GenoVector::v[1] = -GenoVector::v[1];
			return *this;
		}

		GenoVector2<T> getAdd(const T & x, const T & y) {
			return { GenoVector::v[0] + x,
			         GenoVector::v[1] + y };
		}

		GenoVector2<T> getAdd(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] + vector.v[0],
			         GenoVector::v[1] + vector.v[1] };
		}

		GenoVector2<T> & add(const T & x, const T & y) {
			GenoVector::v[0] += x;
			GenoVector::v[1] += y;
			return *this;
		}

		GenoVector2<T> & add(const GenoVector2<T> & vector) {
			GenoVector::v[0] += vector.v[0];
			GenoVector::v[1] += vector.v[1];
			return *this;
		}

		GenoVector2<T> getSubtract(const T & x, const T & y) {
			return { GenoVector::v[0] - x,
			         GenoVector::v[1] - y };
		}

		GenoVector2<T> getSubtract(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] - vector.v[0],
			         GenoVector::v[1] - vector.v[1] };
		}

		GenoVector2<T> & subtract(const T & x, const T & y) {
			GenoVector::v[0] -= x;
			GenoVector::v[1] -= y;
			return *this;
		}

		GenoVector2<T> & subtract(const GenoVector2<T> & vector) {
			GenoVector::v[0] -= vector.v[0];
			GenoVector::v[1] -= vector.v[1];
			return *this;
		}

		GenoVector2<T> getMultiply(const T & scalar) const {
			return { GenoVector::v[0] * scalar,
			         GenoVector::v[1] * scalar };
		}

		GenoVector2<T> getMultiply(const T & x, const T & y) {
			return { GenoVector::v[0] * x,
			         GenoVector::v[1] * y };
		}

		GenoVector2<T> getMultiply(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] * vector.v[0],
			         GenoVector::v[1] * vector.v[1] };
		}

		GenoVector2<T> & multiply(const T & scalar) {
			GenoVector::v[0] *= scalar;
			GenoVector::v[1] *= scalar;
			return *this;
		}

		GenoVector2<T> & multiply(const T & x, const T & y) {
			GenoVector::v[0] *= x;
			GenoVector::v[1] *= y;
			return *this;
		}

		GenoVector2<T> & multiply(const GenoVector2<T> & vector) {
			GenoVector::v[0] *= vector.v[0];
			GenoVector::v[1] *= vector.v[1];
			return *this;
		}

		GenoVector2<T> getDivide(const T & scalar) const {
			return { GenoVector::v[0] / scalar,
			         GenoVector::v[1] / scalar };
		}

		GenoVector2<T> getDivide(const T & x, const T & y) {
			return { GenoVector::v[0] / x,
			         GenoVector::v[1] / y };
		}

		GenoVector2<T> getDivide(const GenoVector2<T> & vector) const {
			return { GenoVector::v[0] / vector.v[0],
			         GenoVector::v[1] / vector.v[1] };
		}

		GenoVector2<T> & divide(const T & scalar) {
			GenoVector::v[0] /= scalar;
			GenoVector::v[1] /= scalar;
			return *this;
		}

		GenoVector2<T> & divide(const T & x, const T & y) {
			GenoVector::v[0] /= x;
			GenoVector::v[1] /= y;
			return *this;
		}

		GenoVector2<T> & divide(const GenoVector2<T> & vector) {
			GenoVector::v[0] /= vector.v[0];
			GenoVector::v[1] /= vector.v[1];
			return *this;
		}
		
		T getLength() const {
			return sqrt(GenoVector::v[0] * GenoVector::v[0]
			          + GenoVector::v[1] * GenoVector::v[1]);
		}

		T getLengthSquared() const {
			return GenoVector::v[0] * GenoVector::v[0]
			     + GenoVector::v[1] * GenoVector::v[1];
		}

		GenoVector2<T> & setLength(const T & length) {
			T scale = length / getLength();
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			return *this;
		}

		T dot(const GenoVector2<T> & vector) const {
			return GenoVector::v[0] * vector.v[0] + GenoVector::v[1] * vector.v[1];
		}

		GenoVector2<T> getProject(const T & x, const T & y) const {
			T scalar = (GenoVector::v[0] * x + GenoVector::v[1] * y) / (x * x + y * y);
			return GenoVector2<T>(scalar * x, scalar * y);
		}

		GenoVector2<T> getProject(const GenoVector2<T> & vector) const {
			return (dot(vector) / vector.getLengthSquared()) * vector;
		}

		GenoVector2<T> & project(const GenoVector2<T> & vector) {
			T scalar = dot(vector) / vector.lengthSquared();
			GenoVector::v[0] = scalar * vector.v[0];
			GenoVector::v[1] = scalar * vector.v[1];
			return *this;
		}

		T getAngle() const {
			return atan2(GenoVector::v[1], GenoVector::v[0]);
		}

		GenoVector2<T> & setAngle(const T & angle) {
			T length = getLength();
			GenoVector::v[0] = cos(angle) * length;
			GenoVector::v[1] = sin(angle) * length;
			return *this;
		}

		GenoVector2<T> getRotate(const T & angle) const {
			T sine   = sin(angle);
			T cosine = cos(angle);
			return { GenoVector::v[0] * cosine - GenoVector::v[1] * sine,
			         GenoVector::v[0] * sine   + GenoVector::v[1] * cosine };
		}

		GenoVector2<T> & rotate(const T & angle) {
			T sine   = sin(angle);
			T cosine = cos(angle);
			T x = GenoVector::v[0] * cosine - GenoVector::v[1] * sine;
			T y = GenoVector::v[0] * sine   + GenoVector::v[1] * cosine;
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector2<T> & set(const T & x, const T & y) {
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector2<T> & set(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			return *this;
		}

		GenoVector2<T> getTranslate(const T & translateX, const T & translateY) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] + translateY };
		}

		GenoVector2<T> getTranslate(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[1] };
		}

		GenoVector2<T> & translate(const T & translateX, const T & translateY) {
			GenoVector::v[0] += translateX;
			GenoVector::v[1] += translateY;
			return *this;
		}

		GenoVector2<T> & translate(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[1];
			return *this;
		}

		GenoVector2<T> getScale(const T & scale) const {
			return { GenoVector::v[0] * scale,
			         GenoVector::v[1] * scale };
		}

		GenoVector2<T> getScale(const T & scaleX, const T & scaleY) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] * scaleY };
		}

		GenoVector2<T> getScale(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[1] };
		}

		GenoVector2<T> & scale(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			return *this;
		}

		GenoVector2<T> & scale(const T & scaleX, const T & scaleY) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[1] *= scaleY;
			return *this;
		}

		GenoVector2<T> & scale(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[1];
			return *this;
		}

		GenoVector2<T> & setX(const T & x) {
			GenoVector::v[0] = x;
			return *this;
		}

		GenoVector2<T> & setY(const T & y) {
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector2<T> & setXY(const T & x, const T & y) {
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector2<T> & setXY(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			return *this;
		}

		GenoVector2<T> & setYX(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[1];
			GenoVector::v[1] = vector.v[0];
			return *this;
		}

		GenoVector2<T> getTranslateX(const T & translateX) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] };
		}

		GenoVector2<T> getTranslateY(const T & translateY) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] + translateY };
		}
		
		GenoVector2<T> getTranslateXY(const T & translateX, const T & translateY) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] + translateY };
		}

		GenoVector2<T> getTranslateXY(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[1] };
		}

		GenoVector2<T> getTranslateYX(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[1],
			         GenoVector::v[1] + translate.v[0] };
		}

		GenoVector2<T> & translateX(const T & translateX) {
			GenoVector::v[0] += translateX;
			return *this;
		}

		GenoVector2<T> & translateY(const T & translateY) {
			GenoVector::v[1] += translateY;
			return *this;
		}

		GenoVector2<T> & translateXY(const T & translateX, const T & translateY) {
			GenoVector::v[0] += translateX;
			GenoVector::v[1] += translateY;
			return *this;
		}

		GenoVector2<T> & translateXY(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[1];
			return *this;
		}

		GenoVector2<T> & translateYX(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[1];
			GenoVector::v[1] += translate.v[0];
			return *this;
		}

		GenoVector2<T> getScaleX(const T & scaleX) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] };
		}

		GenoVector2<T> getScaleY(const T & scaleY) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] * scaleY };
		}

		GenoVector2<T> getScaleXY(const T & scale) const {
			return { GenoVector::v[0] * scale,
			         GenoVector::v[1] * scale };
		}

		GenoVector2<T> getScaleXY(const T & scaleX, const T & scaleY) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] * scaleY };
		}

		GenoVector2<T> getScaleXY(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[1] };
		}

		GenoVector2<T> getScaleYX(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[1],
			         GenoVector::v[1] * scale.v[0] };
		}

		GenoVector2<T> & scaleX(const T & scaleX) {
			GenoVector::v[0] *= scaleX;
			return *this;
		}

		GenoVector2<T> & scaleY(const T & scaleY) {
			GenoVector::v[1] *= scaleY;
			return *this;
		}

		GenoVector2<T> & scaleXY(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			return *this;
		}

		GenoVector2<T> & scaleXY(const T & scaleX, const T & scaleY) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[1] *= scaleY;
			return *this;
		}

		GenoVector2<T> & scaleXY(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[1];
			return *this;
		}

		GenoVector2<T> & scaleYX(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[1];
			GenoVector::v[1] *= scale.v[0];
			return *this;
		}

		T & x() {
			return GenoVector::v[0];
		}

		T & y() {
			return GenoVector::v[1];
		}

		T x() const {
			return GenoVector::v[0];
		}

		T y() const {
			return GenoVector::v[1];
		}

		GenoVector2<T> xx() const {
			return { GenoVector::v[0],
			         GenoVector::v[0] };
		}

		GenoVector2<T> xy() const {
			return { GenoVector::v[0],
			         GenoVector::v[1] };
		}

		GenoVector2<T> yx() const {
			return { GenoVector::v[1],
			         GenoVector::v[0] };
		}

		GenoVector2<T> yy() const {
			return { GenoVector::v[1],
			         GenoVector::v[1] };
		}

		GenoVector3<T> xxx() const {
			return { GenoVector::v[0], 
			         GenoVector::v[0], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> xxy() const {
			return { GenoVector::v[0], 
			         GenoVector::v[0], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> xyx() const {
			return { GenoVector::v[0], 
			         GenoVector::v[1], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> xyy() const {
			return { GenoVector::v[0], 
			         GenoVector::v[1], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> yxx() const {
			return { GenoVector::v[1], 
			         GenoVector::v[0], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> yxy() const {
			return { GenoVector::v[1], 
			         GenoVector::v[0], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> yyx() const {
			return { GenoVector::v[1], 
			         GenoVector::v[1], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> yyy() const {
			return { GenoVector::v[1], 
			         GenoVector::v[1], 
			         GenoVector::v[1] };
		}

		virtual ~GenoVector2() noexcept {}
};

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector2<T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << '>' << std::endl;
}

template <typename FT>
GenoVector2<FT> operator*(const FT & left, const GenoVector2<FT> & right) {
	return { left * right.v[0], left * right.v[1] };
}

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