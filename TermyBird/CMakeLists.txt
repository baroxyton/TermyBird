add_executable(termybird main.cpp)

target_link_libraries(termybird PRIVATE
    AK
    LibCore
    LibMain
)

target_include_directories(termybird PRIVATE ${LADYBIRD_SOURCE_DIR})