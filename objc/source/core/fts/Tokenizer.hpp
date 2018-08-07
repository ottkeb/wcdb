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

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <WCDB/Abstract.h>
#include <WCDB/Tokenize.hpp>
#include <cstddef>
#include <vector>

#pragma GCC visibility push(hidden)

namespace WCDB {

namespace FTS {

#pragma mark - Cursor
class CursorInfo : public CursorInfoBase {
public:
    enum class TokenType : unsigned int {
        None = 0,
        BasicMultilingualPlaneLetter = 0x00000001,
        BasicMultilingualPlaneDigit = 0x00000002,
        BasicMultilingualPlaneSymbol = 0x00000003,
        BasicMultilingualPlaneOther = 0x0000FFFF,
        AuxiliaryPlaneOther = 0xFFFFFFFF,
    };

    CursorInfo(const char *input, int inputLength, TokenizerInfoBase *tokenizerInfo);

    int step(const char **ppToken, int *pnBytes, int *piStartOffset, int *piEndOffset, int *piPosition) override;

protected:
    const char *m_input;
    int m_inputLength;

    int m_position;
    int m_startOffset;
    int m_endOffset;

    int m_cursor;
    TokenType m_cursorTokenType;
    int m_cursorTokenLength;
    int cursorStep();
    int cursorSetup();

    //You must figure out the unicode character set of [symbol] on current platform or implement it refer to http://www.fileformat.info/info/unicode/category/index.htm
    typedef unsigned short UnicodeChar;
    virtual int isSymbol(UnicodeChar theChar, bool *result) = 0;

    int lemmatization(const char *input, int inputLength);
    std::vector<char> m_lemmaBuffer;
    int m_lemmaBufferLength; //>0 lemma is not empty

    std::vector<int> m_subTokensLengthArray;
    int m_subTokensCursor;
    bool m_subTokensDoubleChar;
    void subTokensStep();

    std::vector<char> m_buffer;
    int m_bufferLength;
};

} //namespace FTS

} //namespace WCDB

#pragma GCC visibility pop

#endif /* Tokenizer_hpp */
