#ifndef CFCONFIG_SRC_CONFIG_H
#define CFCONFIG_SRC_CONFIG_H

#include <clang/Format/Format.h>
#include <string_view>

namespace cfconfig {
namespace config {

clang::format::FormatStyle GetBaseConfig();

void PromptStyle(clang::format::FormatStyle& style);

}  // namespace config
}  // namespace cfconfig

#endif  // CFCONFIG_SRC_CONFIG_H
