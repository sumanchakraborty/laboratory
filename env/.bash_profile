# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# ===============================================================
# SYSTEM
# ===============================================================
# oldPS1=$PS1
# oldPS2=$PS2
# export PS1="suman>"
  export PS1="\u@\h \w> "
  export PATH=$PATH:$HOME/bin

# ===============================================================
# GIT Prompt Configuration
# ===============================================================
# export GIT_PS1_SHOWDIRTYSTATE=1
# export GIT_PS1_SHOWCOLORHINTS=1
# export GIT_PS1_SHOWUNTRACKEDFILES=1
# export PS1='\[\033[1;36m\]\u@\h:\[\033[0m\]\[\033[1;34m\]\w\[\033[0m\] \[\033[1;32m\]$(__git_ps1)\[\033[0m\]\$ '

# ===============================================================
# ENVIRONMENT VARIABLES
# ===============================================================
# export P4USER=schakraborty
# export P4PORT=ixin-cm-vmp4proxy:1999
# export P4CLIENT=ixin-golf-Suman
# export PKGGET_DEPOTS=/mnt/ixiasw_tmp\&/mnt/ixiasw3
# export P4DIFF=vimdiff

# ===============================================================
# COMMAND ALIAS
# ===============================================================
# system
  alias ..='cd ..'
  alias ll='ls -lahGFh'
  alias vi='vim'
# screen
  alias screenx='screen -x'                 # attach
  alias screenr='screen -r'                 # resume
  alias screenl='screen -ls'
  alias screeno='screen -S suman'
  alias screenc='screen -S suman -X quit'
# build
# alias ixvm='cd perforce-bps/ixvm/ &&
#             source p4env &&
#             cd bpslinuxcontroller/main/'
# alias cdvm='cd perforce-bps/bps-vm/ &&
#             source p4env &&
#             cd main/tests/libsoftnp/'
# alias cdps='cd perforce-bps/bps-ps/ &&
#             source p4env &&
#             cd main/tests/libsoftnp/'
# alias cdfs='cd perforce-bps/bps-fs/ &&
#             source p4env &&
#             cd main/tests/libsoftnp/'

