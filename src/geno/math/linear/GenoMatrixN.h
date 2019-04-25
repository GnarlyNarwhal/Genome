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
 * INPLIED, INCLUDING BUT NOT LINITED TO THE WARRANTIES OF NERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGENENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIN, DANAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FRON,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include "../../GenoInts.h"

#ifndef GNARLY_GENOME_VECTOR_FORWARD
#define GNARLY_GENOME_VECTOR_FORWARD

template <uint32 N, typename T>
class GenoVector<N, T>;

#endif // GNARLY_GENOME_VECTOR_FORWARD

#ifndef GNARLY_GENOME_MATRIX_FORWARD
#define GNARLY_GENOME_MATRIX_FORWARD

template <uint32 N, uint32 M, typename T>
class GenoMatrix;

#endif // GNARLY_GENOME_MATRIX_FORWARD

#ifndef GNARLY_GENOME_MATRIXN
#define GNARLY_GENOME_MATRIXN

#include <ostream>

#include "GenoVector.h"
#include "GenoMatrix.h"

template <uint32 N, typename T>
class GenoMatrix<N, N, T> {

	static_assert(N > 0 && N > 0, "Matrix dimensions must be greater than 0!");

	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] m;
		}
	public:
		T * m;

		static GenoMatrix<N, N, T> makeIdentity() {
			auto identity = new T[N * N];
			for (uint32 i = 0; i < N * N; ++i) {
				if (i % N == i / N)
					identity[i] = 1;
				else
					identity[i] = 0;
			}
			return identity;
		}

		GenoMatrix() :
			m(new T[N * N]()) {}

		GenoMatrix(T * m, bool owner = true) noexcept :
			owner(owner),
			m(m) {}
		
		GenoMatrix(std::initializer_list<T> list) :
			m(new T[N * N]) {
			auto min  = list.size() < N * N ? list.size() : N * N;
			auto init = list.begin();
			for (uint32 i = 0; i < min; ++i)
				m[(i % N) * N + (i / N)] = init[i];
		}

		template <typename T2>
		GenoMatrix(const GenoMatrix<N, N, T2> & matrix) :
			m(new T[N * N]) {
			for (uint32 i = 0; i < N * N; ++i)
				m[i] = (T) matrix.m[i];
		}

		GenoMatrix(const GenoMatrix<N, N, T> & matrix) :
			m(new T[N * N]) {
			for (uint32 i = 0; i < N * N; ++i)
				m[i] = matrix.m[i];
		}

		GenoMatrix(GenoMatrix<N, N, T> && matrix) noexcept :
			owner(matrix.owner),
			m(matrix.m) {
			matrix.owner = false;
		}

		GenoMatrix<N, N, T> & operator=(const GenoMatrix<N, N, T> & matrix) {
			for (uint32 i = 0; i < N * N; ++i)
				m[i] = matrix.m[i];
			return *this;
		}

		GenoMatrix<N, N, T> & operator=(GenoMatrix<N, N, T> && matrix) noexcept {
			clean();
			owner = matrix.owner;
			m = matrix.m;
			matrix.owner = false;
			return *this;
		}

		GenoMatrix<N, N, T> & operator+=(const GenoMatrix<N, N, T> & matrix) {
			for (uint32 i = 0; i < N * N; ++i)
				m[i] += matrix.m[i];
			return *this;
		}

		GenoMatrix<N, N, T> & operator-=(const GenoMatrix<N, N, T> & matrix) {
			for (uint32 i = 0; i < N * N; ++i)
				m[i] -= matrix.m[i];
			return *this;
		}

		GenoMatrix<N, N, T> & operator*=(const GenoMatrix<N, N, T> & matrix) {
			return *this = *this * matrix;
		}

		GenoVector<N, T> operator[](uint32 index) const noexcept {
			return GenoVector<N, T>(index * N, false);
		}

		GenoMatrix<N, N, T> & setIdentity() {
			for (uint32 i = 0; i < N * N; ++i) {
				if (i % N == i / N)
					m[i] = 1;
				else
					m[i] = 0;
			}
			return *this;
		}

		~GenoMatrix() {
			clean();
		}
};

template <uint32 N, typename T>
T det(const GenoMatrix<N, N, T> & matrix) {
	auto ret    = T{ 0 };
	auto sign   = T{ 1 };
	GenoMatrix<N - 1, N - 1, T> storage;
	for (uint32 i = 0; i < N; ++i) {
		auto offset = uint32( -1 );
		for (uint32 j = 0; j < N * N; ++j)
			if (j % N != 0 && j / N != i)
				storage.m[++offset] = matrix.m[j];
		ret  += sign * matrix.m[i * N] * det(storage);
		sign *= -1;
	}
	return ret;
}

template <typename T>
T det(const GenoMatrix<2, 2, T> & matrix) {
	return matrix.m[0] * matrix.m[3] - matrix.m[2] * matrix.m[1];
}

template <typename T>
T det(const GenoMatrix<1, 1, T> & matrix) {
	return matrix.m[0];
}

template <uint32 N> using GenoMatrixNb  = GenoMatrix<N, N,  int8 >;
template <uint32 N> using GenoMatrixNub = GenoMatrix<N, N, uint8 >;
template <uint32 N> using GenoMatrixNs  = GenoMatrix<N, N,  int16>;
template <uint32 N> using GenoMatrixNus = GenoMatrix<N, N, uint16>;
template <uint32 N> using GenoMatrixNi  = GenoMatrix<N, N,  int32>;
template <uint32 N> using GenoMatrixNui = GenoMatrix<N, N, uint32>;
template <uint32 N> using GenoMatrixNl  = GenoMatrix<N, N,  int8 >;
template <uint32 N> using GenoMatrixNul = GenoMatrix<N, N, uint64>;
template <uint32 N> using GenoMatrixNf  = GenoMatrix<N, N, float >;
template <uint32 N> using GenoMatrixNd  = GenoMatrix<N, N, double>;

#define GNARLY_GENOME_MATRIXN_FORWARD
#endif // GNARLY_GENOME_MATRIXN