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

#ifndef GNARLY_GENOME_VECTOR1
#define GNARLY_GENOME_VECTOR1

#include "GenoVector.h"

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

#define GNARLY_GENOME_VECTOR1_FORWARD
#endif // GNARLY_GENOME_VECTOR1