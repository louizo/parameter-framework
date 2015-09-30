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

#include "XmlSink.h"
#include "XmlSource.h"

class CConfigurableElement;
class CParameterBlackboard;
class CSyncerSet;

/**
 * CConfigurableElementAccessor class is used to access the settings of a configurable
 * element with an XML string interface.
 *
 * Can be used as:
 *    - IXmlSource for CXmlMemoryDocSource to for settings reading in XML
 *    - IXmlSink for CXmlMemoryDocSink to for settings reading in XML
 *
 * @see CXmlMemoryDocSource
 * @see CXmlMemoryDocSink
 *
 */
class CConfigurableElementAccessor : public IXmlSink, public IXmlSource
{
public:
    CConfigurableElementAccessor(const CConfigurableElement* pConfigurableElement,
        CParameterBlackboard* pParameterBlackboard, CSyncerSet* pStagingSyncerSet,
        bool bValueSpaceIsRaw, bool bOutputRawFormatIsHex = false);

    // From IXmlSink
    virtual bool fromXml(const CXmlElement& xmlElement, CXmlSerializingContext& serializingContext);

    // From IXmlSource
    virtual void toXml(CXmlElement& xmlElement, CXmlSerializingContext& serializingContext) const;
private:
    /**
     * Accessed configurable element
     */
    const CConfigurableElement* _pConfigurableElement;
    /**
     * Accessed blackboard
     */
    CParameterBlackboard* _pParameterBlackboard;
    /**
     * Staging syncer set.
     * When present (not NULL), used to stage the syncers for coalesced synchronization
     * after writing settings in main blackboard
     */
    CSyncerSet* _pStagingSyncerSet;
    /**
     * Value space used for conversions
     */
    bool _bValueSpaceIsRaw;
    /**
    * Output Raw Format used for conversions
    */
    bool _bOutputRawFormatIsHex;
};

