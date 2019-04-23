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

#include <mutex>
#include <memory>

#include "GenoThreadPool.h"

void GenoThreadPool::threadLoop(uint32 threadId, GenoThreadPool * pool) {
	while (pool->isActive.load()) {
		GenoThreadPoolJobPackage * job = pool->requestJob(threadId);
		if (job != 0) {
			job->job(job->data);
			pool->activeThreads[threadId].store(false);
		}
		else
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
	}
}

GenoThreadPool::GenoThreadPoolJobPackage * GenoThreadPool::requestJob(uint32 threadId) {
	std::lock_guard<std::mutex> lock(jobMutex);
	if (jobCount > 0) {
		activeThreads[threadId].store(true);
		--jobCount;
		return &jobs[jobCount];
	}
	else
		return 0;
}

uint32 GenoThreadPool::physicalThreadCount() {
	return std::thread::hardware_concurrency();
}

GenoThreadPool::GenoThreadPool(uint32 numThreads, uint32 initialQueueCapacity) :
	isActive(true),
	numThreads(numThreads),
	threads(new std::thread[numThreads]),
	activeThreads(new std::atomic_bool[numThreads]),
	jobCount(0),
	jobCapacity(initialQueueCapacity == 0 ? 16 : initialQueueCapacity),
	jobs(new GenoThreadPoolJobPackage[jobCapacity]) {
	for (uint32 i = 0; i < numThreads; ++i) {
		threads[i] = std::thread(threadLoop, i, this);
		activeThreads[i].store(false);
	}
}

void GenoThreadPool::submitJob(GenoThreadPoolJob job, GenoThreadPoolJobData data) {
	std::lock_guard<std::mutex> lock(jobMutex);
	if (jobCount >= jobCapacity) {
		jobCapacity *= 2;
		GenoThreadPoolJobPackage * newJobs = new GenoThreadPoolJobPackage[jobCapacity];
		memcpy(newJobs, jobs, sizeof(GenoThreadPoolJobPackage) * jobCount);
		delete [] jobs;
		jobs = newJobs;
	}
	jobs[jobCount] = { job, data };
	++jobCount;
}

void GenoThreadPool::wait() {
	while (jobCount > 0)
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
	for (uint32 i = 0; i < numThreads; ++i) {
		if (activeThreads[i].load()) {
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
			i = 0;
		}
	}
}

GenoThreadPool::~GenoThreadPool() {
	isActive.store(false);
	for (uint32 i = 0; i < numThreads; ++i)
		threads[i].join();
	delete [] threads;
	delete [] activeThreads;
	delete [] jobs;
}