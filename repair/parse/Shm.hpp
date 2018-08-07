/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef Shm_hpp
#define Shm_hpp

#include <WCDB/FileHandle.hpp>
#include <WCDB/Initializeable.hpp>
#include <WCDB/WalRelated.hpp>

namespace WCDB {

namespace Repair {

class Shm : public WalRelated, public Initializeable {
public:
    Shm(Wal *wal);

    const std::string &getPath() const;

protected:
    bool doInitialize() override;
    void markAsCorrupted(const std::string &message);
    FileHandle m_fileHandle;

public:
    uint32_t getMaxFrame() const;

protected:
    struct Header {
        Header();
        uint32_t version;
        uint32_t ___unused;
        uint32_t ___change;
        uint8_t ___isInit;
        uint8_t ___bigEndChecksum;
        uint16_t ___pageSize;
        uint32_t maxFrame;
        uint32_t ___page;
        uint32_t ___frameChecksum[2];
        uint32_t ___salt[2];
        uint32_t ___checksum[2];
    };
    typedef struct Header Header;

    Header m_header;
};

} // namespace Repair

} // namespace WCDB

#endif /* Shm_hpp */
