#pragma once
#include "Constructor.hpp"
#include <queue>
#include <mutex>

class SynchronizationCall {
    typedef std::function<void()> Callback;
    typedef std::queue<Callback> CallbackQueue;

public:
    DISABLE_CPY_MOV_CTOR(SynchronizationCall)

    static SynchronizationCall& sharedSynronizationCall();

    void operator += (Callback cb);

    void executeAllAndClear();

private:
    CallbackQueue m_queue;
    std::mutex m_mutex;

    explicit SynchronizationCall();
};
