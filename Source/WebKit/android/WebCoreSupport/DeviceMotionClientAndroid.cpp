/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "DeviceMotionClientAndroid.h"

#include "WebViewCore.h"

using namespace WebCore;

namespace android {

DeviceMotionClientAndroid::DeviceMotionClientAndroid()
    : m_client(0)
{
}

void DeviceMotionClientAndroid::setWebViewCore(WebViewCore* webViewCore)
{
    m_webViewCore = webViewCore;
    ASSERT(m_webViewCore);
}

void DeviceMotionClientAndroid::setController(DeviceMotionController* controller)
{
    // This will be called by the Page constructor before the WebViewCore
    // has been configured regarding the mock. We cache the controller for
    // later use.
    m_controller = controller;
    ASSERT(m_controller);
}

void DeviceMotionClientAndroid::startUpdating()
{
    client()->startUpdating();
}

void DeviceMotionClientAndroid::stopUpdating()
{
    client()->stopUpdating();
}

DeviceMotionData* DeviceMotionClientAndroid::currentDeviceMotion() const
{
    return client()->currentDeviceMotion();
}

void DeviceMotionClientAndroid::deviceMotionControllerDestroyed()
{
      delete this;
}

DeviceMotionClient* DeviceMotionClientAndroid::client() const
{
    if (!m_client) {
        m_client = m_webViewCore->deviceMotionAndOrientationManager()->motionClient();
        m_client->setController(m_controller);
    }
    return m_client;
}

} // namespace android
