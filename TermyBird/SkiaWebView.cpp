/*
 * Copyright (c) 2025, TermyBird Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "SkiaWebView.h"

namespace TermyBird {

static Web::DevicePixelRect const screen_rect { 0, 0, 1920, 1080 };

NonnullOwnPtr<SkiaWebView> SkiaWebView::create(Core::AnonymousBuffer theme, Web::DevicePixelSize window_size)
{
    auto view = adopt_own(*new SkiaWebView(move(theme), window_size));
    view->initialize_client(CreateNewClient::Yes);

    return view;
}

NonnullOwnPtr<SkiaWebView> SkiaWebView::create_child(SkiaWebView& parent, u64 page_index)
{
    auto view = adopt_own(*new SkiaWebView(parent.m_theme, parent.m_viewport_size));

    view->m_client_state.client = parent.client();
    view->m_client_state.page_index = page_index;
    view->initialize_client(CreateNewClient::No);

    return view;
}

SkiaWebView::SkiaWebView(Core::AnonymousBuffer theme, Web::DevicePixelSize viewport_size)
    : m_theme(move(theme))
    , m_viewport_size(viewport_size)
{
    on_new_web_view = [this](auto, auto, Optional<u64> page_index) {
        auto web_view = page_index.has_value()
            ? SkiaWebView::create_child(*this, *page_index)
            : SkiaWebView::create(m_theme, m_viewport_size);

        m_child_web_views.append(move(web_view));
        return m_child_web_views.last()->handle();
    };

    on_reposition_window = [this](auto position) {
        client().async_set_window_position(m_client_state.page_index, position.template to_type<Web::DevicePixels>());

        client().async_did_update_window_rect(m_client_state.page_index);
    };

    on_resize_window = [this](auto size) {
        m_viewport_size = size.template to_type<Web::DevicePixels>();

        client().async_set_window_size(m_client_state.page_index, m_viewport_size);
        client().async_set_viewport_size(m_client_state.page_index, m_viewport_size);

        client().async_did_update_window_rect(m_client_state.page_index);
    };

    on_restore_window = [this]() {
        set_system_visibility_state(Web::HTML::VisibilityState::Visible);
    };

    on_minimize_window = [this]() {
        set_system_visibility_state(Web::HTML::VisibilityState::Hidden);
    };

    on_maximize_window = [this]() {
        m_viewport_size = screen_rect.size();

        client().async_set_window_position(m_client_state.page_index, screen_rect.location());
        client().async_set_window_size(m_client_state.page_index, screen_rect.size());
        client().async_set_viewport_size(m_client_state.page_index, screen_rect.size());

        client().async_did_update_window_rect(m_client_state.page_index);
    };

    on_fullscreen_window = [this]() {
        m_viewport_size = screen_rect.size();

        client().async_set_window_position(m_client_state.page_index, screen_rect.location());
        client().async_set_window_size(m_client_state.page_index, screen_rect.size());
        client().async_set_viewport_size(m_client_state.page_index, screen_rect.size());

        client().async_did_update_window_rect(m_client_state.page_index);
    };

    on_request_alert = [this](auto const&) {
        m_pending_dialog = Web::Page::PendingDialog::Alert;
    };

    on_request_confirm = [this](auto const&) {
        m_pending_dialog = Web::Page::PendingDialog::Confirm;
    };

    on_request_prompt = [this](auto const&, auto const& default_) {
        m_pending_dialog = Web::Page::PendingDialog::Prompt;
        m_pending_prompt_text = default_;
    };

    on_request_set_prompt_text = [this](auto const& message) {
        m_pending_prompt_text = message;
    };

    on_request_accept_dialog = [this]() {
        switch (m_pending_dialog) {
        case Web::Page::PendingDialog::None:
            break;
        case Web::Page::PendingDialog::Alert:
            alert_closed();
            break;
        case Web::Page::PendingDialog::Confirm:
            confirm_closed(true);
            break;
        case Web::Page::PendingDialog::Prompt:
            prompt_closed(m_pending_prompt_text);
            break;
        case Web::Page::PendingDialog::BeforeUnload:
            confirm_closed(true);
            break;
        }

        m_pending_dialog = Web::Page::PendingDialog::None;
        m_pending_prompt_text.clear();
    };

    on_request_dismiss_dialog = [this]() {
        switch (m_pending_dialog) {
        case Web::Page::PendingDialog::None:
            break;
        case Web::Page::PendingDialog::Alert:
            alert_closed();
            break;
        case Web::Page::PendingDialog::Confirm:
            confirm_closed(false);
            break;
        case Web::Page::PendingDialog::Prompt:
            prompt_closed({});
            break;
        case Web::Page::PendingDialog::BeforeUnload:
            confirm_closed(false);
            break;
        }

        m_pending_dialog = Web::Page::PendingDialog::None;
        m_pending_prompt_text.clear();
    };

    on_request_color_picker = [this](auto const&) {
        // For a Skia-only WebView, we don't show color pickers
        color_picker_update({}, Web::HTML::ColorPickerUpdateState::Closed);
    };

    on_request_file_picker = [this](auto const&, auto) {
        // For a Skia-only WebView, we don't show file pickers
        file_picker_closed({});
    };

    on_request_select_dropdown = [this](auto const&, auto, auto const&) {
        // For a Skia-only WebView, we don't show dropdowns
        select_dropdown_closed({});
    };

    on_insert_clipboard_entry = [this](auto const& data, auto const& mime_type) {
        // Store clipboard data in our internal clipboard
        Web::Clipboard::SystemClipboardItem item;
        Web::Clipboard::SystemClipboardRepresentation representation;
        representation.data = data;
        representation.mime_type = mime_type;
        item.system_clipboard_representations.append(move(representation));
        m_clipboard = move(item);
    };

    on_request_clipboard_entries = [this](auto request_id) {
        Vector<Web::Clipboard::SystemClipboardItem> items;
        if (m_clipboard.has_value())
            items.append(m_clipboard.value());
        retrieved_clipboard_entries(request_id, items);
    };
}

void SkiaWebView::initialize_client(CreateNewClient create_new_client)
{
    ViewImplementation::initialize_client(create_new_client);

    client().async_update_system_theme(m_client_state.page_index, m_theme);
    client().async_set_viewport_size(m_client_state.page_index, viewport_size());
    client().async_set_window_size(m_client_state.page_index, viewport_size());
    client().async_update_screen_rects(m_client_state.page_index, { { screen_rect } }, 0);
}

void SkiaWebView::update_zoom()
{
    client().async_set_device_pixels_per_css_pixel(m_client_state.page_index, m_device_pixel_ratio * m_zoom_level);
    client().async_set_viewport_size(m_client_state.page_index, m_viewport_size);
}

}