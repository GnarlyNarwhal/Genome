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

#ifndef GNARLY_GENOME_VECTOR
#define GNARLY_GENOME_VECTOR

#include <ostream>
#include <initializer_list>
#include <vector>

#include "../GenoInts.h"

template <uint32 N, typename T>
class GenoVector {

	static_assert(N > 0, "Vector dimensions must be greater than 0!");

	private:
		GenoVector(T * v) :
			v(v) {}
	public:
		T * v;

		GenoVector() :
			v(new T[N] ()) {}

		GenoVector(std::initializer_list<T> list) :
			v(new T[N]) {
			const T * VECTOR_END = v + N;
			const T * iterator = list.begin() - 1;
			T * vector = v - 1;
			while (++iterator < list.end() && ++v < VECTOR_END)
				*v = *iterator;
		}
		
		GenoVector(const GenoVector<N, T> & vector) :
			v(new T[N]) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = vector.v[i];
		}
		
		GenoVector(GenoVector<N, T> && vector) noexcept :
			v(vector.v) {
			vector.v = 0;
		}

		GenoVector<N, T> & operator=(std::initializer_list<T> list) {
			const T * const VECTOR_END = v + N;
			const T * iterator = list.begin() - 1;
			T * vector = v - 1;
			while (++iterator < list.end() && ++vector < VECTOR_END)
				*vector = *iterator;
		}

		GenoVector<N, T> & operator=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = vector.v[i];
			return *this;
		}
		
		GenoVector<N, T> & operator=(GenoVector<N, T> && vector) noexcept {
			delete [] v;
			v = vector.v;
			vector.v = 0;
			return *this;
		}

		GenoVector<N, T> & operator+=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] += vector.v[i];
			return *this;
		}

		GenoVector<N, T> & operator-=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] -= vector.v[i];
			return *this;
		}

		GenoVector<N, T> & operator*=(const T & scalar) {
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scalar;
			return *this;
		}

		GenoVector<N, T> & operator*=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] += vector.v[i];
			return *this;
		}

		GenoVector<N, T> & operator/=(const T & scalar) {
			for (uint32 i = 0; i < N; ++i)
				v[i] /= scalar;
			return *this;
		}

		GenoVector<N, T> & operator/=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] -= vector.v[i];
			return *this;
		}

		GenoVector<N, T> operator-() const {
			GenoVector<N, T> negative = *this;
			negative.v[0] = -negative.v[0];
			negative.v[1] = -negative.v[1];
			return negative;
		}

		GenoVector<N, T> operator+(const GenoVector<N, T> & vector) const {
			T * newV = new T[N];
			for (uint32 i = 0; i < N; ++i)
				newV[i] = v[i] + vector.v[i];
			return GenoVector<N, T>(newV);
		}

		GenoVector<N, T> operator+(GenoVector<N, T> && vector) const {
			GenoVector<N, T> sum = vector;
			for (uint32 i = 0; i < N; ++i)
				sum.v[i] = v[i] + sum.v[i];
			return sum;
		}

		GenoVector<N, T> operator-(const GenoVector<N, T> & vector) const {
			T * newV = new T[N];
			for (uint32 i = 0; i < N; ++i)
				newV[i] = v[i] - vector.v[i];
			return GenoVector<N, T>(newV);
		}

		GenoVector<N, T> operator-(GenoVector<N, T> && vector) const {
			GenoVector<N, T> difference = vector;
			for (uint32 i = 0; i < N; ++i)
				difference.v[i] = v[i] - difference.v[i];
			return difference;
		}

		GenoVector<N, T> operator*(const GenoVector<N, T> & vector) const {
			T * newV = new T[N];
			for (uint32 i = 0; i < N; ++i)
				newV[i] = v[i] * vector.v[i];
			return GenoVector<N, T>(newV);
		}

		GenoVector<N, T> operator*(GenoVector<N, T> && vector) const {
			GenoVector<N, T> product = vector;
			for (uint32 i = 0; i < N; ++i)
				product.v[i] = v[i] * product.v[i];
			return product;
		}

		GenoVector<N, T> operator/(const GenoVector<N, T> & vector) const {
			T * newV = new T[N];
			for (uint32 i = 0; i < N; ++i)
				newV[i] = v[i] / vector.v[i];
			return GenoVector<N, T>(newV);
		}

		GenoVector<N, T> operator/(GenoVector<N, T> && vector) const {
			GenoVector<N, T> quotient = vector;
			for (uint32 i = 0; i < N; ++i)
				quotient.v[i] = v[i] / quotient.v[i];
			return quotient;
		}
		
		bool operator==(const GenoVector<N, T> & vector) const {
			for (uint32 i = 0; i < N; ++i)
				if (v[i] != vector.v[i])
					return false;
			return true;
		}

		bool operator!=(const GenoVector<N, T> & vector) const {
			return !operator==(vector);
		}

		T length() const {
			T lengthSquared = 0;
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return sqrt(lengthSquared);
		}

		T lengthSquared() const {
			T lengthSquared = T();
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return lengthSquared;
		}

		T dot(const GenoVector<N, T> & vector) const {
			T ret = T();
			for (uint32 i = 0; i < N; ++i)
				ret += v[i] * vector.v[i];
			return ret;
		}

		GenoVector<N, T> getProjectionOnto(const GenoVector<N, T> & vector) const {
			return (dot(vector) / vector.lengthSquared()) * vector;
		}

		GenoVector<N, T> getProjectionOnto(GenoVector<N, T> && vector) const {
			return (dot(vector) / vector.lengthSquared()) * vector;
		}

		GenoVector<N, T> & projectOnto(const GenoVector<N, T> & vector) {
			T scalar = dot(vector) / vector.lengthSquared();
			for (uint32 i = 0; i < N; ++i)
				v[i] = scalar * vector.v[i];
			return *this;
		}

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <uint32 N, typename T>
std::ostream & operator<<(std::ostream & stream, const GenoVector<N, T> & vector) {
	stream << '<';
	for (uint32 i = 0; i < N; ++i) {
		stream << vector.v[i];
		if (i < N - 1)
			stream << ", ";
	}
	return stream << '>';
}

#define GNARLY_GENOME_VECTOR_FORWARD
#endif // GNARLY_GENOME_VECTOR