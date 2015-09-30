/*
 * Copyright (c) 2011-2014, Intel Corporation
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
#include "ConfigurableElementAccessor.h"
#include "ConfigurableElement.h"
#include "ConfigurationAccessContext.h"
#include "Subsystem.h"

CConfigurableElementAccessor::CConfigurableElementAccessor(const CConfigurableElement* pConfigurableElement,
    CParameterBlackboard* pParameterBlackboard, CSyncerSet* pStagingSyncerSet,
    bool bValueSpaceIsRaw, bool bOutputRawFormatIsHex)
    : _pConfigurableElement(pConfigurableElement), _pParameterBlackboard(pParameterBlackboard),
    _pStagingSyncerSet(pStagingSyncerSet), _bValueSpaceIsRaw(bValueSpaceIsRaw),
    _bOutputRawFormatIsHex(bOutputRawFormatIsHex)
{
}

bool CConfigurableElementAccessor::fromXml(const CXmlElement& xmlElement, CXmlSerializingContext& serializingContext)
{

    return true;
}

void CConfigurableElementAccessor::toXml(CXmlElement& xmlElement, CXmlSerializingContext& serializingContext) const
{
    std::string strError;

    // Create configuration access context
    CConfigurationAccessContext configurationAccessContext(strError, true);

    // Deal with deferred syncrhonization
    configurationAccessContext.setStagingSyncerSet(_pStagingSyncerSet);

    // Provide current value space
    configurationAccessContext.setValueSpaceRaw(_bValueSpaceIsRaw);

    // Provide current output raw format
    configurationAccessContext.setOutputRawFormat(_bOutputRawFormatIsHex);

    // Deal with Endianness
    const CSubsystem* pSubsystem = _pConfigurableElement->getBelongingSubsystem();

    if (pSubsystem && pSubsystem != _pConfigurableElement) {

        // Element is a descendant of subsystem

        // Retrieve subsystem Endianness
        configurationAccessContext.setBigEndianSubsystem(pSubsystem->isBigEndian());
    }

    // Assign blackboard to configuration context
    configurationAccessContext.setParameterBlackboard(_pParameterBlackboard);

    // Assign base offset to configuration context
    // Put 0 for main blackboard access
    configurationAccessContext.setBaseOffset(0);

    // Serialize values as XML (element contents)
    _pConfigurableElement->serializeXmlSettings(const_cast<CXmlElement&>(xmlElement), configurationAccessContext);
}
