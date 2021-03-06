// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_SYSTEM_REBOOT_REBOOT_UTIL_H_
#define CHROMECAST_SYSTEM_REBOOT_REBOOT_UTIL_H_

#include <string>
#include <vector>

#include "chromecast/public/reboot_shlib.h"

namespace chromecast {

// A wrapper util for the RebootShlib interface. This acts as a translation
// layer between cast_shell call sites (such as the setup API, process_manager,
// and crash_uploader) and the actual RebootShlib API.
// The RebootShlib interface should never need to be used directly; instead
// prefer to use the RebootUtil interface.
class RebootUtil {
 public:

  static void Initialize(const std::vector<std::string>& argv);
  static void Finalize();

  // Indicates if any RebootSources are supported for rebooting.
  static bool IsRebootSupported();

  // The RebootShlib::RebootSource uses weakly typed enums, so this
  // can be used to validate a RebootSource value is actually valid.
  static bool IsValidRebootSource(RebootShlib::RebootSource reboot_source);

  // Before calling RebootNow, the caller must check that reboot is supported
  // for the RebootSource being attempted.
  static bool IsRebootSourceSupported(RebootShlib::RebootSource reboot_source);
  static bool RebootNow(RebootShlib::RebootSource reboot_source);

  // Before calling SetFdrForNextReboot, the caller must check that fdr
  // for next reboot is supported.
  static bool IsFdrForNextRebootSupported();
  static void SetFdrForNextReboot();

  // Before calling SetOtaForNextReboot, the caller must check that ota
  // for next reboot is supported.
  static bool IsOtaForNextRebootSupported();
  static void SetOtaForNextReboot();

  // These are used for logging/metrics purposes. In general, setting the last
  // reboot type is handled automatically by RebootUtil, so it should not
  // be necessary to set explicitly.
  static RebootShlib::RebootSource GetLastRebootSource();
  // Returns true if successful.
  static bool SetLastRebootSource(RebootShlib::RebootSource reboot_source);
};

}  // namespace chromecast

#endif  // CHROMECAST_SYSTEM_REBOOT_REBOOT_UTIL_H_
