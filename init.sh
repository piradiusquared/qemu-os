# Prepare build:
sudo apt-get update
sudo apt-install build-essential
sudo apt-install bison
sudo apt-install flex
sudo apt-install libgmp3-dev
sudo apt-install libmpc-dev
sudo apt-install libmpfr-dev
sudo apt-install texinfo

sudo apt-get install curl # For online packages

export PREFIX="$HOME"/opt/cross
export TARGET=i686-elf
export PATH="$PREFIX"/bin:$PATH"

mkdir /tmp/src
cd /tmp/src