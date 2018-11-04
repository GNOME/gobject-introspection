FROM fedora:28

RUN dnf -y install \
    autoconf \
    autoconf-archive \
    automake \
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
    libtool \
    libXft-devel \
    libXfixes-devel \
    libattr-devel \
    libffi-devel \
    libmount-devel \
    libselinux-devel \
    libxml2-devel \
    libxslt \
    make \
    mesa-libGL-devel \
    ninja-build \
    pcre-devel \
    python3 \
    python3-devel \
    python3-mako \
    python3-markdown \
    python3-pip \
    python3-wheel \
    redhat-rpm-config \
    systemtap-sdt-devel \
    zlib-devel \
 && dnf clean all

RUN pip3 install meson==0.48.0

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8
