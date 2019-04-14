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

namespace GenoVectorDimensions {
	GenoVectorDimension<2> z;
}

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

		template <uint32 N>
		T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 3, "GenoVector<3, T> has no dimension w!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension  < 4, "GenoVector<3, T> has no dimension beyond z!");
			return v[GenoVectorDimensions::GenoVectorDimension<N>::dimension];
		}

		template <uint32 N>
		const T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) const noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension != 3, "GenoVector<3, T> has no dimension w!");
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension  < 4, "GenoVector<3, T> has no dimension beyond z!");
			return v[GenoVectorDimensions::GenoVectorDimension<N>::dimension];
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

		GenoVector<3, T> & setXY(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setXZ(T x, T z) {
			v[0] = x;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setXZ(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setYX(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setYZ(T y, T z) {
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setYZ(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setZX(const GenoVector<2, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setZY(const GenoVector<2, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<3, T> & setXYZ(T x, T y, T z) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<3, T> & setXYZ(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & setXZY(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & setYXZ(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & setYZX(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & setZXY(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & setZYX(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<3, T> & translateX(T translateX) {
			v[0] += translateX;
		}

		GenoVector<3, T> & translateY(T translateY) {
			v[1] += translateY;
		}

		GenoVector<3, T> & translateZ(T translateZ) {
			v[2] += translateZ;
		}

		GenoVector<3, T> & translateXY(T translateX, T translateY) {
			v[0] += translateX;
			v[1] += translateY;
		}

		GenoVector<3, T> & translateXY(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<3, T> & translateXZ(T translateX, T translateZ) {
			v[0] += translateX;
			v[2] += translateZ;
		}

		GenoVector<3, T> & translateXZ(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
		}

		GenoVector<3, T> & translateYX(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<3, T> & translateYZ(T translateY, T translateZ) {
			v[1] += translateY;
			v[2] += translateZ;
		}

		GenoVector<3, T> & translateYZ(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
		}

		GenoVector<3, T> & translateZX(const GenoVector<2, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<3, T> & translateZY(const GenoVector<2, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<3, T> & translateXYZ(T translateX, T translateY, T translateZ) {
			v[0] += translateX;
			v[1] += translateY;
			v[2] += translateZ;
		}

		GenoVector<3, T> & translateXYZ(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<3, T> & translateXZY(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<3, T> & translateYXZ(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<3, T> & translateYZX(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<3, T> & translateZXY(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<3, T> & translateZYX(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<3, T> & scaleX(T scaleX) {
			v[0] *= scaleX;
		}

		GenoVector<3, T> & scaleY(T scaleY) {
			v[1] *= scaleY;
		}

		GenoVector<3, T> & scaleZ(T scaleZ) {
			v[2] *= scaleZ;
		}

		GenoVector<3, T> & scaleXY(T scale) {
			v[0] *= scale;
			v[1] *= scale;
		}

		GenoVector<3, T> & scaleXY(T scaleX, T scaleY) {
			v[0] *= scaleX;
			v[1] *= scaleY;
		}

		GenoVector<3, T> & scaleXY(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<3, T> & scaleXZ(T scale) {
			v[0] *= scale;
			v[2] *= scale;
		}

		GenoVector<3, T> & scaleXZ(T scaleX, T scaleZ) {
			v[0] *= scaleX;
			v[2] *= scaleZ;
		}

		GenoVector<3, T> & scaleXZ(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
		}

		GenoVector<3, T> & scaleYX(T scale) {
			v[1] *= scale;
			v[0] *= scale;
		}

		GenoVector<3, T> & scaleYX(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
		}

		GenoVector<3, T> & scaleYZ(T scale) {
			v[1] *= scale;
			v[2] *= scale;
		}

		GenoVector<3, T> & scaleYZ(T scaleY, T scaleZ) {
			v[1] *= scaleY;
			v[2] *= scaleZ;
		}

		GenoVector<3, T> & scaleYZ(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
		}

		GenoVector<3, T> & scaleZX(T scale) {
			v[2] *= scale;
			v[0] *= scale;
		}

		GenoVector<3, T> & scaleZX(const GenoVector<2, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
		}

		GenoVector<3, T> & scaleZY(T scale) {
			v[2] *= scale;
			v[1] *= scale;
		}

		GenoVector<3, T> & scaleZY(const GenoVector<2, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<3, T> & scaleXYZ(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[2] *= scale;
		}

		GenoVector<3, T> & scaleXYZ(T scaleX, T scaleY, T scaleZ) {
			v[0] *= scaleX;
			v[1] *= scaleY;
			v[2] *= scaleZ;
		}

		GenoVector<3, T> & scaleXYZ(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<3, T> & scaleXZY(T scale) {
			v[0] *= scale;
			v[2] *= scale;
			v[1] *= scale;
		}

		GenoVector<3, T> & scaleXZY(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<3, T> & scaleYXZ(T scale) {
			v[1] *= scale;
			v[0] *= scale;
			v[2] *= scale;
		}

		GenoVector<3, T> & scaleYXZ(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<3, T> & scaleYZX(T scale) {
			v[1] *= scale;
			v[2] *= scale;
			v[0] *= scale;
		}

		GenoVector<3, T> & scaleYZX(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<3, T> & scaleZXY(T scale) {
			v[2] *= scale;
			v[0] *= scale;
			v[1] *= scale;
		}

		GenoVector<3, T> & scaleZXY(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<3, T> & scaleZYX(T scale) {
			v[2] *= scale;
			v[1] *= scale;
			v[0] *= scale;
		}

		GenoVector<3, T> & scaleZYX(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		T getX() const {
			return v[0];
		}

		T getY() const {
			return v[1];
		}

		T getZ() const {
			return v[2];
		}

		GenoVector<2, T> getXX() const {
			return { v[0], v[0] };
		}

		GenoVector<2, T> getXY() const {
			return { v[0], v[1] };
		}

		GenoVector<2, T> getXZ() const {
			return { v[0], v[2] };
		}

		GenoVector<2, T> getYX() const {
			return { v[1], v[0] };
		}

		GenoVector<2, T> getYY() const {
			return { v[1], v[1] };
		}

		GenoVector<2, T> getYZ() const {
			return { v[1], v[2] };
		}

		GenoVector<2, T> getZX() const {
			return { v[2], v[0] };
		}

		GenoVector<2, T> getZY() const {
			return { v[2], v[1] };
		}

		GenoVector<2, T> getZZ() const {
			return { v[2], v[2] };
		}

		GenoVector<3, T> getXXX() const {
			return { v[0], v[0], v[0] };
		}

		GenoVector<3, T> getXXY() const {
			return { v[0], v[0], v[1] };
		}

		GenoVector<3, T> getXXZ() const {
			return { v[0], v[0], v[2] };
		}

		GenoVector<3, T> getXYX() const {
			return { v[0], v[1], v[0] };
		}

		GenoVector<3, T> getXYY() const {
			return { v[0], v[1], v[1] };
		}

		GenoVector<3, T> getXYZ() const {
			return { v[0], v[1], v[2] };
		}

		GenoVector<3, T> getXZX() const {
			return { v[0], v[2], v[0] };
		}

		GenoVector<3, T> getXZY() const {
			return { v[0], v[2], v[1] };
		}

		GenoVector<3, T> getXZZ() const {
			return { v[0], v[2], v[2] };
		}

		GenoVector<3, T> getYXX() const {
			return { v[1], v[0], v[0] };
		}

		GenoVector<3, T> getYXY() const {
			return { v[1], v[0], v[1] };
		}

		GenoVector<3, T> getYXZ() const {
			return { v[1], v[0], v[2] };
		}

		GenoVector<3, T> getYYX() const {
			return { v[1], v[1], v[0] };
		}

		GenoVector<3, T> getYYY() const {
			return { v[1], v[1], v[1] };
		}

		GenoVector<3, T> getYYZ() const {
			return { v[1], v[1], v[2] };
		}

		GenoVector<3, T> getYZX() const {
			return { v[1], v[2], v[0] };
		}

		GenoVector<3, T> getYZY() const {
			return { v[1], v[2], v[1] };
		}

		GenoVector<3, T> getYZZ() const {
			return { v[1], v[2], v[2] };
		}

		GenoVector<3, T> getZXX() const {
			return { v[2], v[0], v[0] };
		}

		GenoVector<3, T> getZXY() const {
			return { v[2], v[0], v[1] };
		}

		GenoVector<3, T> getZXZ() const {
			return { v[2], v[0], v[2] };
		}

		GenoVector<3, T> getZYX() const {
			return { v[2], v[1], v[0] };
		}

		GenoVector<3, T> getZYY() const {
			return { v[2], v[1], v[1] };
		}

		GenoVector<3, T> getZYZ() const {
			return { v[2], v[1], v[2] };
		}

		GenoVector<3, T> getZZX() const {
			return { v[2], v[2], v[0] };
		}

		GenoVector<3, T> getZZY() const {
			return { v[2], v[2], v[1] };
		}

		GenoVector<3, T> getZZZ() const {
			return { v[2], v[2], v[2] };
		}

		GenoVector<4, T> getXXXX() const {
			return { v[0], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getXXXY() const {
			return { v[0], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getXXXZ() const {
			return { v[0], v[0], v[0], v[2] };
		}

		GenoVector<4, T> getXXYX() const {
			return { v[0], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getXXYY() const {
			return { v[0], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getXXYZ() const {
			return { v[0], v[0], v[1], v[2] };
		}

		GenoVector<4, T> getXXZX() const {
			return { v[0], v[0], v[2], v[0] };
		}

		GenoVector<4, T> getXXZY() const {
			return { v[0], v[0], v[2], v[1] };
		}

		GenoVector<4, T> getXXZZ() const {
			return { v[0], v[0], v[2], v[2] };
		}

		GenoVector<4, T> getXYXX() const {
			return { v[0], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getXYXY() const {
			return { v[0], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getXYXZ() const {
			return { v[0], v[1], v[0], v[2] };
		}

		GenoVector<4, T> getXYYX() const {
			return { v[0], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getXYYY() const {
			return { v[0], v[1], v[1], v[1] };
		}

		GenoVector<4, T> getXYYZ() const {
			return { v[0], v[1], v[1], v[2] };
		}

		GenoVector<4, T> getXYZX() const {
			return { v[0], v[1], v[2], v[0] };
		}

		GenoVector<4, T> getXYZY() const {
			return { v[0], v[1], v[2], v[1] };
		}

		GenoVector<4, T> getXYZZ() const {
			return { v[0], v[1], v[2], v[2] };
		}

		GenoVector<4, T> getXZXX() const {
			return { v[0], v[2], v[0], v[0] };
		}

		GenoVector<4, T> getXZXY() const {
			return { v[0], v[2], v[0], v[1] };
		}

		GenoVector<4, T> getXZXZ() const {
			return { v[0], v[2], v[0], v[2] };
		}

		GenoVector<4, T> getXZYX() const {
			return { v[0], v[2], v[1], v[0] };
		}

		GenoVector<4, T> getXZYY() const {
			return { v[0], v[2], v[1], v[1] };
		}

		GenoVector<4, T> getXZYZ() const {
			return { v[0], v[2], v[1], v[2] };
		}

		GenoVector<4, T> getXZZX() const {
			return { v[0], v[2], v[2], v[0] };
		}

		GenoVector<4, T> getXZZY() const {
			return { v[0], v[2], v[2], v[1] };
		}

		GenoVector<4, T> getXZZZ() const {
			return { v[0], v[2], v[2], v[2] };
		}

		GenoVector<4, T> getYXXX() const {
			return { v[1], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getYXXY() const {
			return { v[1], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getYXXZ() const {
			return { v[1], v[0], v[0], v[2] };
		}

		GenoVector<4, T> getYXYX() const {
			return { v[1], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getYXYY() const {
			return { v[1], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getYXYZ() const {
			return { v[1], v[0], v[1], v[2] };
		}

		GenoVector<4, T> getYXZX() const {
			return { v[1], v[0], v[2], v[0] };
		}

		GenoVector<4, T> getYXZY() const {
			return { v[1], v[0], v[2], v[1] };
		}

		GenoVector<4, T> getYXZZ() const {
			return { v[1], v[0], v[2], v[2] };
		}

		GenoVector<4, T> getYYXX() const {
			return { v[1], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getYYXY() const {
			return { v[1], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getYYXZ() const {
			return { v[1], v[1], v[0], v[2] };
		}

		GenoVector<4, T> getYYYX() const {
			return { v[1], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getYYYY() const {
			return { v[1], v[1], v[1], v[1] };
		}

		GenoVector<4, T> getYYYZ() const {
			return { v[1], v[1], v[1], v[2] };
		}

		GenoVector<4, T> getYYZX() const {
			return { v[1], v[1], v[2], v[0] };
		}

		GenoVector<4, T> getYYZY() const {
			return { v[1], v[1], v[2], v[1] };
		}

		GenoVector<4, T> getYYZZ() const {
			return { v[1], v[1], v[2], v[2] };
		}

		GenoVector<4, T> getYZXX() const {
			return { v[1], v[2], v[0], v[0] };
		}

		GenoVector<4, T> getYZXY() const {
			return { v[1], v[2], v[0], v[1] };
		}

		GenoVector<4, T> getYZXZ() const {
			return { v[1], v[2], v[0], v[2] };
		}

		GenoVector<4, T> getYZYX() const {
			return { v[1], v[2], v[1], v[0] };
		}

		GenoVector<4, T> getYZYY() const {
			return { v[1], v[2], v[1], v[1] };
		}

		GenoVector<4, T> getYZYZ() const {
			return { v[1], v[2], v[1], v[2] };
		}

		GenoVector<4, T> getYZZX() const {
			return { v[1], v[2], v[2], v[0] };
		}

		GenoVector<4, T> getYZZY() const {
			return { v[1], v[2], v[2], v[1] };
		}

		GenoVector<4, T> getYZZZ() const {
			return { v[1], v[2], v[2], v[2] };
		}

		GenoVector<4, T> getZXXX() const {
			return { v[2], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getZXXY() const {
			return { v[2], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getZXXZ() const {
			return { v[2], v[0], v[0], v[2] };
		}

		GenoVector<4, T> getZXYX() const {
			return { v[2], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getZXYY() const {
			return { v[2], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getZXYZ() const {
			return { v[2], v[0], v[1], v[2] };
		}

		GenoVector<4, T> getZXZX() const {
			return { v[2], v[0], v[2], v[0] };
		}

		GenoVector<4, T> getZXZY() const {
			return { v[2], v[0], v[2], v[1] };
		}

		GenoVector<4, T> getZXZZ() const {
			return { v[2], v[0], v[2], v[2] };
		}

		GenoVector<4, T> getZYXX() const {
			return { v[2], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getZYXY() const {
			return { v[2], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getZYXZ() const {
			return { v[2], v[1], v[0], v[2] };
		}

		GenoVector<4, T> getZYYX() const {
			return { v[2], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getZYYY() const {
			return { v[2], v[1], v[1], v[1] };
		}

		GenoVector<4, T> getZYYZ() const {
			return { v[2], v[1], v[1], v[2] };
		}

		GenoVector<4, T> getZYZX() const {
			return { v[2], v[1], v[2], v[0] };
		}

		GenoVector<4, T> getZYZY() const {
			return { v[2], v[1], v[2], v[1] };
		}

		GenoVector<4, T> getZYZZ() const {
			return { v[2], v[1], v[2], v[2] };
		}

		GenoVector<4, T> getZZXX() const {
			return { v[2], v[2], v[0], v[0] };
		}

		GenoVector<4, T> getZZXY() const {
			return { v[2], v[2], v[0], v[1] };
		}

		GenoVector<4, T> getZZXZ() const {
			return { v[2], v[2], v[0], v[2] };
		}

		GenoVector<4, T> getZZYX() const {
			return { v[2], v[2], v[1], v[0] };
		}

		GenoVector<4, T> getZZYY() const {
			return { v[2], v[2], v[1], v[1] };
		}

		GenoVector<4, T> getZZYZ() const {
			return { v[2], v[2], v[1], v[2] };
		}

		GenoVector<4, T> getZZZX() const {
			return { v[2], v[2], v[2], v[0] };
		}

		GenoVector<4, T> getZZZY() const {
			return { v[2], v[2], v[2], v[1] };
		}

		GenoVector<4, T> getZZZZ() const {
			return { v[2], v[2], v[2], v[2] };
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

template<typename T>
GenoVector<3, T> setX(const GenoVector<3, T> & vector, T x) {
	return {
		x,
		vector.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> setY(const GenoVector<3, T> & vector, T y) {
	return {
		vector.v[0],
		y,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> setZ(const GenoVector<3, T> & vector, T z) {
	return {
		vector.v[0],
		vector.v[1],
		z
	};
}

template<typename T>
GenoVector<3, T> setXY(const GenoVector<3, T> & vector, T x, T y) {
	return {
		x,
		y,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> setXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[0],
		   set.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> setXZ(const GenoVector<3, T> & vector, T x, T z) {
	return {
		x,
		vector.v[1],
		z
	};
}

template<typename T>
GenoVector<3, T> setXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[0],
		vector.v[1],
		   set.v[1]
	};
}

template<typename T>
GenoVector<3, T> setYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[1],
		   set.v[0],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> setYZ(const GenoVector<3, T> & vector, T y, T z) {
	return {
		vector.v[0],
		y,
		z
	};
}

template<typename T>
GenoVector<3, T> setYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[0],
		   set.v[1]
	};
}

template<typename T>
GenoVector<3, T> setZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[1],
		vector.v[1],
		   set.v[0]
	};
}

template<typename T>
GenoVector<3, T> setZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[1],
		   set.v[0]
	};
}

template<typename T>
GenoVector<3, T> setX(const GenoVector<3, T> & vector, T x, GenoVector<3, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> setY(const GenoVector<3, T> & vector, T y, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> setZ(const GenoVector<3, T> & vector, T z, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = z;
	return target;
}

template<typename T>
GenoVector<3, T> setXY(const GenoVector<3, T> & vector, T x, T y, GenoVector<3, T> & target) {
	target.v[0] = x;
	target.v[1] = y;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> setXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> setXZ(const GenoVector<3, T> & vector, T x, T z, GenoVector<3, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = z;
	return target;
}

template<typename T>
GenoVector<3, T> setXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> setYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[0];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> setYZ(const GenoVector<3, T> & vector, T y, T z, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = z;
	return target;
}

template<typename T>
GenoVector<3, T> setYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> setZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> setZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & set, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> translateX(const GenoVector<3, T> & vector, T translateX) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateY(const GenoVector<3, T> & vector, T translateY) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateZ(const GenoVector<3, T> & vector, T translateZ) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] + translateZ
	};
}

template<typename T>
GenoVector<3, T> translateXY(const GenoVector<3, T> & vector, T translateX, T translateY) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateXZ(const GenoVector<3, T> & vector, T translateX, T translateZ) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2] + translateZ
	};
}

template<typename T>
GenoVector<3, T> translateXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1],
		vector.v[2] + translate.v[1]
	};
}

template<typename T>
GenoVector<3, T> translateYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateYZ(const GenoVector<3, T> & vector, T translateY, T translateZ) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2] + translateZ
	};
}

template<typename T>
GenoVector<3, T> translateYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1]
	};
}

template<typename T>
GenoVector<3, T> translateZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1],
		vector.v[2] + translate.v[0]
	};
}

template<typename T>
GenoVector<3, T> translateZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0]
	};
}

template<typename T>
GenoVector<3, T> translateXYZ(const GenoVector<3, T> & vector, T translateX, T translateY, T translateZ) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2] + translateZ
	};
}

template<typename T>
GenoVector<3, T> translateXYZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateXZY(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[1]
	};
}

template<typename T>
GenoVector<3, T> translateYXZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[2]
	};
}

template<typename T>
GenoVector<3, T> translateYZX(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1]
	};
}

template<typename T>
GenoVector<3, T> translateZXY(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[0]
	};
}

template<typename T>
GenoVector<3, T> translateZYX(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0]
	};
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<3, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << '>';
}

template<typename T>
GenoVector<3, T> translateX(const GenoVector<3, T> & vector, T translateX, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateY(const GenoVector<3, T> & vector, T translateY, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateZ(const GenoVector<3, T> & vector, T translateZ, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	return target;
}

template<typename T>
GenoVector<3, T> translateXY(const GenoVector<3, T> & vector, T translateX, T translateY, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateXZ(const GenoVector<3, T> & vector, T translateX, T translateZ, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	return target;
}

template<typename T>
GenoVector<3, T> translateXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> translateYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateYZ(const GenoVector<3, T> & vector, T translateY, T translateZ, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	return target;
}

template<typename T>
GenoVector<3, T> translateYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> translateZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> translateZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> translateXYZ(const GenoVector<3, T> & vector, T translateX, T translateY, T translateZ, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	return target;
}

template<typename T>
GenoVector<3, T> translateXYZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateXZY(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> translateYXZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> translateYZX(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> translateZXY(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> translateZYX(const GenoVector<3, T> & vector, const GenoVector<3, T> & translate, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> scaleX(const GenoVector<3, T> & vector, T scaleX) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleY(const GenoVector<3, T> & vector, T scaleY) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleZ(const GenoVector<3, T> & vector, T scaleZ) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scaleZ
	};
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, T scaleX, T scaleY) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1],
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, T scaleX, T scaleZ) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2] * scaleZ
	};
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1],
		vector.v[2] * scale.v[1]
	};
}

template<typename T>
GenoVector<3, T> scaleYX(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, T scaleY, T scaleZ) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ
	};
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1]
	};
}

template<typename T>
GenoVector<3, T> scaleZX(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1],
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1],
		vector.v[2] * scale.v[0]
	};
}

template<typename T>
GenoVector<3, T> scaleZY(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0]
	};
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, T scaleX, T scaleY, T scaleZ) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ
	};
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleXZY(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleXZY(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[1]
	};
}

template<typename T>
GenoVector<3, T> scaleYXZ(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleYXZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[2]
	};
}

template<typename T>
GenoVector<3, T> scaleYZX(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleYZX(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1]
	};
}

template<typename T>
GenoVector<3, T> scaleZXY(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleZXY(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[0]
	};
}

template<typename T>
GenoVector<3, T> scaleZYX(const GenoVector<3, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale
	};
}

template<typename T>
GenoVector<3, T> scaleZYX(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0]
	};
}

template<typename T>
GenoVector<3, T> scaleX(const GenoVector<3, T> & vector, T scaleX, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleY(const GenoVector<3, T> & vector, T scaleY, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleZ(const GenoVector<3, T> & vector, T scaleZ, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, T scaleX, T scaleY, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleXY(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, T scaleX, T scaleZ, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> scaleYX(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleYX(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, T scaleY, T scaleZ, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	return target;
}

template<typename T>
GenoVector<3, T> scaleYZ(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> scaleZX(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleZX(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> scaleZY(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleZY(const GenoVector<3, T> & vector, const GenoVector<2, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, T scaleX, T scaleY, T scaleZ, const GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXYZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleXZY(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleXZY(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> scaleYXZ(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleYXZ(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<3, T> scaleYZX(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleYZX(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<3, T> scaleZXY(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleZXY(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<3, T> scaleZYX(const GenoVector<3, T> & vector, T scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	return target;
}

template<typename T>
GenoVector<3, T> scaleZYX(const GenoVector<3, T> & vector, const GenoVector<3, T> & scale, GenoVector<3, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	return target;
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