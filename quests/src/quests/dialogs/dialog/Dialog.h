#pragma once
#include <format>
#include <functional>
#include <memory>
#include <utility>

#include "quests/dialogs/lines/NPCLine.h"
#include "quests/dialogs/lines/PlayerLine.h"
#include "quests/math/AdjacencyListDirectedGraph.h"

//
// Created by timon on 3/9/26.
//


class DialogStack;


namespace Dialogs {
    class AdvanceWhileDead : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "The dialog was advanced while awaiting a player choice or exhausted.";
        }
    };

    // class ChooseWhileNotAwaitingChoice : public std::exception{
    // public:
    //     [[nodiscard]] const char * what() const noexcept override {
    //         return "The dialog choose method was called while not awaiting a player choice.";
    //     }
    // };


    class Dialog {
    public:
        using index = unsigned int;

        enum Status {
            ALIVE,
            AWAITING_CHOICE,
            EXHAUSTED
        };

    public :
        [[nodiscard]] std::vector<std::vector<NPCLine> > getNPCLines() const {
            return NPC_lines;
        }

        [[nodiscard]] std::vector<PlayerLine> getPlayerLines() const {
            return player_lines;
        }

        [[nodiscard]] Quests::Math::AdjacencyListDirectedGraph<index, index> getTopology() const {
            return topology;
        }

    protected:
        /**
         * The name is a bit misleading : an option which is hidden from the player is still present in this.
         */
        std::vector<PlayerLine> presented_options = {};

        std::vector<std::vector<NPCLine> > NPC_lines;
        std::vector<PlayerLine> player_lines;

        Quests::Math::AdjacencyListDirectedGraph<index, index> topology;

        index current_stack = 0;
        index current_line_in_stack = 0;

    public:
        std::function<void(std::vector<PlayerLine>)> present_choices_to_player;
        std::function<void(NPCLine)> present_NPC_line;

        Dialog(
            std::vector<std::vector<NPCLine> > NPC_lines,
            std::vector<PlayerLine> player_lines,
            const Quests::Math::AdjacencyListDirectedGraph<index, index> &topology,
            index starting_stack_index = 0
        )
            : NPC_lines(std::move(NPC_lines)),
              player_lines(std::move(player_lines)),
              topology(topology),
              current_stack(starting_stack_index) {
        }

        /**
         * Advances the dialog.
         * If the dialog is awaiting player input, throws AdvanceWhileAwaitingChoice
         */
        void advance();

        [[nodiscard]] NPCLine getCurrentLine() const;

        /**
         * @return true iff the presented_answer vector is not empty (we are awaiting a player answer)
         */
        [[nodiscard]] Status getStatus() const;


        /**
         * @return the answers the player must choose from that are blocking the dialog
         */
        [[nodiscard]] std::vector<PlayerLine> getPlayerAnswers() const;

        /**
         * Chooses an option that the dialog presented to the player
         * @param chosen_index the index of the option.
         * If < 0 or >= than the number of choices, throws std::out_of_range
         */
        void choose(int chosen_index);

        /**
         * Resets the NPC conversation to the beginning of the last stack
         * (if no choice is being made, in which case this does nothing)
         */
        void softReset();

    public:
    };
}
