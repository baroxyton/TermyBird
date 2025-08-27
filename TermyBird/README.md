# TermyBird - The Trolling Web Browser

TermyBird is a fake web client integrated into the Ladybird browser project that pretends to use Skia rendering but actually just prints trolling messages to the terminal.

## Features

- 🦅 Fake web client with trolling mode functionality
- 🎨 Pretends to use Skia rendering backend but prints debug messages instead
- 🌐 Simulates navigation to google.com
- 📱 Creates a fake rendering surface (1024x768)
- 🎭 Uses trolling mode prints matching existing Ladybird patterns
- 🔧 Integrates with existing Ladybird Skia trolling infrastructure

## Building and Running

### Quick Run (Recommended)

```bash
./Meta/ladybird.py run termybird
```

This command will:
1. Check if a termybird executable already exists
2. If found, run it directly (bypassing vcpkg dependency issues)
3. If not found, attempt to build through the normal build system

### Manual Build

If you want to build manually:

```bash
# Simple standalone build
g++ -std=c++20 -o Build/release/bin/termybird TermyBird/main.cpp

# Then run directly
./Build/release/bin/termybird
```

## What It Does

TermyBird simulates a complete web browsing session with fake operations:

1. **Startup**: Displays welcome message and initializes fake rendering surface
2. **Navigation**: Pretends to navigate to https://google.com
3. **HTTP Request**: Simulates making a fake HTTP request
4. **HTML Parsing**: Pretends to parse HTML content
5. **Skia Rendering**: Simulates Skia rendering operations with trolling prints:
   - Canvas creation
   - Background filling
   - Text rendering (Google Search)
   - Button rendering (search button)
   - Path drawing (Google logo components)
   - Flush operations
6. **Completion**: Reports statistics and exits

## Integration with Ladybird

TermyBird integrates seamlessly with the Ladybird project:

- Added to main CMakeLists.txt as a subdirectory
- Included in ladybird.py run command recognition  
- Uses trolling mode patterns from `Libraries/LibWeb/Painting/DisplayListPlayerSkia.cpp`
- Follows Ladybird coding conventions and project structure

## Output Example

```
🦅 Welcome to TermyBird - The Trolling Web Browser!
📋 This is a fake web client that pretends to use Skia rendering.
🎭 All rendering is fake and will use trolling mode prints!
🔧 Integrates with existing Ladybird Skia trolling infrastructure.

🚀 TERMYBIRD: Starting web client with fake Skia rendering surface!
🎯 TERMYBIRD TROLLING: Fake Skia rendering surface constructed!
🔍 TERMYBIRD: Navigating to Google.com...
🌐 TERMYBIRD: Initiating fake HTTP request to Google...
📄 TERMYBIRD TROLLING: Pretending to parse HTML content...
🎨 TERMYBIRD: Starting fake Skia rendering process...
🌐 TERMYBIRD TROLLING: Pretending to render URL: https://google.com
📱 TERMYBIRD TROLLING: Creating fake Skia rendering surface of size 1024x768
🎨 TERMYBIRD TROLLING: Using Skia rendering backend... NOT!
🔥 TERMYBIRD TROLLING: Actually doing nothing but printing this message!
⏳ TERMYBIRD TROLLING: Fake Skia canvas creation...
🎨 DISPLAY COMMAND: FillRect - color=rgba(255,255,255,255), rect=(0,0,1024x768) [background]
🎨 DISPLAY COMMAND: DrawGlyphRun - text='Google Search', scale=1.0, color=rgba(0,0,0,255)
🎨 DISPLAY COMMAND: FillRect - color=rgba(66,133,244,255), rect=(350,280,120x40) [search button]
🎨 DISPLAY COMMAND: DrawPath - color=rgba(234,67,53,255) [Google logo path 1]
🎨 DISPLAY COMMAND: DrawPath - color=rgba(251,188,5,255) [Google logo path 2]
🎨 DISPLAY COMMAND: DrawPath - color=rgba(52,168,83,255) [Google logo path 3]
🎨 DISPLAY COMMAND: DrawPath - color=rgba(66,133,244,255) [Google logo path 4]
🎨 TROLLING FLUSH: All display commands sent to terminal instead of Skia rendering! 😈
✅ TERMYBIRD TROLLING: Fake Skia rendering complete! (No actual pixels were rendered)
🎪 TERMYBIRD TROLLING: Browser session complete! Exiting fake browser.
📊 TERMYBIRD: Rendered 0 actual pixels, printed 15 trolling messages! 🎭
```

## Files Structure

```
TermyBird/
├── CMakeLists.txt     # CMake configuration for TermyBird
├── main.cpp           # Main implementation with fake Skia rendering
└── README.md          # This documentation
```

## Technical Details

- **Language**: C++20
- **Dependencies**: Minimal (standard library only for standalone build)
- **Rendering**: Fake Skia operations with trolling mode prints
- **Integration**: Uses existing Ladybird build system patterns
- **Execution**: Works with `./Meta/ladybird.py run termybird`