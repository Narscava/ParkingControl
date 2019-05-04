#pragma once
#ifndef RING_BUFFER
#define RING_BUFFER
#include <boost/atomic.hpp>
#include "GpsInfo.h"
template<typename T, size_t Size>
class RingBuffer {
public:
	RingBuffer() : head_(0), tail_(0) {}
	bool push(const T & value)
	{
		size_t head = head_.load(boost::memory_order_relaxed);
		size_t next_head = next(head);
		if (next_head == tail_.load(boost::memory_order_acquire))
			return false;
		ring_[head] = value;
		head_.store(next_head, boost::memory_order_release);
		return true;
	}
	bool pop(T & value)
	{
		size_t tail = tail_.load(boost::memory_order_relaxed);
		if (tail == head_.load(boost::memory_order_acquire))
			return false;
		value = ring_[tail];
		tail_.store(next(tail), boost::memory_order_release);
		return true;
	}
private:
	size_t next(size_t current)
	{
		return (current + 1) % Size;
	}
	T ring_[Size];
	boost::atomic<size_t> head_, tail_;
};
typedef RingBuffer<char,20480> CharRingBuffer;
typedef RingBuffer<GpsInfo,2048> GpsRingBuffer;
#endif
