workspace(name="dxball")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "sfml",
    urls = ["https://github.com/SFML/SFML/archive/refs/tags/2.6.1.tar.gz"],
    sha256 = "82535db9e57105d4f3a8aedabd138631defaedc593cab589c924b7d7a11ffb9d",
    build_file = "//third_party:sfml.BUILD.bazel",
    strip_prefix = "SFML-2.6.1",
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "476303bd0f1b04cc311fc258f1708a5f6ef82d3091e53fd1977fa20383425a6a",
    strip_prefix = "rules_foreign_cc-0.10.1",
    url = "https://github.com/bazelbuild/rules_foreign_cc/releases/download/0.10.1/rules_foreign_cc-0.10.1.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.10.1/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()
