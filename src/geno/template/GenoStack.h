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

#ifndef GNARLY_GENOME_STACK
#define GNARLY_GENOME_STACK

#include <utility>
#include <initializer_list>

#include "../GenoInts.h"
#include "../exceptions/GenoMaxCapacityException.h"

template <typename T>
class GenoStack {
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
		GenoStack(uint32 capacity = 16) :
			capacity(capacity),
			array(new T[capacity]) {}

		GenoStack(std::initializer_list<T> list) :
			capacity(list.size() * 2),
			length(list.size()),
			array(new T[capacity]) {
			auto init = list.begin();
			for (uint32 i = 0; i < list.size(); ++i)
				array[i] = init[i];
		}

		GenoStack(const GenoStack<T> & stack) :
			capacity(stack.capacity),
			length(stack.length),
			array(new T[capacity]) {
			for (uint32 i = 0; i < stack.length; ++i)
				array[i] = stack.array[i];
		}

		GenoStack(GenoStack<T> && stack) noexcept :
			capacity(stack.capacity),
			length(stack.length),
			array(stack.array) {
			stack.array = 0;
		}

		GenoStack<T> & operator=(const GenoStack<T> & stack) {
			clean();
			capacity = stack.capacity;
			length   = stack.length;
			array = new T[capacity];
			for (uint32 i = 0; i < stack.length; ++i)
				array[i] = stack.array[i];
			return *this;
		}
		
		GenoStack<T> & operator=(GenoArrayList<T> && stack) noexcept {
			clean();
			capacity = stack.capacity;
			length   = stack.length;
			array    = stack.array;
			stack.array = 0;
			return *this;
		}

		void push(const T & element) {
			checkCapacity();
			array[length] = element;
			++length;
		}

		T pop() {
			return std::move(array[--length]);
		}

		~GenoStack() {
			clean();
		}
};

#define GNARLY_GENOME_STACK_FORWARD
#endif // GNARLY_GENOME_STACK