package(default_visibility = ["//visibility:public"])

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

config_setting(
    name = "windows",
    values = {
        "crosstool_top": "@mxebzl//tools/windows:toolchain",
    }
)

cc_binary(
    name = "conquest",
    data = ["//content"],
    linkopts = select({
        ":windows": ["-mwindows", "-lSDL2main" ],
        "//conditions:default": [],
    }) + [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-lSDL2_ttf",
        "-static-libstdc++",
        "-static-libgcc",
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
        "arm_screen.cc",
        "email_screen.cc",
        "four_screen.cc",
        "lobby_screen.cc",
        "minigame_screen.cc",
        "rps_screen.cc",
    ],
    hdrs = [
        "arm_screen.h",
        "email_screen.h",
        "four_screen.h",
        "lobby_screen.h",
        "minigame_screen.h",
        "rps_screen.h",
    ],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:font",
        "@libgam//:screen",
        "@libgam//:sprite",
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

pkg_winzip(
    name = "conquest-windows",
    files = [
        ":conquest",
        "//content",
    ],
)

pkg_tar(
    name = "conquest-linux",
    extension = "tar.gz",
    strip_prefix = "/",
    package_dir = "conquest/",
    srcs = [
        ":conquest",
        "//content",
    ],
)
