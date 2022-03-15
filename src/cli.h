#ifndef CFCONFIG_SRC_CLI_H
#define CFCONFIG_SRC_CLI_H

#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace cfconfig {
namespace cli {

/**
 * @brief Prompt the user for a yes or no answer.
 *
 * @param[in] prompt the prompt to show the user
 * @param[in] def the default value (used when no input is given)
 *
 * @return True if the user answered yes, false if no.
 */
bool Prompt(const std::string_view prompt, bool def);

/**
 * @brief Prompt the user for an integer value within a range.
 *
 * @param[in] prompt the prompt to show the user
 * @param[in] min the minimum allowable value
 * @param[in] max the maximum allowable value
 * @param[in] def the default value
 *
 * @return The user's input.
 */
int Prompt(const std::string_view prompt, int min, int max, int def);

/**
 * @brief Prompt the user for any integer value.
 *
 * This is the same as `Prompt(prompt, INT_MIN, INT_MAX, def)`.
 *
 * @param[in] prompt the prompt to display to the user
 * @param[in] def the default value
 *
 * @return The user's input.
 */
int Prompt(const std::string_view prompt, int def);

template <class T>
struct PromptOpt {
  const std::string_view name;
  const T& value;
};

template <class T>
using PromptOptList = std::vector<PromptOpt<T>>;

template <class T>
inline static const T& Prompt(const std::string_view prompt,
                              const std::string_view desc,
                              const PromptOptList<T>& options, int def) {
  if (options.empty()) {
    throw std::logic_error("empty option list");
  }

  if ((std::size_t)def >= options.size() || def < 0) {
    throw std::out_of_range("default index out of range");
  }

  std::cout << desc << '\n';

  for (int i = 0; const auto& opt : options) {
    std::cout << i++ << ") " << opt.name << '\n';
  }

  int choice = Prompt(prompt, 0, (int)options.size() - 1, def);

  return options[choice].value;
}

}  // namespace cli
}  // namespace cfconfig

#endif  // CFCONFIG_SRC_CLI_H
