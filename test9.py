from colorama import * #tty stuff dont work on windows.
from time import sleep
from random import randint
from sys import * #get arguments from prompt #i also need sys.exit() for covering py2exe errors!
init() #initialize colorama - be sure to ask professor to install one before running this!
color=31 #color code ranges from 31 to 37
while 1: #loop forever
	try: #until ctrl+c was pressed
		color+=1 #add 1 every loop
		if color==37: # if 37, go back to 31 and continue looping
			color=31
		y_axis=randint(1,26) #isnt this obvious??
		x_axis=randint(1,81) #this one as well.
		try:
			sleep(float(argv[1]))
		except IndexError: #if theres nothing on argv[1], do 1.
			sleep(1)
		print("\033[2J\033["+str(y_axis)+";"+str(x_axis)+"H\033["+str(color)+"m",end='') #show class 'some infos' first.
		try:
			print(str(argv[2]),end='')
		except IndexError: #if theres nothing on argv[2], do "Hello, world!".
			print("Hello, World!",end='')
	except KeyboardInterrupt: #if ctrl+c is pressed
		print("\033[2JI LOVE YOU") #clear screen and print "I LOVE YOU"
		exit() #and safely exit.
#am hoping not to freak out like the last time when doing presentation in front of class :^(
#some infos:
#	\033[2J = clear screen
#	\033[y_axis;x_axisH = move cursor to x,y axis
#	\033[colorm = textcolor code ranging from 31 to 37
#	default terminal size would be around 80x25 characters, hence "randint(1,26)" and "randint(1,81)"