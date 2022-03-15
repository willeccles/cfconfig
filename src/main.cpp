#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>

#include "cli.h"
#include "config.h"

int main(int argc, char** argv) {
  // quick mock-up (this should not be permanently here, but this is a rough
  // idea of how this should look)
  auto style = cfconfig::config::GetBaseConfig();

  cfconfig::config::PromptStyle(style);

  return 0;
}
