#
# export DISPLAY=:0
#
# cpp
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

# golang
export GOPATH=$HOME/d4ta/go
export GOBIN=$GOPATH/bin
export PATH=$PATH:$GOPATH/bin

export GO111MODULE=auto
export GOPROXY=https://goproxy.cn,direct

# pfetch
export PF_INFO="ascii title os kernel uptime pkgs wm memory"

# ranger preventing nested ranger instances
ranger() {
    if [ -z "$RANGER_LEVEL" ]; then
        /usr/bin/ranger "$@"
    else
        exit
    fi
}

