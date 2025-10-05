# TermyBird - Headless Web Client with Terminal Output

This directory contains the TermyBird implementation - a headless web client that integrates with the project's modified Skia rendering engine to print web rendering commands to the terminal instead of rendering to a display.

## Features

- **Headless Web Client**: Uses LibWebView's HeadlessWebView for browser functionality without GUI
- **Terminal Output**: Leverages the existing "trolling mode" Skia renderer modifications that print rendering commands to stdout
- **Google.com Navigation**: Automatically navigates to Google.com to demonstrate web content loading and rendering
- **Build Integration**: Fully integrated with the project's build system via CMake

## Usage

Compile and run with:
```bash
./Meta/ladybird.py run termybird
```

## Implementation Details

- **main.cpp**: Creates a SkiaWebView, navigates to Google.com, and runs an event loop with a timer
- **SkiaWebView.cpp/h**: Custom web view implementation that uses Skia for rendering with a paint refresh timer
- **CMakeLists.txt**: Builds the `termybird` executable with necessary library dependencies
- **Integration**: Added to root CMakeLists.txt as a subdirectory under ENABLE_GUI_TARGETS
- **Timer**: A 10-second timer keeps the event loop alive to allow page loading and rendering before graceful exit

## Expected Output

When running, TermyBird will:
1. Display startup messages with TermyBird branding
2. Show page loading progress
3. Print Skia rendering commands to terminal (thanks to the modified renderer)
4. Run for 10 seconds to allow full page loading and rendering
5. Exit gracefully

The terminal output will include rendering commands like:
- `🎨 DISPLAY COMMAND: FillRect - rect=(...) color=rgba(...)`
- `🎨 DISPLAY COMMAND: DrawGlyphRun - ... glyphs, ...`
- `🎨 TROLLING FLUSH: All display commands sent to terminal instead of Skia rendering! 😈`