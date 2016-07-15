#include "SynchronizationCall.hpp"

SynchronizationCall &SynchronizationCall::sharedSynronizationCall() {
    static SynchronizationCall singleTon;
    return singleTon;
}

void SynchronizationCall::operator +=(SynchronizationCall::Callback cb) {
    std::lock_guard<std::mutex> lg(m_mutex);
    m_queue.push(cb);
}

void SynchronizationCall::executeAllAndClear() {
    std::lock_guard<std::mutex> lg(m_mutex);
    while(!m_queue.empty()) {
        m_queue.front()();
        m_queue.pop();
    }
}

SynchronizationCall::SynchronizationCall() {}
