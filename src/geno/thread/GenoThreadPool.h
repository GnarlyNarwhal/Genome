/*******************************************************************************
 *
 * Copyright (c) 2018 Gnarly Narwhal
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

#ifndef GNARLY_GENOME_THREAD_POOL
#define GNARLY_GENOME_THREAD_POOL

#include <mutex>
#include <thread>
#include <atomic>

#include "../GenoInts.h"

typedef void * GenoThreadPoolJobData;
typedef void (*GenoThreadPoolJob)(GenoThreadPoolJobData data);

/**
 * A thread pool
**/
class GenoThreadPool {
	private:
		struct GenoThreadPoolJobPackage {
			GenoThreadPoolJob job;
			GenoThreadPoolJobData data;
		};

		std::atomic_bool isActive;
		uint32 numThreads;
		std::mutex jobMutex;
		std::thread * threads;
		std::atomic_bool * activeThreads;

		uint32 jobCount;
		uint32 jobCapacity;
		GenoThreadPoolJobPackage * jobs;

		static void threadLoop(uint32 threadId, GenoThreadPool * pool);

		GenoThreadPoolJobPackage * requestJob(uint32 threadId);
	public:
		/**
		 * Returns the number of physical threads the system has if possible
		**/
		static uint32 physicalThreadCount();

		/**
		 * Creates a thread pool
		 *
		 * @param numThreads - The number of threads in the pool, defaults to physicalThreadCount()
		 * @param initialQueueCapacity - The initial capacity of the job queue. Queue will grow to fit but resizing is expensive
		**/
		GenoThreadPool(uint32 numThreads = physicalThreadCount(), uint32 initialQueueCapacity = 16);

		/**
		 * Submits a job to the thread pool
		 *
		 * @param job - The job to be queued
		 * @param data - The data for the queued job
		**/
		void submitJob(GenoThreadPoolJob job, GenoThreadPoolJobData data = 0);

		/**
		 * Waits until all submitted jobs have finished
		**/
		void wait();

		/**
		 * Destroys the thread pool
		 *
		 * Waits until all jobs have been completed before exiting
		**/
		~GenoThreadPool();
};

#define GNARLY_GENOME_THREAD_POOL_FORWARD
#endif // GNARLY_GENOME_THREAD_POOL