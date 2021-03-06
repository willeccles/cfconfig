#include "cli.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "util.h"

namespace cfconfig {
namespace cli {

namespace {
void PrintYesNoPrompt(const std::string_view prompt, bool def) {
  std::cout << prompt << " [";
  if (def) {
    std::cout << "Y/n] ";
  } else {
    std::cout << "y/N] ";
  }
  std::cout.flush();
}

void PrintIntegerPrompt(const std::string_view prompt, int def) {
  // TODO how can we show the valid range of values here?
  std::cout << prompt << " (" << def << ") ";
  std::cout.flush();
}
}

bool Prompt(const std::string_view prompt, bool def) {
  PrintYesNoPrompt(prompt, def);

  std::string line{};
  while (std::getline(std::cin, line)) {
    auto trimmed = util::Trim(line);
    if (trimmed.size() == 0) {
      return def;
    }

    switch (trimmed[0]) {
      case 'Y':
      case 'y':
        return true;

      case 'N':
      case 'n':
        return false;

      default:
        std::cerr << "Invalid response\n";
        PrintYesNoPrompt(prompt, def);
        break;
    }
  }

  throw std::runtime_error("failed to read from stdin");
}

int Prompt(const std::string_view prompt, int min, int max, int def) {
  if (min > max || min > def || max < def) {
    throw std::logic_error("invalid min and max values");
  }

  PrintIntegerPrompt(prompt, def);

  std::string line{};
  while (std::getline(std::cin, line)) {
    line = util::Trim(line);
    if (line.size() == 0) {
      return def;
    }

    try {
      int val = std::stoi(line, nullptr, 0);

      if (val < min || val > max) {
        throw std::out_of_range{"input value out of range"};
      }

      return val;
    } catch (const std::invalid_argument&) {
      std::cerr << "Invalid value\n";
    } catch (const std::out_of_range&) {
      std::cerr << "Value out of range\n";
    }

    PrintIntegerPrompt(prompt, def);
  }

  throw std::runtime_error("failed to read from stdin");
}

int Prompt(const std::string_view prompt, int def) {
  return Prompt(prompt, std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max(), def);
}

}  // namespace cli
}  // namespace cfconfig
