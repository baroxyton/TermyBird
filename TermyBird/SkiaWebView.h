/*
 * Copyright (c) 2025, TermyBird Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibCore/Forward.h>
#include <LibGfx/Forward.h>
#include <LibWeb/Page/Page.h>
#include <LibWeb/PixelUnits.h>
#include <LibWebView/Forward.h>
#include <LibWebView/ViewImplementation.h>

namespace TermyBird {

class WEBVIEW_API SkiaWebView : public WebView::ViewImplementation {
public:
    static NonnullOwnPtr<SkiaWebView> create(Core::AnonymousBuffer theme, Web::DevicePixelSize window_size);
    static NonnullOwnPtr<SkiaWebView> create_child(SkiaWebView&, u64 page_index);

protected:
    SkiaWebView(Core::AnonymousBuffer theme, Web::DevicePixelSize viewport_size);

    void initialize_client(CreateNewClient) override;
    void update_zoom() override;

    virtual Web::DevicePixelSize viewport_size() const override { return m_viewport_size; }
    virtual Gfx::IntPoint to_content_position(Gfx::IntPoint widget_position) const override { return widget_position; }
    virtual Gfx::IntPoint to_widget_position(Gfx::IntPoint content_position) const override { return content_position; }

    Core::AnonymousBuffer m_theme;
    Web::DevicePixelSize m_viewport_size;

    Web::Page::PendingDialog m_pending_dialog { Web::Page::PendingDialog::None };
    Optional<String> m_pending_prompt_text;

    // FIXME: We should implement UI-agnostic platform APIs to interact with the system clipboard.
    Optional<Web::Clipboard::SystemClipboardItem> m_clipboard;

    Vector<NonnullOwnPtr<SkiaWebView>> m_child_web_views;
};

}