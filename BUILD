package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "ld37",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-lSDL2_ttf",
    ],
    srcs = ["main.cc"],
    deps = [
        ":title_screen",
        "@libgam//:game",
    ],
)

cc_library(
    name = "appearing_text",
    srcs = ["appearing_text.cc"],
    hdrs = ["appearing_text.h"],
    deps = [
        "@libgam//:audio",
        "@libgam//:font",
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "game_screens",
    srcs = [
        "email_screen.cc",
        "lobby_screen.cc",
        "minigame_screen.cc",
        "rps_screen.cc",
    ],
    hdrs = [
        "email_screen.h",
        "lobby_screen.h",
        "minigame_screen.h",
        "rps_screen.h",
    ],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:font",
        "@libgam//:screen",
        "@libgam//:spritemap",
        ":appearing_text",
        ":game_state",
        ":generators",
        ":person",
    ],
)

cc_library(
    name = "game_state",
    srcs = ["game_state.cc"],
    hdrs = ["game_state.h"],
)

cc_library(
    name = "generators",
    srcs = ["generators.cc"],
    hdrs = ["generators.h"],
)

cc_library(
    name = "person",
    srcs = ["person.cc"],
    hdrs = ["person.h"],
    deps = [
        "@libgam//:spritemap",
    ],
)

cc_library(
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:font",
        "@libgam//:screen",
        ":game_screens",
        ":game_state",
    ],
)
