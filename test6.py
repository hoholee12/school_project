from time import sleep
from colorama import *
init()
def clear():
	print("\033[2J")

def position(x,y):
	print('\033['+str(y)+';'+str(x)+'H', end='')

def posname(x,y,name):
	print('\033['+str(y)+';'+str(x)+'H'+str(name))

clear()
position(20,20)
print("hello")
sleep(1)
clear()
posname(20,20,"hello!")