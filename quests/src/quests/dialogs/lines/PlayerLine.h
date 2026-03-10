#pragma once
#include <functional>
#include <string>
//
// Created by timon on 3/9/26.
//

namespace Dialogs {
    class PlayerLine {
    protected:
        std::string line_key;

    public:
        std::function<bool()> visibility_check_function;
        std::function<bool()> available_function;

        /**
         * @param line_key the key of the dialog line in the translations file
         * @param visibility_check_function callback that returns whether the option is visible to the player
         * @param available_function callback that returns whether the option can be picked by the player
         */
        PlayerLine(
            std::string line_key,
            std::function<bool()> visibility_check_function = [] { return true; },
            std::function<bool()> available_function = [] { return true; }
        ) : line_key(std::move(line_key)),
            visibility_check_function(std::move(visibility_check_function)),
            available_function(std::move(available_function)) {
        }

        [[nodiscard]] bool is_visible() const { return visibility_check_function(); }
        [[nodiscard]] bool is_available() const { return available_function(); }
    };
}
