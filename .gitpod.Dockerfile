FROM gitpod/workspace-full

RUN sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    sudo apt update && sudo apt install -y gcc-11 g++-11 && \
    sudo update-alternatives --remove-all cpp && \
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110 --slave /usr/bin/g++ g++ /usr/bin/g++-11 --slave /usr/bin/gcov gcov /usr/bin/gcov-11 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-11 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-11  --slave /usr/bin/cpp cpp /usr/bin/cpp-11

RUN sudo apt install -y silversearcher-ag entr