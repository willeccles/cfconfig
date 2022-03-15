#include <clang/Format/Format.h>

#include <iostream>

namespace cf = clang::format;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "missing style\n";
    return 1;
  }

  cf::FormatStyle style{};

  if (cf::getPredefinedStyle(argv[1], cf::FormatStyle::LanguageKind::LK_Cpp,
                             &style)) {
    std::cout << cf::configurationAsText(style) << '\n';
    return 0;
  } else {
    std::cerr << "unknown style: " << argv[1] << '\n';
    return 1;
  }

  return 0;
}
