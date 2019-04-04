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
#include <utility>
#include <initializer_list>

#include "../GenoInts.h"

template <uint32 N, typename T>
class GenoVector {

	static_assert(N > 0, "Vector dimensions must be greater than 0!");

	public:
		T * v;

		GenoVector() :
			v(new T[N]()) {}

		GenoVector(T * v) noexcept :
			v(v) {}
		
		explicit GenoVector(T value) :
			v(new T[N]) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = value;
		}

		GenoVector(std::initializer_list<T> list) :
			v(new T[N]) {
			const T * VECTOR_END = v + N;
			const T * iterator = list.begin() - 1;
			T * vector = v - 1;
			while (++iterator < list.end() && ++vector < VECTOR_END)
				*vector = *iterator;
		}

		template <typename T2>
		GenoVector(const GenoVector<N, T2> & vector) :
			v(new T[N]) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = (T) vector.v[i];
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

		GenoVector<N, T> & operator*=(T scalar) {
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scalar;
			return *this;
		}

		GenoVector<N, T> & operator*=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] *= vector.v[i];
			return *this;
		}

		GenoVector<N, T> & operator/=(T scalar) {
			for (uint32 i = 0; i < N; ++i)
				v[i] /= scalar;
			return *this;
		}

		GenoVector<N, T> & operator/=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] /= vector.v[i];
			return *this;
		}

		T & operator[](uint32 index) noexcept {
			return v[index];
		}

		const T & operator[](uint32 index) const noexcept {
			return v[index];
		}
		
		double getLength() const {
			T lengthSquared = 0;
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return sqrt(lengthSquared);
		}

		T getLengthSquared() const {
			T lengthSquared = T();
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return lengthSquared;
		}

		GenoVector<N, T> & negate() {
			for (uint32 i = 0; i < N; ++i)
				v[i] = -v[i];
			return *this;
		}

		GenoVector<N, T> & project(const GenoVector<N, T> & projection) {
			T scalar = dot(*this, projection) / projection.getLengthSquared();
			for (uint32 i = 0; i < N; ++i)
				v[i] = scalar * projection.v[i];
			return *this;
		}

		GenoVector<N, T> & translate(const GenoVector<N, T> & translate) {
			for (uint32 i = 0; i < N; ++i)
				v[i] += translate.v[i];
			return *this;
		}

		GenoVector<N, T> & scale(T scale) {
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scale;
			return *this;
		}

		GenoVector<N, T> & scale(const GenoVector<N, T> & scale) {
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scale.v[i];
			return *this;
		}

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <uint32 N, typename T>
GenoVector<N, T> operator-(const GenoVector<N, T> & vector) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = -vector.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator+(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] + right.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator-(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] - right.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(const GenoVector<N, T> & left, T right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] * right;
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(T left, const GenoVector<N, T> & right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left * right.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] * right.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator/(const GenoVector<N, T> & left, T right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] / right;
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> operator/(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] / right.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N + 1, T> operator|(const GenoVector<N, T> & left, T right) {
	T * newV = new T[N + 1];
	for (uint32 i = 0; i < N + 1; ++i)
		newV[i] = left.v[i];
	newV[N] = right;
	return GenoVector<N + 1, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N + 1, T> operator|(T left, const GenoVector<N, T> & right) {
	T * newV = new T[N + 1];
	newV[0] = left;
	for (uint32 i = 0; i < N + 1; ++i)
		newV[i + 1] = right.v[i];
	return GenoVector<N + 1, T>(newV);
}

template <uint32 N, uint32 N2, typename T>
GenoVector<N + N2, T> operator|(const GenoVector<N, T> & left, const GenoVector<N2, T> & right) {
	T * newV = new T[N + N2];
	T * vRight = newV + N;
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i];
	for (uint32 i = 0; i < N2; ++i)
		vRight[i] = right.v[i];
	return GenoVector<N + N2, T>(newV);	
}

