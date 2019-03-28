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
class GenoVector2;

#endif // GNARLY_GENOME_VECTOR2_FORWARD

#ifndef GNARLY_GENOME_VECTOR3
#define GNARLY_GENOME_VECTOR3

#include <ostream>

#include "GenoVector.h"
#include "GenoVector2.h"

template <typename T>
class GenoVector3 : public GenoVector<3, T> {
	private:
		typedef GenoVector<3, T> GenoVector;

		GenoVector3(T * newV) :
			GenoVector(newV) {}
	public:
		GenoVector3() :
			GenoVector() {}

		GenoVector3(const T & x) :
			GenoVector(new T[3] { x, T(), T() }) {}

		GenoVector3(const T & x, const T & y) :
			GenoVector(new T[3] { x, y, T() }) {}

		GenoVector3(const T & x, const T & y, const T & z) :
			GenoVector(new T[3] { x, y, z }) {}

		GenoVector3(const GenoVector3<T> & vector) :
			GenoVector(vector) {}

		GenoVector3(GenoVector3<T> && vector) noexcept :
			GenoVector(vector) {}

		GenoVector3<T> & operator=(const GenoVector3<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			GenoVector::v[2] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & operator=(GenoVector3<T> && vector) {
			GenoVector::operator=(vector);
			return *this;
		}

		GenoVector3<T> & operator+=(const GenoVector3<T> & vector) {
			GenoVector::v[0] += vector.v[0];
			GenoVector::v[1] += vector.v[1];
			GenoVector::v[2] += vector.v[2];
			return *this;
		}

		GenoVector3<T> & operator-=(const GenoVector3<T> & vector) {
			GenoVector::v[0] -= vector.v[0];
			GenoVector::v[1] -= vector.v[1];
			GenoVector::v[2] -= vector.v[2];
			return *this;
		}

		GenoVector3<T> & operator*=(const T & scalar) {
			GenoVector::v[0] *= scalar;
			GenoVector::v[1] *= scalar;
			GenoVector::v[2] *= scalar;
			return *this;
		}

		GenoVector3<T> & operator*=(const GenoVector3<T> & vector) {
			GenoVector::v[0] *= vector.v[0];
			GenoVector::v[1] *= vector.v[1];
			GenoVector::v[2] *= vector.v[2];
			return *this;
		}

		GenoVector3<T> & operator/=(const T & scalar) {
			GenoVector::v[0] /= scalar;
			GenoVector::v[1] /= scalar;
			GenoVector::v[2] /= scalar;
			return *this;
		}

		GenoVector3<T> & operator/=(const GenoVector3<T> & vector) {
			GenoVector::v[0] /= vector.v[0];
			GenoVector::v[1] /= vector.v[1];
			GenoVector::v[2] /= vector.v[2];
			return *this;
		}

		GenoVector3<T> operator-() const {
			return { -GenoVector::v[0],
			         -GenoVector::v[1],
			         -GenoVector::v[2] };
		}

		GenoVector3<T> operator+(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] + vector.v[0],
			         GenoVector::v[1] + vector.v[1],
			         GenoVector::v[2] + vector.v[2] };
		}

		GenoVector3<T> operator-(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] - vector.v[0],
			         GenoVector::v[1] - vector.v[1],
			         GenoVector::v[2] - vector.v[2] };
		}

		GenoVector3<T> operator*(const T & scalar) const {
			return { GenoVector::v[0] * scalar,
			         GenoVector::v[1] * scalar,
			         GenoVector::v[2] * scalar };
		}

		GenoVector3<T> operator*(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] * vector.v[0],
			         GenoVector::v[1] * vector.v[1],
			         GenoVector::v[2] * vector.v[2] };
		}

		GenoVector3<T> operator/(const T & scalar) const {
			return { GenoVector::v[0] / scalar,
			         GenoVector::v[1] / scalar,
			         GenoVector::v[2] / scalar };
		}

		GenoVector3<T> operator/(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] / vector.v[0],
			         GenoVector::v[1] / vector.v[1],
			         GenoVector::v[2] / vector.v[2] };
		}

		bool operator==(const GenoVector3<T> & vector) const {
			return GenoVector::v[0] == vector.v[0]
			    && GenoVector::v[1] == vector.v[1]
			    && GenoVector::v[2] == vector.v[2];
		}

		bool operator!=(const GenoVector3<T> & vector) const {
			return GenoVector::v[0] != vector.v[0]
			    || GenoVector::v[1] != vector.v[1]
			    || GenoVector::v[2] != vector.v[2];
		}

		GenoVector3<T> getNegate() const {
			return { -GenoVector::v[0],
			         -GenoVector::v[1],
			         -GenoVector::v[2] };
		}

		GenoVector3<T> & negate() {
			GenoVector::v[0] = -GenoVector::v[0];
			GenoVector::v[1] = -GenoVector::v[1];
			GenoVector::v[2] = -GenoVector::v[2];
			return *this;
		}

		GenoVector3<T> getAdd(const T & x, const T & y, const T & z) const {
			return { GenoVector::v[0] + x,
			         GenoVector::v[1] + y,
			         GenoVector::v[2] + z };
		}

		GenoVector3<T> getAdd(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] + vector.v[0],
			         GenoVector::v[1] + vector.v[1],
			         GenoVector::v[2] + vector.v[2] };
		}

		GenoVector3<T> & add(const T & x, const T & y, const T & z) {
			GenoVector::v[0] += x;
			GenoVector::v[1] += y;
			GenoVector::v[2] += z;
			return *this;
		}

		GenoVector3<T> & add(const GenoVector3<T> & vector) {
			GenoVector::v[0] += vector.v[0];
			GenoVector::v[1] += vector.v[1];
			GenoVector::v[2] += vector.v[2];
			return *this;
		}

		GenoVector3<T> getSubtract(const T & x, const T & y, const T & z) const {
			return { GenoVector::v[0] - x,
			         GenoVector::v[1] - y,
			         GenoVector::v[2] - z };
		}

		GenoVector3<T> getSubtract(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] - vector.v[0],
			         GenoVector::v[1] - vector.v[1],
			         GenoVector::v[2] - vector.v[2] };
		}

		GenoVector3<T> & subtract(const T & x, const T & y, const T & z) {
			GenoVector::v[0] -= x;
			GenoVector::v[1] -= y;
			GenoVector::v[2] -= z;
			return *this;
		}

		GenoVector3<T> & subtract(const GenoVector3<T> & vector) {
			GenoVector::v[0] -= vector.v[0];
			GenoVector::v[1] -= vector.v[1];
			GenoVector::v[2] -= vector.v[2];
			return *this;
		}

		GenoVector3<T> getMultiply(const T & scalar) const {
			return { GenoVector::v[0] * scalar,
			         GenoVector::v[1] * scalar,
			         GenoVector::v[2] * scalar };
		}

		GenoVector3<T> getMultiply(const T & x, const T & y, const T & z) const {
			return { GenoVector::v[0] * x,
			         GenoVector::v[1] * y,
			         GenoVector::v[2] * z };
		}

		GenoVector3<T> getMultiply(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] * vector.v[0],
			         GenoVector::v[1] * vector.v[1],
			         GenoVector::v[2] * vector.v[2] };
		}

		GenoVector3<T> & multiply(const T & scalar) {
			GenoVector::v[0] *= scalar;
			GenoVector::v[1] *= scalar;
			GenoVector::v[2] *= scalar;
			return *this;
		}

		GenoVector3<T> & multiply(const T & x, const T & y, const T & z) {
			GenoVector::v[0] *= x;
			GenoVector::v[1] *= y;
			GenoVector::v[2] *= z;
			return *this;
		}

		GenoVector3<T> & multiply(const GenoVector3<T> & vector) {
			GenoVector::v[0] *= vector.v[0];
			GenoVector::v[1] *= vector.v[1];
			GenoVector::v[2] *= vector.v[2];
			return *this;
		}

		GenoVector3<T> getDivide(const T & scalar) const {
			return { GenoVector::v[0] / scalar,
			         GenoVector::v[1] / scalar,
			         GenoVector::v[2] / scalar };
		}

		GenoVector3<T> getDivide(const T & x, const T & y, const T & z) const {
			return { GenoVector::v[0] / x,
			         GenoVector::v[1] / y,
			         GenoVector::v[2] / z };
		}

		GenoVector3<T> getDivide(const GenoVector3<T> & vector) const {
			return { GenoVector::v[0] / vector.v[0],
			         GenoVector::v[1] / vector.v[1],
			         GenoVector::v[2] / vector.v[2] };
		}

		GenoVector3<T> & divide(const T & scalar) {
			GenoVector::v[0] /= scalar;
			GenoVector::v[1] /= scalar;
			GenoVector::v[2] /= scalar;
			return *this;
		}

		GenoVector3<T> & divide(const T & x, const T & y, const T & z) {
			GenoVector::v[0] /= x;
			GenoVector::v[1] /= y;
			GenoVector::v[2] /= z;
			return *this;
		}

		GenoVector3<T> & divide(const GenoVector3<T> & vector) {
			GenoVector::v[0] /= vector.v[0];
			GenoVector::v[1] /= vector.v[1];
			GenoVector::v[2] /= vector.v[2];
			return *this;
		}

		T getLength() const {
			return sqrt(GenoVector::v[0] * GenoVector::v[0]
			          + GenoVector::v[1] * GenoVector::v[1]
			          + GenoVector::v[2] * GenoVector::v[2]);
		}

		T getLengthSquared() const {
			return GenoVector::v[0] * GenoVector::v[0]
			     + GenoVector::v[1] * GenoVector::v[1]
			     + GenoVector::v[2] * GenoVector::v[2];
		}

		GenoVector3<T> & setLength(const T & length) {
			T scale = length / getLength();
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			GenoVector::v[2] *= scale;
			return *this;
		}

		T dot(const GenoVector3<T> & vector) const {
			return GenoVector::v[0] * vector.v[0]
			     + GenoVector::v[1] * vector.v[1];
		}

		GenoVector3<T> getProject(const T & x, const T & y, const T & z) const {
			T scalar = (GenoVector::v[0] * x + GenoVector::v[1] * y) / (x * x + y * y + z * z);
			return GenoVector3<T>(scalar * x, scalar * y, scalar * z);
		}

		GenoVector3<T> getProject(const GenoVector3<T> & vector) const {
			return (dot(vector) / vector.getLengthSquared()) * vector;
		}

		GenoVector3<T> & project(const GenoVector3<T> & vector) {
			T scalar = dot(vector) / vector.getLengthSquared();
			GenoVector::v[0] = scalar * vector.v[0];
			GenoVector::v[1] = scalar * vector.v[1];
			GenoVector::v[2] = scalar * vector.v[2];
			return *this;
		}

		GenoVector3<T> & set(const T & x, const T & y, const T & z) {
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			GenoVector::v[2] = z;
			return *this;
		}

		GenoVector3<T> & set(const GenoVector3<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			GenoVector::v[2] = vector.v[2];
			return *this;
		}

		GenoVector3<T> getTranslate(const T & translateX, const T & translateY, const T & translateZ) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] + translateY,
			         GenoVector::v[2] + translateZ };
		}

		GenoVector3<T> getTranslate(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[1],
			         GenoVector::v[2] + translate.v[2] };
		}

		GenoVector3<T> & translate(const T & translateX, const T & translateY, const T & translateZ) {
			GenoVector::v[0] += translateX;
			GenoVector::v[1] += translateY;
			GenoVector::v[2] += translateZ;
			return *this;
		}

		GenoVector3<T> & translate(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[1];
			GenoVector::v[2] += translate.v[2];
			return *this;
		}

		GenoVector3<T> getScale(const T & scale) const {
			return { GenoVector::v[0] * scale,
			         GenoVector::v[1] * scale,
			         GenoVector::v[2] * scale };
		}

		GenoVector3<T> getScale(const T & scaleX, const T & scaleY, const T & scaleZ) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] * scaleY,
			         GenoVector::v[2] * scaleZ };
		}

		GenoVector3<T> getScale(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[1],
			         GenoVector::v[2] * scale.v[2] };
		}

		GenoVector3<T> scale(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			GenoVector::v[2] *= scale;
		}

		GenoVector3<T> scale(const T & scaleX, const T & scaleY, const T & scaleZ) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[1] *= scaleY;
			GenoVector::v[2] *= scaleZ;
		}

		GenoVector3<T> scale(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[1];
			GenoVector::v[2] *= scale.v[2];
		}

		GenoVector3<T> & setX(const T & x) {
			GenoVector::v[0] = x;
			return *this;
		}

		GenoVector3<T> & setY(const T & y) {
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector3<T> & setZ(const T & z) {
			GenoVector::v[2] = z;
			return *this;
		}

		GenoVector3<T> & setXY(const T & x, const T & y) {
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			return *this;
		}

		GenoVector3<T> & setXY(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setXZ(const T & x, const T & z) {
			GenoVector::v[0] = x;
			GenoVector::v[2] = z;
			return *this;
		}

		GenoVector3<T> & setXZ(const GenoVector2<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[2] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setYX(const GenoVector2<T> & vector) {
			GenoVector::v[1] = vector.v[0];
			GenoVector::v[0] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setYZ(const T & y, const T & z) {
			GenoVector::v[1] = y;
			GenoVector::V[2] = z;
			return *this;
		}

		GenoVector3<T> & setYZ(const GenoVector2<T> & vector) {
			GenoVector::v[1] = vector.v[0];
			GenoVector::v[2] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setZX(const GenoVector2<T> & vector) {
			GenoVector::v[2] = vector.v[0];
			GenoVector::v[0] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setZY(const GenoVector2<T> & vector) {
			GenoVector::v[2] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			return *this;
		}

		GenoVector3<T> & setXYZ(const T & x, const T & y, const T & z) {
			GenoVector::v[0] = x;
			GenoVector::v[1] = y;
			GenoVector::v[2] = z;
			return *this;
		}

		GenoVector3<T> & setXYZ(const GenoVector3<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			GenoVector::v[2] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & setXZY(const GenoVector3<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[2] = vector.v[1];
			GenoVector::v[1] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & setYXZ(const GenoVector3<T> & vector) {
			GenoVector::v[1] = vector.v[0];
			GenoVector::v[0] = vector.v[1];
			GenoVector::v[2] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & setYZX(const GenoVector3<T> & vector) {
			GenoVector::v[1] = vector.v[0];
			GenoVector::v[2] = vector.v[1];
			GenoVector::v[0] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & setZXY(const GenoVector3<T> & vector) {
			GenoVector::v[2] = vector.v[0];
			GenoVector::v[0] = vector.v[1];
			GenoVector::v[1] = vector.v[2];
			return *this;
		}

		GenoVector3<T> & setZYX(const GenoVector3<T> & vector) {
			GenoVector::v[0] = vector.v[0];
			GenoVector::v[1] = vector.v[1];
			GenoVector::v[2] = vector.v[2];
			return *this;
		}

		GenoVector3<T> getTranslateX(const T & translateX) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getTranslateY(const T & translateY) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] + translateY,
			         GenoVector::v[2] };
		}

		GenoVector3<T> getTranslateZ(const T & translateZ) const {
			return { GenoVector::v[0],
			         GenoVector::v[1],
			         GenoVector::v[2] + translateZ };
		}

		GenoVector3<T> getTranslateXY(const T & translateX, const T & translateY) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] + translateY,
			         GenoVector::v[2] };
		}

		GenoVector3<T> getTranslateXY(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[1],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getTranslateXZ(const T & translateX, const T & translateZ) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1],
			         GenoVector::v[2] + translateZ };
		}

		GenoVector3<T> getTranslateXZ(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1],
			         GenoVector::v[2] + translate.v[1] };
		}

		GenoVector3<T> getTranslateYX(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[1],
			         GenoVector::v[1] + translate.v[0],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getTranslateYZ(const T & translateY, const T & translateZ) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] + translateY,
			         GenoVector::v[2] + translateZ };
		}

		GenoVector3<T> getTranslateYZ(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] + translate.v[0],
			         GenoVector::v[2] + translate.v[1] };
		}

		GenoVector3<T> getTranslateZX(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0] + translate.v[1],
			         GenoVector::v[1],
			         GenoVector::v[2] + translate.v[0] };
		}

		GenoVector3<T> getTranslateZY(const GenoVector2<T> & translate) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] + translate.v[1],
			         GenoVector::v[2] + translate.v[0] };
		}

		GenoVector3<T> getTranslateXYZ(const T & translateX, const T & translateY, const T & translateZ) const {
			return { GenoVector::v[0] + translateX,
			         GenoVector::v[1] + translateY,
			         GenoVector::v[2] + translateZ };
		}

		GenoVector3<T> getTranslateXYZ(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[1],
			         GenoVector::v[2] + translate.v[2] };
		}

		GenoVector3<T> getTranslateXZY(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[0],
			         GenoVector::v[1] + translate.v[2],
			         GenoVector::v[2] + translate.v[1] };
		}

		GenoVector3<T> getTranslateYXZ(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[1],
			         GenoVector::v[1] + translate.v[0],
			         GenoVector::v[2] + translate.v[2] };
		}

		GenoVector3<T> getTranslateYZX(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[1],
			         GenoVector::v[1] + translate.v[2],
			         GenoVector::v[2] + translate.v[0] };
		}

		GenoVector3<T> getTranslateZXY(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[2],
			         GenoVector::v[1] + translate.v[0],
			         GenoVector::v[2] + translate.v[1] };
		}

		GenoVector3<T> getTranslateZYX(const GenoVector3<T> & translate) const {
			return { GenoVector::v[0] + translate.v[2],
			         GenoVector::v[1] + translate.v[1],
			         GenoVector::v[2] + translate.v[0] };
		}

		GenoVector3<T> & translateX(const T & translateX) {
			GenoVector::v[0] += translateX;
			return *this;
		}
		
		GenoVector3<T> & translateY(const T & translateY) {
			GenoVector::v[1] += translateY;
			return *this;
		}

		GenoVector3<T> & translateZ(const T & translateZ) {
			GenoVector::v[2] += translateZ;
			return *this;
		}

		GenoVector3<T> & translateXY(const T & translateX, const T & translateY) {
			GenoVector::v[0] += translateX;
			GenoVector::v[1] += translateY;
			return *this;
		}

		GenoVector3<T> & translateXY(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[1];
			return *this;
		}

		GenoVector3<T> & translateXZ(const T & translateX, const T & translateZ) {
			GenoVector::v[0] += translateX;
			GenoVector::v[2] += translateZ;
			return *this;
		}

		GenoVector3<T> & translateXZ(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[2] += translate.v[1];
			return *this;
		}

		GenoVector3<T> & translateYX(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[1];
			GenoVector::v[1] += translate.v[0];
			return *this;
		}

		GenoVector3<T> & translateYZ(const T & translateY, const T & translateZ) {
			GenoVector::v[1] += translateY;
			GenoVector::v[2] += translateZ;
			return *this;
		}

		GenoVector3<T> & translateYZ(const GenoVector2<T> & translate) {
			GenoVector::v[1] += translate.v[0];
			GenoVector::v[2] += translate.v[1];
			return *this;
		}

		GenoVector3<T> & translateZX(const GenoVector2<T> & translate) {
			GenoVector::v[0] += translate.v[1];
			GenoVector::v[2] += translate.v[0];
			return *this;
		}

		GenoVector3<T> & translateZY(const GenoVector2<T> & translate) {
			GenoVector::v[1] += translate.v[1];
			GenoVector::v[2] += translate.v[0];
			return *this;
		}

		GenoVector3<T> & translateXYZ(const T & translateX, const T & translateY, const T & translateZ) {
			GenoVector::v[0] += translateX;
			GenoVector::v[1] += translateY;
			GenoVector::v[2] += translateZ;
			return *this;
		}

		GenoVector3<T> & translateXYZ(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[1];
			GenoVector::v[2] += translate.v[2];
			return *this;
		}

		GenoVector3<T> & translateXZY(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[0];
			GenoVector::v[1] += translate.v[2];
			GenoVector::v[2] += translate.v[1];
			return *this;
		}

		GenoVector3<T> & translateYXZ(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[1];
			GenoVector::v[1] += translate.v[0];
			GenoVector::v[2] += translate.v[2];
			return *this;
		}

		GenoVector3<T> & translateYZX(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[2];
			GenoVector::v[1] += translate.v[0];
			GenoVector::v[2] += translate.v[1];
			return *this;
		}

		GenoVector3<T> & translateZXY(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[1];
			GenoVector::v[1] += translate.v[2];
			GenoVector::v[2] += translate.v[0];
			return *this;
		}

		GenoVector3<T> & translateZYX(const GenoVector3<T> & translate) {
			GenoVector::v[0] += translate.v[2];
			GenoVector::v[1] += translate.v[1];
			GenoVector::v[2] += translate.v[0];
			return *this;
		}

		GenoVector3<T> getScaleX(const T & scaleX) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getScaleY(const T & scaleY) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] * scaleY,
			         GenoVector::v[2] };
		}

		GenoVector3<T> getScaleZ(const T & scaleZ) const {
			return { GenoVector::v[0],
			         GenoVector::v[1],
			         GenoVector::v[2] * scaleZ };
		}

		GenoVector3<T> getScaleXY(const T & scaleX, const T & scaleY) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] * scaleY,
			         GenoVector::v[2] };
		}

		GenoVector3<T> getScaleXY(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[1],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getScaleXZ(const T & scaleX, const T & scaleZ) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1],
			         GenoVector::v[2] * scaleZ };
		}

		GenoVector3<T> getScaleXZ(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1],
			         GenoVector::v[2] * scale.v[1] };
		}

		GenoVector3<T> getScaleYX(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[1],
			         GenoVector::v[1] * scale.v[0],
			         GenoVector::v[2] };
		}

		GenoVector3<T> getScaleYZ(const T & scaleY, const T & scaleZ) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] * scaleY,
			         GenoVector::v[2] * scaleZ };
		}

		GenoVector3<T> getScaleYZ(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] * scale.v[0],
			         GenoVector::v[2] * scale.v[1] };
		}

		GenoVector3<T> getScaleZX(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0] * scale.v[1],
			         GenoVector::v[1],
			         GenoVector::v[2] * scale.v[0] };
		}

		GenoVector3<T> getScaleZY(const GenoVector2<T> & scale) const {
			return { GenoVector::v[0],
			         GenoVector::v[1] * scale.v[1],
			         GenoVector::v[2] * scale.v[0] };
		}

		GenoVector3<T> getScaleXYZ(const T & scaleX, const T & scaleY, const T & scaleZ) const {
			return { GenoVector::v[0] * scaleX,
			         GenoVector::v[1] * scaleY,
			         GenoVector::v[2] * scaleZ };
		}

		GenoVector3<T> getScaleXYZ(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[1],
			         GenoVector::v[2] * scale.v[2] };
		}

		GenoVector3<T> getScaleXZY(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[0],
			         GenoVector::v[1] * scale.v[2],
			         GenoVector::v[2] * scale.v[1] };
		}

		GenoVector3<T> getScaleYXZ(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[1],
			         GenoVector::v[1] * scale.v[0],
			         GenoVector::v[2] * scale.v[2] };
		}

		GenoVector3<T> getScaleYZX(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[1],
			         GenoVector::v[1] * scale.v[2],
			         GenoVector::v[2] * scale.v[0] };
		}

		GenoVector3<T> getScaleZXY(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[2],
			         GenoVector::v[1] * scale.v[0],
			         GenoVector::v[2] * scale.v[1] };
		}

		GenoVector3<T> getScaleZYX(const GenoVector3<T> & scale) const {
			return { GenoVector::v[0] * scale.v[2],
			         GenoVector::v[1] * scale.v[1],
			         GenoVector::v[2] * scale.v[0] };
		}

		GenoVector3<T> & scaleX(const T & scaleX) {
			GenoVector::v[0] *= scaleX;
			return *this;
		}
		
		GenoVector3<T> & scaleY(const T & scaleY) {
			GenoVector::v[1] *= scaleY;
			return *this;
		}

		GenoVector3<T> & scaleZ(const T & scaleZ) {
			GenoVector::v[2] *= scaleZ;
			return *this;
		}

		GenoVector3<T> & scaleXY(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			return *this;
		}

		GenoVector3<T> & scaleXY(const T & scaleX, const T & scaleY) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[1] *= scaleY;
			return *this;
		}

		GenoVector3<T> & scaleXY(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[1];
			return *this;
		}

		GenoVector3<T> & scaleXZ(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[2] *= scale;
			return *this;
		}

		GenoVector3<T> & scaleXZ(const T & scaleX, const T & scaleZ) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[2] *= scaleZ;
			return *this;
		}

		GenoVector3<T> & scaleXZ(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[2] *= scale.v[1];
			return *this;
		}

		GenoVector3<T> & scaleYX(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[1];
			GenoVector::v[1] *= scale.v[0];
			return *this;
		}

		GenoVector3<T> & scaleYZ(const T & scale) {
			GenoVector::v[1] *= scale;
			GenoVector::v[2] *= scale;
			return *this;
		}

		GenoVector3<T> & scaleYZ(const T & scaleY, const T & scaleZ) {
			GenoVector::v[1] *= scaleY;
			GenoVector::v[2] *= scaleZ;
			return *this;
		}

		GenoVector3<T> & scaleYZ(const GenoVector2<T> & scale) {
			GenoVector::v[1] *= scale.v[0];
			GenoVector::v[2] *= scale.v[1];
			return *this;
		}

		GenoVector3<T> & scaleZX(const GenoVector2<T> & scale) {
			GenoVector::v[0] *= scale.v[1];
			GenoVector::v[2] *= scale.v[0];
			return *this;
		}

		GenoVector3<T> & scaleZY(const GenoVector2<T> & scale) {
			GenoVector::v[1] *= scale.v[1];
			GenoVector::v[2] *= scale.v[0];
			return *this;
		}

		GenoVector3<T> & scaleXYZ(const T & scale) {
			GenoVector::v[0] *= scale;
			GenoVector::v[1] *= scale;
			GenoVector::v[2] *= scale;
			return *this;
		}

		GenoVector3<T> & scaleXYZ(const T & scaleX, const T & scaleY, const T & scaleZ) {
			GenoVector::v[0] *= scaleX;
			GenoVector::v[1] *= scaleY;
			GenoVector::v[2] *= scaleZ;
			return *this;
		}

		GenoVector3<T> & scaleXYZ(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[1];
			GenoVector::v[2] *= scale.v[2];
			return *this;
		}

		GenoVector3<T> & scaleXZY(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[0];
			GenoVector::v[1] *= scale.v[2];
			GenoVector::v[2] *= scale.v[1];
			return *this;
		}

		GenoVector3<T> & scaleYXZ(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[1];
			GenoVector::v[1] *= scale.v[0];
			GenoVector::v[2] *= scale.v[2];
			return *this;
		}

		GenoVector3<T> & scaleYZX(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[2];
			GenoVector::v[1] *= scale.v[0];
			GenoVector::v[2] *= scale.v[1];
			return *this;
		}

		GenoVector3<T> & scaleZXY(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[1];
			GenoVector::v[1] *= scale.v[2];
			GenoVector::v[2] *= scale.v[0];
			return *this;
		}

		GenoVector3<T> & scaleZYX(const GenoVector3<T> & scale) {
			GenoVector::v[0] *= scale.v[2];
			GenoVector::v[1] *= scale.v[1];
			GenoVector::v[2] *= scale.v[0];
			return *this;
		}

		T & x() {
			return GenoVector::v[0];
		}

		T & y() {
			return GenoVector::v[1];
		}

		T & z() {
			return GenoVector::v[2];
		}

		T x() const {
			return GenoVector::v[0];
		}

		T y() const {
			return GenoVector::v[1];
		}

		T z() const {
			return GenoVector::v[2];
		}

		GenoVector2<T> xx() const {
			return { GenoVector::v[0],
			         GenoVector::v[0] };
		}

		GenoVector2<T> xy() const {
			return { GenoVector::v[0],
			         GenoVector::v[1] };
		}

		GenoVector2<T> xz() const {
			return { GenoVector::v[0],
			         GenoVector::v[2] };
		}

		GenoVector2<T> yx() const {
			return { GenoVector::v[1],
			         GenoVector::v[0] };
		}

		GenoVector2<T> yy() const {
			return { GenoVector::v[1],
			         GenoVector::v[1] };
		}

		GenoVector2<T> yz() const {
			return { GenoVector::v[1],
			         GenoVector::v[2] };
		}

		GenoVector2<T> zx() const {
			return { GenoVector::v[2],
			         GenoVector::v[0] };
		}

		GenoVector2<T> zy() const {
			return { GenoVector::v[2],
			         GenoVector::v[1] };
		}

		GenoVector2<T> zz() const {
			return { GenoVector::v[2],
			         GenoVector::v[2] };
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

		GenoVector3<T> xxz() const {
			return { GenoVector::v[0], 
			         GenoVector::v[0], 
			         GenoVector::v[2] };
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

		GenoVector3<T> xyz() const {
			return { GenoVector::v[0], 
			         GenoVector::v[1], 
			         GenoVector::v[2] };
		}

		GenoVector3<T> xzx() const {
			return { GenoVector::v[0], 
			         GenoVector::v[2], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> xzy() const {
			return { GenoVector::v[0], 
			         GenoVector::v[2], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> xzz() const {
			return { GenoVector::v[0], 
			         GenoVector::v[2], 
			         GenoVector::v[2] };
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

		GenoVector3<T> yxz() const {
			return { GenoVector::v[1], 
			         GenoVector::v[0], 
			         GenoVector::v[2] };
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

		GenoVector3<T> yyz() const {
			return { GenoVector::v[1], 
			         GenoVector::v[1], 
			         GenoVector::v[2] };
		}

		GenoVector3<T> yzx() const {
			return { GenoVector::v[1], 
			         GenoVector::v[2], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> yzy() const {
			return { GenoVector::v[1], 
			         GenoVector::v[2], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> yzz() const {
			return { GenoVector::v[1], 
			         GenoVector::v[2], 
			         GenoVector::v[2] };
		}

		GenoVector3<T> zxx() const {
			return { GenoVector::v[2], 
			         GenoVector::v[0], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> zxy() const {
			return { GenoVector::v[2], 
			         GenoVector::v[0], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> zxz() const {
			return { GenoVector::v[2], 
			         GenoVector::v[0], 
			         GenoVector::v[2] };
		}

		GenoVector3<T> zyx() const {
			return { GenoVector::v[2], 
			         GenoVector::v[1], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> zyy() const {
			return { GenoVector::v[2], 
			         GenoVector::v[1], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> zyz() const {
			return { GenoVector::v[2], 
			         GenoVector::v[1], 
			         GenoVector::v[2] };
		}

		GenoVector3<T> zzx() const {
			return { GenoVector::v[2], 
			         GenoVector::v[2], 
			         GenoVector::v[0] };
		}

		GenoVector3<T> zzy() const {
			return { GenoVector::v[2], 
			         GenoVector::v[2], 
			         GenoVector::v[1] };
		}

		GenoVector3<T> zzz() const {
			return { GenoVector::v[2], 
			         GenoVector::v[2], 
			         GenoVector::v[2] };
		}

		virtual ~GenoVector3() noexcept {}
};

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector3<T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << '>' << std::endl;
}

template <typename FT>
GenoVector3<FT> operator*(const FT & left, const GenoVector3<FT> & right) {
	return { left * right.v[0], left * right.v[1], left * right.v[2] };
}

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
