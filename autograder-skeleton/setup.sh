
# googletest
apt-get -y install build-essential cmake libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib

# other packages
apt-get -y install python3.8 clang
