
# ===============================================================
# PROMPT
# ===============================================================
# oldPS1=$PS1
# oldPS2=$PS2
  export PS1="suman>"
# export PS1="\u@\h \w> "

# ===============================================================
# ENVIRONMENT VARIABLES
# ===============================================================
  export P4USER=schakraborty
  export P4PORT=ixin-cm-vmp4proxy:1999
  export P4CLIENT=ixin-golf-Suman
  export PKGGET_DEPOTS=/mnt/ixiasw_tmp\&/mnt/ixiasw3
  export P4DIFF=vimdiff

# ===============================================================
# COMMAND ALIAS
# ===============================================================
# system
  alias ..='cd ..'
  alias ll='ls -lahGFh'
  alias vi='vim'
# screen
  alias screenl='screen -ls'
  alias screeno='screen -S suman'
  alias screenc='screen -S suman -X quit'
# build
  alias clean='rm -rf ixload_tarballs &&
               rm -rf out &&
               rm -rf *.pyc &&
               rm -rf *_release &&
               rm -rf *_debug'
  alias build='clean && 
               sh build.sh . out'

# alias buildd='scons build=debug ixload_tarballs/IxLoad_framework.tar ixload_tarballs/nfsClient.tar ixload_tarballs/IxLoadAuto.tar'
# alias buildr='scons build=release ixos=yes -j 5 ixload_tarballs/IxLoad_framework.tar ixload_tarballs/nfsClient.tar ixload_tarballs/IxLoadAuto.tar'
# alias buildv='scons build=debug valgrind=yes ixload_tarballs/IxLoad_framework.tar ixload_tarballs/nfsClient.tar ixload_tarballs/IxLoadAuto.tar'
# alias builda='scons build=debug asdfalloc=yes ixload_tarballs/IxLoad_framework.tar ixload_tarballs/nfsClient.tar ixload_tarballs/IxLoadAuto.tar'
