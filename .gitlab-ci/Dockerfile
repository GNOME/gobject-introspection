FROM fedora:29

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
    libattr-devel \
    libffi-devel \
    libmount-devel \
    libselinux-devel \
    libtool \
    libXfixes-devel \
    libXft-devel \
    libxml2-devel \
    libxslt \
    make \
    mesa-libGL-devel \
    ninja-build \
    openssl-devel \
    pcre-devel \
    python3 \
    python3-devel \
    python3-pip \
    python3-wheel \
    readline-devel \
    redhat-rpm-config \
    sqlite-devel \
    systemtap-sdt-devel \
    zlib-devel \
 && dnf clean all

RUN pip3 install meson==0.50.1

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

USER user
WORKDIR /home/user

ENV LANG C.UTF-8

ENV PYENV_ROOT /home/user/.pyenv
ENV PATH="${PYENV_ROOT}/shims:${PYENV_ROOT}/bin:${PATH}"
ENV PYTHON_CONFIGURE_OPTS="--enable-shared"
RUN curl -L https://raw.githubusercontent.com/pyenv/pyenv-installer/master/bin/pyenv-installer | bash
RUN pyenv install 3.5.6
