#!/bin/bash

INSTALL_PATH="."
INSTALL_DIR="/rf24libs"

ROOT_PATH=${INSTALL_PATH}
ROOT_PATH+=${INSTALL_DIR}

DORF24=1
DORF24Network=1
DORF24Mesh=1
DORF24Gateway=1

## pretty ugly
git config --global http.sslVerify false

echo""
echo "RF24 libraries installer by TMRh20"
echo "report issues at https://github.com/TMRh20/RF24/issues"
echo ""
echo "******************** NOTICE **********************"
echo "Installer will create an 'rf24libs' folder for installation of selected libraries"
echo "To prevent mistaken deletion, users must manually delete existing library folders within 'rf24libs' if upgrading"
echo "Run 'rm -r rf24libs' to clear the entire directory"
echo ""
echo "** This is a modified script to build a Docker image - Updated by KSE **"

if [[ $DORF24Gateway > 0 ]]
then
	echo ""
	echo "Install ncurses library (Recommended for RF24Gateway)"
    apt-get install -y libncurses5-dev
	echo ""
fi

if [[ $DORF24 > 0 ]]
then
	echo "Installing RF24 Repo..."
	echo ""
	git clone https://github.com/tmrh20/RF24.git ${ROOT_PATH}/RF24
    sed -i 's/-march=armv6zk/-marm/g' ${ROOT_PATH}/RF24/configure
	echo ""
	make install -C ${ROOT_PATH}/RF24
    
	echo ""
fi

if [[ $DORF24Network > 0 ]]
then
	echo "Installing RF24Network_DEV Repo..."
	echo ""
	git clone -b Development https://github.com/tmrh20/RF24Network.git ${ROOT_PATH}/RF24Network
	echo ""
	make install -C ${ROOT_PATH}/RF24Network
	echo ""
fi

if [[ $DORF24Mesh > 0 ]]
then
	echo "Installing RF24Mesh Repo..."
	echo ""
	git clone https://github.com/tmrh20/RF24Mesh.git ${ROOT_PATH}/RF24Mesh
    sed -i 's/NETWORK_DEFAULT_ADDRESS/04444/g' ${ROOT_PATH}/RF24Mesh/RF24Mesh_config.h
	echo ""
	make install -C ${ROOT_PATH}/RF24Mesh
	echo ""
fi

# if [[ $DORF24Gateway > 0 ]]
# then
# 	echo "Installing RF24Gateway Repo..."
# 	echo ""
# 	git clone https://github.com/tmrh20/RF24Gateway.git ${ROOT_PATH}/RF24Gateway
# #     cp /tmp/Makefile.inc ${ROOT_PATH}/RF24Gateway
# 	echo ""

#     echo "Changing RPi CE and CSN pins"
#     ed -s rf24libs/RF24Gateway/examples/ncurses/RF24Gateway_ncurses.cpp <<< $'/RF24 radio/s/22,0/25,8/g\nw'
# 	make install -C ${ROOT_PATH}/RF24Gateway
	
#     #echo ""; echo -n "Build an RF24Gateway example"
#     #make -B -C${ROOT_PATH}/RF24Gateway/examples/ncurses; echo ""; echo "Complete, to run the example, cd to rf24libs/RF24Gateway/examples/ncurses and enter  sudo ./RF24Gateway_ncurses";;
# fi
echo ""
echo ""
echo "*** Installer Complete ***"
echo "See http://tmrh20.github.io for documentation"
echo "See http://tmrh20.blogspot.com for info "
echo ""