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
#include "GenoVector3.h"
#include "GenoVectorDimensions.h"

namespace GenoVectorDimensions {
	extern GenoVectorDimension<3> w;
}

template <typename T>
class GenoVector<4, T> {
	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] v;
		}

	public:
		static GenoVector<4, T> * newArray(uint32 length) {
			T * v = new T[4 * length];
			GenoVector<4, T> * ret = new GenoVector<4, T>[length];
			ret[0] = GenoVector<4, T>(v);
			for (uint32 i = 1; i < length; ++i)
				ret[i] = GenoVector<4, T>(v + i * 4, false);
			return ret;
		}

		T * v;

		GenoVector() :
			v(new T[4]()) {}

		GenoVector(T * v, bool owner = true) noexcept :
			owner(owner),
			v(v) {}

		explicit GenoVector(T value) :
			v(new T[4] { value, value, value, value }) {}

		GenoVector(T x, T y, T z, T w) :
			v(new T[4] { x, y, z, w }) {}

		template <typename T2>
		GenoVector(const GenoVector<4, T2> & vector) :
			v(new T[4] {
				(T) vector.v[0],
				(T) vector.v[1],
				(T) vector.v[2],
				(T) vector.v[3]
			}) {}

		GenoVector(const GenoVector<4, T> & vector) :
			v(new T[4] {
				vector.v[0],
				vector.v[1],
				vector.v[2],
				vector.v[3]
			}) {}

		GenoVector(GenoVector<4, T> && vector) :
			owner(vector.owner),
			v(vector.v) {
			vector.owner = false;
		}

		GenoVector<4, T> & operator=(const GenoVector<4, T> & vector) {
			v[0] = vector.v[0];
			v[1] = vector.v[1];
			v[2] = vector.v[2];
			v[3] = vector.v[3];
			return *this;
		}

		GenoVector<4, T> & operator=(GenoVector<4, T> && vector) {
			if (owner) {
				clean();
				owner = vector.owner;
				v = vector.v;
				vector.owner = false;
			}
			else {
				v[0] = vector.v[0];
				v[1] = vector.v[1];
				v[2] = vector.v[2];
				v[3] = vector.v[3];
			}
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
		
		template <uint32 N>
		T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension < 4, "GenoVector<4, T> has no dimension beyond w!");
			return v[GenoVectorDimensions::GenoVectorDimension<N>::dimension];
		}

		template <uint32 N>
		const T & operator[](const GenoVectorDimensions::GenoVectorDimension<N> & dimension) const noexcept {
			static_assert(GenoVectorDimensions::GenoVectorDimension<N>::dimension < 4, "GenoVector<4, T> has no dimension beyond w!");
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

		T & z() noexcept {
			return v[2];
		}

		const T & z() const noexcept {
			return v[2];
		}

		T & w() noexcept {
			return v[3];
		}

		const T & w() const noexcept {
			return v[3];
		}

		T getLength() const {
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

		GenoVector<4, T> & setLength(T length) {
			auto scalar = length / getLength();
			v[0] *= scalar;
			v[1] *= scalar;
			v[2] *= scalar;
			v[3] *= scalar;
			return *this;
		}

		GenoVector<4, T> & normalize() {
			auto scalar = 1 / getLength();
			v[0] *= scalar;
			v[1] *= scalar;
			v[2] *= scalar;
			v[3] *= scalar;
			return *this;
		}
		
		GenoVector<2, T> & negate() {
			v[0] = -v[0];
			v[1] = -v[1];
			v[2] = -v[2];
			v[3] = -v[3];
			return *this;
		}

		GenoVector<4, T> & project(const GenoVector<4, T> & projection) {
			auto scalar = dot(*this, projection) / projection.getLengthSquared();
			v[0] /= scalar;
			v[1] /= scalar;
			v[2] /= scalar;
			v[3] /= scalar;
			return *this;
		}

		GenoVector<4, T> & set(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & translate(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
			v[3] += translate.v[3];
			return *this;
		}
		
		GenoVector<4, T> & scale(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[2] *= scale;
			v[3] *= scale;
			return *this;
		}
		
		GenoVector<4, T> & scale(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
			v[3] *= scale.v[3];
			return *this;
		}

		GenoVector<4, T> & setX(T x) {
			v[0] = x;
			return *this;
		}

		GenoVector<4, T> & setY(T y) {
			v[1] = y;
			return *this;
		}

		GenoVector<4, T> & setZ(T z) {
			v[2] = z;
			return *this;
		}

		GenoVector<4, T> & setW(T w) {
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setXY(T x, T y) {
			v[0] = x;
			v[1] = y;
			return *this;
		}

		GenoVector<4, T> & setXY(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setXZ(T x, T z) {
			v[0] = x;
			v[2] = z;
			return *this;
		}

		GenoVector<4, T> & setXZ(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setXW(T x, T w) {
			v[0] = x;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setXW(const GenoVector<2, T> & set) {
			v[0] = set.v[0];
			v[3] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setYX(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setYZ(T y, T z) {
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<4, T> & setYZ(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setYW(T y, T w) {
			v[1] = y;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setYW(const GenoVector<2, T> & set) {
			v[1] = set.v[0];
			v[3] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setZX(const GenoVector<2, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setZY(const GenoVector<2, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setZW(T z, T w) {
			v[2] = z;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setZW(const GenoVector<2, T> & set) {
			v[2] = set.v[0];
			v[3] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setWX(const GenoVector<2, T> & set) {
			v[3] = set.v[0];
			v[0] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setWY(const GenoVector<2, T> & set) {
			v[3] = set.v[0];
			v[1] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setWZ(const GenoVector<2, T> & set) {
			v[3] = set.v[0];
			v[2] = set.v[1];
			return *this;
		}

		GenoVector<4, T> & setXYZ(T x, T y, T z) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			return *this;
		}

		GenoVector<4, T> & setXYZ(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXYW(T x, T y, T w) {
			v[0] = x;
			v[1] = y;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setXYW(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXZY(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXZW(T x, T z, T w) {
			v[0] = x;
			v[2] = z;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setXZW(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXWY(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[3] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXWZ(const GenoVector<3, T> & set) {
			v[0] = set.v[0];
			v[3] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYXZ(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYXW(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYZX(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYZW(T y, T z, T w) {
			v[1] = y;
			v[2] = z;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setYZW(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYWX(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[3] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setYWZ(const GenoVector<3, T> & set) {
			v[1] = set.v[0];
			v[3] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZXY(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZXW(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZYX(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZYW(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			v[3] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZWX(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[3] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setZWY(const GenoVector<3, T> & set) {
			v[2] = set.v[0];
			v[3] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWXY(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[0] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWXZ(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[0] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWYX(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[1] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWYZ(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWZX(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[2] = set.v[1];
			v[0] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setWZY(const GenoVector<3, T> & set) {
			v[3] = set.v[0];
			v[2] = set.v[1];
			v[1] = set.v[2];
			return *this;
		}

		GenoVector<4, T> & setXYZW(T x, T y, T z, T w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
			return *this;
		}

		GenoVector<4, T> & setXYZW(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setXYWZ(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[1] = set.v[1];
			v[3] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setXZYW(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			v[1] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setXZWY(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[2] = set.v[1];
			v[3] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setXWYZ(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[3] = set.v[1];
			v[1] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setXWZY(const GenoVector<4, T> & set) {
			v[0] = set.v[0];
			v[3] = set.v[1];
			v[2] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYXZW(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			v[2] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYXWZ(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[0] = set.v[1];
			v[3] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYZXW(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			v[0] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYZWX(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[2] = set.v[1];
			v[3] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYWXZ(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[3] = set.v[1];
			v[0] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setYWZX(const GenoVector<4, T> & set) {
			v[1] = set.v[0];
			v[3] = set.v[1];
			v[2] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZXYW(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			v[1] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZXWY(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[0] = set.v[1];
			v[3] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZYXW(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			v[0] = set.v[2];
			v[3] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZYWX(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[1] = set.v[1];
			v[3] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZWXY(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[3] = set.v[1];
			v[0] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setZWYX(const GenoVector<4, T> & set) {
			v[2] = set.v[0];
			v[3] = set.v[1];
			v[1] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWXYZ(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[0] = set.v[1];
			v[1] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWXZY(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[0] = set.v[1];
			v[2] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWYXZ(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[1] = set.v[1];
			v[0] = set.v[2];
			v[2] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWYZX(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[1] = set.v[1];
			v[2] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWZXY(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[2] = set.v[1];
			v[0] = set.v[2];
			v[1] = set.v[3];
			return *this;
		}

		GenoVector<4, T> & setWZYX(const GenoVector<4, T> & set) {
			v[3] = set.v[0];
			v[2] = set.v[1];
			v[1] = set.v[2];
			v[0] = set.v[3];
			return *this;
		}
		
		GenoVector<4, T> & translateX(T translateX) {
			v[0] += translateX;
		}

		GenoVector<4, T> & translateY(T translateY) {
			v[1] += translateY;
		}

		GenoVector<4, T> & translateZ(T translateZ) {
			v[2] += translateZ;
		}

		GenoVector<4, T> & translateW(T translateW) {
			v[3] += translateW;
		}

		GenoVector<4, T> & translateXY(T translateX, T translateY) {
			v[0] += translateX;
			v[1] += translateY;
		}

		GenoVector<4, T> & translateXY(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<4, T> & translateXZ(T translateX, T translateZ) {
			v[0] += translateX;
			v[2] += translateZ;
		}

		GenoVector<4, T> & translateXZ(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
		}

		GenoVector<4, T> & translateXW(T translateX, T translateW) {
			v[0] += translateX;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateXW(const GenoVector<2, T> & translate) {
			v[0] += translate.v[0];
			v[3] += translate.v[1];
		}

		GenoVector<4, T> & translateYX(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<4, T> & translateYZ(T translateY, T translateZ) {
			v[1] += translateY;
			v[2] += translateZ;
		}

		GenoVector<4, T> & translateYZ(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
		}

		GenoVector<4, T> & translateYW(T translateY, T translateW) {
			v[1] += translateY;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateYW(const GenoVector<2, T> & translate) {
			v[1] += translate.v[0];
			v[3] += translate.v[1];
		}

		GenoVector<4, T> & translateZX(const GenoVector<2, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<4, T> & translateZY(const GenoVector<2, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<4, T> & translateZW(T translateZ, T translateW) {
			v[2] += translateZ;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateZW(const GenoVector<2, T> & translate) {
			v[2] += translate.v[0];
			v[3] += translate.v[1];
		}

		GenoVector<4, T> & translateWX(const GenoVector<2, T> & translate) {
			v[3] += translate.v[0];
			v[0] += translate.v[1];
		}

		GenoVector<4, T> & translateWY(const GenoVector<2, T> & translate) {
			v[3] += translate.v[0];
			v[1] += translate.v[1];
		}

		GenoVector<4, T> & translateWZ(const GenoVector<2, T> & translate) {
			v[3] += translate.v[0];
			v[2] += translate.v[1];
		}

		GenoVector<4, T> & translateXYZ(T translateX, T translateY, T translateZ) {
			v[0] += translateX;
			v[1] += translateY;
			v[2] += translateZ;
		}

		GenoVector<4, T> & translateXYZ(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateXYW(T translateX, T translateY, T translateW) {
			v[0] += translateX;
			v[1] += translateY;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateXYW(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateXZY(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateXZW(T translateX, T translateZ, T translateW) {
			v[0] += translateX;
			v[2] += translateZ;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateXZW(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateXWY(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[3] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateXWZ(const GenoVector<3, T> & translate) {
			v[0] += translate.v[0];
			v[3] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateYXZ(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateYXW(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateYZX(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateYZW(T translateY, T translateZ, T translateW) {
			v[1] += translateY;
			v[2] += translateZ;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateYZW(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateYWX(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[3] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateYWZ(const GenoVector<3, T> & translate) {
			v[1] += translate.v[0];
			v[3] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateZXY(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateZXW(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateZYX(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateZYW(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
			v[3] += translate.v[2];
		}

		GenoVector<4, T> & translateZWX(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[3] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateZWY(const GenoVector<3, T> & translate) {
			v[2] += translate.v[0];
			v[3] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateWXY(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[0] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateWXZ(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[0] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateWYX(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[1] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateWYZ(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
		}

		GenoVector<4, T> & translateWZX(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[2] += translate.v[1];
			v[0] += translate.v[2];
		}

		GenoVector<4, T> & translateWZY(const GenoVector<3, T> & translate) {
			v[3] += translate.v[0];
			v[2] += translate.v[1];
			v[1] += translate.v[2];
		}

		GenoVector<4, T> & translateXYZW(T translateX, T translateY, T translateZ, T translateW) {
			v[0] += translateX;
			v[1] += translateY;
			v[2] += translateZ;
			v[3] += translateW;
		}

		GenoVector<4, T> & translateXYZW(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateXYWZ(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[1] += translate.v[1];
			v[3] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateXZYW(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
			v[1] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateXZWY(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[2] += translate.v[1];
			v[3] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateXWYZ(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[3] += translate.v[1];
			v[1] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateXWZY(const GenoVector<4, T> & translate) {
			v[0] += translate.v[0];
			v[3] += translate.v[1];
			v[2] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateYXZW(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
			v[2] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateYXWZ(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[0] += translate.v[1];
			v[3] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateYZXW(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
			v[0] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateYZWX(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[2] += translate.v[1];
			v[3] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & translateYWXZ(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[3] += translate.v[1];
			v[0] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateYWZX(const GenoVector<4, T> & translate) {
			v[1] += translate.v[0];
			v[3] += translate.v[1];
			v[2] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & translateZXYW(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
			v[1] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateZXWY(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[0] += translate.v[1];
			v[3] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateZYXW(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
			v[0] += translate.v[2];
			v[3] += translate.v[3];
		}

		GenoVector<4, T> & translateZYWX(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[1] += translate.v[1];
			v[3] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & translateZWXY(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[3] += translate.v[1];
			v[0] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateZWYX(const GenoVector<4, T> & translate) {
			v[2] += translate.v[0];
			v[3] += translate.v[1];
			v[1] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & translateWXYZ(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[0] += translate.v[1];
			v[1] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateWXZY(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[0] += translate.v[1];
			v[2] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateWYXZ(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[1] += translate.v[1];
			v[0] += translate.v[2];
			v[2] += translate.v[3];
		}

		GenoVector<4, T> & translateWYZX(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[1] += translate.v[1];
			v[2] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & translateWZXY(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[2] += translate.v[1];
			v[0] += translate.v[2];
			v[1] += translate.v[3];
		}

		GenoVector<4, T> & translateWZYX(const GenoVector<4, T> & translate) {
			v[3] += translate.v[0];
			v[2] += translate.v[1];
			v[1] += translate.v[2];
			v[0] += translate.v[3];
		}

		GenoVector<4, T> & scaleX(T scaleX) {
			v[0] *= scaleX;
		}

		GenoVector<4, T> & scaleY(T scaleY) {
			v[1] *= scaleY;
		}

		GenoVector<4, T> & scaleZ(T scaleZ) {
			v[2] *= scaleZ;
		}

		GenoVector<4, T> & scaleW(T scaleW) {
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleXY(T scale) {
			v[0] *= scale;
			v[1] *= scale;
		}

		GenoVector<4, T> & scaleXY(T scaleX, T scaleY) {
			v[0] *= scaleX;
			v[1] *= scaleY;
		}

		GenoVector<4, T> & scaleXY(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<4, T> & scaleXZ(T scale) {
			v[0] *= scale;
			v[2] *= scale;
		}

		GenoVector<4, T> & scaleXZ(T scaleX, T scaleZ) {
			v[0] *= scaleX;
			v[2] *= scaleZ;
		}

		GenoVector<4, T> & scaleXZ(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
		}

		GenoVector<4, T> & scaleXW(T scale) {
			v[0] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleXW(T scaleX, T scaleW) {
			v[0] *= scaleX;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleXW(const GenoVector<2, T> & scale) {
			v[0] *= scale.v[0];
			v[3] *= scale.v[1];
		}

		GenoVector<4, T> & scaleYX(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
		}

		GenoVector<4, T> & scaleYZ(T scale) {
			v[1] *= scale;
			v[2] *= scale;
		}

		GenoVector<4, T> & scaleYZ(T scaleY, T scaleZ) {
			v[1] *= scaleY;
			v[2] *= scaleZ;
		}

		GenoVector<4, T> & scaleYZ(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
		}

		GenoVector<4, T> & scaleYW(T scale) {
			v[1] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleYW(T scaleY, T scaleW) {
			v[1] *= scaleY;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleYW(const GenoVector<2, T> & scale) {
			v[1] *= scale.v[0];
			v[3] *= scale.v[1];
		}

		GenoVector<4, T> & scaleZX(const GenoVector<2, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
		}

		GenoVector<4, T> & scaleZY(const GenoVector<2, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<4, T> & scaleZW(T scale) {
			v[2] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleZW(T scaleZ, T scaleW) {
			v[2] *= scaleZ;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleZW(const GenoVector<2, T> & scale) {
			v[2] *= scale.v[0];
			v[3] *= scale.v[1];
		}

		GenoVector<4, T> & scaleWX(const GenoVector<2, T> & scale) {
			v[3] *= scale.v[0];
			v[0] *= scale.v[1];
		}

		GenoVector<4, T> & scaleWY(const GenoVector<2, T> & scale) {
			v[3] *= scale.v[0];
			v[1] *= scale.v[1];
		}

		GenoVector<4, T> & scaleWZ(const GenoVector<2, T> & scale) {
			v[3] *= scale.v[0];
			v[2] *= scale.v[1];
		}

		GenoVector<4, T> & scaleXYZ(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[2] *= scale;
		}

		GenoVector<4, T> & scaleXYZ(T scaleX, T scaleY, T scaleZ) {
			v[0] *= scaleX;
			v[1] *= scaleY;
			v[2] *= scaleZ;
		}

		GenoVector<4, T> & scaleXYZ(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXYW(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleXYW(T scaleX, T scaleY, T scaleW) {
			v[0] *= scaleX;
			v[1] *= scaleY;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleXYW(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXZY(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXZW(T scale) {
			v[0] *= scale;
			v[2] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleXZW(T scaleX, T scaleZ, T scaleW) {
			v[0] *= scaleX;
			v[2] *= scaleZ;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleXZW(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXWY(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[3] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXWZ(const GenoVector<3, T> & scale) {
			v[0] *= scale.v[0];
			v[3] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYXZ(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYXW(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYZX(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYZW(T scale) {
			v[1] *= scale;
			v[2] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleYZW(T scaleY, T scaleZ, T scaleW) {
			v[1] *= scaleY;
			v[2] *= scaleZ;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleYZW(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYWX(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[3] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleYWZ(const GenoVector<3, T> & scale) {
			v[1] *= scale.v[0];
			v[3] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZXY(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZXW(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZYX(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZYW(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
			v[3] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZWX(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[3] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleZWY(const GenoVector<3, T> & scale) {
			v[2] *= scale.v[0];
			v[3] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWXY(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[0] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWXZ(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[0] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWYX(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[1] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWYZ(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWZX(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[2] *= scale.v[1];
			v[0] *= scale.v[2];
		}

		GenoVector<4, T> & scaleWZY(const GenoVector<3, T> & scale) {
			v[3] *= scale.v[0];
			v[2] *= scale.v[1];
			v[1] *= scale.v[2];
		}

		GenoVector<4, T> & scaleXYZW(T scale) {
			v[0] *= scale;
			v[1] *= scale;
			v[2] *= scale;
			v[3] *= scale;
		}

		GenoVector<4, T> & scaleXYZW(T scaleX, T scaleY, T scaleZ, T scaleW) {
			v[0] *= scaleX;
			v[1] *= scaleY;
			v[2] *= scaleZ;
			v[3] *= scaleW;
		}

		GenoVector<4, T> & scaleXYZW(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleXYWZ(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[1] *= scale.v[1];
			v[3] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleXZYW(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
			v[1] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleXZWY(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[2] *= scale.v[1];
			v[3] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleXWYZ(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[3] *= scale.v[1];
			v[1] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleXWZY(const GenoVector<4, T> & scale) {
			v[0] *= scale.v[0];
			v[3] *= scale.v[1];
			v[2] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYXZW(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
			v[2] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYXWZ(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[0] *= scale.v[1];
			v[3] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYZXW(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
			v[0] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYZWX(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[2] *= scale.v[1];
			v[3] *= scale.v[2];
			v[0] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYWXZ(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[3] *= scale.v[1];
			v[0] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleYWZX(const GenoVector<4, T> & scale) {
			v[1] *= scale.v[0];
			v[3] *= scale.v[1];
			v[2] *= scale.v[2];
			v[0] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZXYW(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
			v[1] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZXWY(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[0] *= scale.v[1];
			v[3] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZYXW(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
			v[0] *= scale.v[2];
			v[3] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZYWX(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[1] *= scale.v[1];
			v[3] *= scale.v[2];
			v[0] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZWXY(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[3] *= scale.v[1];
			v[0] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleZWYX(const GenoVector<4, T> & scale) {
			v[2] *= scale.v[0];
			v[3] *= scale.v[1];
			v[1] *= scale.v[2];
			v[0] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWXYZ(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[0] *= scale.v[1];
			v[1] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWXZY(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[0] *= scale.v[1];
			v[2] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWYXZ(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[1] *= scale.v[1];
			v[0] *= scale.v[2];
			v[2] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWYZX(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[1] *= scale.v[1];
			v[2] *= scale.v[2];
			v[0] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWZXY(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[2] *= scale.v[1];
			v[0] *= scale.v[2];
			v[1] *= scale.v[3];
		}

		GenoVector<4, T> & scaleWZYX(const GenoVector<4, T> & scale) {
			v[3] *= scale.v[0];
			v[2] *= scale.v[1];
			v[1] *= scale.v[2];
			v[0] *= scale.v[3];
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

		T getW() const {
			return v[3];
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

		GenoVector<2, T> getXW() const {
			return { v[0], v[3] };
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

		GenoVector<2, T> getYW() const {
			return { v[1], v[3] };
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

		GenoVector<2, T> getZW() const {
			return { v[2], v[3] };
		}

		GenoVector<2, T> getWX() const {
			return { v[3], v[0] };
		}

		GenoVector<2, T> getWY() const {
			return { v[3], v[1] };
		}

		GenoVector<2, T> getWZ() const {
			return { v[3], v[2] };
		}

		GenoVector<2, T> getWW() const {
			return { v[3], v[3] };
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

		GenoVector<3, T> getXXW() const {
			return { v[0], v[0], v[3] };
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

		GenoVector<3, T> getXYW() const {
			return { v[0], v[1], v[3] };
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

		GenoVector<3, T> getXZW() const {
			return { v[0], v[2], v[3] };
		}

		GenoVector<3, T> getXWX() const {
			return { v[0], v[3], v[0] };
		}

		GenoVector<3, T> getXWY() const {
			return { v[0], v[3], v[1] };
		}

		GenoVector<3, T> getXWZ() const {
			return { v[0], v[3], v[2] };
		}

		GenoVector<3, T> getXWW() const {
			return { v[0], v[3], v[3] };
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

		GenoVector<3, T> getYXW() const {
			return { v[1], v[0], v[3] };
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

		GenoVector<3, T> getYYW() const {
			return { v[1], v[1], v[3] };
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

		GenoVector<3, T> getYZW() const {
			return { v[1], v[2], v[3] };
		}

		GenoVector<3, T> getYWX() const {
			return { v[1], v[3], v[0] };
		}

		GenoVector<3, T> getYWY() const {
			return { v[1], v[3], v[1] };
		}

		GenoVector<3, T> getYWZ() const {
			return { v[1], v[3], v[2] };
		}

		GenoVector<3, T> getYWW() const {
			return { v[1], v[3], v[3] };
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

		GenoVector<3, T> getZXW() const {
			return { v[2], v[0], v[3] };
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

		GenoVector<3, T> getZYW() const {
			return { v[2], v[1], v[3] };
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

		GenoVector<3, T> getZZW() const {
			return { v[2], v[2], v[3] };
		}

		GenoVector<3, T> getZWX() const {
			return { v[2], v[3], v[0] };
		}

		GenoVector<3, T> getZWY() const {
			return { v[2], v[3], v[1] };
		}

		GenoVector<3, T> getZWZ() const {
			return { v[2], v[3], v[2] };
		}

		GenoVector<3, T> getZWW() const {
			return { v[2], v[3], v[3] };
		}

		GenoVector<3, T> getWXX() const {
			return { v[3], v[0], v[0] };
		}

		GenoVector<3, T> getWXY() const {
			return { v[3], v[0], v[1] };
		}

		GenoVector<3, T> getWXZ() const {
			return { v[3], v[0], v[2] };
		}

		GenoVector<3, T> getWXW() const {
			return { v[3], v[0], v[3] };
		}

		GenoVector<3, T> getWYX() const {
			return { v[3], v[1], v[0] };
		}

		GenoVector<3, T> getWYY() const {
			return { v[3], v[1], v[1] };
		}

		GenoVector<3, T> getWYZ() const {
			return { v[3], v[1], v[2] };
		}

		GenoVector<3, T> getWYW() const {
			return { v[3], v[1], v[3] };
		}

		GenoVector<3, T> getWZX() const {
			return { v[3], v[2], v[0] };
		}

		GenoVector<3, T> getWZY() const {
			return { v[3], v[2], v[1] };
		}

		GenoVector<3, T> getWZZ() const {
			return { v[3], v[2], v[2] };
		}

		GenoVector<3, T> getWZW() const {
			return { v[3], v[2], v[3] };
		}

		GenoVector<3, T> getWWX() const {
			return { v[3], v[3], v[0] };
		}

		GenoVector<3, T> getWWY() const {
			return { v[3], v[3], v[1] };
		}

		GenoVector<3, T> getWWZ() const {
			return { v[3], v[3], v[2] };
		}

		GenoVector<3, T> getWWW() const {
			return { v[3], v[3], v[3] };
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

		GenoVector<4, T> getXXXW() const {
			return { v[0], v[0], v[0], v[3] };
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

		GenoVector<4, T> getXXYW() const {
			return { v[0], v[0], v[1], v[3] };
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

		GenoVector<4, T> getXXZW() const {
			return { v[0], v[0], v[2], v[3] };
		}

		GenoVector<4, T> getXXWX() const {
			return { v[0], v[0], v[3], v[0] };
		}

		GenoVector<4, T> getXXWY() const {
			return { v[0], v[0], v[3], v[1] };
		}

		GenoVector<4, T> getXXWZ() const {
			return { v[0], v[0], v[3], v[2] };
		}

		GenoVector<4, T> getXXWW() const {
			return { v[0], v[0], v[3], v[3] };
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

		GenoVector<4, T> getXYXW() const {
			return { v[0], v[1], v[0], v[3] };
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

		GenoVector<4, T> getXYYW() const {
			return { v[0], v[1], v[1], v[3] };
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

		GenoVector<4, T> getXYZW() const {
			return { v[0], v[1], v[2], v[3] };
		}

		GenoVector<4, T> getXYWX() const {
			return { v[0], v[1], v[3], v[0] };
		}

		GenoVector<4, T> getXYWY() const {
			return { v[0], v[1], v[3], v[1] };
		}

		GenoVector<4, T> getXYWZ() const {
			return { v[0], v[1], v[3], v[2] };
		}

		GenoVector<4, T> getXYWW() const {
			return { v[0], v[1], v[3], v[3] };
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

		GenoVector<4, T> getXZXW() const {
			return { v[0], v[2], v[0], v[3] };
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

		GenoVector<4, T> getXZYW() const {
			return { v[0], v[2], v[1], v[3] };
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

		GenoVector<4, T> getXZZW() const {
			return { v[0], v[2], v[2], v[3] };
		}

		GenoVector<4, T> getXZWX() const {
			return { v[0], v[2], v[3], v[0] };
		}

		GenoVector<4, T> getXZWY() const {
			return { v[0], v[2], v[3], v[1] };
		}

		GenoVector<4, T> getXZWZ() const {
			return { v[0], v[2], v[3], v[2] };
		}

		GenoVector<4, T> getXZWW() const {
			return { v[0], v[2], v[3], v[3] };
		}

		GenoVector<4, T> getXWXX() const {
			return { v[0], v[3], v[0], v[0] };
		}

		GenoVector<4, T> getXWXY() const {
			return { v[0], v[3], v[0], v[1] };
		}

		GenoVector<4, T> getXWXZ() const {
			return { v[0], v[3], v[0], v[2] };
		}

		GenoVector<4, T> getXWXW() const {
			return { v[0], v[3], v[0], v[3] };
		}

		GenoVector<4, T> getXWYX() const {
			return { v[0], v[3], v[1], v[0] };
		}

		GenoVector<4, T> getXWYY() const {
			return { v[0], v[3], v[1], v[1] };
		}

		GenoVector<4, T> getXWYZ() const {
			return { v[0], v[3], v[1], v[2] };
		}

		GenoVector<4, T> getXWYW() const {
			return { v[0], v[3], v[1], v[3] };
		}

		GenoVector<4, T> getXWZX() const {
			return { v[0], v[3], v[2], v[0] };
		}

		GenoVector<4, T> getXWZY() const {
			return { v[0], v[3], v[2], v[1] };
		}

		GenoVector<4, T> getXWZZ() const {
			return { v[0], v[3], v[2], v[2] };
		}

		GenoVector<4, T> getXWZW() const {
			return { v[0], v[3], v[2], v[3] };
		}

		GenoVector<4, T> getXWWX() const {
			return { v[0], v[3], v[3], v[0] };
		}

		GenoVector<4, T> getXWWY() const {
			return { v[0], v[3], v[3], v[1] };
		}

		GenoVector<4, T> getXWWZ() const {
			return { v[0], v[3], v[3], v[2] };
		}

		GenoVector<4, T> getXWWW() const {
			return { v[0], v[3], v[3], v[3] };
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

		GenoVector<4, T> getYXXW() const {
			return { v[1], v[0], v[0], v[3] };
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

		GenoVector<4, T> getYXYW() const {
			return { v[1], v[0], v[1], v[3] };
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

		GenoVector<4, T> getYXZW() const {
			return { v[1], v[0], v[2], v[3] };
		}

		GenoVector<4, T> getYXWX() const {
			return { v[1], v[0], v[3], v[0] };
		}

		GenoVector<4, T> getYXWY() const {
			return { v[1], v[0], v[3], v[1] };
		}

		GenoVector<4, T> getYXWZ() const {
			return { v[1], v[0], v[3], v[2] };
		}

		GenoVector<4, T> getYXWW() const {
			return { v[1], v[0], v[3], v[3] };
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

		GenoVector<4, T> getYYXW() const {
			return { v[1], v[1], v[0], v[3] };
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

		GenoVector<4, T> getYYYW() const {
			return { v[1], v[1], v[1], v[3] };
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

		GenoVector<4, T> getYYZW() const {
			return { v[1], v[1], v[2], v[3] };
		}

		GenoVector<4, T> getYYWX() const {
			return { v[1], v[1], v[3], v[0] };
		}

		GenoVector<4, T> getYYWY() const {
			return { v[1], v[1], v[3], v[1] };
		}

		GenoVector<4, T> getYYWZ() const {
			return { v[1], v[1], v[3], v[2] };
		}

		GenoVector<4, T> getYYWW() const {
			return { v[1], v[1], v[3], v[3] };
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

		GenoVector<4, T> getYZXW() const {
			return { v[1], v[2], v[0], v[3] };
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

		GenoVector<4, T> getYZYW() const {
			return { v[1], v[2], v[1], v[3] };
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

		GenoVector<4, T> getYZZW() const {
			return { v[1], v[2], v[2], v[3] };
		}

		GenoVector<4, T> getYZWX() const {
			return { v[1], v[2], v[3], v[0] };
		}

		GenoVector<4, T> getYZWY() const {
			return { v[1], v[2], v[3], v[1] };
		}

		GenoVector<4, T> getYZWZ() const {
			return { v[1], v[2], v[3], v[2] };
		}

		GenoVector<4, T> getYZWW() const {
			return { v[1], v[2], v[3], v[3] };
		}

		GenoVector<4, T> getYWXX() const {
			return { v[1], v[3], v[0], v[0] };
		}

		GenoVector<4, T> getYWXY() const {
			return { v[1], v[3], v[0], v[1] };
		}

		GenoVector<4, T> getYWXZ() const {
			return { v[1], v[3], v[0], v[2] };
		}

		GenoVector<4, T> getYWXW() const {
			return { v[1], v[3], v[0], v[3] };
		}

		GenoVector<4, T> getYWYX() const {
			return { v[1], v[3], v[1], v[0] };
		}

		GenoVector<4, T> getYWYY() const {
			return { v[1], v[3], v[1], v[1] };
		}

		GenoVector<4, T> getYWYZ() const {
			return { v[1], v[3], v[1], v[2] };
		}

		GenoVector<4, T> getYWYW() const {
			return { v[1], v[3], v[1], v[3] };
		}

		GenoVector<4, T> getYWZX() const {
			return { v[1], v[3], v[2], v[0] };
		}

		GenoVector<4, T> getYWZY() const {
			return { v[1], v[3], v[2], v[1] };
		}

		GenoVector<4, T> getYWZZ() const {
			return { v[1], v[3], v[2], v[2] };
		}

		GenoVector<4, T> getYWZW() const {
			return { v[1], v[3], v[2], v[3] };
		}

		GenoVector<4, T> getYWWX() const {
			return { v[1], v[3], v[3], v[0] };
		}

		GenoVector<4, T> getYWWY() const {
			return { v[1], v[3], v[3], v[1] };
		}

		GenoVector<4, T> getYWWZ() const {
			return { v[1], v[3], v[3], v[2] };
		}

		GenoVector<4, T> getYWWW() const {
			return { v[1], v[3], v[3], v[3] };
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

		GenoVector<4, T> getZXXW() const {
			return { v[2], v[0], v[0], v[3] };
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

		GenoVector<4, T> getZXYW() const {
			return { v[2], v[0], v[1], v[3] };
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

		GenoVector<4, T> getZXZW() const {
			return { v[2], v[0], v[2], v[3] };
		}

		GenoVector<4, T> getZXWX() const {
			return { v[2], v[0], v[3], v[0] };
		}

		GenoVector<4, T> getZXWY() const {
			return { v[2], v[0], v[3], v[1] };
		}

		GenoVector<4, T> getZXWZ() const {
			return { v[2], v[0], v[3], v[2] };
		}

		GenoVector<4, T> getZXWW() const {
			return { v[2], v[0], v[3], v[3] };
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

		GenoVector<4, T> getZYXW() const {
			return { v[2], v[1], v[0], v[3] };
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

		GenoVector<4, T> getZYYW() const {
			return { v[2], v[1], v[1], v[3] };
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

		GenoVector<4, T> getZYZW() const {
			return { v[2], v[1], v[2], v[3] };
		}

		GenoVector<4, T> getZYWX() const {
			return { v[2], v[1], v[3], v[0] };
		}

		GenoVector<4, T> getZYWY() const {
			return { v[2], v[1], v[3], v[1] };
		}

		GenoVector<4, T> getZYWZ() const {
			return { v[2], v[1], v[3], v[2] };
		}

		GenoVector<4, T> getZYWW() const {
			return { v[2], v[1], v[3], v[3] };
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

		GenoVector<4, T> getZZXW() const {
			return { v[2], v[2], v[0], v[3] };
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

		GenoVector<4, T> getZZYW() const {
			return { v[2], v[2], v[1], v[3] };
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

		GenoVector<4, T> getZZZW() const {
			return { v[2], v[2], v[2], v[3] };
		}

		GenoVector<4, T> getZZWX() const {
			return { v[2], v[2], v[3], v[0] };
		}

		GenoVector<4, T> getZZWY() const {
			return { v[2], v[2], v[3], v[1] };
		}

		GenoVector<4, T> getZZWZ() const {
			return { v[2], v[2], v[3], v[2] };
		}

		GenoVector<4, T> getZZWW() const {
			return { v[2], v[2], v[3], v[3] };
		}

		GenoVector<4, T> getZWXX() const {
			return { v[2], v[3], v[0], v[0] };
		}

		GenoVector<4, T> getZWXY() const {
			return { v[2], v[3], v[0], v[1] };
		}

		GenoVector<4, T> getZWXZ() const {
			return { v[2], v[3], v[0], v[2] };
		}

		GenoVector<4, T> getZWXW() const {
			return { v[2], v[3], v[0], v[3] };
		}

		GenoVector<4, T> getZWYX() const {
			return { v[2], v[3], v[1], v[0] };
		}

		GenoVector<4, T> getZWYY() const {
			return { v[2], v[3], v[1], v[1] };
		}

		GenoVector<4, T> getZWYZ() const {
			return { v[2], v[3], v[1], v[2] };
		}

		GenoVector<4, T> getZWYW() const {
			return { v[2], v[3], v[1], v[3] };
		}

		GenoVector<4, T> getZWZX() const {
			return { v[2], v[3], v[2], v[0] };
		}

		GenoVector<4, T> getZWZY() const {
			return { v[2], v[3], v[2], v[1] };
		}

		GenoVector<4, T> getZWZZ() const {
			return { v[2], v[3], v[2], v[2] };
		}

		GenoVector<4, T> getZWZW() const {
			return { v[2], v[3], v[2], v[3] };
		}

		GenoVector<4, T> getZWWX() const {
			return { v[2], v[3], v[3], v[0] };
		}

		GenoVector<4, T> getZWWY() const {
			return { v[2], v[3], v[3], v[1] };
		}

		GenoVector<4, T> getZWWZ() const {
			return { v[2], v[3], v[3], v[2] };
		}

		GenoVector<4, T> getZWWW() const {
			return { v[2], v[3], v[3], v[3] };
		}

		GenoVector<4, T> getWXXX() const {
			return { v[3], v[0], v[0], v[0] };
		}

		GenoVector<4, T> getWXXY() const {
			return { v[3], v[0], v[0], v[1] };
		}

		GenoVector<4, T> getWXXZ() const {
			return { v[3], v[0], v[0], v[2] };
		}

		GenoVector<4, T> getWXXW() const {
			return { v[3], v[0], v[0], v[3] };
		}

		GenoVector<4, T> getWXYX() const {
			return { v[3], v[0], v[1], v[0] };
		}

		GenoVector<4, T> getWXYY() const {
			return { v[3], v[0], v[1], v[1] };
		}

		GenoVector<4, T> getWXYZ() const {
			return { v[3], v[0], v[1], v[2] };
		}

		GenoVector<4, T> getWXYW() const {
			return { v[3], v[0], v[1], v[3] };
		}

		GenoVector<4, T> getWXZX() const {
			return { v[3], v[0], v[2], v[0] };
		}

		GenoVector<4, T> getWXZY() const {
			return { v[3], v[0], v[2], v[1] };
		}

		GenoVector<4, T> getWXZZ() const {
			return { v[3], v[0], v[2], v[2] };
		}

		GenoVector<4, T> getWXZW() const {
			return { v[3], v[0], v[2], v[3] };
		}

		GenoVector<4, T> getWXWX() const {
			return { v[3], v[0], v[3], v[0] };
		}

		GenoVector<4, T> getWXWY() const {
			return { v[3], v[0], v[3], v[1] };
		}

		GenoVector<4, T> getWXWZ() const {
			return { v[3], v[0], v[3], v[2] };
		}

		GenoVector<4, T> getWXWW() const {
			return { v[3], v[0], v[3], v[3] };
		}

		GenoVector<4, T> getWYXX() const {
			return { v[3], v[1], v[0], v[0] };
		}

		GenoVector<4, T> getWYXY() const {
			return { v[3], v[1], v[0], v[1] };
		}

		GenoVector<4, T> getWYXZ() const {
			return { v[3], v[1], v[0], v[2] };
		}

		GenoVector<4, T> getWYXW() const {
			return { v[3], v[1], v[0], v[3] };
		}

		GenoVector<4, T> getWYYX() const {
			return { v[3], v[1], v[1], v[0] };
		}

		GenoVector<4, T> getWYYY() const {
			return { v[3], v[1], v[1], v[1] };
		}

		GenoVector<4, T> getWYYZ() const {
			return { v[3], v[1], v[1], v[2] };
		}

		GenoVector<4, T> getWYYW() const {
			return { v[3], v[1], v[1], v[3] };
		}

		GenoVector<4, T> getWYZX() const {
			return { v[3], v[1], v[2], v[0] };
		}

		GenoVector<4, T> getWYZY() const {
			return { v[3], v[1], v[2], v[1] };
		}

		GenoVector<4, T> getWYZZ() const {
			return { v[3], v[1], v[2], v[2] };
		}

		GenoVector<4, T> getWYZW() const {
			return { v[3], v[1], v[2], v[3] };
		}

		GenoVector<4, T> getWYWX() const {
			return { v[3], v[1], v[3], v[0] };
		}

		GenoVector<4, T> getWYWY() const {
			return { v[3], v[1], v[3], v[1] };
		}

		GenoVector<4, T> getWYWZ() const {
			return { v[3], v[1], v[3], v[2] };
		}

		GenoVector<4, T> getWYWW() const {
			return { v[3], v[1], v[3], v[3] };
		}

		GenoVector<4, T> getWZXX() const {
			return { v[3], v[2], v[0], v[0] };
		}

		GenoVector<4, T> getWZXY() const {
			return { v[3], v[2], v[0], v[1] };
		}

		GenoVector<4, T> getWZXZ() const {
			return { v[3], v[2], v[0], v[2] };
		}

		GenoVector<4, T> getWZXW() const {
			return { v[3], v[2], v[0], v[3] };
		}

		GenoVector<4, T> getWZYX() const {
			return { v[3], v[2], v[1], v[0] };
		}

		GenoVector<4, T> getWZYY() const {
			return { v[3], v[2], v[1], v[1] };
		}

		GenoVector<4, T> getWZYZ() const {
			return { v[3], v[2], v[1], v[2] };
		}

		GenoVector<4, T> getWZYW() const {
			return { v[3], v[2], v[1], v[3] };
		}

		GenoVector<4, T> getWZZX() const {
			return { v[3], v[2], v[2], v[0] };
		}

		GenoVector<4, T> getWZZY() const {
			return { v[3], v[2], v[2], v[1] };
		}

		GenoVector<4, T> getWZZZ() const {
			return { v[3], v[2], v[2], v[2] };
		}

		GenoVector<4, T> getWZZW() const {
			return { v[3], v[2], v[2], v[3] };
		}

		GenoVector<4, T> getWZWX() const {
			return { v[3], v[2], v[3], v[0] };
		}

		GenoVector<4, T> getWZWY() const {
			return { v[3], v[2], v[3], v[1] };
		}

		GenoVector<4, T> getWZWZ() const {
			return { v[3], v[2], v[3], v[2] };
		}

		GenoVector<4, T> getWZWW() const {
			return { v[3], v[2], v[3], v[3] };
		}

		GenoVector<4, T> getWWXX() const {
			return { v[3], v[3], v[0], v[0] };
		}

		GenoVector<4, T> getWWXY() const {
			return { v[3], v[3], v[0], v[1] };
		}

		GenoVector<4, T> getWWXZ() const {
			return { v[3], v[3], v[0], v[2] };
		}

		GenoVector<4, T> getWWXW() const {
			return { v[3], v[3], v[0], v[3] };
		}

		GenoVector<4, T> getWWYX() const {
			return { v[3], v[3], v[1], v[0] };
		}

		GenoVector<4, T> getWWYY() const {
			return { v[3], v[3], v[1], v[1] };
		}

		GenoVector<4, T> getWWYZ() const {
			return { v[3], v[3], v[1], v[2] };
		}

		GenoVector<4, T> getWWYW() const {
			return { v[3], v[3], v[1], v[3] };
		}

		GenoVector<4, T> getWWZX() const {
			return { v[3], v[3], v[2], v[0] };
		}

		GenoVector<4, T> getWWZY() const {
			return { v[3], v[3], v[2], v[1] };
		}

		GenoVector<4, T> getWWZZ() const {
			return { v[3], v[3], v[2], v[2] };
		}

		GenoVector<4, T> getWWZW() const {
			return { v[3], v[3], v[2], v[3] };
		}

		GenoVector<4, T> getWWWX() const {
			return { v[3], v[3], v[3], v[0] };
		}

		GenoVector<4, T> getWWWY() const {
			return { v[3], v[3], v[3], v[1] };
		}

		GenoVector<4, T> getWWWZ() const {
			return { v[3], v[3], v[3], v[2] };
		}

		GenoVector<4, T> getWWWW() const {
			return { v[3], v[3], v[3], v[3] };
		}

		virtual ~GenoVector() noexcept {
			clean();
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
GenoVector<4, T> setLength(const GenoVector<4, T> & vector, T length) {
	auto scalar = length / vector.getLength();
	return {
		vector.v[0] * scalar,
		vector.v[1] * scalar,
		vector.v[2] * scalar,
		vector.v[3] * scalar
	};
}

template <typename T>
GenoVector<4, T> & setLength(const GenoVector<4, T> & vector, T length, GenoVector<4, T> & target) {
	auto scalar = length / vector.getLength();
	target.v[0] = vector.v[0] * scalar;
	target.v[1] = vector.v[1] * scalar;
	target.v[2] = vector.v[2] * scalar;
	target.v[3] = vector.v[3] * scalar;
	return target;
}

template <typename T>
GenoVector<4, T> normalize(const GenoVector<4, T> & vector) {
	auto scalar = 1 / vector.getLength();
	return {
		vector.v[0] * scalar,
		vector.v[1] * scalar,
		vector.v[2] * scalar,
		vector.v[3] * scalar
	};
}

template <typename T>
GenoVector<4, T> & normalize(const GenoVector<4, T> & vector, GenoVector<4, T> & target) {
	auto scalar = 1 / vector.getLength();
	target.v[0] = vector.v[0] * scalar;
	target.v[1] = vector.v[1] * scalar;
	target.v[2] = vector.v[2] * scalar;
	target.v[3] = vector.v[3] * scalar;
	return target;
}

template <typename T>
GenoVector<4, T> negate(const GenoVector<4, T> & vector) {
	return {
		-vector.v[0],
		-vector.v[1],
		-vector.v[2],
		-vector.v[3]
	};
}

template <typename T>
GenoVector<4, T> & negate(const GenoVector<4, T> & vector, GenoVector<4, T> & target) {
	target.v[0] = -vector.v[0];
	target.v[1] = -vector.v[1];
	target.v[2] = -vector.v[2];
	target.v[3] = -vector.v[3];
	return target;
}

template <typename T>
T dot(const GenoVector<4, T> & left, const GenoVector<4, T> & right) {
	return (
		left.v[0] * right.v[0] +
		left.v[1] * right.v[1] +
		left.v[2] * right.v[2] +
		left.v[3] * right.v[3]
	);
}

template <typename T>
GenoVector<4, T> project(const GenoVector<4, T> & vector, const GenoVector<4, T> & projection) {
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	return {
		scalar * projection.v[0],
		scalar * projection.v[1],
		scalar * projection.v[2],
		scalar * projection.v[3]
	};
}

template <typename T>
GenoVector<4, T> & project(const GenoVector<4, T> & vector, const GenoVector<4, T> & projection, GenoVector<4, T> & target) {
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	target.v[0] = scalar * projection.v[0];
	target.v[1] = scalar * projection.v[1];
	target.v[2] = scalar * projection.v[2];
	target.v[3] = scalar * projection.v[3];
	return target;
}

template <typename T>
GenoVector<4, T> translate(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0]	+ translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[3]
	};
}

template <typename T>
GenoVector<4, T> & translate(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template <typename T>
GenoVector<4, T> scale(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale,
		vector.v[3] * scale
	};
}

template <typename T>
GenoVector<4, T> & scale(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3] * scale;
	return target;
}

template <typename T>
GenoVector<4, T> scale(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[3]
	};
}

template <typename T>
GenoVector<4, T> & scale(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setX(const GenoVector<4, T> & vector, T x) {
	return {
		x,
		vector.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setY(const GenoVector<4, T> & vector, T y) {
	return {
		vector.v[0],
		y,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setZ(const GenoVector<4, T> & vector, T z) {
	return {
		vector.v[0],
		vector.v[1],
		z,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setW(const GenoVector<4, T> & vector, T w) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2],
		w
	};
}

template<typename T>
GenoVector<4, T> setXY(const GenoVector<4, T> & vector, T x, T y) {
	return {
		x,
		y,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[0],
		   set.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXZ(const GenoVector<4, T> & vector, T x, T z) {
	return {
		x,
		vector.v[1],
		z,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[0],
		vector.v[1],
		   set.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXW(const GenoVector<4, T> & vector, T x, T w) {
	return {
		x,
		vector.v[1],
		vector.v[2],
		w
	};
}

template<typename T>
GenoVector<4, T> setXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[0],
		vector.v[1],
		vector.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[1],
		   set.v[0],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setYZ(const GenoVector<4, T> & vector, T y, T z) {
	return {
		vector.v[0],
		y,
		z,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[0],
		   set.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setYW(const GenoVector<4, T> & vector, T y, T w) {
	return {
		vector.v[0],
		y,
		vector.v[2],
		w
	};
}

template<typename T>
GenoVector<4, T> setYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[0],
		vector.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[1],
		vector.v[1],
		   set.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[1],
		   set.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setZW(const GenoVector<4, T> & vector, T z, T w) {
	return {
		vector.v[0],
		vector.v[1],
		z,
		w
	};
}

template<typename T>
GenoVector<4, T> setZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		vector.v[1],
		   set.v[0],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		   set.v[1],
		vector.v[1],
		vector.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		   set.v[1],
		vector.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set) {
	return {
		vector.v[0],
		vector.v[1],
		   set.v[1],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setXYZ(const GenoVector<4, T> & vector, T x, T y, T z) {
	return {
		x,
		y,
		z,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		   set.v[1],
		   set.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXYW(const GenoVector<4, T> & vector, T x, T y, T w) {
	return {
		x,
		y,
		vector.v[2],
		w
	};
}

template<typename T>
GenoVector<4, T> setXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		   set.v[1],
		vector.v[2],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		   set.v[2],
		   set.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setXZW(const GenoVector<4, T> & vector, T x, T z, T w) {
	return {
		x,
		vector.v[1],
		z,
		w
	};
}

template<typename T>
GenoVector<4, T> setXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		vector.v[1],
		   set.v[1],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		   set.v[2],
		vector.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[0],
		vector.v[1],
		   set.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		   set.v[0],
		   set.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		   set.v[0],
		vector.v[2],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		   set.v[0],
		   set.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setYZW(const GenoVector<4, T> & vector, T y, T z, T w) {
	return {
		vector.v[0],
		y,
		z,
		w
	};
}

template<typename T>
GenoVector<4, T> setYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[0],
		   set.v[1],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		   set.v[0],
		vector.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[0],
		   set.v[2],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		   set.v[2],
		   set.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		vector.v[1],
		   set.v[0],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		   set.v[1],
		   set.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> setZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[1],
		   set.v[0],
		   set.v[2]
	};
}

template<typename T>
GenoVector<4, T> setZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		vector.v[1],
		   set.v[0],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[2],
		   set.v[0],
		   set.v[1]
	};
}

template<typename T>
GenoVector<4, T> setWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		   set.v[2],
		vector.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[1],
		vector.v[1],
		   set.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		   set.v[1],
		vector.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[1],
		   set.v[2],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		   set.v[2],
		vector.v[1],
		   set.v[1],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set) {
	return {
		vector.v[0],
		   set.v[2],
		   set.v[1],
		   set.v[0]
	};
}

template<typename T>
GenoVector<4, T> setX(const GenoVector<4, T> & vector, T x, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setY(const GenoVector<4, T> & vector, T y, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setZ(const GenoVector<4, T> & vector, T z, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = z;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setW(const GenoVector<4, T> & vector, T w, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setXY(const GenoVector<4, T> & vector, T x, T y, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = y;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXZ(const GenoVector<4, T> & vector, T x, T z, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = z;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXW(const GenoVector<4, T> & vector, T x, T w, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setYZ(const GenoVector<4, T> & vector, T y, T z, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = z;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setYW(const GenoVector<4, T> & vector, T y, T w, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = vector.v[2];
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[0];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setZW(const GenoVector<4, T> & vector, T z, T w, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = z;
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[0];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[1];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[1];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setXYZ(const GenoVector<4, T> & vector, T x, T y, T z, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = y;
	target.v[2] = z;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXYW(const GenoVector<4, T> & vector, T x, T y, T w, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = y;
	target.v[2] = vector.v[2];
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[1];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[2];
	target.v[2] =    set.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setXZW(const GenoVector<4, T> & vector, T x, T z, T w, GenoVector<4, T> & target) {
	target.v[0] = x;
	target.v[1] = vector.v[1];
	target.v[2] = z;
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[1];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] =    set.v[2];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[0];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[0];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setYZW(const GenoVector<4, T> & vector, T y, T z, T w, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = y;
	target.v[2] = z;
	target.v[3] = w;
	return target;
}

template<typename T>
GenoVector<4, T> setYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[1];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] =    set.v[0];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[0];
	target.v[2] =    set.v[2];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[2];
	target.v[2] =    set.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[0];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> setZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[0];
	target.v[3] =    set.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> setZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[0];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[2];
	target.v[2] =    set.v[0];
	target.v[3] =    set.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> setWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] =    set.v[2];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[1];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] =    set.v[1];
	target.v[2] = vector.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[1];
	target.v[2] =    set.v[2];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] =    set.v[2];
	target.v[1] = vector.v[1];
	target.v[2] =    set.v[1];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> setWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & set, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] =    set.v[2];
	target.v[2] =    set.v[1];
	target.v[3] =    set.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateX(const GenoVector<4, T> & vector, T translateX) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateY(const GenoVector<4, T> & vector, T translateY) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZ(const GenoVector<4, T> & vector, T translateZ) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] + translateZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateW(const GenoVector<4, T> & vector, T translateW) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2],
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateXY(const GenoVector<4, T> & vector, T translateX, T translateY) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXZ(const GenoVector<4, T> & vector, T translateX, T translateZ) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2] + translateZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1],
		vector.v[2] + translate.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXW(const GenoVector<4, T> & vector, T translateX, T translateW) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2],
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1],
		vector.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYZ(const GenoVector<4, T> & vector, T translateY, T translateZ) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2] + translateZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYW(const GenoVector<4, T> & vector, T translateY, T translateW) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2],
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[0],
		vector.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZW(const GenoVector<4, T> & vector, T translateZ, T translateW) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] + translateZ,
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1],
		vector.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateXYZ(const GenoVector<4, T> & vector, T translateX, T translateY, T translateZ) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2] + translateZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXYW(const GenoVector<4, T> & vector, T translateX, T translateY, T translateW) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2],
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXZW(const GenoVector<4, T> & vector, T translateX, T translateZ, T translateW) {
	return {
		vector.v[0] + translateX,
		vector.v[1],
		vector.v[2] + translateZ,
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYZW(const GenoVector<4, T> & vector, T translateY, T translateZ, T translateW) {
	return {
		vector.v[0],
		vector.v[1] + translateY,
		vector.v[2] + translateZ,
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[0],
		vector.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[2],
		vector.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[1],
		vector.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate) {
	return {
		vector.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateXYZW(const GenoVector<4, T> & vector, T translateX, T translateY, T translateZ, T translateW) {
	return {
		vector.v[0] + translateX,
		vector.v[1] + translateY,
		vector.v[2] + translateZ,
		vector.v[3] + translateW
	};
}

template<typename T>
GenoVector<4, T> translateXYZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXYWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateXZYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateXZWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateXWYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateXWZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[0],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateYXZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYXWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateYZXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateYZWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateYWXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateYWZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[0],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateZXYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZXWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateZYXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[3]
	};
}

template<typename T>
GenoVector<4, T> translateZYWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[2]
	};
}

template<typename T>
GenoVector<4, T> translateZWXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateZWYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[0],
		vector.v[3] + translate.v[1]
	};
}

template<typename T>
GenoVector<4, T> translateWXYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWXZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[1],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWYXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[3],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWYZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[1],
		vector.v[2] + translate.v[2],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWZXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[2],
		vector.v[1] + translate.v[3],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateWZYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate) {
	return {
		vector.v[0] + translate.v[3],
		vector.v[1] + translate.v[2],
		vector.v[2] + translate.v[1],
		vector.v[3] + translate.v[0]
	};
}

template<typename T>
GenoVector<4, T> translateX(const GenoVector<4, T> & vector, T translateX, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateY(const GenoVector<4, T> & vector, T translateY, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZ(const GenoVector<4, T> & vector, T translateZ, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateW(const GenoVector<4, T> & vector, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateXY(const GenoVector<4, T> & vector, T translateX, T translateY, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZ(const GenoVector<4, T> & vector, T translateX, T translateZ, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXW(const GenoVector<4, T> & vector, T translateX, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZ(const GenoVector<4, T> & vector, T translateY, T translateZ, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYW(const GenoVector<4, T> & vector, T translateY, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZW(const GenoVector<4, T> & vector, T translateZ, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateXYZ(const GenoVector<4, T> & vector, T translateX, T translateY, T translateZ, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXYW(const GenoVector<4, T> & vector, T translateX, T translateY, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZW(const GenoVector<4, T> & vector, T translateX, T translateZ, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZW(const GenoVector<4, T> & vector, T translateY, T translateZ, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateXYZW(const GenoVector<4, T> & vector, T translateX, T translateY, T translateZ, T translateW, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translateX;
	target.v[1] = vector.v[1] + translateY;
	target.v[2] = vector.v[2] + translateZ;
	target.v[3] = vector.v[3] + translateW;
	return target;
}

template<typename T>
GenoVector<4, T> translateXYZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXYWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateXZWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateXWYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateXWZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[0];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateYXZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYXWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateYZWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateYWXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateYWZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[0];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateZXYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZXWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateZYXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> translateZYWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> translateZWXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateZWYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[0];
	target.v[3] = vector.v[3] + translate.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> translateWXYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWXZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[1];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWYXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[3];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWYZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[1];
	target.v[2] = vector.v[2] + translate.v[2];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWZXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[2];
	target.v[1] = vector.v[1] + translate.v[3];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> translateWZYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & translate, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] + translate.v[3];
	target.v[1] = vector.v[1] + translate.v[2];
	target.v[2] = vector.v[2] + translate.v[1];
	target.v[3] = vector.v[3] + translate.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleX(const GenoVector<4, T> & vector, T scaleX) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleY(const GenoVector<4, T> & vector, T scaleY) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZ(const GenoVector<4, T> & vector, T scaleZ) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scaleZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleW(const GenoVector<4, T> & vector, T scaleW) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2],
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, T scaleX, T scaleY) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1],
		vector.v[2] * scale,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, T scaleX, T scaleZ) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2] * scaleZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1],
		vector.v[2] * scale.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1],
		vector.v[2],
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, T scaleX, T scaleW) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2],
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1],
		vector.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1] * scale,
		vector.v[2] * scale,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, T scaleY, T scaleZ) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1] * scale,
		vector.v[2],
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, T scaleY, T scaleW) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2],
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[0],
		vector.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scale,
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, T scaleZ, T scaleW) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scaleZ,
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1],
		vector.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale) {
	return {
		vector.v[0],
		vector.v[1],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleZ) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ,
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2],
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleW) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2],
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1],
		vector.v[2] * scale,
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, T scaleX, T scaleZ, T scaleW) {
	return {
		vector.v[0] * scaleX,
		vector.v[1],
		vector.v[2] * scaleZ,
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[2],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0],
		vector.v[1] * scale,
		vector.v[2] * scale,
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, T scaleY, T scaleZ, T scaleW) {
	return {
		vector.v[0],
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ,
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[0],
		vector.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[2],
		vector.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[1],
		vector.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale) {
	return {
		vector.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, T scale) {
	return {
		vector.v[0] * scale,
		vector.v[1] * scale,
		vector.v[2] * scale,
		vector.v[3] * scale
	};
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleZ, T scaleW) {
	return {
		vector.v[0] * scaleX,
		vector.v[1] * scaleY,
		vector.v[2] * scaleZ,
		vector.v[3] * scaleW
	};
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXYWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleXZYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleXZWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleXWYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleXWZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[0],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleYXZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYXWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleYZXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleYZWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleYWXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleYWZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[0],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleZXYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZXWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleZYXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[3]
	};
}

template<typename T>
GenoVector<4, T> scaleZYWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[2]
	};
}

template<typename T>
GenoVector<4, T> scaleZWXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleZWYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[0],
		vector.v[3] * scale.v[1]
	};
}

template<typename T>
GenoVector<4, T> scaleWXYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWXZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[1],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWYXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[3],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWYZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[1],
		vector.v[2] * scale.v[2],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWZXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[2],
		vector.v[1] * scale.v[3],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleWZYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale) {
	return {
		vector.v[0] * scale.v[3],
		vector.v[1] * scale.v[2],
		vector.v[2] * scale.v[1],
		vector.v[3] * scale.v[0]
	};
}

template<typename T>
GenoVector<4, T> scaleX(const GenoVector<4, T> & vector, T scaleX, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleY(const GenoVector<4, T> & vector, T scaleY, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZ(const GenoVector<4, T> & vector, T scaleZ, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleW(const GenoVector<4, T> & vector, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, T scaleX, T scaleY, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, T scaleX, T scaleZ, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, T scaleX, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, T scaleY, T scaleZ, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, T scaleY, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleYW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, T scaleZ, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleZW(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWX(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWY(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWZ(const GenoVector<4, T> & vector, const GenoVector<2, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleZ, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, T scaleX, T scaleZ, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, T scaleY, T scaleZ, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYWZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZXW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZYW(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZWX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZWY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWXY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWXZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWYX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWYZ(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWZX(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWZY(const GenoVector<4, T> & vector, const GenoVector<3, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, T scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale;
	target.v[1] = vector.v[1] * scale;
	target.v[2] = vector.v[2] * scale;
	target.v[3] = vector.v[3] * scale;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, T scaleX, T scaleY, T scaleZ, T scaleW, const GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scaleX;
	target.v[1] = vector.v[1] * scaleY;
	target.v[2] = vector.v[2] * scaleZ;
	target.v[3] = vector.v[3] * scaleW;
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXYWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXZWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXWYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleXWZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[0];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYXZW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYXWZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYZWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYWXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleYWZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[0];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZXYW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZXWY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZYXW(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[3];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZYWX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[2];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZWXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleZWYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[0];
	target.v[3] = vector.v[3] * scale.v[1];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWXYZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWXZY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[1];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWYXZ(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[3];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWYZX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[1];
	target.v[2] = vector.v[2] * scale.v[2];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWZXY(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[2];
	target.v[1] = vector.v[1] * scale.v[3];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template<typename T>
GenoVector<4, T> scaleWZYX(const GenoVector<4, T> & vector, const GenoVector<4, T> & scale, GenoVector<4, T> & target) {
	target.v[0] = vector.v[0] * scale.v[3];
	target.v[1] = vector.v[1] * scale.v[2];
	target.v[2] = vector.v[2] * scale.v[1];
	target.v[3] = vector.v[3] * scale.v[0];
	return target;
}

template <typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<4, T> & vector) {
	return stream << '<' << vector.v[0] << ", " << vector.v[1] << ", " << vector.v[2] << ", " << vector.v[3] << '>';
}

template <typename T> using GenoVector4 = GenoVector<4, T>;

using GenoVector4b  = GenoVector4< int8 >;
using GenoVector4ub = GenoVector4<uint8 >;
using GenoVector4s  = GenoVector4< int16>;
using GenoVector4us = GenoVector4<uint16>;
using GenoVector4i  = GenoVector4< int32>;
using GenoVector4ui = GenoVector4<uint32>;
using GenoVector4l  = GenoVector4< int64>;
using GenoVector4ul = GenoVector4<uint64>;
using GenoVector4f  = GenoVector4<float >;
using GenoVector4d  = GenoVector4<double>;

#define GNARLY_GENOME_VECTOR4_FORWARD
#endif // GNARLY_GENOME_VECTOR4