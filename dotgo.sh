#! /bin/sh

path=`pwd`
xconfig=$HOME/.config
flocal=$$HOME/.local/share

# alacritty
mkdir -pv $xconfig/alacritty
ln -sfv $path/alacritty/alacritty.toml $xconfig/alacritty/alacritty.toml

# bspwm
#mkdir -pv $xconfig/bspwm
#ln -sfv $path/bspwm/bspwmrc $xconfig/bspwm/bspwmrc
#ln -sfv $path/bspwm/sxhkdrc $xconfig/sxhkd/sxhkdrc

# clang
ln -sfv $path/clang/clang-format ~/.clang-format

# feh
#ln -sfv $path/pictures/fehbg ~/.fehbg

# fontconfig
mkdir -pv $xconfig/fontconfig
ln -sfv $path/fontconfig/fonts.conf $xconfig/fontconfig/fonts.conf
ln -sfv $path/fontconfig/10-dpi.conf $xconfig/fontconfig/conf.d/10-dpi.conf

# fcitx5
mkdir -p flocal/fcitx5/rime
mkdir -p flocal/fcitx5/themes
ln -sfv $path/fcitx5/themes $flocal/fcitx5/themes 
ln -sfv $path/fcitx5/default.custom.yaml $flocal/fcitx5/rime/default.custom.yaml

# hyprland
mkdir -pv $xconfig/hypr
ln -sfv $path/hypr/hyprland.conf $xconfig/hypr/hyprland.conf
# ln -sfv $path/hypr/hyprpaper.conf $xconfig/hypr
# ln -sfv $path/hypr/hypridle.conf $xconfig/hypr

# keynav
#mkdir -pv $xconfig/keynav
#ln -sfv $path/keynav/keynavrc $xconfig/keynav/keynavrc

# picom(compton)
#mkdir -pv $xconfig/picom
#ln -sfv $path/picom/picom.conf $xconfig/picom/picom.conf

# waybar
mkdir -pv $xconfig/waybar
ln -sfv $path/waybar/config.jsonc $xconfig/waybar/config.jsonc
ln -sfv $path/waybar/style.css $xconfig/waybar/style.css

# mpd ncmpcpp
mkdir -pv $xconfig/ncmpcpp $xconfig/mpd
ln -sfv $path/mpd-ncmpcpp/bindings $xconfig/ncmpcpp/bindings
ln -sfv $path/mpd-ncmpcpp/config $xconfig/ncmpcpp/config
ln -sfv $path/mpd-ncmpcpp/mpd.conf $xconfig/mpd/mpd.conf

# polybar
#mkdir -pv $xconfig/polybar
#ln -sfv $path/polybar/config $xconfig/polybar/config

# ranger
mkdir -pv $xconfig/ranger
ln -sfv $path/ranger/rc.conf $xconfig/ranger/rc.conf

# rofi
#mkdir -pv $xconfig/rofi
#ln -sfv $path/rofi/config.rasi $xconfig/rofi/config.rasi
# ln -sfv $path/rofi/arc-red-dark.rasi $xconfig/rofi/arc-red-dark.rasi

# termite
mkdir -pv $xconfig/termite
ln -sfv $path/termite/config $xconfig/termite/config

# tmux
ln -sfv $path/tmux/tmux.conf ~/.tmux.conf

# vim
mkdir -pv ~/.vim ~/.vim/vim
ln -sfv $path/vim/vimrc ~/.vimrc
ln -sfv $path/vim/keymap.vim ~/.vim/vim/keymap.vim
ln -sfv $path/vim/plugin.vim ~/.vim/vim/plugin.vim
ln -sfv $path/vim/coc-settings.json ~/.vim/coc-settings.json

# nvim
mkdir -pv $xconfig/nvim
ln -sfv $path/vim/init.vim $xconfig/nvim/init.vim
ln -sfv $path/vim/coc-settings.json $xconfig/nvim/coc-settings.json

# xorg
mkdir -pv $xconfig/xorg
ln -sfv $path/xorg/Xmodmap $xconfig/xorg/Xmodmap
ln -sfv $path/xorg/Xresources $xconfig/xorg/Xresources
ln -sfv $path/xorg/xinitrc ~/.xinitrc

# zathura
mkdir -pv $xconfig/zathura
ln -sfv $path/zathura/zathurarc $xconfig/zathura/zathurarc

# zsh
mkdir -pv $xconfig/zsh
ln -sfv $path/zsh/alias.sh $xconfig/zsh/alias.sh
ln -sfv $path/zsh/utils_env.sh $xconfig/zsh/utils_env.sh
ln -sfv $path/zsh/LESS_TERMCAP $xconfig/zsh/LESS_TERMCAP
ln -sfv $path/zsh/fsph_prompt.sh $xconfig/zsh/fsph_prompt.sh
ln -sfv $path/zsh/lgfs_prompt.sh $xconfig/zsh/lgfs_prompt.sh

ln -sfv $path/zsh/zshenv ~/.zshenv
ln -sfv $path/zsh/zshrc $xconfig/zsh/.zshrc
ln -sfv $path/zsh/zpreztorc $xconfig/zsh/.zpreztorc

#
# [root]
#
# pacman 
# sudo ln -sfv $path/pacman/pacman.log /var/log/pacman.log

# xorg
# sudo ln -sfv $path/xorg/20-intel.conf /etc/X11/xorg.conf.d/20-intel.conf
# sudo ln -sfv $path/xorg/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf

# 
# [archived]
#
## aria2
# ln -sfv $path/aria2/aria2.conf ~/.aria2/aria2.conf
# ln -sfv $path/aria2/delete.aria2.sh ~/.aria2/delete.aria2.sh
# ln -sfv $path/aria2/delete.sh ~/.aria2/delete.sh
# ln -sfv $path/aria2/dht.dat ~/.aria2/dht.dat
# ln -sfv $path/aria2/dht6.dat ~/.aria2/dht6.dat

# i3-gaps, i3status
# ln -sfv $path/i3status/config $xconfig/i3status/config
# ln -sfv $path/i3status/net-speed.sh $xconfig/i3status/net-speed.sh
# ln -sfv $path/i3wm/config $xconfig/i3/config

# dwm
# ln -sfv $path/dwm/startdwm ~/.startdwm
# ln -sfv $path/dwmstatus/startdwmstatus ~/.startdwmstatus

# redshift
# ln -sfv $path/redshift/redshift.conf $xconfig/redshift.conf

