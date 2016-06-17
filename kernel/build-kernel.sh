#!/bin/bash

# yum install net-tools dos2unix vim cscope kernel-devel rpmdevtools
# yum install ncurses-devel qt3-devel libXi-devel gcc-c++
# yum install bison bc xmlto asciidoc hmaccalc pesign 
# yum install binutils-devel newt-devel python-devel 
# yum install audit-libs-devel numactl-devel pciutils-devel
# yum install rpm-build redhat-rpm-config perl perl-ExtUtils-Embed
# yum install elfutils-devel elfutils-libelf-devel zlib-devel

# rpm -Uvh kernel-<version>.src.rpm
# cd rpmbuild

# vim SPECS/kernel.spec
# %define buildid .suman

# rm -rf tmp && mkdir tmp
# cp SOURCES/linux-3.10.0-123.el7.tar.xz tmp/

# tar -xvJf tmp/linux-3.10.0-123.el7.tar.xz -C tmp/
# <edit> tmp/linux-3.10.0-123.el7
  rm -rf SOURCES/linux-3.10.0-123.el7.tar.xz
  tar -cvJf SOURCES/linux-3.10.0-123.el7.tar.xz -C tmp/ linux-3.10.0-123.el7
  rpmbuild -ba --with baseonly --without debuginfo --target=`uname -m` SPECS/kernel.spec
  rpm -ivh --force RPMS/x86_64/kernel-3.10.0-123.el7.suman.x86_64.rpm

