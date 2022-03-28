#!/bin/bash
# (C) 2018-2020 Felix Hauri - felix@f-hauri.ch
# Licensed under terms of GPL v3. www.gnu.org
# Color browser using hsv<->rgb functions

SRCDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ -e $SRCDIR/hsvrgb.sh ] ;then . $SRCDIR/hsvrgb.sh
   else echo >&2 "Functions file 'hsvrgb.sh' not found."; exit 1
fi

drawLines(){ 
    local -ia sl=() vl=() hl=() colors
    local -i i
    local sint
    for ((i=0 ; 2*cols > i ; i++ ))
    do
        rgb $((17950000/cols*i/100000)) $s $v colors;
        hl+=(${colors[@]});
        sint=0000$((i*100000/cols));
        rgb $h ${sint::-5}.${sint: -5} $v colors;
        sl+=(${colors[@]});
        rgb $h $s $((25600000/cols*i/100000)) colors;
        vl+=(${colors[@]});
    done;
    printf -v Hline "$ColFmt" ${hl[@]};
    printf -v Sline "$ColFmt" ${sl[@]};
    printf -v Vline "$ColFmt" ${vl[@]};
}

start=${EPOCHREALTIME/.}
cols=$(tput cols)
printf -v ColFmt '%*s' "$cols" ''
ColFmt=${ColFmt// /'\e[48;2;%d;%d;%d;38;2;%d;%d;%dm\U2590'}
ColFmt+='\e[0m'

step=1

format='\e8%s\n\e[K%s\U2191\n%s\n\e[K%s\U2191\n%s\n\e[K%s\U2191\n'
format+=' R: %3d, G: %3d, B: %3d  => #%02X%02X%02X  \e[0;48;2;%d;%d;%dm    \e[0'
format+='m\n T: %3d, S: %06.5f, V: %3d          \e[0;48;2;%d;%d;%dm    \e[0m\n'
format+='                                     \e[48;5;%dm    \e[0m\e[11C%3d\n'
format+='              1 byte ANSI -> [%3d]   \e[48;5;%dm    \e[0m \U2592 \e[2D'

rehsv() { hsv $r $g $b out;h=${out[0]} s=${out[1]} v=${out[2]};}
rergb() { rgb $h $s $v out;r=${out[0]} g=${out[1]} b=${out[2]};}
h=180 s=.8 v=180
rergb
printf "   Initialisation...\r"
drawLines
renderColor=$(( ( ${EPOCHREALTIME/.} - start ) < 100000 ))

# h=$((RANDOM%360)) v=$((RANDOM%255))
# printf -v s .%03d $((RANDOM%999)) 
# rergb
printf -v clearPanel '\n\n\n\n\n\n%43s%s\n%43s%s\n%43s%s\n%43s%s\r\e[9A\e7' \| \
       ' Use keys [RGBHSV] to change values,' \| \
       ' Lower case to lower, upper to higher' \| \
       ' by step:    [+-] (in/de)crase step.' \| \
       $' or [\e[1mu\e[0m] for \47\e[1mUsage\e[0m\47.'
echo -n "$clearPanel"
while :;do
    ((renderColor)) && drawLines
    h_blank=00$((1000*cols*h/360))
    printf -v h_blank "%.0f" ${h_blank::-3}.${h_blank: -3}
    printf -v h_blank '%*s' $((h_blank>(cols-1)?(cols-1):h_blank)) ''
    printf -v s_blank %.6f "$s"
    s_blank=00$((1000*cols*10#${s_blank/.}/1000000))
    printf -v s_blank "%.0f" ${s_blank::-3}.${s_blank: -3}
    printf -v s_blank '%*s' $((s_blank>(cols-1)?(cols-1):s_blank)) ''
    v_blank=00$((1000*cols*v/255))
    printf -v v_blank "%.0f" ${v_blank::-3}.${v_blank: -3}
    printf -v v_blank '%*s' $((v_blank>(cols-1)?(cols-1):v_blank)) ''
    sr=$(( r/42>5?5:r/42 )) sg=$(( g/42>5?5:g/42 )) sb=$(( b/42>5?5:b/42 ))
    sv=$(( 16 + sr * 36 + sg * 6+ sb ))
    printf "$format" \
	   "$Hline" "$h_blank" "$Sline" "$s_blank" "$Vline" "$v_blank" \
	   $r $g $b $r $g $b $r $g $b $h $s $v $r $g $b $sv $step $sv{,}
    printf $'\e[21C%\04714d\U00B5s\e[K\e[37D' $(( ${EPOCHREALTIME/.} -start ))
    [ -v keypress ] || IFS= read -rsn 1 keypress
    start=${EPOCHREALTIME/.}
    case $keypress in
	q ) break ;;
	u ) printf '\e8'
	    printf '\n\e[K%-12s %s' \
		   $'\e[A\e[KHSV-RGB Color browser - Usage:' $'\n\e[K' \
		   '  [RrGgBbVb]' \
		   "Incrase/decrase value by step ('$step'), from 0 to 255.." \
		   '  [HhTt]' 'Incrase/decrase Hue (tint), loop over 0 - 359.' \
		   '  [Ss]' \
		   "Increase/decrase Saturation by .006 x step ($step)." \
		   '  [Cc]' 'Toggle Color bar rendering (upper C fix HSV)' \
		   '  [+-]' 'Incrase/decrase step.' \
		   '  [u]' 'show this.' '  [q]' quit. '' 
	    read -sn 1 -t 20 _
	    printf "\e8%s" "$clearPanel"
	    ;;
	c ) ((renderColor=1-renderColor)) ;;
	C ) ((renderColor=1-renderColor)) || {
		or=$r og=$g ob=$b
		h=180 s=.8 v=180
		rergb
		drawLines
		r=$or g=$og b=$ob
		rehsv
	    };;
	- ) step=$(( step-1 > 1 ? step-1 : 1 ))     ;;
	+ ) step=$(( step+1 < 128 ? step+1 : 128 )) ;;
	r ) r=$(( r-step > 0 ? r-step : 0 ))   ;rehsv;;
	R ) r=$(( r+step < 255 ? r+step : 255));rehsv;;
	g ) g=$(( g-step > 0 ? g-step : 0 ))   ;rehsv;;
	G ) g=$(( g+step < 255 ? g+step : 255));rehsv;;
	b ) b=$(( b-step > 0 ? b-step : 0 ))   ;rehsv;;
	B ) b=$(( b+step < 255 ? b+step : 255));rehsv;;
	t|h ) h=$(( ( h+360 - step ) % 360 ))  ;rergb;;
	T|H ) h=$(( ( h+step ) % 360 ))        ;rergb;;
	v|l ) v=$(( v-step > 0 ? v-step : 0 ))   ;rergb;;
	V|L ) v=$(( v+step < 255 ? v+step : 255));rergb;;
	s ) printf -v s %.6f $s
	    s=00000$(( s=10#${s/.}, s-step*6000 > 0 ? s-step * 6000 : 0 ))
	    printf -v s %.5f ${s::-6}.${s: -6} ;rergb;;
	S ) printf -v s %.6f $s
	    s=00000$(( s=10#${s/.}, s+step*6000 < 1000000 ?s+step*6000:1000000))
	    printf -v s %.5f ${s::-6}.${s: -6} ;rergb;;
	* ) printf '\e[32C[%03d]\e[7D' \'"$keypress"
    esac
    unset keypress
done
echo $'\e[0m'
