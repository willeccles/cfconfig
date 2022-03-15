#ifndef CFCONFIG_SRC_UTIL_H
#define CFCONFIG_SRC_UTIL_H

#include <clang/Basic/Version.h>

#include <string_view>

namespace cfconfig {
namespace util {

/**
 * @brief Check that the clang version built against is at least major.minor.
 *
 * @param major major version
 * @param minor minor version
 */
#define CF_VER_MIN(major,minor) (((CLANG_VERSION_MAJOR) > (major)) ||     \
                                 (((CLANG_VERSION_MAJOR) == (major)) &&   \
                                  ((CLANG_VERSION_MINOR) >= (minor))))

/**
 * @brief Trim leading and trailing spaces from a string and return it.
 *
 * @param str the string view to trim
 *
 * @return The trimmed string view.
 */
std::string_view Trim(std::string_view str);

}  // namespace util
}  // namespace cfconfig

#endif  // CFCONFIG_SRC_UTIL_H
