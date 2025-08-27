/*
 * Copyright (c) 2025, TermyBird Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/LexicalPath.h>
#include <LibCore/AnonymousBuffer.h>
#include <LibCore/EventLoop.h>
#include <LibCore/System.h>
#include <LibCore/Timer.h>
#include <LibGfx/SystemTheme.h>
#include <LibMain/Main.h>
#include <LibURL/Parser.h>
#include <LibWeb/PixelUnits.h>
#include <LibWebView/BrowserProcess.h>
#include <LibWebView/HeadlessWebView.h>
#include <LibWebView/Utilities.h>

ErrorOr<int> ladybird_main([[maybe_unused]] Main::Arguments arguments)
{
    // Initialize platform and browser process
    WebView::platform_init();
    WebView::BrowserProcess browser_process;

    printf("🦅 TermyBird - Web Client with Terminal Output 🦅\n");
    
    // Create a web client with a standard viewport size and unused rendering surface
    Web::DevicePixelSize viewport_size { 1024, 768 };
    printf("Creating web client (viewport: %dx%d)...\n", viewport_size.width().value(), viewport_size.height().value());
    
    // Load the default theme for proper rendering
    auto theme_path = LexicalPath::join(WebView::s_ladybird_resource_root, "themes"sv, "Default.ini"sv);
    auto theme = TRY(Gfx::load_system_theme(theme_path.string()));
    
    // Create the web client (using HeadlessWebView for the rendering surface)
    auto web_view = WebView::HeadlessWebView::create(move(theme), viewport_size);

    // Set up event loop
    Core::EventLoop event_loop;

    // Set up callbacks to see when page loads
    web_view->on_load_start = [](URL::URL const& url, bool is_redirect) {
        printf("📥 Loading: %s %s\n", url.to_string().to_byte_string().characters(), is_redirect ? "(redirect)" : "");
    };

    web_view->on_load_finish = [](URL::URL const& url) {
        printf("✅ Finished loading: %s\n", url.to_string().to_byte_string().characters());
        printf("🎨 Rendering surface created but unused (as requested)\n");
    };

    // Parse the target URL
    auto url = URL::Parser::basic_parse("https://google.com"sv);
    if (!url.has_value()) {
        printf("❌ Failed to parse URL: https://google.com\n");
        return 1;
    }

    printf("🌐 Navigating to: %s\n", url->to_string().to_byte_string().characters());
    printf("📝 Web client running with unused rendering surface:\n");
    printf("========================================================\n");

    // Navigate to Google
    web_view->load(url.value());

    // Run the event loop indefinitely to keep the web client running
    // The program will continue until manually terminated (Ctrl+C)
    printf("🔄 Web client running indefinitely. Press Ctrl+C to exit.\n");

    return event_loop.exec();
}