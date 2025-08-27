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

    printf("🦅 TermyBird - Headless Web Client with Terminal Output 🦅\n");
    
    // Create a headless web view with a standard viewport size
    Web::DevicePixelSize viewport_size { 1024, 768 };
    printf("Creating headless web view (viewport: %dx%d)...\n", viewport_size.width().value(), viewport_size.height().value());
    
    // Load the default theme for proper rendering
    auto theme_path = LexicalPath::join(WebView::s_ladybird_resource_root, "themes"sv, "Default.ini"sv);
    auto theme = TRY(Gfx::load_system_theme(theme_path.string()));
    
    // Create the headless web view
    auto web_view = WebView::HeadlessWebView::create(move(theme), viewport_size);

    // Set up event loop
    Core::EventLoop event_loop;

    // Set up callbacks to see when page loads
    web_view->on_load_start = [](URL::URL const& url, bool is_redirect) {
        printf("📥 Loading: %s %s\n", url.to_string().to_byte_string().characters(), is_redirect ? "(redirect)" : "");
    };

    web_view->on_load_finish = [](URL::URL const& url) {
        printf("✅ Finished loading: %s\n", url.to_string().to_byte_string().characters());
        printf("🎨 Skia rendering commands should appear above!\n");
    };

    // Parse the target URL
    auto url = URL::Parser::basic_parse("https://google.com"sv);
    if (!url.has_value()) {
        printf("❌ Failed to parse URL: https://google.com\n");
        return 1;
    }

    printf("🌐 Navigating to: %s\n", url->to_string().to_byte_string().characters());
    printf("📝 Terminal output from Skia renderer will appear below:\n");
    printf("========================================================\n");

    // Navigate to Google
    web_view->load(url.value());

    // Run the event loop for a limited time to let the page load and render
    // Since this is a demo, we'll run for a reasonable amount of time
    printf("⏳ Running for 10 seconds to allow page loading and rendering...\n");
    
    auto timer = Core::Timer::create_single_shot(10000, [&] {
        printf("⏰ Time's up! Exiting TermyBird.\n");
        event_loop.quit(0);
    });
    timer->start();

    return event_loop.exec();
}