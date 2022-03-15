list(APPEND CFCONFIG_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(cfconfig ${CFCONFIG_SOURCES})

target_link_libraries(cfconfig clangFormat)

target_compile_definitions(cfconfig PUBLIC
  $<$<CONFIG:Debug>:
  DEBUG=1
  _DEBUG=1
  >
  )

target_compile_options(cfconfig PRIVATE
  $<$<CONFIG:Debug>: -Og -g>
  $<$<CONFIG:Release>: -O3 -flto -Werror>
  -W -Wall -pedantic
  )

target_link_options(cfconfig PRIVATE
  $<$<CONFIG:Release>: -flto -O3 -s>
  )
