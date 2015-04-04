#encryptor/decryptor program by hoholee12@naver.com
#1337 biches.
#i do know there are lots of vulnerabilities with this method. this is just for fun.
from sys import argv
def encrypt(f):
	with open(f,'r') as result:
		arr=[]
		i=0
		while True:
			arr.append(result.read(1))
			if not arr[i]:
				break
			i+=1
	try:
		secretkey=input("input new key:")
		secretkey2=input("input key again:")
		if secretkey != secretkey2:
			print("incorrect key entered!")
			exit()
	except KeyboardInterrupt:
		exit()
	if not secretkey:
		secretkey="badasscryptography"
	multiplication=0
	p=0
	for c in secretkey:
		p+=1
		multiplication=multiplication+(p*ord(str(c)))

	with open(f,'w') as stuff:
		stuff.write("1337")
		stuff.write(str(1337*multiplication))
		stuff.write(",")
		for j in range(0,i):
			stuff.write(str(multiplication*ord(arr[j])))
			if arr[j+1]:
				stuff.write(",")
def decrypt(f):
	with open(f,'r') as stuff:
		for i in stuff:
			if not '1337' in i:
				print("its not mine.") #exception
				exit()
			i=i.replace('1337','')
		i=i.split(',')
	try:
		secretkey=input("input password:")
	except KeyboardInterrupt:
		exit()
	if not secretkey:
		secretkey="badasscryptography"
	multiplication=0
	p=0
	for c in secretkey:
		p+=1
		multiplication=multiplication+(p*ord(str(c)))
	if not str(multiplication*1337) in i[0]:
		print("incorrect password!")
		exit()
	i.pop(0)

	with open(f,'w') as result:
		for j in i:
			result.write(chr(int(int(j)/multiplication)))
def help():
	print("encryptor/decryptor program by hoholee12@naver.com\n1337 biches.\nUsage: test12.py -h [file]")
try:
	if argv[1] == '-h':
		help()
	else:
		with open(argv[1],'r') as stuff:
			for i in stuff:
				if not '1337' in i:
					a=input("would you like to encrypt this file?: y or n")
					if a != 'y':
						print('aborted.')
						exit()
					encrypt(argv[1])
					exit()
				else:
					print("this file was encrypted by 1337 crypto engine!")
					decrypt(argv[1])
					exit()
except IndexError:
	help()
except KeyboardInterrupt:
	exit()
except FileNotFoundError:
	print("there is no such thing as '",argv[1],"'")
	exit(1)

