FROM fedora:34

RUN dnf -y install \
    flex \
    bison \
    gcc \
    gcc-c++ \
    git \
    libmount-devel \
    ninja-build \
    pcre-devel \
    pkgconf \
    python3 \
    python3-devel \
    python3-pip \
    python3-wheel \
 && dnf clean all

RUN pip3 install meson==0.58.2

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8
