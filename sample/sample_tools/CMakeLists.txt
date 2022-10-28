add_executable(SampleTools main.cpp)


set_target_properties(SampleTools PROPERTIES PREFIX "")

target_include_directories(SampleTools PUBLIC
    ../tools/Public
)

add_dependencies(SampleTools 
    Tools
)

target_link_libraries(SampleTools
    Tools
)
