/*
 * Copyright (c) 2024, TermyBird Team
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "TermyPageClient.h"
#include <LibGfx/Palette.h>
#include <LibWeb/CSS/StyleComputer.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/Page/Page.h>

namespace TermyBird {

GC_DEFINE_ALLOCATOR(TermyPageClient);

GC::Ref<TermyPageClient> TermyPageClient::create(JS::VM& vm)
{
    return vm.heap().allocate_without_realm<TermyPageClient>(vm);
}

TermyPageClient::TermyPageClient(JS::VM& vm)
{
    // Create a fake page with Skia rendering
    m_page = Web::Page::create(vm, *this);
    
    // Set up for Skia CPU rendering (trolling mode!)
    m_page->set_size({ 1920, 1080 });
    
    dbgln("🐦 TermyBird PageClient created! Trolling mode activated with fake Skia surface! 🐦");
}

TermyPageClient::~TermyPageClient() = default;

Gfx::Palette TermyPageClient::palette() const
{
    // Return a basic dark palette for trolling
    return Gfx::Palette::default_palette();
}

DevicePixelRect TermyPageClient::screen_rect() const
{
    // Fake screen size
    return DevicePixelRect { 0, 0, 1920, 1080 };
}

Web::DisplayListPlayerType TermyPageClient::display_list_player_type() const
{
    // Force Skia CPU for maximum trolling prints
    return Web::DisplayListPlayerType::SkiaCPU;
}

void TermyPageClient::page_did_change_title(ByteString const& title)
{
    dbgln("🐦 TROLLING: Page title changed to: '{}' (bet you didn't expect this output!)", title);
}

void TermyPageClient::page_did_request_navigate_back()
{
    dbgln("🐦 TROLLING: Someone tried to go back! Not happening in our fake browser! 🐦");
}

void TermyPageClient::page_did_request_navigate_forward()
{
    dbgln("🐦 TROLLING: Forward navigation requested! We're going nowhere! 🐦");
}

void TermyPageClient::page_did_request_refresh()
{
    dbgln("🐦 TROLLING: Refresh requested! Pretending to refresh our fake page! 🐦");
}

Web::Page::CookieJar& TermyPageClient::page_did_request_cookie_jar()
{
    dbgln("🐦 TROLLING: Cookie jar requested! Serving fake cookies! 🍪🐦");
    return m_cookie_jar;
}

void TermyPageClient::page_did_request_new_tab(URL::URL const& url)
{
    dbgln("🐦 TROLLING: New tab requested for '{}' - opening in imaginary tab! 🐦", url);
}

void TermyPageClient::page_did_request_activate_tab()
{
    dbgln("🐦 TROLLING: Tab activation requested! Activating our fake tab! 🐦");
}

void TermyPageClient::page_did_close()
{
    dbgln("🐦 TROLLING: Page closed! Goodbye fake world! 🐦");
}

void TermyPageClient::page_did_update_favicon(Gfx::Bitmap const&)
{
    dbgln("🐦 TROLLING: Favicon updated! Look at our beautiful fake icon! 🐦");
}

void TermyPageClient::page_did_allocate_backing_stores(i32 front_bitmap_id, Gfx::ShareableBitmap, i32 back_bitmap_id, Gfx::ShareableBitmap)
{
    dbgln("🐦 TROLLING: Skia backing stores allocated! Front: {}, Back: {} - fake rendering engaged! 🐦", front_bitmap_id, back_bitmap_id);
}

void TermyPageClient::page_did_change_selection()
{
    dbgln("🐦 TROLLING: Text selection changed! Selecting pixels in our fake world! 🐦");
}

void TermyPageClient::page_did_request_cursor_change(Gfx::Cursor const&)
{
    dbgln("🐦 TROLLING: Cursor change requested! Showing our fake cursor! 🐦");
}

void TermyPageClient::page_did_layout(CSSPixelSize content_size)
{
    dbgln("🐦 TROLLING: Layout complete! Fake content size: {}x{} - Skia rendering in progress! 🐦", content_size.width().to_int(), content_size.height().to_int());
}

void TermyPageClient::page_did_change_url(URL::URL const& url)
{
    dbgln("🐦 TROLLING: URL changed to '{}' - welcome to our fake navigation! 🐦", url);
}

void TermyPageClient::page_did_finish_loading(URL::URL const& url)
{
    dbgln("🐦 TROLLING: Page '{}' finished loading! Fake Skia rendering complete! 🐦", url);
}

void TermyPageClient::page_did_create_new_document(Web::DOM::Document& document)
{
    dbgln("🐦 TROLLING: New document created! Title: '{}' - Time for some fake Skia magic! 🐦", document.title().to_byte_string());
}

}