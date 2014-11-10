#ifndef SYNCHRONIZATIONCALL_HPP
#define SYNCHRONIZATIONCALL_HPP

#include "SynchronizationQueue.hpp"
#include <boost/function.hpp>

class SynchronizationCall : public SynchronizationQueue<boost::function<void ()>>
{
public:
	static SynchronizationCall& instance() {
		static SynchronizationCall object;
		return object;
	}
};

#endif
