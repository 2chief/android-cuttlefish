/*
 * Copyright (C) 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "host/commands/cvd/instances/group_selector.h"

#include <android-base/parseint.h>

#include "host/commands/cvd/cli/selector/device_selector_utils.h"

namespace cuttlefish {

Result<LocalInstanceGroup> GroupSelector::FindGroup(
    const InstanceDatabase& instance_database) {
  if (filter_.Empty()) {
    auto default_group = CF_EXPECT(FindDefaultGroup(instance_database));
    return default_group;
  }
  auto groups = CF_EXPECT(instance_database.FindGroups(filter_));
  CF_EXPECT(groups.size() == 1, "groups.size() = " << groups.size());
  return *(groups.cbegin());
}

Result<LocalInstanceGroup> GroupSelector::FindDefaultGroup(
    const InstanceDatabase& instance_database) {
  auto group = CF_EXPECT(selector::GetDefaultGroup(instance_database));
  return group;
}

}  // namespace cuttlefish