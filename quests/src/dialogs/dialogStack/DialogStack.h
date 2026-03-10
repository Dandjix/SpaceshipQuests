#pragma once
#include <vector>

#include "src/dialogs/dialog/Dialog.h"
#include "src/dialogs/playerLine/PlayerLine.h"


//
// Created by timon on 3/9/26.
//


class DialogStack {
    std::vector<Dialogs::NPCLine> lines;
    std::vector<Dialogs::PlayerLine> answers;

    DialogStack(
        std::vector<Dialogs::NPCLine> lines,
        std::vector<Dialogs::PlayerLine> answers
    ) : lines(std::move(lines)), answers(std::move(answers)) {
    }
};
