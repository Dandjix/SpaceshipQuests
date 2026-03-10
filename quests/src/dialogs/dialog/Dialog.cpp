//
// Created by timon on 3/9/26.
//

#include "Dialog.h"

#include <iostream>

void Dialogs::Dialog::advance() {
    if (getStatus() != ALIVE)
        throw AdvanceWhileDead();

    current_line_in_stack ++;

    if (current_line_in_stack >= NPC_lines.at(current_stack).size() - 1) {
        auto edges_from = topology.getEdgesFrom(current_stack);

        std::vector<PlayerLine> player_choices = {};
        for (auto [to,edge]: edges_from) {
            player_choices.emplace_back(player_lines.at(edge));
        }

        presented_options = player_choices;
        return;
    }
}

Dialogs::NPCLine Dialogs::Dialog::getCurrentLine() const {
    return NPC_lines.at(current_stack).at(current_line_in_stack);
}

Dialogs::Dialog::Status Dialogs::Dialog::getStatus() const {
    if (!presented_options.empty())
        return AWAITING_CHOICE;

    if (topology.getEdgesFrom(current_stack).empty() && current_line_in_stack >= NPC_lines.at(current_stack).size() - 1)
        return EXHAUSTED;

    return ALIVE;
}

std::vector<Dialogs::PlayerLine> Dialogs::Dialog::getPlayerAnswers() const {
    return presented_options;
}

void Dialogs::Dialog::choose(int chosen_index) {

    auto edges = topology.getEdgesFrom(current_stack);


    // auto chosen0 = presented_options.at(chosen_index); // this is how to get the line if you want to
    auto [vertex, edge] = edges.at(chosen_index);

    current_stack = vertex;
    current_line_in_stack = 0;
    presented_options.clear();
}

void Dialogs::Dialog::softReset() {
}
