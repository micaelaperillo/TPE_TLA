#! /bin/bash

set -euxo pipefail

BASE_PATH="$(dirname "$0")/../.."
cd "$BASE_PATH"

sudo apt-get install bison --yes
sudo apt-get install cmake --yes
sudo apt-get install flex --yes
sudo apt-get install gcc --yes
sudo apt-get install make --yes
pip3 install pygame 
pip3 install numpy 
pip3 install tk 

echo "All done."
