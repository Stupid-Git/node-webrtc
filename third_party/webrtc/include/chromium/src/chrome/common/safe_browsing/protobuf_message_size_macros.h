// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_SAFE_BROWSING_PROTOBUF_MESSAGE_SIZE_MACROS_H_
#define CHROME_COMMON_SAFE_BROWSING_PROTOBUF_MESSAGE_SIZE_MACROS_H_

// Null out all the macros that need nulling.
#include "chrome/common/safe_browsing/ipc_protobuf_message_null_macros.h"

// Set up so next include will generate size methods.
#undef IPC_PROTOBUF_MESSAGE_TRAITS_BEGIN
#undef IPC_PROTOBUF_MESSAGE_TRAITS_OPTIONAL_FUNDAMENTAL_MEMBER
#undef IPC_PROTOBUF_MESSAGE_TRAITS_OPTIONAL_COMPLEX_MEMBER
#undef IPC_PROTOBUF_MESSAGE_TRAITS_REPEATED_COMPLEX_MEMBER
#undef IPC_PROTOBUF_MESSAGE_TRAITS_END

#define IPC_PROTOBUF_MESSAGE_TRAITS_BEGIN(message_name) \
  void ParamTraits<message_name>::GetSize(base::PickleSizer* s, \
                                          const param_type& p) {
#define IPC_PROTOBUF_MESSAGE_TRAITS_OPTIONAL_COMPLEX_MEMBER \
  IPC_PROTOBUF_MESSAGE_TRAITS_OPTIONAL_FUNDAMENTAL_MEMBER
#define IPC_PROTOBUF_MESSAGE_TRAITS_OPTIONAL_FUNDAMENTAL_MEMBER(name) \
  s->AddBool();                                                       \
  if (p.has_##name())                                                 \
    GetParamSize(s, p.name());
#define IPC_PROTOBUF_MESSAGE_TRAITS_REPEATED_COMPLEX_MEMBER(name) \
  GetParamSize(s, p.name());
#define IPC_PROTOBUF_MESSAGE_TRAITS_END() }

#endif  // CHROME_COMMON_SAFE_BROWSING_PROTOBUF_MESSAGE_SIZE_MACROS_H_
