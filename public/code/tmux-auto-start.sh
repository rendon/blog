[[ $- != *i* ]] && return
[[ $TERM != screen* ]] && exec tmux -2
