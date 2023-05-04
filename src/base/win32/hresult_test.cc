// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "base/win32/hresult.h"

#include <utility>

#include "testing/gmock.h"
#include "testing/gunit.h"

namespace mozc::win32 {
namespace {

TEST(HResultTest, HResult) {
  constexpr HResult hr(E_FAIL);
  EXPECT_EQ(hr, E_FAIL);
  EXPECT_EQ(hr.hr(), E_FAIL);
  EXPECT_FALSE(hr.ok());

  HResult hr1(S_OK), hr2(E_UNEXPECTED);
  EXPECT_EQ(hr1.hr(), S_OK);
  EXPECT_TRUE(hr1.ok());
  EXPECT_EQ(hr2.hr(), E_UNEXPECTED);
  EXPECT_FALSE(hr2.ok());

  std::swap(hr1, hr2);
  EXPECT_EQ(hr1.hr(), E_UNEXPECTED);
  EXPECT_EQ(hr2.hr(), S_OK);
}

TEST(HResultTest, ReturnIfErrorHResult) {
  auto f = []() -> HRESULT {
    RETURN_IF_FAILED_HRESULT(S_OK);
    RETURN_IF_FAILED_HRESULT(E_FAIL);
    return S_FALSE;
  };
  EXPECT_EQ(f(), E_FAIL);
}

}  // namespace
}  // namespace mozc::win32
