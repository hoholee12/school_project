# this is my homework:D
from tweepy import *
from urllib.request import *
from time import *

#private stuff -leave this part out when editing!!

#tweepy stuff
auth=OAuthHandler(consumer_key,consumer_secret)
auth.secure=True
auth.set_access_token(access_token,access_token_secret)
api=API(auth)
#print(api.me().name)

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













