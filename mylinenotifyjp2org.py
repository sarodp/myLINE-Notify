#!usr/bin/python3
# -*- coding: utf-8 -*-
#
# ==Blogs Japan
# origin: gisfile1.txt
# http://blog.futurestandard.jp/entry/2017/02/04/131343
# http://tech.innovation.co.jp/2016/10/14/Try-Line-Notify.html
#
# ==Blog thai
# http://lookmoonoi.blogspot.com/2017/04/line-notify-raspberry-pi.html?m=1
#


# ==LINE Notify API document
# https://notify-bot.line.me/doc/en/   
#
# shell commands '$ curl...' sending LINE Notifications
'''
# Line Notify a message ===================================
$ curl -X POST https://notify-api.line.me/api/notify 
	   -H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \
	   -F 'message=test'
'''

'''
# Line Notify an image file ===================================
$ curl -X POST https://notify-api.line.me/api/notify 
	   -H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \
	   -F 'message=test' \
	   -F 'imageFile=@/PATH/TO/IMAGE/cony.jpg'       
'''

'''
# Line Notify a Sticker ===================================
$ curl 	-X POST https://notify-api.line.me/api/notify 
		-H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \
		-F 'message=test' 
		-F 'stickerPackageId=1' 
		-F 'stickerId=113'
'''


import urllib.parse
import pycurl,time 

#--https://notify-bot.line.me/my/ 
#--you must generate token_key here first.
token_key = '<your token_key>'

headers = str("Authorization: Bearer "+token_key)

#--LINE Notify Image File
def line_notifyIMG(xmessage,imagefile,xheaders):
	curl = pycurl.Curl()
	curl.setopt(pycurl.URL, 'https://notify-api.line.me/api/notify')
	curl.setopt(pycurl.HTTPHEADER, [headers])

	curl.setopt(pycurl.HTTPPOST, [
	('message', xmessage.encode('utf-8')),
	('imageFile', (curl.FORM_FILE, str(imagefile))) ])

	curl.perform()


#--LINE Notify sticker
def line_notifySTK(xmessage,stkpid,stkid,xheaders):
	curl = pycurl.Curl()
	curl.setopt(pycurl.URL, 'https://notify-api.line.me/api/notify')
	curl.setopt(pycurl.HTTPHEADER, [xheaders])

	curl.setopt(pycurl.HTTPPOST, [
	('message', xmessage.encode('utf-8')),
	('stickerPackageId', str(stkpid)),
	('stickerId', str(stkid)) ])

	curl.perform()

#--LINE Notify Message
def line_notifyMSG(xmessage,xheaders):
	curl = pycurl.Curl()
	curl.setopt(pycurl.URL, 'https://notify-api.line.me/api/notify')
	curl.setopt(pycurl.HTTPHEADER, [xheaders])

	curl.setopt(pycurl.HTTPPOST, [
	('message', xmessage.encode('utf-8')) ])

	curl.perform()

#--LINE Notify Message - another way
def line_notifyMSG00(xmessage):
	LINE_NOTIFY_URL = 'https://notify-api.line.me/api/notify'
	LINE_NOTIFY_TOKEN = '<your line notify token>'  #
	headers = { 'Authorization' : 'Bearer %s' % LINE_NOTIFY_TOKEN }
	data={'message': xmessage}
	field_data = urllib.parse.urlencode(data)

	curl = pycurl.Curl()
	curl.setopt(pycurl.URL, LINE_NOTIFY_URL)
	curl.setopt(pycurl.HTTPHEADER, ["%s: %s" % t for t in headers.items()])
	curl.setopt(pycurl.POSTFIELDS, field_data)

	curl.perform()


if __name__ == "__main__":
	xmsg=("ทดสอบส่งสติกเกอร์  เวลา %s" % (time.ctime()))
	stkpid = 1
	stkid = 118
	#line_notifySTK(xmsg,stkpid,stkid,headers)
	line_notifySTK(token_key,stkpid,stkid,headers)


	'''
	xmsg=("ทดสอบส่งข้อความภาษาไทย  เวลา %s" % (time.ctime()))
	line_notifyMSG(xmsg,headers)

	xfile ='myphoto2.png'
	xmsg=("%s รูปภาพดญ.โปรแกรม  เวลา %s" % (xfile,time.ctime()))
	line_notifyIMG(xmsg,xfile,headers)
	'''

