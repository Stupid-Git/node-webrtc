// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OFFLINE_PAGES_BACKGROUND_MARK_ATTEMPT_STARTED_TASK_H_
#define COMPONENTS_OFFLINE_PAGES_BACKGROUND_MARK_ATTEMPT_STARTED_TASK_H_

#include <stdint.h>

#include "components/offline_pages/background/request_queue_store.h"
#include "components/offline_pages/background/update_request_task.h"
#include "components/offline_pages/core/task.h"

namespace offline_pages {

class MarkAttemptStartedTask : public UpdateRequestTask {
 public:
  MarkAttemptStartedTask(RequestQueueStore* store,
                         int64_t request_id,
                         const RequestQueueStore::UpdateCallback& callback);
  ~MarkAttemptStartedTask() override;

 protected:
  // UpdateRequestTask implementation:
  void UpdateRequestImpl(std::unique_ptr<UpdateRequestsResult> result) override;
};

}  // namespace offline_pages

#endif  // COMPONENTS_OFFLINE_PAGES_BACKGROUND_MARK_ATTEMPT_STARTED_TASK_H_
