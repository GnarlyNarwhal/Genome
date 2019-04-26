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
#include <cmath>
#include <initializer_list>

#include "../../GenoInts.h"

template <uint32 N, typename T>
class GenoVector {

	static_assert(N > 0, "Vector dimensions must be greater than 0!");

	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] v;
		}

	public:
		static GenoVector<N, T> * newArray(uint32 length) {
			T * v = new T[N * length];
			GenoVector<N, T> * ret = new GenoVector<N, T>[length];
			ret[0] = GenoVector<N, T>(v);
			for (uint32 i = 1; i < length; ++i)
				ret[i] = GenoVector<N, T>(v + i * N, false);
			return ret;
		}

		T * v;

		GenoVector() :
			v(new T[N]()) {}

		GenoVector(T * v, bool owner = true) noexcept :
			owner(owner),
			v(v) {}
		
		explicit GenoVector(T value) :
			v(new T[N]) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = value;
		}

		GenoVector(std::initializer_list<T> list) :
			v(new T[N]) {
			auto min  = list.size() < N ? list.size() : N;
			auto init = list.begin();
			for (uint32 i = 0; i < min; ++i)
				v[i] = init[i];
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
			owner(vector.owner),
			v(vector.v) {
			vector.owner = false;
		}

		GenoVector<N, T> & operator=(const GenoVector<N, T> & vector) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = vector.v[i];
			return *this;
		}
		
		GenoVector<N, T> & operator=(GenoVector<N, T> && vector) noexcept {
			if (owner) {
				clean();
				owner = vector.owner;
				v = vector.v;
				vector.owner = false;
			}
			else for (uint32 i = 0; i < N; ++i)
				v[i] = vector.v[i];
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
		
		T getLength() const {
			auto lengthSquared = 0;
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return sqrt(lengthSquared);
		}

		T getLengthSquared() const {
			auto lengthSquared = 0;
			for (uint32 i = 0; i < N; ++i)
				lengthSquared += v[i] * v[i];
			return lengthSquared;
		}

		GenoVector<N, T> & setLength(T length) {
			auto scalar = length / getLength();
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scalar;
			return *this;
		}

		GenoVector<N, T> & normalize() {
			auto scalar = 1 / getLength();
			for (uint32 i = 0; i < N; ++i)
				v[i] *= scalar;
			return *this;
		}

		GenoVector<N, T> & negate() {
			for (uint32 i = 0; i < N; ++i)
				v[i] = -v[i];
			return *this;
		}

		GenoVector<N, T> & project(const GenoVector<N, T> & projection) {
			auto scalar = dot(*this, projection) / projection.getLengthSquared();
			for (uint32 i = 0; i < N; ++i)
				v[i] = scalar * projection.v[i];
			return *this;
		}

		GenoVector<N, T> & set(const GenoVector<N, T> & set) {
			for (uint32 i = 0; i < N; ++i)
				v[i] = set.v[i];
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
			clean();
		}
};

template <uint32 N, typename T>
GenoVector<N, T> operator-(const GenoVector<N, T> & vector) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = -vector.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator+(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] + right.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator-(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] - right.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(const GenoVector<N, T> & left, T right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] * right;
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(T left, const GenoVector<N, T> & right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left * right.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator*(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] * right.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator/(const GenoVector<N, T> & left, T right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] / right;
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> operator/(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i] / right.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N + 1, T> operator|(const GenoVector<N, T> & left, T right) {
	auto newV = new T[N + 1];
	for (uint32 i = 0; i < N + 1; ++i)
		newV[i] = left.v[i];
	newV[N] = right;
	return newV;
}

template <uint32 N, typename T>
GenoVector<N + 1, T> operator|(T left, const GenoVector<N, T> & right) {
	auto newV = new T[N + 1];
	newV[0] = left;
	for (uint32 i = 0; i < N + 1; ++i)
		newV[i + 1] = right.v[i];
	return newV;
}

template <uint32 N, uint32 N2, typename T>
GenoVector<N + N2, T> operator|(const GenoVector<N, T> & left, const GenoVector<N2, T> & right) {
	auto newV = new T[N + N2];
	auto vRight = newV + N;
	for (uint32 i = 0; i < N; ++i)
		newV[i] = left.v[i];
	for (uint32 i = 0; i < N2; ++i)
		vRight[i] = right.v[i];
	return newV;	
}

template <uint32 N, typename T>
GenoVector<N, T> setLength(const GenoVector<N, T> & vector, T length) {
	auto scalar = length / vector.getLength();
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scalar;
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> & setLength(const GenoVector<N, T> & vector, T length, const GenoVector<N, T> & target) {
	auto scalar = length / vector.getLength();
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] * scalar;
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> normalize(const GenoVector<N, T> & vector) {
	auto scalar = 1 / vector.getLength();
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scalar;
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> & normalize(const GenoVector<N, T> & vector, const GenoVector<N, T> & target) {
	auto scalar = 1 / vector.getLength();
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] * scalar;
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> negate(const GenoVector<N, T> & vector) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = -vector.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> & negate(const GenoVector<N, T> & vector, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = -vector.v[i];
	return target;
}

template <uint32 N, typename T>
T dot(const GenoVector<N, T> & left, const GenoVector<N, T> & right) {
	auto product = T();
	for (uint32 i = 0; i < N; ++i)
		product += left.v[i] * right.v[i];
	return product;
}

template <uint32 N, typename T>
GenoVector<N, T> project(const GenoVector<N, T> & vector, const GenoVector<N, T> & projection) {
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = scalar * projection.v[i];
	return newV;
}

template <uint32 N, typename T>
GenoVector<N, T> & project(const GenoVector<N, T> & vector, const GenoVector<N, T> & projection, GenoVector<N, T> & target) {
	auto scalar = dot(vector, projection) / projection.getLengthSquared();
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = scalar * projection.v[i];
	return target;
}

template <uint32 N, typename T>
T angleBetween(const GenoVector<N, T> & vector1, const GenoVector<N, T> & vector2) {
	return acos(dot(vector1, vector2) / (vector1.getLength() * vector2.getLength()));
}

template <uint32 N, typename T>
GenoVector<N, T> & translate(const GenoVector<N, T> & vector, const GenoVector<N, T> & translate) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] + translate.v[i];
	return newV;
}


template <uint32 N, typename T>
GenoVector<N, T> & translate(const GenoVector<N, T> & vector, const GenoVector<N, T> & translate, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] + translate.v[i];
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, T scale) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scale;
	return newV;
}


template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, T scale, GenoVector<N, T> & target) {
	for (uint32 i = 0; i < N; ++i)
		target.v[i] = vector.v[i] * scale;
	return target;
}

template <uint32 N, typename T>
GenoVector<N, T> & scale(const GenoVector<N, T> & vector, const GenoVector<N, T> & scale) {
	auto newV = new T[N];
	for (uint32 i = 0; i < N; ++i)
		newV[i] = vector.v[i] * scale.v[i];
	return newV;
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

#define GNARLY_GENOME_VECTOR_FORWARD
#endif // GNARLY_GENOME_VECTOR
