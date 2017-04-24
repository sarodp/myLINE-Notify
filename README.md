# myLINE-Notify  
Testing LINE Notify API  

### Blogs Japan  
* origin: gisfile1.txt  https://github.com/sarodp/myLINE-Notify/blob/master/gistfile1.txt  
* http://blog.futurestandard.jp/entry/2017/02/04/131343  
* http://tech.innovation.co.jp/2016/10/14/Try-Line-Notify.html  
  
### Blog thai  
* http://lookmoonoi.blogspot.com/2017/04/line-notify-raspberry-pi.html?m=1  
  
### LINE Notify API document  
* https://notify-bot.line.me/doc/en/     

  
### you must generate token_key here first.  
* https://notify-bot.line.me/my/   
  
  
  
### shell commands '$ curl...' sending LINE Notifications  
```  
# Line Notify a message ===================================  
$ curl -X POST https://notify-api.line.me/api/notify   
	   -H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \  
	   -F 'message=test'  

# Line Notify an image file ===================================
$ curl -X POST https://notify-api.line.me/api/notify 
	   -H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \
	   -F 'message=test' \
	   -F 'imageFile=@/PATH/TO/IMAGE/cony.jpg'       

# Line Notify a Sticker ===================================
$ curl 	-X POST https://notify-api.line.me/api/notify 
		-H 'Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN' \
		-F 'message=test' 
		-F 'stickerPackageId=1' 
		-F 'stickerId=113'
```
