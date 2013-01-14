#!/bin/sh
# Send alarm sms you mobile phone from sms.ru
# Go http://sms.ru/?panel=support&subpanel=api , get you api-id 
# and store to file `echo "<you api-id>" >/etc/wmr/api_id.sms.ru`
# Sample: echo "00000-0000-0000-000-000000" >/etc/wmr/api_id.sms.ru
#
# Store you phone numer to send sms in file /etc/wmr/phone.sms.ru 
# `echo "<you phone number>" >/etc/wmr/phone.sms.ru`
# Sample: echo "79219998877" >/etc/wmr/phone.sms.ru

if [ "$1" == "" ] ;
then
    echo "SMS send message for wmr-oregon weather logger"
    echo "(c) 2012 Den68 <idg68@yandex.ru>"
    echo "Global download URL: http://code.google.com/p/wmr/"
    echo ""
    echo "Please, enter text to sms message, example:"
    echo ""
    echo "$0 \"Alarm event send sms sensor 1\""
    echo "$0 \"Temperature outdoor is: -28C\""
    echo ""
    echo ""
    exit
fi

	if [ ! -x "`which curl`" ]; then
                echo "Error: curl executable not found"
		echo "Go http://curl.haxx.se/ , download and install curl"
	        echo ""
	        echo ""
                exit 1
        fi

        if [ ! -f "/etc/wmr/phone.sms.ru" ]; then
		mkdir -p /etc/wmr
                echo "Error: file /etc/wmr/phone.sms.ru not found"
		echo "Store you phone numer to send sms in file /etc/wmr/phone.sms.ru"
	        echo "Format example: 79219998877"
	        echo ""
		
		if [ -x "`which read`" ]; then
		    read RDI -t 25 -n 11 -p "Enter you phone number:"
		    echo ${RDI} >/etc/wmr/phone.sms.ru
		else
	    	    echo "sapmle: echo "79219998877" >/etc/wmr/phone.sms.ru"
            	    exit 1
		fi

		echo ""
        fi

        if [ ! -f "/etc/wmr/api_id.sms.ru" ]; then
                echo "Error: file /etc/wmr/api_id.sms.ru not found"
		echo "Go http://sms.ru/?panel=support&subpanel=api , get you api-id"
		echo "and store to file: echo 'you-api-id' >/etc/wmr/api_id.sms.ru"
		echo ""

		if [ -x "`which read`" ]; then
		    read RDI -t 25 -n 36 -p "Enter you API-ID in sms.ru:"
		    echo ${RDI} >/etc/wmr/api_id.sms.ru
		else
		    echo "sample: echo "00000-0000-0000-000-000000" >/etc/wmr/api_id.sms.ru"
            	    exit 1
		fi

		echo ""
        fi

PHONE_N=`cat /etc/wmr/phone.sms.ru`
API_ID=`cat /etc/wmr/api_id.sms.ru`

curl -d "text=$1" http://sms.ru/sms/send\?api_id=${API_ID}\&to=${PHONE_N}

exit

