# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# ===============================================================
# SYSTEM
# ===============================================================
  export PS1="\u@\h \w> "
  export PATH=$PATH:$HOME/bin
  export CSCOPE_EDITOR=vim

# ===============================================================
# GIT Prompt Configuration
# ===============================================================
  source ~/git-prompt.sh
  export GIT_PS1_SHOWCOLORHINTS=true
  export PS1='\[\033[1;36m\]\u@\h:\[\033[0m\]\[\033[1;34m\]\w\[\033[0m\] \[\033[1;32m\]$(__git_ps1)\[\033[0m\]\$ '

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
# tmux
  alias tmux="TERM=screen-256color tmux"
  alias tmuxo='tmux new -s suman'
  alias tmuxa='tmux attach'
  alias tmuxl='tmux list-sessions'
  alias tmuxk='tmux kill-session -t suman'

# ===============================================================
# COMMAND ALIAS
# ===============================================================
  export GOPATH=~/go
  export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin

# utility
# alias cdlab='cd ~ && date &&
#              cd laboratory/ &&
#              git br'

