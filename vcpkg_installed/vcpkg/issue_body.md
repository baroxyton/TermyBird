Package: angle:x64-linux@chromium_7258

**Host Environment**

- Host: x64-linux
- Compiler: GNU 13.3.0
-    vcpkg-tool version: 2025-07-21-d4b65a2b83ae6c3526acd1c6f3b51aff2a884533
    vcpkg-scripts version: ee0973d809 2025-08-18 (9 days ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
CMake Warning at /home/runner/work/TermyBird/TermyBird/Meta/CMake/vcpkg/overlay-ports/angle/portfile.cmake:2 (message):
  Building with a gcc version less than 6.1 is not supported.
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)


CMake Warning at /home/runner/work/TermyBird/TermyBird/Meta/CMake/vcpkg/overlay-ports/angle/portfile.cmake:3 (message):
  angle currently requires the following libraries from the system package
  manager:

      mesa-common-dev

  

  These can be installed on Ubuntu systems via apt-get install
  mesa-common-dev.
Call Stack (most recent call first):
  scripts/ports.cmake:206 (include)


Downloading https://github.com/google/angle/archive/79ac1a8cd767a32cce6401203e20c4bd4ca4d539.tar.gz -> google-angle-79ac1a8cd767a32cce6401203e20c4bd4ca4d539.tar.gz
Successfully downloaded google-angle-79ac1a8cd767a32cce6401203e20c4bd4ca4d539.tar.gz
-- Extracting source /usr/local/share/vcpkg/downloads/google-angle-79ac1a8cd767a32cce6401203e20c4bd4ca4d539.tar.gz
-- Applying patch 001-fix-builder-error.patch
-- Applying patch fix-freebsd.patch
-- Using source at /usr/local/share/vcpkg/buildtrees/angle/src/bd4ca4d539-27842c5e34.clean
Downloading https://github.com/WebKit/WebKit/raw/0742522b24152262b04913242cb0b3c48de92ba0/Source/ThirdParty/ANGLE/gni-to-cmake.py -> gni-to-cmake.py
Successfully downloaded gni-to-cmake.py
-- Setting up python virtual environment...
-- Installing python packages: ply
-- Setting up python virtual environment... finished.
Downloading https://github.com/WebKit/WebKit/raw/0742522b24152262b04913242cb0b3c48de92ba0/Source/ThirdParty/ANGLE/include/CMakeLists.txt -> include_CMakeLists.txt
Successfully downloaded include_CMakeLists.txt
Downloading https://github.com/WebKit/WebKit/raw/0742522b24152262b04913242cb0b3c48de92ba0/Source/cmake/WebKitCompilerFlags.cmake -> WebKitCompilerFlags.cmake
Successfully downloaded WebKitCompilerFlags.cmake
Downloading https://github.com/WebKit/WebKit/raw/0742522b24152262b04913242cb0b3c48de92ba0/Source/cmake/DetectSSE2.cmake -> DetectSSE2.cmake
Successfully downloaded DetectSSE2.cmake
Downloading https://github.com/WebKit/WebKit/raw/0742522b24152262b04913242cb0b3c48de92ba0/Source/cmake/WebKitMacros.cmake -> WebKitMacros.cmake
Successfully downloaded WebKitMacros.cmake
-- Fetching https://chromium.googlesource.com/chromium/src/third_party/zlib 4028ebf8710ee39d2286cb0f847f9b95c59f84d8...
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: /usr/bin/git fetch https://chromium.googlesource.com/chromium/src/third_party/zlib 4028ebf8710ee39d2286cb0f847f9b95c59f84d8 --depth 1 -n
    Working Directory: /usr/local/share/vcpkg/downloads/git-tmp
    Error code: 128
    See logs for more information:
      /usr/local/share/vcpkg/buildtrees/angle/git-fetch-x64-linux-err.log

Call Stack (most recent call first):
  scripts/cmake/vcpkg_from_git.cmake:86 (vcpkg_execute_required_process)
  /home/runner/work/TermyBird/TermyBird/Meta/CMake/vcpkg/overlay-ports/angle/portfile.cmake:155 (vcpkg_from_git)
  /home/runner/work/TermyBird/TermyBird/Meta/CMake/vcpkg/overlay-ports/angle/portfile.cmake:168 (checkout_in_path)
  scripts/ports.cmake:206 (include)



