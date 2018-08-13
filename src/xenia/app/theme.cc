#include "theme.h"

ThemeRes Theme::LoadTheme() {
  if (directory_.isNull() || directory_.isEmpty()) {
    return THEME_NOT_FOUND;
  }

  if (!config_.LoadFromFile(directory_ + "/theme.json")) {
    return THEME_MISCONFIGURED;  // also happens if json file is missing
  }
  return THEME_LOAD_OK;
}
