FROM rhub/fedora-clang

RUN dnf -y install git
RUN dnf install dnf-plugins-core
RUN dnf -y copr enable vbatts/bazel
RUN dnf -y install bazel4
