#!/bin/sh
curl -X POST https://notify-api.line.me/api/notify \
-H 'Authorization: Bearer NNhRa4wR2qn9UEedZdVIoazbka2EGo84Jvy5Er9izH9' \
-F 'message=test sending a sticker.' 
-F 'stickerPackageId=1' 
-F 'stickerId=113'
