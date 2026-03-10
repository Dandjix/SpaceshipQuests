#pragma once
#include <functional>
#include <memory>

#include "math/AdjacencyListDirectedGraph.h"

//
// Created by timon on 3/9/26.
//


class DialogStack;

namespace Dialogs {
    class PlayerLine;
    class NPCLine;
}

namespace Dialogs {
    class Dialog {
    public:
        Dialog(
            const Quests::Math::AdjacencyListDirectedGraph<DialogStack*,int> &dialog,
            std::function<void(std::vector<const PlayerLine &>)> present_choices_to_player,
            std::function<void(const NPCLine &)> present_npc_line
        )
            : present_choices_to_player(std::move(present_choices_to_player)),
              present_NPC_line(std::move(present_npc_line)),
              dialog(dialog) {
        }

    protected:
        Quests::Math::AdjacencyListDirectedGraph<DialogStack*,int> dialog;
    public:
        std::function<void(std::vector<const PlayerLine &>)> present_choices_to_player;
        std::function<void(const NPCLine &)> present_NPC_line;


    public:
    };
}
