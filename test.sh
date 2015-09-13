source standard.sh --source --bbpass --supass

#VT100 ESCAPE SEQUENCES
#
#\e[ ? m
#	-use ';' to pass multiple seq to terminal
#	-'0' resets everything
#	-'1' makes text bold
#	-'2' makes text darker
#	-'3' makes text italic
#	-'4' makes text underlined
#	-'5' makes text highlighted
#	-'6' does nothing
#	-'7' makes text and background color inverted
#	-'8' makes text disappear
#	-'9' strikes text
#	-'30'~'37' foreground color
#	-'40'~'47' background color
#	-'x0' black
#	-'x1' red
#	-'x2' green
#	-'x3' yellow
#	-'x4' blue
#	-'x5' magenta
#	-'x6' cyan
#	-'x7' white

#	^[ == ESC
#	A == up, B == down, C == right, D == left
#	^[[A		^[[B		^[[C		^[[D
#	n=how much
#	\e[nA		\e[nB		\e[nC		\e[nD

#	\e7 - save position
#	\e8 - restore position

#MORE STUFF: http://www.braun-home.net/michael/mbedit/info/misc/VT100_commands.htm




#titlemate Hello, World!
arrowkeys(){
	#bak=$(stty -g)
	#trap "stty $bak; return 0" 2
	while read -rsn1 ui; do
		case "$ui" in
		$'\x1b')    # Handle ESC sequence.
			# Flush read. We account for sequences for Fx keys as
			# well. 6 should suffice far more then enough.
			read -rsn1 -t 0.1 tmp
			if [ "$tmp" == "[" ]; then
				read -rsn1 -t 0.1 tmp
			fi
			echo $tmp
			# Flush "stdin" with 0.1  sec timeout.
			read -rsn5 -t 0.1
			break
			;;
		*)
			echo $tmp
			break;
		;;
		esac
	done
}

while true; do
	loc=$(arrowkeys)
	echo $loc
done

echo -e "playstation motherfucker\e7\e[18Dfuck\e8boy"
debug_shell


while read -rsn1 ui; do
    case "$ui" in
    $'\x1b')    # Handle ESC sequence.
        # Flush read. We account for sequences for Fx keys as
        # well. 6 should suffice far more then enough.
        read -rsn1 -t 0.1 tmp
        if [[ "$tmp" == "[" ]]; then
            read -rsn1 -t 0.1 tmp
            case "$tmp" in
            "A") printf "Up\n";;
            "B") printf "Down\n";;
            "C") printf "Right\n";;
            "D") printf "Left\n";;
            esac
        fi
        # Flush "stdin" with 0.1  sec timeout.
        read -rsn5 -t 0.1
        ;;
    # Other one byte (char) cases. Here only quit.
    q) break;;
    esac
done
