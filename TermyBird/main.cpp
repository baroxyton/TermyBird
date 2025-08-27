/*
 * Copyright (c) 2024, TermyBird Contributors <contributors@termybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/String.h>
#include <LibCore/ArgsParser.h>
#include <LibCore/EventLoop.h>
#include <LibCore/Timer.h>
#include <LibMain/Main.h>
#include <stdio.h>

class FakeSkiaRenderingSurface : public RefCounted<FakeSkiaRenderingSurface> {
public:
    static NonnullRefPtr<FakeSkiaRenderingSurface> create(int width, int height)
    {
        return adopt_ref(*new FakeSkiaRenderingSurface(width, height));
    }

    void render_url(String const& url)
    {
        printf("🌐 TERMYBIRD TROLLING: Pretending to render URL: %s\n", url.characters());
        printf("📱 TERMYBIRD TROLLING: Creating fake Skia rendering surface of size %dx%d\n", 
               m_width, m_height);
        printf("🎨 TERMYBIRD TROLLING: Using Skia rendering backend... NOT!\n");
        printf("🔥 TERMYBIRD TROLLING: Actually doing nothing but printing this message!\n");
        
        // Simulate some Skia "rendering" operations
        simulate_skia_operations();
        
        printf("✅ TERMYBIRD TROLLING: Fake Skia rendering complete! (No actual pixels were rendered)\n");
    }

    void simulate_skia_operations()
    {
        // Simulate typical Skia operations that would happen during web page rendering
        printf("⏳ TERMYBIRD TROLLING: Fake Skia canvas creation...\n");
        printf("🎨 DISPLAY COMMAND: FillRect - color=rgba(255,255,255,255), rect=(0,0,%dx%d) [background]\n", m_width, m_height);
        printf("🎨 DISPLAY COMMAND: DrawGlyphRun - text='Google Search', scale=1.0, color=rgba(0,0,0,255)\n");
        printf("🎨 DISPLAY COMMAND: FillRect - color=rgba(66,133,244,255), rect=(350,280,120x40) [search button]\n");
        printf("🎨 DISPLAY COMMAND: DrawPath - color=rgba(234,67,53,255) [Google logo path 1]\n");
        printf("🎨 DISPLAY COMMAND: DrawPath - color=rgba(251,188,5,255) [Google logo path 2]\n");
        printf("🎨 DISPLAY COMMAND: DrawPath - color=rgba(52,168,83,255) [Google logo path 3]\n");
        printf("🎨 DISPLAY COMMAND: DrawPath - color=rgba(66,133,244,255) [Google logo path 4]\n");
        printf("🎨 TROLLING FLUSH: All display commands sent to terminal instead of Skia rendering! 😈\n");
    }

    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    explicit FakeSkiaRenderingSurface(int width, int height)
        : m_width(width), m_height(height)
    {
        printf("🎯 TERMYBIRD TROLLING: Fake Skia rendering surface constructed!\n");
    }

    int m_width;
    int m_height;
};

class TermyBirdWebClient {
public:
    TermyBirdWebClient()
    {
        printf("🚀 TERMYBIRD: Starting web client with fake Skia rendering surface!\n");
        m_surface = FakeSkiaRenderingSurface::create(1024, 768);
    }

    void navigate_to_google()
    {
        String google_url = "https://google.com"sv;
        printf("🔍 TERMYBIRD: Navigating to Google.com...\n");
        printf("🌐 TERMYBIRD: Initiating fake HTTP request to Google...\n");
        printf("📄 TERMYBIRD TROLLING: Pretending to parse HTML content...\n");
        printf("🎨 TERMYBIRD: Starting fake Skia rendering process...\n");
        m_surface->render_url(google_url);
    }

    void run()
    {
        navigate_to_google();
        
        // Keep the event loop running for a bit to simulate a real browser
        auto timer = Core::Timer::create();
        timer->set_single_shot(true);
        timer->set_interval(3000); // 3 seconds
        timer->on_timeout = [this]() {
            printf("🎪 TERMYBIRD TROLLING: Browser session complete! Exiting fake browser.\n");
            printf("📊 TERMYBIRD: Rendered 0 actual pixels, printed %d trolling messages! 🎭\n", 15);
            Core::EventLoop::current().quit(0);
        };
        timer->start();
    }

private:
    NonnullRefPtr<FakeSkiaRenderingSurface> m_surface;
};

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    Core::EventLoop event_loop;

    printf("🦅 Welcome to TermyBird - The Trolling Web Browser!\n");
    printf("📋 This is a fake web client that pretends to use Skia rendering.\n");
    printf("🎭 All rendering is fake and will use trolling mode prints!\n");
    printf("🔧 Integrates with existing Ladybird Skia trolling infrastructure.\n");
    printf("\n");

    auto client = make<TermyBirdWebClient>();
    client->run();

    return event_loop.exec();
}