template <uint32 N, typename T>
GenoVector<N, T> negate(const GenoVector<N, T> & vector) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = -vector.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> & negate(const GenoVector<N, T> & vector, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = -vector.v[i];
	return target;
}

template <uint32 N, typename T>
T dot(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	T product = T();
	for (uint32 i = 0; i < N; ++i)
		product += left.v[i] * right.v[i];
	return product;
}

template <uint32 N, typename T>
GenoVector<N, T> project(const GenoVector<N, T> & vector, const GenoVector<N, T> & projection) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = scalar * projection.v[i];
	return GenoVector<N, T>(newV);
}

template <uint32 N, typename T>
GenoVector<N, T> & project(const GenoVector<N, T> & vector, const GenoVector<N, T> & projection, GenoVector<N, T> & target) {
	T scalar = dot(vector, projection) / projection.getLengthSquared();
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = scalar * projection.v[i];
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> & translate(const GenoVector<N, T> & vector, const GenoVector<N, T> & translate) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] + translate.v[i];
	return GenoVector<N, T>(newV);
}


template <uint32 N, typename T>
GenoVector<N, T> & translate(const GenoVector<N, T> & vector, const GenoVector<N, T> & translate, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] + translate.v[i];
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, T scale) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scale;
	return GenoVector<N, T>(newV);
}


template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, T scale, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] * scale;
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, const GenoVector<N, T> & scale) {
	T * newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scale.v[i];
	return GenoVector<N, T>(newV);
}


template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, const GenoVector<N, T> & scale, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] * scale.v[i];
	return target;
}

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

template <uint32 N> using GenoVectorNb  = GenoVector<N,  int8 >;
template <uint32 N> using GenoVectorNub = GenoVector<N, uint8 >;
template <uint32 N> using GenoVectorNs  = GenoVector<N,  int16>;
template <uint32 N> using GenoVectorNus = GenoVector<N, uint16>;
template <uint32 N> using GenoVectorNi  = GenoVector<N,  int32>;
template <uint32 N> using GenoVectorNui = GenoVector<N, uint32>;
template <uint32 N> using GenoVectorNl  = GenoVector<N,  int64>;
template <uint32 N> using GenoVectorNul = GenoVector<N, uint64>;
template <uint32 N> using GenoVectorNf  = GenoVector<N, float >;
template <uint32 N> using GenoVectorNd  = GenoVector<N, double>;

template <typename T> using GenoVector1 = GenoVector<1, T>;

using GenoVector1b  = GenoVector1< int8 >;
using GenoVector1ub = GenoVector1<uint8 >;
using GenoVector1s  = GenoVector1< int16>;
using GenoVector1us = GenoVector1<uint16>;
using GenoVector1i  = GenoVector1< int32>;
using GenoVector1ui = GenoVector1<uint32>;
using GenoVector1l  = GenoVector1< int64>;
using GenoVector1ul = GenoVector1<uint64>;
using GenoVector1f  = GenoVector1<float >;
using GenoVector1d  = GenoVector1<double>;

GenoVector1b  operator "" _gvb (uint64 x)      { return { ( int8 ) x }; }
GenoVector1ub operator "" _gvub(uint64 x)      { return { (uint8 ) x }; }
GenoVector1s  operator "" _gvs (uint64 x)      { return { ( int16) x }; }
GenoVector1us operator "" _gvus(uint64 x)      { return { (uint16) x }; }
GenoVector1i  operator "" _gvi (uint64 x)      { return { ( int32) x }; }
GenoVector1ui operator "" _gvui(uint64 x)      { return { (uint32) x }; }
GenoVector1l  operator "" _gvl (uint64 x)      { return { ( int64) x }; }
GenoVector1ul operator "" _gvul(uint64 x)      { return { (uint64) x }; }
GenoVector1f  operator "" _gvf (long double x) { return { (float ) x }; }
GenoVector1d  operator "" _gvd (long double x) { return { (double) x }; }

#define GNARLY_GENOME_VECTOR_FORWARD
#endif // GNARLY_GENOME_VECTOR