```

<details><summary>/usr/local/share/vcpkg/buildtrees/angle/git-fetch-x64-linux-err.log</summary>

```
fatal: unable to access 'https://chromium.googlesource.com/chromium/src/third_party/zlib/': Could not resolve host: chromium.googlesource.com
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "builtin-baseline": "ee0973d8090e4e3e452244bb50d34c25fe907dc2",
  "dependencies": [
    {
      "name": "angle",
      "platform": "osx",
      "features": [
        "metal"
      ]
    },
    {
      "name": "angle",
      "platform": "linux | windows | android | freebsd"
    },
    {
      "name": "curl",
      "default-features": false,
      "features": [
        "brotli",
        "non-http",
        "http2",
        "http3",
        "openssl",
        "websockets",
        "zstd"
      ]
    },
    {
      "name": "dirent",
      "platform": "windows"
    },
    "fast-float",
    {
      "name": "ffmpeg",
      "features": [
        "avcodec",
        "avformat",
        "dav1d",
        "openh264",
        "opus",
        "webp",
        "theora",
        "vorbis",
        "vpx",
        "zlib"
      ]
    },
    {
      "name": "fontconfig",
      "platform": "linux | freebsd | openbsd | osx | windows"
    },
    {
      "name": "harfbuzz",
      "platform": "linux | freebsd | openbsd | windows",
      "features": [
        "freetype",
        "icu"
      ]
    },
    {
      "name": "harfbuzz",
      "platform": "osx",
      "features": [
        "coretext",
        "icu"
      ]
    },
    "icu",
    "libjpeg-turbo",
    "libjxl",
    {
      "name": "libpng",
      "features": [
        "apng"
      ]
    },
    {
      "name": "libproxy",
      "platform": "!(android | freebsd)"
    },
    {
      "name": "libavif",
      "features": [
        "dav1d"
      ]
    },
    "libtommath",
    {
      "name": "libwebp",
      "features": [
        "anim",
        "libwebpmux",
        "simd"
      ]
    },
    {
      "name": "mman",
      "platform": "windows"
    },
    "openssl",
    {
      "name": "qtbase",
      "platform": "freebsd",
      "default-features": false,
      "features": [
        "doubleconversion",
        "fontconfig",
        "freetype",
        "gui",
        "icu",
        "jpeg",
        "network",
        "opengl",
        "pcre2",
        "png",
        "thread",
        "vulkan",
        "widgets",
        "xcb",
        "xcb-xlib",
        "xlib",
        "xrender",
        "zstd"
      ]
    },
    {
      "name": "qtbase",
      "platform": "windows",
      "default-features": false,
      "features": [
        "doubleconversion",
        "freetype",
        "gui",
        "icu",
        "jpeg",
        "network",
        "opengl",
        "pcre2",
        "png",
        "thread",
        "vulkan",
        "widgets",
        "zstd"
      ]
    },
    {
      "name": "qtmultimedia",
      "platform": "windows | freebsd"
    },
    {
      "name": "pthread",
      "platform": "windows"
    },
    "simdutf",
    {
      "name": "skia",
      "platform": "osx",
      "features": [
        "metal",
        "fontconfig",
        "harfbuzz",
        "icu"
      ]
    },
    {
      "name": "skia",
      "platform": "linux | freebsd | openbsd | windows",
      "features": [
        "freetype",
        "fontconfig",
        "harfbuzz",
        "icu",
        "vulkan"
      ]
    },
    {
      "name": "skia",
      "platform": "android",
      "features": [
        "vulkan"
      ]
    },
    "sqlite3",
    "vulkan",
    {
      "name": "tiff",
      "features": [
        "zstd"
      ]
    },
    "vulkan-headers",
    "woff2",
    "zlib"
  ],
  "overrides": [
    {
      "name": "angle",
      "version": "chromium_7258#0"
    },
    {
      "name": "curl",
      "version": "8.15.0#1"
    },
    {
      "name": "dirent",
      "version": "1.25#0"
    },
    {
      "name": "fast-float",
      "version": "8.0.2#0"
    },
    {
      "name": "ffmpeg",
      "version": "7.1.1#3"
    },
    {
      "name": "fontconfig",
      "version": "2.15.0#4"
    },
    {
      "name": "harfbuzz",
      "version": "10.2.0#0"
    },
    {
      "name": "icu",
      "version": "76.1#0"
    },
    {
      "name": "libjpeg-turbo",
      "version": "3.1.0#2"
    },
    {
      "name": "libjxl",
      "version": "0.11.1#3"
    },
    {
      "name": "libpng",
      "version": "1.6.48#0"
    },
    {
      "name": "libproxy",
      "version": "0.4.18#3"
    },
    {
      "name": "libtommath",
      "version": "1.3.0#2"
    },
    {
      "name": "libavif",
      "version": "1.3.0#0"
    },
    {
      "name": "libwebp",
      "version": "1.5.0#1"
    },
    {
      "name": "mman",
      "version": "git-f5ff813#5"
    },
    {
      "name": "openssl",
      "version": "3.5.1#0"
    },
    {
      "name": "qtbase",
      "version": "6.8.3#2"
    },
    {
      "name": "qtmultimedia",
      "version": "6.8.3#0"
    },
    {
      "name": "simdutf",
      "version": "7.3.3#0"
    },
    {
      "name": "skia",
      "version": "129#0"
    },
    {
      "name": "sqlite3",
      "version": "3.50.2#0"
    },
    {
      "name": "woff2",
      "version": "1.0.2#5"
    },
    {
      "name": "zlib",
      "version": "1.3.1"
    }
  ]
}

```
</details>
