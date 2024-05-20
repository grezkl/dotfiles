source $XDG_CONFIG_HOME/zsh/fsph_prompt.sh

if [ -n "$BASH_VERSION" ]; then
    if [ "$UID" -eq 0 ]; then
        export PS1='\[\e[01;31m\]\u@\h\[\e[00m\]:\[\e[01;34m\]\w\[\e[00m\]\# '
    else
        export PS1='\[\e[01;32m\]\u@\h\[\e[00m\]:\[\e[01;34m\]\w\[\e[00m\]\$ '
    fi
else
    if [ "$UID" -eq 0 ]; then
        export PROMPT='%F{9}%n@%m%f:%F{12}%~%f%# '
    else
        autoload -Uz vcs_info
        precmd_vcs_info() { vcs_info }
        precmd_functions+=( precmd_vcs_info )
        zstyle ':vcs_info:git:*' formats '%F{11}[%b]'
        zstyle ':vcs_info:*' enable git
        # λ
        export PROMPT='%F{12}[%*] %F{1}%n%F{8}@%F{10}%m %F{9}%F{3}$(_fish_collapsed_pwd)%F{14}>%f%  '
        export RPROMPT='%(?.. %F{1}✘ %?) $vcs_info_msg_0_'

    fi
fi
