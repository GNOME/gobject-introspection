FROM fedora:41

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
    python3-lxml \
    python3-packaging \
    python3-pip \
    python3-rnc2rng \
    python3-setuptools \
    python3-wheel \
    zlib-devel \
 && dnf clean all

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8
ENV PATH="/usr/bin:/home/user/.local/bin"

RUN pip3 install --user meson==1.4.2
