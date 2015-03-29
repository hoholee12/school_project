# this is my homework:D
from tweepy import *
from urllib.request import *

#private stuff -leave this part out when editing!!
consumer_key="TlcvCB9srGSXjR7mWUAMdYFRm"
consumer_secret="ecWtLw6Gf4vNDCpp3nxAgWCVyFtl5Q573sWXzNkLVY0QSb4G91"
access_token="456669442—TV6T3YZC1Cu824HR6CHlgk0xH2jrDba72FFOOytD"
access_token_secret="VhhagTRrh5HV9TKJZv8oajBn35usL3v95sy3hFsQDHqb7"

#tweepy stuff
auth=OAuthHandler(consumer_key,consumer_secret)
auth.set_access_token(access_token,access_token_secret)
api=API(auth_handler=auth,api_root='/1.1',secure=True)
#print(api.me().name)

api.update_status(status='hello')
exit()

#old one modified
def prices():
	#this one is for price
    page=urlopen("http://cs.sch.ac.kr/prices.py")
    page=page.read().decode("utf8")
    loc=page.find('$')
    start=loc+1
    end=loc+5
    global price
    price=float(page[start:end])
	
	#this one is for time2
    loc2=page.find('<p>Price on')
    start2=loc2+12
    end2=loc2+37
    global time2
    time2=str(page[start2:end2])

#loop and print if price is smaller than 4.74
while 1: #loop
	try:
		prices() #get price from cs.sch.ac.kr
		sleep(1) #sleep for a sec
		if price < 4.74: #if price is smaller than 4.74
			stats='its $'+str(price)+', so you\'d better buy it NOW.\ntime: '+time2 #save result to a variable
			api.update_status(status=stats) #send the variable to my twitter
			#print('result: $'+str(price)+' time: '+time2)
	except KeyboardInterrupt:
		exit()
#and its complete!













