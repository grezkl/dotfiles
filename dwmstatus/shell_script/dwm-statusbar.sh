# dwm status bar
# while true
# do
#
#     date +"%a %F %R" > /tmp/CurTime.tmp
#     sleep 60s
#
# done &
while true
do

    # net speed
#     NET="wlp1s0"
    # R1=`cat /sys/class/net/$NET/statistics/rx_bytes`
    # T1=`cat /sys/class/net/$NET/statistics/tx_bytes`
    # sleep 1
    # R2=`cat /sys/class/net/$NET/statistics/rx_bytes`
    # T2=`cat /sys/class/net/$NET/statistics/tx_bytes`
    # TBPS=`expr $T2 - $T1`
    # RBPS=`expr $R2 - $R1`
    # TKBPS=`expr $TBPS / 128`
    # RKBPS=`expr $RBPS / 128`

    # LOCALTIME=$(< /tmp/CurTime.tmp)
    # BAT=$( acpi -b | awk '{ print $4 " " $5 }' | tr -d ',' )
    BAT=$( acpi -b | awk '{ print $4 }' | tr -d ',' )
    VOL=$(amixer get Master | tail -n1 |  sed -r "s/.*\[(.*)%\].*/\1/")
    LOCALTIME=$(date +"%a %F %R")
    CPU=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1"%"}')
    MEM=$(free -h | awk '/Mem:/ {print $3}' | tr -d 'i')
    TMP=$(echo $[$(cat /sys/class/thermal/thermal_zone0/temp)/1000])
    # MPC=$(mpc -f %file% | awk -F '[./]' 'NR==1{print $2}')
    SPT=""
    # SPT=""
    #                                     「」
    # xsetroot -name " VOL $VOL% | CPU $CPU | MEM $MEM | $TMP°C | BAT $BAT | $LOCALTIME "
    # xsetroot -name "[ VOL $VOL% ] [ CPU $CPU ] [ MEM $MEM ] [ $TMP°C ] [ BAT $BAT ] [ $LOCALTIME ]"
    # xsetroot -name "[VOL $VOL%] [CPU $CPU] [MEM $MEM] [$TMP°C] [BAT $BAT] [$LOCALTIME]"
    # xsetroot -name "[V $VOL%] [C $CPU] [M $MEM] [T $TMP°C] [B $BAT] [$LOCALTIME]"
    # xsetroot -name "  $MPC $SPT  $VOL% $SPT  $CPU $SPT  $MEM $SPT  $TMP°C $SPT  $BAT $SPT $LOCALTIME  "
    # xsetroot -name "  $MPC   $VOL%   $CPU   $MEM   $TMP°C   $BAT  $LOCALTIME  "
    # xsetroot -name "  $VOL%   $CPU   $MEM   $TMP°C   $BAT  $LOCALTIME  "
    xsetroot -name "  $VOL% $SPT  $CPU $SPT  $MEM $SPT  $TMP°C $SPT  $BAT $SPT $LOCALTIME  "
    # xsetroot -name " [ $VOL%] [ $CPU] [ $MEM] [ $TMP°C] [ $BAT] [$LOCALTIME]  "
    # xsetroot -name " [ $TKBPS K/s| $RKBPS K/s] [ $VOL%] [ $CPU] [ $MEM] [ $TMP°C] [ $BAT] [$LOCALTIME]  "
    # xsetroot -name "  $TKBPS K/s   $RKBPS K/s   $VOL%   $CPU   $MEM   $TMP°C   $BAT  $LOCALTIME  "

    # if acpi -a | grep off-line > /dev/null; then
    # xsetroot -name "[$( acpi -b | awk '{ print $4 " " $5 }' | tr -d ',' )]  [$(amixer get Master | tail -n1 |  sed -r "s/.*\[(.*)%\].*/\1/")]  [$(date +"%a %F %R")]"
    # else
    # xsetroot -name "[$( acpi -b | awk '{ print $4 " " $5 }' | tr -d ',' )]  [$(amixer get Master | tail -n1 |  sed -r "s/.*\[(.*)%\].*/\1/")]  [$(date +"%a %F %R")]"
    # fi
    sleep 10s
done &
