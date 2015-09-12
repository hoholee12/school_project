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

#MORE STUFF: http://www.braun-home.net/michael/mbedit/info/misc/VT100_commands.htm

titlemate Hello, World!
debug_shell

