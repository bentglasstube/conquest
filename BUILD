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
    name = "email_screen",
    srcs = ["email_screen.cc"],
    hdrs = ["email_screen.h"],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:font",
        "@libgam//:screen",
        ":game_state",
        ":generators",
        ":lobby_screen",
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
    name = "lobby_screen",
    srcs = ["lobby_screen.cc"],
    hdrs = ["lobby_screen.h"],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        ":game_state",
    ],
)

cc_library(
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        "@libgam//:text",
        ":email_screen",
        ":game_state",
    ],
)
