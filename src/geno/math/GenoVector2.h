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

#ifndef GNARLY_GENOME_VECTOR2
#define GNARLY_GENOME_VECTOR2

#include <initializer_list>

#include "GenoVector.h"

template <typename T>
class GenoVector2 : GenoVector<2, T> {
	public:
		GenoVector2() :
			GenoVector<2, T>() {}
		
		GenoVector2(T x) :
			GenoVector<2, T>() {
			GenoVector<2, T>::v[0] = x;
		}

		GenoVector2(T x, T y) :
			GenoVector<2, T>() {
			GenoVector<2, T>::v[0] = x;
			GenoVector<2, T>::v[1] = y;
		}

		GenoVector2(std::initializer_list<T> list) :
			GenoVector<2, T>(list) {}

		GenoVector2(const GenoVector2<T> & vector) :
			GenoVector<2, T>(vector) {}

		GenoVector2(GenoVector2<T> && vector) noexcept :
			GenoVector<2, T>(vector) {}

		GenoVector2<T> & operator=(std::initializer_list<T> list) {
			GenoVector<2, T>::operator=(list);
			return *this;
		}

		GenoVector2<T> & operator=(const GenoVector2<T> & vector) {
			GenoVector<2, T>::v[0] = vector.v[0];
			GenoVector<2, T>::v[1] = vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator=(GenoVector2<T> && vector) {
			GenoVector<2, T>::operator=(vector);
			return *this;
		}

		GenoVector2<T> & operator+=(const GenoVector2<T> & vector) {
			GenoVector<2, T>::v[0] += vector.v[0];
			GenoVector<2, T>::v[1] += vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator-=(const GenoVector2<T> & vector) {
			GenoVector<2, T>::v[0] -= vector.v[0];
			GenoVector<2, T>::v[1] -= vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator*=(const GenoVector2<T> & vector) {
			GenoVector<2, T>::v[0] *= vector.v[0];
			GenoVector<2, T>::v[1] *= vector.v[1];
			return *this;
		}

		GenoVector2<T> & operator/=(const GenoVector2<T> & vector) {
			GenoVector<2, T>::v[0] /= vector.v[0];
			GenoVector<2, T>::v[1] /= vector.v[1];
			return *this;
		}

		virtual ~GenoVector2() noexcept {}
};

typedef GenoVector2<int8>   GenoVector2b;
typedef GenoVector2<uint8>  GenoVector2ub;
typedef GenoVector2<int16>  GenoVector2s;
typedef GenoVector2<uint16> GenoVector2us;
typedef GenoVector2<int32>  GenoVector2i;
typedef GenoVector2<uint32> GenoVector2ui;
typedef GenoVector2<int64>  GenoVector2l;
typedef GenoVector2<uint64> GenoVector2ul;
typedef GenoVector2<float>  GenoVector2f;
typedef GenoVector2<double> GenoVector2d;

#define GNARLY_GENOME_VECTOR2_FORWARD
#endif // GNARLY_GENOME_VECTOR2