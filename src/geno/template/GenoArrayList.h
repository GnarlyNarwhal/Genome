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

#ifndef GNARLY_GENOME_ARRAY_LIST
#define GNARLY_GENOME_ARRAY_LIST

#include <utility>
#include <initializer_list>

#include "../GenoInts.h"
#include "../exceptions/GenoMaxCapacityException.h"

template <typename T>
class GenoArrayList {
	private:
		uint32 capacity;
		uint32 length;
		T * array;

		void clean() noexcept {
			delete [] array;
		}

		void reallocate(uint32 newCapacity) {
			capacity = newCapacity;
			auto newArray = new T[capacity];
			for (uint32 i = 0; i < length; ++i)
				newArray[i] = std::move(array[i]);
			clean();
			array = newArray;
		}

		void checkCapacity() {
			if (length == capacity) {
				if (capacity == 0xFFFFFFFF)
					throw GenoMaxCapacityException();
				else if (capacity > 0x7FFFFFFF)
					reallocate(0xFFFFFFFF);
				else
					reallocate(capacity << 1);
			}
		}

	public:
		GenoArrayList(uint32 capacity = 16) :
			capacity(capacity),
			array(new T[capacity]) {}

		GenoArrayList(std::initializer_list<T> list) :
			capacity(list.size() * 2),
			length(list.size()),
			array(new T[capacity]) {
			auto init = list.begin();
			for (uint32 i = 0; i < list.size(); ++i)
				array[i] = init[i];
		}

		GenoArrayList(const GenoArrayList<T> & list) :
			capacity(list.capacity),
			length(list.length),
			array(new T[capacity]) {
			for (uint32 i = 0; i < list.length; ++i)
				array[i] = list.array[i];
		}

		GenoArrayList(GenoArrayList<T> && list) noexcept :
			capacity(list.capacity),
			length(list.length),
			array(list.array) {
			list.array = 0;
		}

		GenoArrayList<T> & operator=(const GenoArrayList<T> & list) {
			clean();
			capacity = list.capacity;
			length   = list.length;
			array = new T[capacity];
			for (uint32 i = 0; i < list.length; ++i)
				array[i] = list.array[i];
			return *this;
		}
		
		GenoArrayList<T> & operator=(GenoArrayList<T> && list) noexcept {
			clean();
			capacity = list.capacity;
			length   = list.length;
			array    = list.array;
			list.array = 0;
			return *this;
		}

		T & operator[](uint32 index) noexcept {
			return array[index];
		}
		
		const T & operator[](uint32 index) const noexcept {
			return array[index];
		}

		uint32 getLength() const noexcept {
			return length;
		}

		void add(const T & element) {
			checkCapacity();
			array[length] = element;
			++length;
		}

		void add(uint32 index, const T & element) {
			checkCapacity();
			for (uint32 i = length; i > index; --i)
				array[i] = std::move(array[i - 1]);
			array[index] = element;
			++length;
		}

		void remove(uint32 index) {
			--length;
			for (uint32 i = index; i < length; ++i)
				array[i] = std::move(array[i + 1]);
		}

		void remove(uint32 begin, uint32 end) {
			auto distance = end - begin;
			length -= end;
			for (uint32 i = begin; i < length; ++i)
				array[i] = std::move(array[i + distance]);
		}

		void clear() noexcept {
			length = 0;
		}

		void pack() {
			reallocate(length);
		}

		~GenoArrayList() {
			clean();
		}
};

#define GNARLY_GENOME_ARRAY_LIST_FORWARD
#endif // GNARLY_GENOME_ARRAY_LIST