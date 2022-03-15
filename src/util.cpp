#include "util.h"

#include <algorithm>
#include <string_view>

namespace cfconfig {
namespace util {

std::string_view Trim(std::string_view str) {
  str.remove_prefix(std::min(str.find_first_not_of(" \t\n\r"), str.size()));
  str.remove_suffix(std::min(str.size() - (str.find_last_not_of(" \t\n\r") + 1),
                             str.size()));
  return str;
}

}  // namespace util
}  // namespace cfconfig
