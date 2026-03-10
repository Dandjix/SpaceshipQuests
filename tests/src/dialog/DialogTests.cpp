//
// Created by timon on 3/9/26.
//

#include <gtest/gtest.h>

#include "quests/dialogs/dialog/Dialog.h"
#include "quests/dialogs/lines/NPCLine.h"
#include "quests/dialogs/lines/PlayerLine.h"

// #include "dialogs/dialog/Dialog.h"

TEST(DialogTestSuite, SimpleDialogFlowTest) {

    auto lines_1 = std::vector{ //0
        Dialogs::NPCLine("Have you heard of the high elves ?"),
        Dialogs::NPCLine("What am I saying ? Of course you didn't."),
    };

    auto answers_1 = std::vector{
        Dialogs::PlayerLine("I love you."), //0
        Dialogs::PlayerLine("I will personally shove 50 potatoes up your *** if you don't give me access right now"), //1
    };

    auto lines_2 = std::vector{ //1
        Dialogs::NPCLine("No homo tho amirite ?"),
    };

    auto lines_3 = std::vector{//2
        Dialogs::NPCLine("..."),
        Dialogs::NPCLine("*Dies of cringe*"),
    };

    auto topology = Quests::Math::AdjacencyListDirectedGraph<Dialogs::Dialog::index,Dialogs::Dialog::index>();

    //refer to the numbers in comments next to the npc and player lines declarations
    topology.addVertex(0);
    topology.addVertex(1);
    topology.addVertex(2);
    topology.addEdge(0,1,0);
    topology.addEdge(0,2,1);

    struct Player {
        std::vector<Dialogs::Dialog::index> npc_lines;
        std::vector<Dialogs::Dialog::index> player_lines;
    };

    Player player ={};

    Dialogs::Dialog dialog = {
        {lines_1,lines_2,lines_3},
        answers_1,
        topology
    };

    ASSERT_EQ(dialog.getCurrentLine().line_key,"Have you heard of the high elves ?");
    ASSERT_EQ(dialog.getStatus(),Dialogs::Dialog::ALIVE);

    dialog.advance();

    ASSERT_EQ(dialog.getCurrentLine().line_key,"What am I saying ? Of course you didn't.");
    ASSERT_EQ(dialog.getStatus(),Dialogs::Dialog::AWAITING_CHOICE);

    ASSERT_THROW(dialog.advance(),Dialogs::AdvanceWhileDead);
    dialog.choose(1);

    ASSERT_EQ(dialog.getCurrentLine().line_key,"...");
    ASSERT_EQ(dialog.getStatus(),Dialogs::Dialog::ALIVE);

    dialog.advance();

    ASSERT_EQ(dialog.getCurrentLine().line_key,"*Dies of cringe*");
    ASSERT_EQ(dialog.getStatus(),Dialogs::Dialog::EXHAUSTED);

    ASSERT_THROW(dialog.advance(),Dialogs::AdvanceWhileDead);
}