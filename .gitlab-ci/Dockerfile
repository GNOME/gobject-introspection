FROM fedora:27

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
    meson \
    pcre-devel \
    python3-devel \
    python3-mako \
    systemtap-sdt-devel \
    zlib-devel

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.utf8
