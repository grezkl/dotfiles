eval $(thefuck --alias)

export LESS="--RAW-CONTROL-CHARS"
[[ -f $XDG_CONFIG_HOME/zsh/LESS_TERMCAP ]] && . $XDG_CONFIG_HOME/zsh/LESS_TERMCAP

alias fw='export ALL_PROXY=socks5://127.0.0.1:10889'
alias uv='unset ALL_PROXY'
alias pyay='ALL_PROXY=socks5://127.0.0.1:10889 yay'
alias cip='curl cip.cc'
alias wea='curl wttr.in/shenzhen'
alias ctg='ctags -R --c++-kinds=+px --fields=+niazs --extras=+q -f .tags'
alias clg='clang++ -O2 -std=c++14 -Weverything -Wno-c++98-compat'
alias clgm='fn() { clang++ -O2 -std=c++14 -Weverything -Wno-c++98-compat $2 $3 $4 -o $1 -lmuduo_net -lmuduo_base -lpthread;};fn'
alias nocap='amixer set Capture nocap'
# alias ocr='~/Downloads/ScreenShot/ocr_temp/scrot_ocr_xclip.sh'

alias ls='ls --color=tty'
alias l='ls -lah'
alias la='ls -lAh'
alias ll='ls -lh'

alias cp='cp -i'
alias afind='ack -il'
alias diff='diff --color=auto'
alias grep='grep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
alias egrep='egrep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
alias fgrep='fgrep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
alias z='_z 2>&1'

alias nv='nvim'
alias vim='nvim'
alias VIM='vim'
alias emacs='vim'
alias pc='proxychains4'
alias rn='ranger'
alias cpm='cppman'
alias zc='z -c'
alias cmk='mkdir build && cd build && cmake .. && make VERBOSE=1'

alias -s c='vim'
alias -s cc='vim'
alias -s cpp='vim'
alias -s gz='tar -xzvf'
alias -s tgz='tar -xzvf'
alias -s bz2='tar -xjvf'

# git 
alias ga='git add'
alias gac='git add . && git commit -m'
alias gbr='git branch'
alias gco='git checkout'
alias gcb='git checkout -b'
alias gc='git commit -m'
alias gd='git diff'
alias gp='git push'
alias gpm='git push -u origin master'
alias gl='git pull'
alias glm='git pull origin master'
alias gm='git merge'
alias gst='git status'
alias glola='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset'\'' --all'
alias glols='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset'\'' --stat'
alias lg='lazygit'

# golang
alias gb='go build'
alias gr='go run'
