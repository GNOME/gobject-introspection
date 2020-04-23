FROM fedora:29

RUN dnf -y install \
    flex \
    bison \
    gcc \
    gcc-c++ \
    git \
    ninja-build \
    pkgconf \
    python3 \
    python3-devel \
    python3-pip \
    python3-wheel \
    libmount-devel \
 && dnf clean all

RUN pip3 install meson==0.54.0

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8
