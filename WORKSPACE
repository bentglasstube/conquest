git_repository(
    name = "libgam",
    remote = "https://github.com/bentglasstube/gam.git",
    commit = "a7556b0d8b5a8a130253c428ac253c7da35b062d",
)

git_repository(
    name = "mxebzl",
    remote = "https://github.com/cfrantz/mxebzl.git",
    tag = "20170703_RC03",
)

load("@mxebzl//tools:repository.bzl", "mxe_compilers")
mxe_compilers(
    deps = [
        "compiler",
        "SDL2",
        "SDL2-extras",
        "bzip2",
        "freetype-bootstrap",
        "gettext",
        "glib",
        "harfbuzz",
        "libiconv",
        "pcre",
        "xz",
    ],
)
