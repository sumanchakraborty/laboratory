# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# ===============================================================
# ENVIRONMENT
# ===============================================================
neofetch

# ===============================================================
# COMMAND ALIAS
# ===============================================================
# tmux
  alias tmux="TERM=screen-256color tmux"
  alias tmuxo='tmux new -s suman'
  alias tmuxa='tmux attach'
  alias tmuxl='tmux list-sessions'
  alias tmuxk='tmux kill-session -t suman'
# golang
  export PATH=$PATH:/usr/local/go/bin

