/*
 * Copyright (c) 2024, TermyBird Team
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "TermyPageClient.h"
#include <LibCore/ArgsParser.h>
#include <LibCore/EventLoop.h>
#include <LibCore/Timer.h>
#include <LibGfx/Font/FontDatabase.h>
#include <LibMain/Main.h>
#include <LibURL/URL.h>
#include <LibWeb/Bindings/MainThreadVM.h>
#include <LibWeb/HTML/TraversableNavigable.h>
#include <LibWeb/Loader/ResourceLoader.h>
#include <LibWeb/Page/Page.h>
#include <LibWebView/Utilities.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    Core::ArgsParser args_parser;
    StringView url_string = "https://google.com"sv;
    
    args_parser.add_option(url_string, "URL to navigate to", "url", 'u', "URL");
    args_parser.parse(arguments);

    dbgln("🐦🐦🐦 Welcome to TermyBird - The Ultimate Trolling Web Client! 🐦🐦🐦");
    dbgln("🐦 About to create fake rendering surface and navigate to: {}", url_string);
    
    Core::EventLoop event_loop;

    // Initialize the web engine
    Web::Bindings::initialize_main_thread_vm(Web::Bindings::AgentType::SimilarOriginWindow);
    
    dbgln("🐦 TROLLING: Main thread VM initialized! Time for some fake web browsing!");

    // Initialize font system
    auto& font_database = Gfx::FontDatabase::the();
    font_database.set_default_fonts();
    
    dbgln("🐦 TROLLING: Font database loaded! Ready to render fake text with Skia!");

    // Create our troll page client
    auto& vm = Web::Bindings::main_thread_vm();
    auto page_client = TermyBird::TermyPageClient::create(vm);
    
    dbgln("🐦 TROLLING: TermyPageClient created with fake Skia surface!");

    // Parse the URL
    auto url = URL::URL::create_with_url_or_path(url_string);
    if (!url.is_valid()) {
        dbgln("🐦 ERROR: Invalid URL provided: {}", url_string);
        return 1;
    }

    dbgln("🐦 TROLLING: About to navigate to {} with our fake browser!", url);

    // Navigate to the URL
    auto& page = page_client->page();
    auto& top_level_navigable = page.top_level_traversable_navigable();
    
    dbgln("🐦 TROLLING: Initiating fake navigation with Skia rendering backend!");
    
    // Start the navigation
    (void)top_level_navigable->navigate({ .url = url, .source_document = {}, .exceptions_enabled = false });
    
    dbgln("🐦 TROLLING: Navigation started! Watch the fake magic happen!");

    // Set up a timer to show periodic trolling messages
    auto troll_timer = Core::Timer::create_repeating(2000, [&]() {
        static int troll_count = 0;
        troll_count++;
        
        switch (troll_count % 5) {
        case 0:
            dbgln("🐦 TROLLING STATUS: Still pretending to browse the web with Skia! Iteration {}", troll_count);
            break;
        case 1:
            dbgln("🐦 TROLLING STATUS: Fake rendering in progress... Skia CPU backend working hard! 🎨");
            break;
        case 2:
            dbgln("🐦 TROLLING STATUS: Imaginary pixels being painted! Much wow! Such fake! 🎭");
            break;
        case 3:
            dbgln("🐦 TROLLING STATUS: TermyBird is flying high with fake web content! 🚀");
            break;
        case 4:
            dbgln("🐦 TROLLING STATUS: The web has never been more fake! Skia approves! ✨");
            break;
        }
        
        // Exit after a while to prevent infinite trolling
        if (troll_count >= 15) {
            dbgln("🐦 TROLLING COMPLETE: TermyBird has successfully trolled for {} iterations!", troll_count);
            dbgln("🐦 Mission accomplished! Fake web browsing session ending. 🎯");
            event_loop.quit(0);
        }
    });
    
    troll_timer->start();
    
    dbgln("🐦 TROLLING: Event loop starting! Prepare for maximum fake web experience!");
    
    return event_loop.exec();
}