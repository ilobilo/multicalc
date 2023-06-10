// Copyright (C) 2023  ilobilo

#include <ftxui/component/component.hpp>
#include <ftxui/dom/node.hpp>

#include <functional>
#include <vector>
#include <string>

#define TAB(TAB_RENDERER, UNITS, RENDER_CMD)                                                                               \
{                                                                                                                          \
    int from_sel = 0;                                                                                                      \
    int to_sel = 0;                                                                                                        \
                                                                                                                           \
    ftxui::Component from_comp = ftxui::Radiobox(&UNITS, &from_sel);                                                       \
    ftxui::Component to_comp = ftxui::Radiobox(&UNITS, &to_sel);                                                           \
                                                                                                                           \
    ftxui::InputOption nomultiline;                                                                                        \
    nomultiline.multiline = false;                                                                                         \
                                                                                                                           \
    std::string val_cont;                                                                                                  \
    ftxui::Component val_comp = ftxui::Input(&val_cont, "Value", nomultiline);                                             \
                                                                                                                           \
    auto hcont = ftxui::Container::Horizontal({                                                                            \
        from_comp, to_comp,                                                                                                \
        ftxui::Container::Vertical({                                                                                       \
            val_comp                                                                                                       \
        })                                                                                                                 \
    });                                                                                                                    \
                                                                                                                           \
    TAB_RENDERER = ftxui::Renderer(hcont, [&] {                                                                            \
        auto from_win = ftxui::window(ftxui::text("From"), from_comp->Render() | ftxui::vscroll_indicator | ftxui::frame); \
        auto to_win = ftxui::window(ftxui::text("To"), to_comp->Render() | ftxui::vscroll_indicator | ftxui::frame);       \
                                                                                                                           \
        auto val_win = ftxui::window(ftxui::text(UNITS[from_sel]), val_comp->Render());                                    \
        auto out_win = ftxui::window(ftxui::text(UNITS[to_sel]), ftxui::vflow(RENDER_CMD(from_sel, to_sel, val_cont)));    \
                                                                                                                           \
        constexpr size_t vbox_height = 6;                                                                                  \
        return ftxui::vbox({                                                                                               \
                ftxui::hbox({                                                                                              \
                    from_win,                                                                                              \
                    to_win,                                                                                                \
                    ftxui::vbox({                                                                                          \
                        val_win | size(ftxui::WIDTH, ftxui::GREATER_THAN, 20)                                              \
                                | size(ftxui::HEIGHT, ftxui::EQUAL, vbox_height / 2),                                      \
                        out_win | size(ftxui::WIDTH, ftxui::GREATER_THAN, 20)                                              \
                                | size(ftxui::HEIGHT, ftxui::EQUAL, vbox_height / 2)                                       \
                    }),                                                                                                    \
                    ftxui::filler()                                                                                        \
                }) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, vbox_height)                                                 \
        }) | ftxui::flex_grow;                                                                                             \
    });                                                                                                                    \
}
