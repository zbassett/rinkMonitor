#!/bin/bash


INSTALL_DIR="/tmp/rf24libs"

mkdir ${INSTALL_DIR}

ROOT_PATH=${INSTALL_DIR}

DORF24=0
DORF24Network=0
DORF24Mesh=0
DORF24Gateway=0

echo""
echo "RF24 libraries installer by TMRh20"
echo "report issues at https://github.com/TMRh20/RF24/issues"
echo ""
echo "******************** NOTICE **********************"
echo "Installer will create an 'rf24libs' folder for installation of selected libraries"
echo "To prevent mistaken deletion, users must manually delete existing library folders within 'rf24libs' if upgrading"
echo "Run 'sudo rm -r rf24libs' to clear the entire directory"
echo ""
echo ""

echo "Installing RF24 Repo..."
echo ""
git clone https://github.com/tmrh20/RF24.git ${ROOT_PATH}/RF24
# echo '/usr/local/lib/arm-linux-gnueabihf' >> /etc/ld.so.conf
# ldconfig
#  exec /tmp/rf24libs/RF24/configure --driver=MRAA --extra-cflags=-marm
# # sed -i 's/-pthread/-pthread -marm/g' ${ROOT_PATH}/RF24/Makefile.inc

# echo "about to install..."

# make install /tmp/rf24libs/RF24
# echo ""

# echo "Installing RF24Network_DEV Repo..."
# echo "about to clone..."
# git clone https://github.com/tmrh20/RF24Network.git ${ROOT_PATH}/RF24Network
# echo "about to make install..."
# make -C ${ROOT_PATH}/RF24Network
# make install -B -C ${ROOT_PATH}/RF24Network
# echo ""

# echo "Installing RF24Mesh Repo..."
# echo ""
# git clone https://github.com/tmrh20/RF24Mesh.git ${ROOT_PATH}/RF24Mesh
# echo ""
# make install -B -C ${ROOT_PATH}/RF24Mesh
# echo ""



# echo ""
# echo ""
# echo "*** Installer Complete ***"
# echo "See http://tmrh20.github.io for documentation"
# echo "See http://tmrh20.blogspot.com for info "
# echo ""
# echo "Listing files in install directory:"
ls ${ROOT_PATH}