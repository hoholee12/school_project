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




titlemate Hello, World!


while true; do
	loc=$(arrowkeys) #new API!!
	case $loc in
		"A") echo up;;
		"B") echo down;;
		"C") echo right;;
		"D") echo left;;
		"q") break;;
		*) echo $loc;;
	esac
done

echo -e "playstation motherfucker\e7\e[18Dfuck\e8boy"
debug_shell


