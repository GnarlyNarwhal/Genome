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

#ifndef GNARLY_GENOME_POLYGON
#define GNARLY_GENOME_POLYGON

#include <initializer_list>

#include "../../GenoInts.h"
#include "../GenoConstants.h"
#include "../linear/GenoVector2.h"

template <typename T>
class GenoPolygon {
	private:
		uint32 numVertices;
		bool owner = true;

		void clean() {
			if (owner)
				delete [] p;
		}
	public:
		GenoVector2<T> * p;

		GenoPolygon(uint32 numVertices) :
			numVertices(numVertices),
			p(GenoVector2<T>::newArray(numVertices)) {
			auto angle  = GENO_TAU<double> / (numVertices + 1);
			auto vertex = GenoVector2<T>{ 0, -1 }.rotate(angle / 2);
			for (uint32 i = 0; i < numVertices; ++i)
				p[i] = vertex.rotate(angle);
		}
		
		GenoPolygon(uint32 numVertices, GenoVector2<T> * p, bool owner = true) :
			numVertices(numVertices),
			p(p) {}

		GenoPolygon(std::initializer_list<GenoVector2<T>> list) :
			numVertices(list.size),
			p(GenoVector2<T>::newArray(numVertices)) {
			auto init = list.begin();
			for (uint32 i = 0; i < numVertices; ++i)
				v[i] = init[i];
		}

		template <typename T2>
		GenoPolygon(const GenoPolygon<T2> & polygon) :
			numVertices(polygon.numVertices),
			p(GenoVector2<T>::newArray(numVertices)) {
			for (uint32 i = 0; i < N; ++i)
				p[i] = (T) polygon.p[i];
		}

		GenoPolygon(const GenoPolygon<T> & polygon) :
			numVertices(polygon.numVertices),
			p(GenoVector2<T>::newArray(numVertices)) {
			for (uint32 i = 0; i < N; ++i)
				p[i] = polygon.p[i];
		}

		GenoPolygon(GenoPolygon<T> && polygon) :
			owner(polygon.owner),
			numVertices(polygon.numVertices),
			p(polygon.p) {
			polygon.p = 0;
		}

		GenoPolygon<T> & operator=(const GenoPolygon<T> & polygon) {
			clean();
			numVertices = polygon.numVertices;
			p = GenoVector2<T>::newArray(numVertices);
			for (uint32 i = 0; i < numVertices; ++i)
				p[i] = polygon.p[i];
			return *this;
		}

		GenoPolygon<T> & operator=(GenoPolygon<T> && polygon) {
			owner = polygon.owner;
			numVertices = polygon.numVertices;
			p = polygon.numVertices;
			polygon.owner = false;
			return *this;
		}

		uint32 getNumVertices() const {
			return numVertices;
		}

		~GenoPolygon() {
			clean();
		}
};

#define GNARLY_GENOME_POLYGON_FORWARD
#endif // GNARLY_GENOME_POLYGON