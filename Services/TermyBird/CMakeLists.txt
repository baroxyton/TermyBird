set(SOURCES
    TermyPageClient.cpp
)

add_library(termybirdservice STATIC ${SOURCES})
set_target_properties(termybirdservice PROPERTIES AUTOMOC OFF AUTORCC OFF AUTOUIC OFF)

target_include_directories(termybirdservice PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../..>)
target_include_directories(termybirdservice PUBLIC $<BUILD_INTERFACE:${LADYBIRD_SOURCE_DIR}>)
target_include_directories(termybirdservice PUBLIC $<BUILD_INTERFACE:${LADYBIRD_SOURCE_DIR}/Services/>)

target_link_libraries(termybirdservice PUBLIC LibCore LibCrypto LibFileSystem LibGfx LibJS LibMain LibWeb LibWebView LibGC)
target_link_libraries(termybirdservice PRIVATE OpenSSL::Crypto OpenSSL::SSL)

add_executable(TermyBird main.cpp)
target_link_libraries(TermyBird PRIVATE termybirdservice LibURL)

if(WIN32)
    find_package(unofficial-angle REQUIRED CONFIG)
    target_link_libraries(TermyBird PRIVATE LibTextCodec unofficial::angle::libGLESv2)
endif()