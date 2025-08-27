/*
 * Copyright (c) 2024, TermyBird Team
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGfx/Rect.h>
#include <LibWeb/Page/Page.h>
#include <LibWeb/PixelUnits.h>

namespace TermyBird {

class TermyPageClient final : public Web::PageClient {
    GC_CELL(TermyPageClient, Web::PageClient);
    GC_DECLARE_ALLOCATOR(TermyPageClient);

public:
    static GC::Ref<TermyPageClient> create(JS::VM& vm);

    virtual ~TermyPageClient() override;

    virtual u64 id() const override { return 1; }
    virtual Web::Page& page() override { return *m_page; }
    virtual Web::Page const& page() const override { return *m_page; }
    virtual bool is_connection_open() const override { return true; }
    virtual Gfx::Palette palette() const override;
    virtual DevicePixelRect screen_rect() const override;
    virtual double device_pixels_per_css_pixel() const override { return 1.0; }
    virtual CSS::PreferredColorScheme preferred_color_scheme() const override { return CSS::PreferredColorScheme::Auto; }
    virtual CSS::PreferredContrast preferred_contrast() const override { return CSS::PreferredContrast::Auto; }
    virtual CSS::PreferredMotion preferred_motion() const override { return CSS::PreferredMotion::Auto; }
    virtual Web::DisplayListPlayerType display_list_player_type() const override;
    virtual bool is_headless() const override { return true; }

    // Page events - add trolling prints
    virtual void page_did_change_title(ByteString const& title) override;
    virtual void page_did_request_navigate_back() override;
    virtual void page_did_request_navigate_forward() override;
    virtual void page_did_request_refresh() override;
    virtual Web::Page::CookieJar& page_did_request_cookie_jar() override;
    virtual void page_did_request_new_tab(URL::URL const& url) override;
    virtual void page_did_request_activate_tab() override;
    virtual void page_did_close() override;
    virtual void page_did_update_favicon(Gfx::Bitmap const& bitmap) override;
    virtual void page_did_allocate_backing_stores(i32 front_bitmap_id, Gfx::ShareableBitmap front_bitmap, i32 back_bitmap_id, Gfx::ShareableBitmap back_bitmap) override;
    virtual void page_did_change_selection() override;
    virtual void page_did_request_cursor_change(Gfx::Cursor const& cursor) override;
    virtual void page_did_layout(CSSPixelSize content_size) override;
    virtual void page_did_change_url(URL::URL const& url) override;
    virtual void page_did_finish_loading(URL::URL const& url) override;
    virtual void page_did_create_new_document(Web::DOM::Document& document) override;

private:
    explicit TermyPageClient(JS::VM& vm);

    GC::Ptr<Web::Page> m_page;
    mutable Web::Page::CookieJar m_cookie_jar;
};

}