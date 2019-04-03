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

#ifndef GNARLY_GENOME_VECTOR2
#define GNARLY_GENOME_VECTOR2

#include "GenoVector.h"

template <typename T>
class GenoVector<2, T> {
	private:
		GenoVector(T * v) :
			v(v) {}
	public:
		T * v;
		
		GenoVector() :
			v(new T[2]) {}

		GenoVector(T x, T y) :
			v(new T[2] { x, y }) {}

		GenoVector(const GenoVector<2, T> & vector) :
			v(new T[2] { vector.v[0], vector.v[1] }) {}

		GenoVector(GenoVector<2, T> && vector) noexcept :
			v(vector.v) {
			vector.v = 0;
		}

		GenoVector<2, T> & operator=(const GenoVector<2, T> & vector) {
			for (uint32 i = 0; i < 2; ++i)
				v[i] = vector.v[i];
			return *this;
		}

		GenoVector<2, T> & operator=(GenoVector<2, T> && vector) noexcept {
			delete[] v;
			v = vector.v;
			vector.v = 0;
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

		virtual ~GenoVector() noexcept {
			delete [] v;
		}
};

template <typename FT>
GenoVector<2, FT> operator-(const GenoVector<2, FT> & vector) {
	return { -vector.v[0],
	         -vector.v[1] };
}

template <typename FT>
GenoVector<2, FT> operator+(const GenoVector<2, FT> & left, const GenoVector<2, FT> & right) {
	return { left.v[0] + right.v[0],
	         left.v[1] + right.v[1] };
}

template <typename FT>
GenoVector<2, FT> operator-(const GenoVector<2, FT> & left, const GenoVector<2, FT> & right) {
	return { left.v[0] - right.v[0],
	         left.v[1] - right.v[1] };
}

template <typename FT>
GenoVector<2, FT> operator*(FT left, const GenoVector<2, FT> & right) {
	return { left * right.v[0],
	         left * right.v[1] };
}

template <typename FT>
GenoVector<2, FT> operator*(const GenoVector<2, FT> & left, FT right) {
	return { left.v[0] * right,
	         left.v[1] * right };
}

template <typename FT>
GenoVector<2, FT> operator*(const GenoVector<2, FT> & left, const GenoVector<2, FT> & right) {
	return { left.v[0] * right.v[0],
	         left.v[1] * right.v[1] };
}

template <typename FT>
GenoVector<2, FT> operator/(const GenoVector<2, FT> & left, FT right) {
	return { left.v[0] / right,
	         left.v[1] / right };
}

template <typename FT>
GenoVector<2, FT> operator/(const GenoVector<2, FT> & left, const GenoVector<2, FT> & right) {
	return { left.v[0] / right.v[0],
	         left.v[1] / right.v[1] };
}

template <typename FT>
GenoVector<3, FT> operator|(FT left, const GenoVector<2, FT> & right) {
	return { left, right.v[0], right.v[1] };
}

template <typename FT>
GenoVector<3, FT> operator|(const GenoVector<2, FT> & left, FT right) {
	return { left.v[0], left.v[1], right };
}

template <typename FT>
GenoVector<4, FT> operator|(const GenoVector<2, FT> & left, const GenoVector<2, FT> & right) {
	return { left.v[0], left.v[1], right.v[0], right.v[1] };
}

template <typename T> using GenoVector3 = GenoVector<3, T>;

using GenoVector2b  = GenoVector<2,  int8 >;
using GenoVector2nb = GenoVector<2, uint8 >;
using GenoVector2s  = GenoVector<2,  int16>;
using GenoVector2us = GenoVector<2, uint16>;
using GenoVector2i  = GenoVector<2,  int32>;
using GenoVector2ui = GenoVector<2, uint32>;
using GenoVector2l  = GenoVector<2,  int64>;
using GenoVector2ul = GenoVector<2, uint64>;
using GenoVector2f  = GenoVector<2, float >;
using GenoVector2d  = GenoVector<2, double>;

#define GNARLY_GENOME_VECTOR2_FORWARD
#endif // GNARLY_GENOME_VECTOR2