#!/bin/sh

if [ ! -f /tmp/WMR_WARNING_$1_$2.lock ] ;
then

echo "Warning! Sensor type: $1 num: $2  battery low (value: $3)"
#
# 	send sms:
# /usr/bin/wmr_sendms_sms.ru.sh "Warning! Sensor type: $1 num: $2  battery low (value: $3)"
#
# 	or send e-mail from sendmail program:
# echo "Warning! Sensor type: $1 num: $2  battery low (value: $3)" | sendmail -f name@your_real_mail_domain.ru you@mail.ru
#
# 	or send e-mail from mail program:
# echo "Warning! Sensor type: $1 num: $2  battery low (value: $3)" | mail -s"Warning! weathers station battery low!" -r name@your_real_mail_domain.ru  you@mail.ru
#
# 	or NET SMB message (needed WinPopup):
#	(see other analog WinPopUp...  http://viktorov.narod.ru/programming/myprograms/vikpopup/)
# echo "Warning! Sensor type: $1 num: $2  battery low (value: $3)" | smbclient -M SMBNAME
#
touch /tmp/WMR_WARNING_$1_$2.lock
date >> /tmp/WMR_WARNING_$1_$2.lock
echo "battery low (value: $3)" >> /tmp/WMR_WARNING_$1_$2.lock

fi
