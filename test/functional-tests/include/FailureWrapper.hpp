/*
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <utility>
#include "Exception.hpp"

namespace parameterFramework
{
template <class T>
class FailureWrapper
{
public:
    FailureWrapper(T *wrapped) : mWrapped(*wrapped) {}

protected:
    /** Wrap a const method that may fail to throw an Exception instead of
     * retuning a boolean.
     *
     * @param[in] method (const) that return a boolean to indicate failure.
     * @param[in] args parameters to call method call with. */
    template <class... MArgs, class... Args>
    void mayFailCall(bool (T::*method)(MArgs...) const, Args&&... args) const {
        std::string error;
        if (not (mWrapped.*method)(std::forward<Args>(args)..., error)) {
            throw Exception(std::move(error));
        }
    }

    /** Wrap a method that may fail to throw an Exception instead of retuning a
     * boolean.
     *
     * @param[in] method that return a boolean to indicate failure.
     * @param[in] args parameters to call method call with. */
    template <class... MArgs, class... Args>
    void mayFailCall(bool (T::*method)(MArgs...), Args&&... args) {
        std::string error;
        if (not (mWrapped.*method)(std::forward<Args>(args)..., error)) {
            throw Exception(std::move(error));
        }
    }

    /** Wrap a method that may indicate failure by returning a null pointer to
     * throw an Exception instead of retuning a null pointer.
     *
     * @param[in] method that return a boolean to indicate failure.
     * @param[in] args parameters to call method call with. */
    template <class ReturnType, class... MArgs, class... Args>
    ReturnType *mayFailCall(ReturnType *(T::*method)(MArgs...), Args&&... args) {
        std::string error;
        ReturnType *ret = (mWrapped.*method)(std::forward<Args>(args)..., error);
        if (ret == NULL) {
            throw Exception(std::move(error));
        }
        return ret;
    }

private:
    T& mWrapped;
};
} // parameterFramework
