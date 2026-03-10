#pragma once
#include <string>
#include <vector>
//
// Created by timon on 3/9/26.
//

namespace Dialogs {
    class NPCLine {
    protected:
        std::string line_key;

    public:
        explicit NPCLine(std::string line_key) : line_key(std::move(line_key)) {  }
    };
}
