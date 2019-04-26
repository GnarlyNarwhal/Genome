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

#ifndef GNARLY_GENOME_QUEUE
#define GNARLY_GENOME_QUEUE

#include <utility>
#include <initializer_list>

#include "../GenoInts.h"
#include "../exceptions/GenoMaxCapacityException.h"

template <typename T>
class GenoQueue {
	private:
		uint32 capacity;
		uint32 read;
		uint32 write;
		uint32 length;
		T * array;

		void clean() noexcept {
			delete [] array;
		}

		void reallocate(uint32 newCapacity) {
			auto newArray = new T[newCapacity];
			for (uint32 i = 0, j = read - 1; i < length; ++i)
				newArray[i] = std::move(array[(++j) %= capacity]);
			clean();
			capacity = newCapacity;
			read = 0;
			write = length;
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
		GenoQueue(uint32 capacity = 16) :
			capacity(capacity),
			array(new T[capacity]) {}

		GenoQueue(std::initializer_list<T> list) :
			capacity(list.size() * 2),
			write(list.size()),
			length(list.size()),
			array(new T[capacity]) {
			auto init = list.begin();
			for (uint32 i = 0; i < list.size(); ++i)
				array[i] = init[i];
		}

		GenoQueue(const GenoQueue<T> & queue) :
			capacity(queue.capacity),
			read(queue.read),
			write(queue.write),
			length(queue.length),
			array(new T[capacity]) {
			for (uint32 i = read; i != write; (++i) %= capacity)
				array[i] = queue.array[i];
		}

		GenoQueue(GenoQueue<T> && queue) noexcept :
			capacity(queue.capacity),
			read(queue.read),
			write(queue.write),
			length(queue.length),
			array(queue.array) {
			queue.array = 0;
		}

		GenoQueue<T> & operator=(const GenoQueue<T> & queue) {
			clean();
			capacity = queue.capacity;
			length   = queue.length;
			array = new T[capacity];
			for (uint32 i = read; i != write; (++i) %= capacity)
				array[i] = queue.array[i];
			return *this;
		}
		
		GenoQueue<T> & operator=(GenoQueue<T> && queue) noexcept {
			clean();
			capacity = queue.capacity;
			read     = queue.read;
			write    = queue.write;
			length   = queue.length;
			array    = queue.array;
			queue.array = 0;
			return *this;
		}

		void enqueue(const T & element) {
			checkCapacity();
			array[write] = element;
			(++write) %= capacity;
			++length;
		}

		T dequeue() {
			uint32 index = read;
			(++read) %= capacity;
			--length;
			return std::move(array[index]);
		}

		void pack() {
			reallocate(length);
		}

		~GenoQueue() {
			clean();
		}
};

#define GNARLY_GENOME_QUEUE_FORWARD
#endif // GNARLY_GENOME_QUEUE