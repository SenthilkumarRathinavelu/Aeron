/*
 * Copyright 2014 - 2015 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDED_AERON_CONCURRENT_LOGBUFFER_BUFFER_CLAIM__
#define INCLUDED_AERON_CONCURRENT_LOGBUFFER_BUFFER_CLAIM__

#include <util/Index.h>
#include <concurrent/AtomicBuffer.h>
#include <concurrent/logbuffer/Header.h>

namespace aeron { namespace concurrent { namespace logbuffer {

class BufferClaim
{
public:
    typedef BufferClaim this_t;

    inline BufferClaim() :
        m_buffer(nullptr, 0)
    {
    }

    inline void wrap(AtomicBuffer& buffer, util::index_t offset, util::index_t length)
    {
        m_buffer.wrap(buffer.getBuffer() + offset, length);
    }

    inline AtomicBuffer& buffer()
    {
        return m_buffer;
    }

    inline util::index_t offset() const
    {
        return DataHeader::LENGTH;
    }

    inline util::index_t length() const
    {
        return m_buffer.getCapacity() - DataHeader::LENGTH;
    }

    inline void commit()
    {
        m_buffer.putInt32Ordered(0, m_buffer.getCapacity());
    }

private:
    AtomicBuffer m_buffer;
};

}}}

#endif
