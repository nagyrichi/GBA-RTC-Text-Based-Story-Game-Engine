#include "story.h"

const Node nodes[] =
{
    {
        "MILA",
        {
            "Emergency channel open.",
            "Can anyone hear me?",
            "My ship crashed.",
            "",
            ""
        },
        3,
        "Respond",
        "Ignore",
        1, 2,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Thank god.",
            "I thought I was",
            "completely alone.",
            "",
            ""
        },
        3,
        "Ask status",
        "Ask location",
        3, 4,
        false, 0,
        false, false
    },

    {
        "SYSTEM",
        {
            "Signal lost.",
            "Hours later the",
            "device vibrates.",
            "",
            ""
        },
        3,
        "Check message",
        "Sleep",
        5, 6,
        true, 120,
        false, false
    },

    {
        "MILA",
        {
            "Life support works.",
            "Food for maybe",
            "two more days.",
            "",
            ""
        },
        3,
        "Search supplies",
        "Stay inside",
        7, 8,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I crashed on",
            "Khepri-4.",
            "Red desert planet.",
            "",
            ""
        },
        3,
        "Search map",
        "Ask about crew",
        9, 10,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "New message:",
            "I found lights",
            "near the canyon.",
            "",
            ""
        },
        3,
        "Go there",
        "Avoid it",
        11, 12,
        false, 0,
        false, false
    },

    {
        "SYSTEM",
        {
            "Battery empty.",
            "Signal terminated.",
            "",
            "",
            ""
        },
        2,
        "",
        "",
        0, 0,
        false, 0,
        true, false
    },

    {
        "MILA",
        {
            "There is an old",
            "cargo station",
            "one hour away.",
            "",
            ""
        },
        3,
        "Travel there",
        "Stay safe",
        13, 8,
        true, 300,
        false, false
    },

    {
        "MILA",
        {
            "The storm outside",
            "is getting worse.",
            "I will wait.",
            "",
            ""
        },
        3,
        "Wait too",
        "Force travel",
        14, 15,
        true, 300,
        false, false
    },

    {
        "MILA",
        {
            "The map shows",
            "a research dome",
            "in the north.",
            "",
            ""
        },
        3,
        "Investigate",
        "Ignore",
        16, 17,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "No survivors.",
            "Only automated",
            "distress beacons.",
            "",
            ""
        },
        3,
        "Keep exploring",
        "Return to ship",
        18, 19,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The lights belong",
            "to solar towers.",
            "Power still works.",
            "",
            ""
        },
        3,
        "Restore systems",
        "Rest here",
        20, 21,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I stayed away.",
            "But now I wonder",
            "what was there.",
            "",
            ""
        },
        3,
        "Go back",
        "Move on",
        11, 22,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I reached the",
            "cargo station.",
            "Doors still open.",
            "",
            ""
        },
        3,
        "Search inside",
        "Check outside",
        23, 24,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The storm passed.",
            "The sky looks",
            "beautiful now.",
            "",
            ""
        },
        3,
        "Continue journey",
        "Stay and watch",
        13, 25,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The research dome",
            "still has oxygen.",
            "Someone lived here.",
            "",
            ""
        },
        3,
        "Search records",
        "Search supplies",
        26, 27,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Maybe that was",
            "the safer choice.",
            "Hard to know.",
            "",
            ""
        },
        3,
        "Continue",
        "Rest",
        18, 21,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I found another",
            "distress signal.",
            "Much weaker.",
            "",
            ""
        },
        3,
        "Track signal",
        "Ignore signal",
        28, 29,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Back at the ship.",
            "Fuel cells almost",
            "fully depleted.",
            "",
            ""
        },
        3,
        "Repair ship",
        "Leave again",
        30, 18,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Power restored.",
            "Long range comms",
            "might work now.",
            "",
            ""
        },
        3,
        "Send distress",
        "Wait first",
        31, 32,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Quiet at last.",
            "I almost forgot",
            "how silence feels.",
            "",
            ""
        },
        3,
        "Sleep",
        "Keep watch",
        33, 34,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I crossed the",
            "canyon safely.",
            "The stars are huge.",
            "",
            ""
        },
        3,
        "Continue",
        "Camp here",
        18, 35,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Outside the station",
            "I found rover",
            "tracks in sand.",
            "",
            ""
        },
        3,
        "Follow tracks",
        "Ignore them",
        36, 22,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Inside: supplies,",
            "water filters and",
            "working batteries.",
            "",
            ""
        },
        3,
        "Take supplies",
        "Leave them",
        37, 24,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The desert is calm.",
            "No movement anywhere.",
            "Just wind.",
            "",
            ""
        },
        3,
        "Travel north",
        "Return inside",
        16, 23,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I stayed for hours",
            "watching the sky.",
            "Worth it.",
            "",
            ""
        },
        3,
        "Continue tomorrow",
        "Stay longer",
        13, 35,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Logs mention an",
            "orbital rescue",
            "window tomorrow.",
            "",
            ""
        },
        3,
        "Prepare beacon",
        "Ignore logs",
        31, 29,
        true, 600,
        false, false
    },

    {
        "MILA",
        {
            "Food secured.",
            "That buys me",
            "another week.",
            "",
            ""
        },
        3,
        "Keep exploring",
        "Return ship",
        18, 19,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The signal comes",
            "from an abandoned",
            "survey drone.",
            "",
            ""
        },
        3,
        "Recover drone",
        "Leave it",
        38, 29,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Maybe ignoring it",
            "was the right",
            "decision after all.",
            "",
            ""
        },
        3,
        "Continue",
        "Rest",
        18, 21,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The engines respond.",
            "Not enough for lift,",
            "but enough for heat.",
            "",
            ""
        },
        3,
        "Keep repairing",
        "Stop work",
        39, 21,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Distress beacon sent.",
            "Now we wait.",
            "",
            "",
            ""
        },
        2,
        "Wait for rescue",
        "Keep moving",
        40, 18,
        true, 900,
        false, false
    },

    {
        "MILA",
        {
            "I should conserve",
            "battery power.",
            "I will contact later.",
            "",
            ""
        },
        3,
        "Wait",
        "Send now",
        31, 31,
        true, 600,
        false, false
    },

    {
        "SYSTEM",
        {
            "Connection lost",
            "during the night.",
            "",
            "",
            ""
        },
        2,
        "",
        "",
        0, 0,
        false, 0,
        true, false
    },

    {
        "MILA",
        {
            "Nothing happened.",
            "But the sunrise",
            "looks incredible.",
            "",
            ""
        },
        3,
        "Continue",
        "Stay here",
        18, 35,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "I camped beneath",
            "the cliffs tonight.",
            "I feel peaceful.",
            "",
            ""
        },
        3,
        "Sleep",
        "Travel onward",
        33, 18,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The rover tracks",
            "lead to a hidden",
            "observation post.",
            "",
            ""
        },
        3,
        "Enter post",
        "Keep walking",
        41, 18,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Supplies loaded.",
            "Survival chances",
            "now much higher.",
            "",
            ""
        },
        3,
        "Keep exploring",
        "End expedition",
        18, 42,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The drone still",
            "contains star maps",
            "and weather data.",
            "",
            ""
        },
        3,
        "Use data",
        "Ignore data",
        43, 18,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The reactor warms",
            "the cabin again.",
            "I might survive.",
            "",
            ""
        },
        3,
        "Keep trying",
        "Accept fate",
        31, 44,
        false, 0,
        false, false
    },

    {
        "SYSTEM",
        {
            "Rescue signal",
            "detected nearby.",
            "Ship approaching.",
            "",
            ""
        },
        3,
        "Answer signal",
        "Stay silent",
        45, 46,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "Inside the post:",
            "working telescope",
            "and fresh water.",
            "",
            ""
        },
        3,
        "Stay there",
        "Leave post",
        47, 18,
        false, 0,
        false, false
    },

    {
        "SYSTEM",
        {
            "Expedition ended.",
            "Signal archived.",
            "",
            "",
            ""
        },
        2,
        "",
        "",
        0, 0,
        false, 0,
        true, true
    },

    {
        "MILA",
        {
            "The maps reveal",
            "safe routes across",
            "the entire planet.",
            "",
            ""
        },
        3,
        "Keep exploring",
        "Prepare rescue",
        18, 31,
        false, 0,
        false, false
    },

    {
        "MILA",
        {
            "The cold finally",
            "overcomes the ship.",
            "Signal fading.",
            "",
            ""
        },
        3,
        "",
        "",
        0, 0,
        false, 0,
        true, false
    },

    {
        "SYSTEM",
        {
            "Rescue successful.",
            "Mila survived.",
            "Connection closed.",
            "",
            ""
        },
        3,
        "",
        "",
        0, 0,
        false, 0,
        true, true
    },

    {
        "SYSTEM",
        {
            "No response sent.",
            "Rescue ship leaves",
            "orbit silently.",
            "",
            ""
        },
        3,
        "",
        "",
        0, 0,
        false, 0,
        true, false
    },

    {
        "MILA",
        {
            "I think I will",
            "stay here awhile.",
            "This world is quiet.",
            "",
            ""
        },
        3,
        "",
        "",
        0, 0,
        false, 0,
        true, true
    }
};

const int node_count = sizeof(nodes) / sizeof(nodes[0]);
