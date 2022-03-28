rgb() {
    local -n _result=$4
    local -i _rgb_i=" (($1%360)/60)%6 "
    local -i _rgb_f=" 100000000*($1%360)/60-_rgb_i*100000000 "
    local _rgb_s
    printf -v _rgb_s %.8f "$2"
    _rgb_s=$((10#${_rgb_s/.}))
    local -i _rgb_l=" $3*(100000000-_rgb_s)/100000000 "
    case $_rgb_i in
        0 )
            local -i _rgb_n="$3*(100000000-(100000000-_rgb_f)*_rgb_s/100000000)/
                                100000000 "
            _result=("$3" "$_rgb_n" "$_rgb_l") ;;
        1 )
            local -i _rgb_m=" $3*(100000000-_rgb_f*_rgb_s/100000000)/100000000 "
            _result=("$_rgb_m" "$3" "$_rgb_l") ;;
        2 )
            local -i _rgb_n="$3*(100000000-(100000000-_rgb_f)*_rgb_s/100000000)/
                                100000000 "
            _result=("$_rgb_l" "$3" "$_rgb_n") ;;
        3 )
            local -i _rgb_m=" $3*(100000000-_rgb_f*_rgb_s/100000000)/100000000 "
            _result=("$_rgb_l" "$_rgb_m" "$3") ;;
        4 )
            local -i _rgb_n="$3*(100000000-(100000000-_rgb_f)*_rgb_s/100000000)/
                                100000000 "
            _result=("$_rgb_n" "$_rgb_l" "$3") ;;
        * )
            local -i _rgb_m=" $3*(100000000-_rgb_f*_rgb_s/100000000)/100000000 "
            _result=("$3" "$_rgb_l" "$_rgb_m") ;;
    esac
}

hsv() {
    local -n _result=$4
    local -i _hsv_min _hsv_t
    local _hsv_s
    local -i _hsv_max=" $1 > $2 ?
                (_hsv_min=($2 > $3 ? $3:$2 ), ( $1 > $3 ? $1 : $3 )) :
                (_hsv_min=($1 > $3 ? $3:$1 ), $2) > $3 ? $2 : $3 "
    case $_hsv_max in 
        $_hsv_min) _hsv_t=0 ;;
        $1) _hsv_t=" ( 60 * ( $2 - $3 ) / ( _hsv_max-_hsv_min )+ 360 )%360";;
        $2) _hsv_t=" 60 * ( $3 - $1 ) / ( _hsv_max-_hsv_min )+ 120 " ;;
        $3) _hsv_t=" 60 * ( $1 - $2 ) / ( _hsv_max-_hsv_min )+ 240 " ;;
    esac
    _hsv_s=0000000$(( _hsv_max==0?0 : 100000000-100000000*_hsv_min / _hsv_max ))
    printf -v _hsv_s %.7f ${_hsv_s::-8}.${_hsv_s: -8}
    _result=($_hsv_t $_hsv_s $_hsv_max)
}
