from colorama import * #tty stuff dont work on windows.
from time import sleep
from random import randint
from sys import * #get arguments from prompt #i also need sys.exit() for covering py2exe errors!
from os import path
init() #initialize colorama - be sure to ask professor to install one before running this!
(name,ext)=__file__.split('.')
name=''.join((name,".cfg"))
already="not there"
if path.isfile(name):
	with open(name) as settings:
		settings=settings.read() #bugfix
		(ghost,sleepy,stuff)=settings.split(';')
		already="there"

try:
	if argv[1]:
		print("your parameter inputs will be ignored.")
except IndexError:
	pass
if already != "there":
	try:
		if argv[1] == "--ghost":
			ghost=1
			argv.remove("--ghost")
			print("ghost effect is ON!",end='')
			sleep(1)
			print("\033[2J",end='')
		else:
			ghost=0
	except IndexError:
		ghost=0
	try:
		sleepy=float(argv[1])
	except (IndexError,TypeError):
		sleepy=.5
	try:
		stuff=argv[2]
	except (IndexError,TypeError):
		stuff="Hello, World!"

stuff_length=len(stuff)
color=31 #color code ranges from 31 to 37
while 1: #loop forever
	try: #until ctrl+c was pressed
		color+=1 #add 1 every loop
		if color==37: # if 37, go back to 31 and continue looping
			color=31
		y_axis=randint(1,26)
		x_axis=randint(1,(81-stuff_length)) #as i said on the top of this script, windows DON'T support tty, therefore NO stty unlike linux.
		sleep(float(sleepy))
		if float(ghost) != 1:
			print("\033[2J",end='')
		print("\033["+str(y_axis)+";"+str(x_axis)+"H\033["+str(color)+"m",end='') #show class 'some infos' first.
		print(stuff,end='')
	except KeyboardInterrupt: #if ctrl+c is pressed
		print("\033[2JI LOVE YOU") #clear screen and print "I LOVE YOU"
		exit() #and safely exit.
#am hoping not to freak out like the last time when doing presentation in front of class :^(
#some infos:
#	\033[2J = clear screen
#	\033[y_axis;x_axisH = move cursor to x,y axis
#	\033[colorm = textcolor code ranging from 31 to 37
#	default terminal size would be around 80x25 characters, hence "randint(1,26)" and "randint(1,81)"