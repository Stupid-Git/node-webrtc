// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ARC_CLIPBOARD_ARC_CLIPBOARD_BRIDGE_H_
#define COMPONENTS_ARC_CLIPBOARD_ARC_CLIPBOARD_BRIDGE_H_

#include "base/macros.h"
#include "components/arc/arc_service.h"
#include "components/arc/common/clipboard.mojom.h"
#include "components/arc/instance_holder.h"
#include "mojo/public/cpp/bindings/binding.h"
#include "mojo/public/cpp/bindings/string.h"

namespace arc {

class ArcClipboardBridge
    : public ArcService,
      public InstanceHolder<mojom::ClipboardInstance>::Observer,
      public mojom::ClipboardHost {
 public:
  explicit ArcClipboardBridge(ArcBridgeService* bridge_service);
  ~ArcClipboardBridge() override;

  // InstanceHolder<mojom::ClipboardInstance>::Observer overrides.
  void OnInstanceReady() override;

  // mojom::ClipboardHost overrides.
  void SetTextContent(const mojo::String& text) override;
  void GetTextContent() override;

 private:
  bool CalledOnValidThread();

  mojo::Binding<mojom::ClipboardHost> binding_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(ArcClipboardBridge);
};

}  // namespace arc

#endif  // COMPONENTS_ARC_CLIPBOARD_ARC_CLIPBOARD_BRIDGE_H_
