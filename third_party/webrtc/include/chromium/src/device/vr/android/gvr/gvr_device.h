// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_VR_ANDROID_GVR_DEVICE_H
#define DEVICE_VR_ANDROID_GVR_DEVICE_H

#include "base/macros.h"
#include "device/vr/vr_device.h"

namespace gvr {
class GvrApi;
}  // namespace gvr

namespace device {

class GvrDeviceProvider;
class GvrDelegate;

class GvrDevice : public VRDevice {
 public:
  GvrDevice(GvrDeviceProvider* provider, GvrDelegate* delegate);
  ~GvrDevice() override;

  // VRDevice
  VRDisplayPtr GetVRDevice() override;
  VRPosePtr GetPose() override;
  void ResetPose() override;

  bool RequestPresent(bool secure_origin) override;
  void ExitPresent() override;

  void SubmitFrame(VRPosePtr pose) override;
  void UpdateLayerBounds(VRLayerBoundsPtr leftBounds,
                         VRLayerBoundsPtr rightBounds) override;

  void SetDelegate(GvrDelegate* delegate);

 private:
  gvr::GvrApi* GetGvrApi();

  GvrDelegate* delegate_;
  GvrDeviceProvider* gvr_provider_;
  bool secure_origin_;
  uint32_t pose_index_ = 0;

  DISALLOW_COPY_AND_ASSIGN(GvrDevice);
};

}  // namespace device

#endif  // DEVICE_VR_ANDROID_GVR_DEVICE_H
