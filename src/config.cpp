#include "config.h"

#include <clang/Basic/Version.h>
#include <clang/Format/Format.h>

#include <array>
#include <iostream>
#include <string_view>

#include "cli.h"
#include "util.h"

namespace cfconfig {
namespace config {

namespace cf = clang::format;

cf::FormatStyle GetBaseConfig() {
  static const cli::PromptOptList<std::string_view> kStyles{
    { "None", "file" },
    { "LLVM", "LLVM" },
    { "Google", "Google" },
    { "Chromium", "Chromium" },
    { "Mozilla", "Mozilla" },
    { "WebKit", "WebKit" },
  };

  auto& chosen = cli::Prompt("Base style?",
                             "Base this configuration on a pre-existing style",
                             kStyles, 0);

  // TODO: getStyle will use "file" to get the style from .clang-format
  if (chosen == "file") {
    return cf::FormatStyle{};
  } else {
    cf::FormatStyle style{};
    // TODO language kind
    cf::getPredefinedStyle(chosen,
                           cf::FormatStyle::LanguageKind::LK_Cpp,
                           &style);
    return style;
  }
}

void PromptStyle(cf::FormatStyle& style) {
  // TODO: InheritsParentConfig

#if CF_VER_MIN(3,3)
  style.AccessModifierOffset = cli::Prompt(
          "Extra indent or outdent of access modifiers, e.g. `public:`",
          style.AccessModifierOffset);
#endif  // 3.3

  /*
   * TODO: nicer way to do this type of thing
   *
   * I think it's best to have a value (e.g. "DontAlign") and a description (the
   * full multi-line description), then have an option to do "?" and get
   * a description. This keeps the output clean until the user actually needs
   * a description, which seems nice. Also, we should be able to specify the
   * default in terms of BAS_* value instead of an index in the list, allowing
   * us to easily use the current value in the `style` structure as the default
   * rather than having to use an index.
   *
   * This should also have a more consistent interface regarding option names
   * and their general descriptions.
   *
   * We also need to consider how we will manage the idea of letting a user
   * specify a maximum compatible clang-format version, which will disable some
   * options.
   */
#if CF_VER_MIN(3,8)
  static const cli::PromptOptList<cf::FormatStyle::BracketAlignmentStyle> kBAS{
    { R"_(Align - Align parameters on the open bracket, e.g.:
    someLongFunction(argument1,
                     argument2);)_", cf::FormatStyle::BAS_Align },
    { R"_(DontAlign - Don't align, instead use `ContinuationIndentWidth`, e.g.:
    someLongFunction(argument1,
        argument2);)_", cf::FormatStyle::BAS_DontAlign },
    { R"_(AlwaysBreak - Always break after an open bracket, if the parameters don't fit on a single line, e.g.:
    someLongFunction(
        argument1, argument2);)_", cf::FormatStyle::BAS_AlwaysBreak },
# if CF_VER_MIN(14,0)
    { R"_(BlockIndent - Always break after an open bracket, if the parameters don't fit on a single line. Closing brackets will be placed on a new line. E.g.:
    someLongFunction(
        argument1, argument2
    ))_", cf::FormatStyle::BAS_BlockIndent },
# endif  // 14.0
  };

  style.AlignAfterOpenBracket = cli::Prompt("AlignAfterOpenBracket",
                                            "Bracket alignment style",
                                            kBAS, 0);
#endif  // 3.8
}

}  // namespace config
}  // namespace cfconfig
