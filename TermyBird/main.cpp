/*
 * Copyright (c) 2025, TermyBird Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/LexicalPath.h>
#include <LibCore/AnonymousBuffer.h>
#include <LibCore/EventLoop.h>
#include <LibCore/System.h>
#include <LibGfx/SystemTheme.h>
#include <LibMain/Main.h>
#include <LibURL/Parser.h>
#include <LibWeb/PixelUnits.h>
#include <LibWebView/BrowserProcess.h>
#include <LibWebView/Utilities.h>
#include "SkiaWebView.h"

ErrorOr<int> ladybird_main([[maybe_unused]] Main::Arguments arguments)
{
    // Initialize platform and browser process
    WebView::platform_init();
    WebView::BrowserProcess browser_process;

    printf("🦅 TermyBird - Web Client with Skia Rendering 🦅\n");
    
    // Create a web client with a standard viewport size
    Web::DevicePixelSize viewport_size { 1024, 768 };
    printf("Creating web client with Skia rendering (viewport: %dx%d)...\n", viewport_size.width().value(), viewport_size.height().value());
    
    // Load the default theme for proper rendering
    auto theme_path = LexicalPath::join(WebView::s_ladybird_resource_root, "themes"sv, "Default.ini"sv);
    auto theme = TRY(Gfx::load_system_theme(theme_path.string()));
    
    // Create the Skia web view (NOT headless - it's a real web client that renders to Skia surface)
    auto web_view = TermyBird::SkiaWebView::create(move(theme), viewport_size);

    // Set up event loop
    Core::EventLoop event_loop;

    // Set up callbacks to see when page loads
    web_view->on_load_start = [](URL::URL const& url, bool is_redirect) {
        printf("📥 Loading: %s %s\n", url.to_string().to_byte_string().characters(), is_redirect ? "(redirect)" : "");
    };

    web_view->on_load_finish = [](URL::URL const& url) {
        printf("✅ Finished loading: %s\n", url.to_string().to_byte_string().characters());
        printf("🎨 Website rendered to Skia surface in memory!\n");
    };

    // Parse the target URL
    auto url = URL::Parser::basic_parse("https://google.com"sv);
    if (!url.has_value()) {
        printf("❌ Failed to parse URL: https://google.com\n");
        return 1;
    }

    printf("🌐 Navigating to: %s\n", url->to_string().to_byte_string().characters());
    printf("📝 Website will be loaded and rendered to a Skia surface stored in memory\n");
    printf("========================================================\n");

    // Navigate to Google
    web_view->load(url.value());

    // Run the event loop indefinitely - the program runs as long as the web client is running
    printf("🔄 Running indefinitely while the web client is active...\n");
    printf("💡 The website is being rendered to a Skia surface stored in memory\n");
    printf("✋ Press Ctrl+C to exit\n");

    return event_loop.exec();
}