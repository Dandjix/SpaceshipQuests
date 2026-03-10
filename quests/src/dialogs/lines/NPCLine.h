#pragma once
#include <string>
#include <vector>
//
// Created by timon on 3/9/26.
//

namespace Dialogs {
    class NPCLine {
    public:
        std::string line_key;

        explicit NPCLine(std::string line_key) : line_key(std::move(line_key)) {  }
    };
}
