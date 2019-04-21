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

#ifndef GNARLY_GENOME_MATRIX
#define GNARLY_GENOME_MATRIX

#include <ostream>

#include "GenoVector.h"

template <uint32 N, uint32 M, typename T>
class GenoMatrix {

	static_assert(N > 0 && M > 0, "Matrix dimensions must be greater than 0!");

	private:
		bool owner = true;

		void clean() {
			if (owner)
				delete [] v;
		}
	public:
		T * m;

		GenoMatrix() :
			m(new T[N * M]()) {}

		GenoMatrix(T * m, bool owner = true) noexcept :
			owner(owner),
			m(m) {}

		template <typename T2>
		GenoMatrix(const GenoMatrix<N, M, T2> & matrix) :
			m(new T[N * M]) {
			for (uint32 i = 0; i < N * M; ++i)
				m[i] = (T) matrix.m[i];
		}

		GenoMatrix(const GenoMatrix<N, M, T> & matrix) :
			m(new T[N * M]) {
			for (uint32 i = 0; i < N * M; ++i)
				m[i] = matrix.m[i];
		}

		GenoMatrix(GenoMatrix<N, M, T> && matrix) noexcept :
			m(matrix.m) {
			matrix.m = 0;
		}

		GenoMatrix<N, M, T> & operator=(const GenoMatrix<N, M, T> & matrix) {
			for (uint32 i = 0; i < N * M; ++i)
				m[i] = matrix.m[i];
			return *this;
		}

		GenoMatrix<N, M, T> & operator=(GenoMatrix<N, M, T> && matrix) {
			clean();
			owner = vector.owner;
			m = matrix.m;
			matrix.owner = false;
			return *this;
		}

		GenoMatrix<N, M, T> & operator+=(const GenoMatrix<N, M, T> & matrix) {
			for (uint32 i = 0; i < N * M; ++i)
				m[i] += matrix.m[i];
			return *this;
		}

		GenoMatrix<N, M, T> & operator-=(const GenoMatrix<N, M, T> & matrix) {
			for (uint32 i = 0; i < N * M; ++i)
				m[i] -= matrix.m[i];
			return *this;
		}

		GenoVector<M, T> operator[](uint32 index) const noexcept {
			return GenoVector<M, T>(index * M, false);
		}

		~GenoMatrix() {
			clean();
		}
};

template <uint32 N, uint32 M, typename T>
GenoMatrix<N, M, T> operator+(const GenoMatrix<N, M, T> & left, const GenoMatrix<N, M, T> & right) {
	auto product = new T[N * M];
	for (uint32 i = 0; i < N * M; ++i)
		product[i] = left.m[i] + right.m[i];
	return GenoMatrix<N, M, T>(product);
}

template <uint32 N, uint32 M, typename T>
GenoMatrix<N, M, T> operator-(const GenoMatrix<N, M, T> & left, const GenoMatrix<N, M, T> & right) {
	auto product = new T[N * M];
	for (uint32 i = 0; i < N * M; ++i)
		product[i] = left.m[i] - right.m[i];
	return GenoMatrix<N, M, T>(product);
}

template <uint32 N, uint32 N2, uint32 M, typename T>
GenoMatrix<N2, M, T> operator*(const GenoMatrix<N, M, T> & left, const GenoMatrix<N2, N, T> & right) {
	auto product = new T[N2 * M];
	for (uint32 i = 0; i < M; ++i) {
		for (uint32 j = 0; j < N2; ++j) {
			product[j * M + i] = 0;
			for (uint32 k = 0; k < N; ++k)
				product[j * M + i] += left.m[k * M + i] * right.m[j * N + k];
		}
	}
	return GenoMatrix<N2, M, T>(product);
}

template <uint32 N, uint32 M, typename T>
std::ostream & operator<<(std::ostream & stream, const GenoMatrix<N, M, T> & matrix) {
	for (uint32 i = 0; i < M; ++i) {
		stream << '[';
		for (uint32 j = 0; j < N; ++j) {
			stream << m[j * M + i];
			if (j < N - 1)
				stream << ", ";
		}
		stream << "]\n";
	}
	return stream;
}

template <uint32 N, uint32 M> using GenoMatrixNMb  = GenoMatrix<N, M,  int8 >;
template <uint32 N, uint32 M> using GenoMatrixNMub = GenoMatrix<N, M, uint8 >;
template <uint32 N, uint32 M> using GenoMatrixNMs  = GenoMatrix<N, M,  int16>;
template <uint32 N, uint32 M> using GenoMatrixNMus = GenoMatrix<N, M, uint16>;
template <uint32 N, uint32 M> using GenoMatrixNMi  = GenoMatrix<N, M,  int32>;
template <uint32 N, uint32 M> using GenoMatrixNMui = GenoMatrix<N, M, uint32>;
template <uint32 N, uint32 M> using GenoMatrixNMl  = GenoMatrix<N, M,  int8 >;
template <uint32 N, uint32 M> using GenoMatrixNMul = GenoMatrix<N, M, uint64>;
template <uint32 N, uint32 M> using GenoMatrixNMf  = GenoMatrix<N, M, float >;
template <uint32 N, uint32 M> using GenoMatrixNMd  = GenoMatrix<N, M, double>;

#define GNARLY_GENOME_MATRIX_FORWARD
#endif // GNARLY_GENOME_MATRIX