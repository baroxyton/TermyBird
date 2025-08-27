set(SOURCES
    main.cpp
    SkiaWebView.cpp
)

add_executable(termybird ${SOURCES})

target_include_directories(termybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(termybird PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/..)
target_include_directories(termybird PRIVATE ${LADYBIRD_SOURCE_DIR})
target_include_directories(termybird PRIVATE ${LADYBIRD_SOURCE_DIR}/Libraries)

target_link_libraries(termybird PRIVATE LibCore LibFileSystem LibGfx LibIPC LibJS LibMain LibWeb LibWebView LibURL)
target_link_libraries(termybird PRIVATE OpenSSL::Crypto OpenSSL::SSL)