FROM fedora:28

RUN dnf -y install \
    bison \
    cairo-devel \
    cairo-gobject-devel \
    ccache \
    chrpath \
    desktop-file-utils \
    elfutils-libelf-devel \
    flex \
    fontconfig-devel \
    freetype-devel \
    gcc \
    gcc-c++ \
    gettext \
    git \
    glib2-devel \
    glibc-devel \
    glibc-headers \
    gtk-doc \
    itstool \
    libXft-devel \
    libXfixes-devel \
    libattr-devel \
    libffi-devel \
    libmount-devel \
    libselinux-devel \
    libxml2-devel \
    libxslt \
    mesa-libGL-devel \
    ninja-build \
    pcre-devel \
    python3 \
    python3-devel \
    python3-mako \
    python3-pip \
    python3-wheel \
    python2 \
    python2-devel \
    python2-mako \
    redhat-rpm-config \
    systemtap-sdt-devel \
    zlib-devel \
 && dnf clean all

RUN pip3 install meson==0.47.1

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8
