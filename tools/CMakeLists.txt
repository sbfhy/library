file(GLOB_RECURSE SOURCES Private/*.cpp)

add_library(Tools SHARED ${SOURCES})
set_target_properties(Tools PROPERTIES PREFIX "")

target_include_directories(Tools PUBLIC
    Public
)