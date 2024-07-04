// Copyright (C) 2023  ilobilo

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <template.hpp>
#include <fmt/core.h>

#include <numbers>

using number_type = long double;

constexpr number_type pound = 2.20462262185;
constexpr number_type ounce = pound * 16;

constexpr number_type au = 149597870700;
constexpr number_type ly = 9460730472580800;
constexpr number_type parsec = number_type(648000) / std::numbers::pi_v<number_type> * au;

auto main() -> int
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    ftxui::Component temp_tab;
    ftxui::Component speed_tab;
    ftxui::Component len_tab;
    ftxui::Component mass_tab;
    ftxui::Component numsys_tab;

    // TEMPERATURE
    const std::vector<std::string> temp_units {
        "Kelvin",
        "Celsius",
        "Fahrenheit",
        "Rankine"
    };

    constexpr number_type (*temp_to_kelvin[])(number_type num) {
        [](number_type num) { return num; },
        [](number_type num) { return num + 273.15; },
        [](number_type num) { return (num - 32) / 1.8 + 273.15; },
        [](number_type num) { return num / 1.8; }
    };

    constexpr number_type (*temp_from_kelvin[])(number_type num) {
        [](number_type num) { return num; },
        [](number_type num) { return num - 273.15; },
        [](number_type num) { return (num - 273.15) * 1.8 + 32; },
        [](number_type num) { return num * 1.8; }
    };

    auto temp_render_cmd = [&] (int from_sel, int to_sel, const std::string &val_cont) {
        ftxui::Elements lines;
        if (val_cont.empty() == false)
        {
            try {
                number_type val = std::stod(val_cont);
                val = temp_to_kelvin[from_sel](val);
                val = temp_from_kelvin[to_sel](val);

                std::string str = std::to_string(val);
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                str.erase(str.find_last_not_of('.') + 1, std::string::npos);
                lines.push_back(ftxui::text(str));
            }
            catch (std::exception const &) { }
        }
        return lines;
    };

    TAB(temp_tab, temp_units, temp_render_cmd)

    // SPEED
    const std::vector<std::string> speed_units {
        "Metres P/S",
        "Kilometres P/S",
        "Kilometres P/H",
        "Miles P/H",
        "Knots",
        "Lightspeed"
    };

    constexpr number_type (*speed_to_mps[])(number_type num) {
        [](number_type num) { return num; },
        [](number_type num) { return num * 1000; },
        [](number_type num) { return num / 3.6; },
        [](number_type num) { return (num * 1.609344) / 3.6; },
        [](number_type num) { return (num * 1.852) / 3.6; },
        [](number_type num) { return num * 299792458; }
    };

    constexpr number_type (*speed_from_mps[])(number_type num) {
        [](number_type num) { return num; },
        [](number_type num) { return num / 1000; },
        [](number_type num) { return num * 3.6; },
        [](number_type num) { return (num * 3.6) / 1.609344; },
        [](number_type num) { return (num * 3.6) / 1.852; },
        [](number_type num) { return num / 299792458; }
    };

    auto speed_render_cmd = [&] (int from_sel, int to_sel, const std::string &val_cont) {
        ftxui::Elements lines;
        if (val_cont.empty() == false)
        {
            try {
                number_type val = std::stod(val_cont);
                if (val < 0)
                    return lines;

                val = speed_to_mps[from_sel](val);
                val = speed_from_mps[to_sel](val);

                std::string str = std::to_string(val);
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                str.erase(str.find_last_not_of('.') + 1, std::string::npos);
                lines.push_back(ftxui::text(str));
            }
            catch (std::exception const &) { }
        }
        return lines;
    };

    TAB(speed_tab, speed_units, speed_render_cmd)

    // LENGTH
    const std::vector<std::string> length_units {
        "Picometre",
        "Nanometre",
        "Micrometre",
        "Millimetre",
        "Centimetre",
        "Decimetre",
        "Metre",
        "Kilometre",
        "Mile",
        "Nautical Mile",
        "Parsec",
        "Astr. Unit AU",
        "Light Year",
    };

    constexpr number_type (*length_to_m[])(number_type num) {
        [](number_type num) { return num / 1000000000000; },
        [](number_type num) { return num / 1000000000; },
        [](number_type num) { return num / 1000000; },
        [](number_type num) { return num / 1000; },
        [](number_type num) { return num / 100; },
        [](number_type num) { return num / 10; },
        [](number_type num) { return num; },
        [](number_type num) { return num * 1000; },
        [](number_type num) { return num * 1609.344; },
        [](number_type num) { return num * 1852; },
        [](number_type num) { return num * parsec; },
        [](number_type num) { return num * au; },
        [](number_type num) { return num * ly; }
    };

    constexpr number_type (*length_from_m[])(number_type num) {
        [](number_type num) { return num * 1000000000000; },
        [](number_type num) { return num * 1000000000; },
        [](number_type num) { return num * 1000000; },
        [](number_type num) { return num * 1000; },
        [](number_type num) { return num * 100; },
        [](number_type num) { return num * 10; },
        [](number_type num) { return num; },
        [](number_type num) { return num / 1000; },
        [](number_type num) { return num / 1609.344; },
        [](number_type num) { return num / 1852; },
        [](number_type num) { return num / parsec; },
        [](number_type num) { return num / au; },
        [](number_type num) { return num / ly; }
    };

    auto length_render_cmd = [&] (int from_sel, int to_sel, const std::string &val_cont) {
        ftxui::Elements lines;
        if (val_cont.empty() == false)
        {
            try {
                number_type val = std::stod(val_cont);
                if (val < 0)
                    return lines;

                val = length_to_m[from_sel](val);
                val = length_from_m[to_sel](val);

                std::string str = std::to_string(val);
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                str.erase(str.find_last_not_of('.') + 1, std::string::npos);
                lines.push_back(ftxui::text(str));
            }
            catch (std::exception const &) { }
        }
        return lines;
    };

    TAB(len_tab, length_units, length_render_cmd)

    // MASS
    const std::vector<std::string> mass_units {
        "Microgramme",
        "Milligramme",
        "Gramme",
        "Kilogramme",
        "Tonne",
        "Pound",
        "Ounce"
    };

    constexpr number_type (*mass_to_kg[])(number_type num) {
        [](number_type num) { return num / 1000000000; },
        [](number_type num) { return num / 1000000; },
        [](number_type num) { return num / 1000; },
        [](number_type num) { return num; },
        [](number_type num) { return num * 1000; },
        [](number_type num) { return num / pound; },
        [](number_type num) { return num / ounce; }
    };

    constexpr number_type (*mass_from_kg[])(number_type num) {
        [](number_type num) { return num * 1000000000; },
        [](number_type num) { return num * 1000000; },
        [](number_type num) { return num * 1000; },
        [](number_type num) { return num; },
        [](number_type num) { return num / 1000; },
        [](number_type num) { return num * pound; },
        [](number_type num) { return num * ounce; }
    };

    auto mass_render_cmd = [&] (int from_sel, int to_sel, const std::string &val_cont) {
        ftxui::Elements lines;
        if (val_cont.empty() == false)
        {
            try {
                number_type val = std::stod(val_cont);
                if (val < 0)
                    return lines;

                val = mass_to_kg[from_sel](val);
                val = mass_from_kg[to_sel](val);

                std::string str = std::to_string(val);
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                str.erase(str.find_last_not_of('.') + 1, std::string::npos);
                lines.push_back(ftxui::text(str));
            }
            catch (std::exception const &) { }
        }
        return lines;
    };

    TAB(mass_tab, mass_units, mass_render_cmd)

    // NUMERICAL SYSTEM
    const std::vector<std::string> numsys_units {
        "Binary",
        "Octal",
        "Decimal",
        "Hexadecimal"
    };

    constexpr int numsys_from[] { 2, 8, 10, 16 };
    constexpr std::string (*numsys_to[])(intmax_t num) {
        [](intmax_t num) { return fmt::format("0b{:b}", num); },
        [](intmax_t num) { return fmt::format("0{:o}", num); },
        [](intmax_t num) { return std::to_string(num); },
        [](intmax_t num) { return fmt::format("0x{:x}", num); },
    };

    auto numsys_render_cmd = [&] (int from_sel, int to_sel, const std::string &val_cont) {
        ftxui::Elements lines;
        if (val_cont.empty() == false)
        {
            try {
                intmax_t val = std::stoll(val_cont, nullptr, numsys_from[from_sel]);
                std::string str = numsys_to[to_sel](val);
                lines.push_back(ftxui::text(str));
            }
            catch (std::exception const &) { }
        }
        return lines;
    };

    TAB(numsys_tab, numsys_units, numsys_render_cmd)

    int tabi = 0;
    std::vector<std::string> tabs { " Temperature ", " Speed ", " Length ", " Mass ", " Numerical System " };

    auto tabsel = ftxui::Menu(&tabs, &tabi, ftxui::MenuOption::HorizontalAnimated());
    auto tabcont = ftxui::Container::Tab({
        temp_tab, speed_tab, len_tab, mass_tab, numsys_tab
    }, &tabi);

    auto maincont = ftxui::Container::Vertical({ tabsel, tabcont });

    auto mainrend = ftxui::Renderer(maincont, [&] {
        return ftxui::vbox({
            ftxui::text("MultiCalc") | ftxui::bold | ftxui::hcenter,
            ftxui::separator(),
            tabsel->Render(),
            tabcont->Render() | ftxui::flex
        });
    });

    std::atomic_bool refresh_ui_continue = true;
    std::thread refresh_ui([&] {
        while (refresh_ui_continue)
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);

            screen.Post(ftxui::Event::Custom);
        }
    });

    screen.Loop(mainrend);
    refresh_ui_continue = false;
    refresh_ui.join();

    return 0;
}