#! /bin/bash

# GradeScope tech support workaround for glibc bug
# (https://bugs.launchpad.net/ubuntu/+source/glibc/+bug/1962606)
mv /bin/uname /bin/uname.orig
printf '#!/bin/bash\n\nif [[ "$1" == "-r" ]] ;then\n echo '4.9.250'\n exit\nelse\n uname.orig "$@"\nfi' > /bin/uname
chmod 755 /bin/uname

# update packages
apt-get -y update
apt-get -y upgrade
apt-get -y dist-upgrade

# googletest
apt-get -y install build-essential cmake libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib

# other packages
apt-get -y install python3.8 clang
