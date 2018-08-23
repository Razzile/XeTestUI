/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include "theme.h"

namespace xe {
namespace app {

ThemeRes Theme::LoadTheme() {
  if (directory_.isNull() || directory_.isEmpty()) {
    return THEME_NOT_FOUND;
  }

  if (!config_.LoadFromFile(directory_ + "/theme.json")) {
    return THEME_MISCONFIGURED;  // also happens if json file is missing
  }
  return THEME_LOAD_OK;
}

}  // namespace app
}  // namespace xe
