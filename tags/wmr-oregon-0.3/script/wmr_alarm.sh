#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] ;
then
    echo "Alarm file for wmr-oregon weather logger"
    echo "(c) 2012 Den68 <idg68@yandex.ru>"
    echo "Global download URL: http://code.google.com/p/wmr/"
    echo ""
    echo "Use format:"
    echo "(SENSOR TYPE) (NUM OF SENSOR) (CURENT STATUS) (ALARM STATUS)"
    echo "Examle:"
    echo "TEMP 1 -7 MIN"
    echo "TEMP 1 28 MAX"
    echo "Run only wmr-oregon software is alarm enabled"
    echo ""
    exit
fi

#
# status battery of sensor
#
if [ "$1" == "BATTERY" ]
then
    #
    # $2 - nuber of sensor 
    # $3 - value battery of sensor
    # $4 - name of sensor
    # sample:
    # /path/to/script/wmr_alarm.sh BATTERY 0 7 TEMP
    #
    # valid name of sensor:
    # "TEMP", "WIND", "RAIN", "UV", "MAIN", "WATER"
    #
	echo "BATTERY NO GOOD: $4 $2 $3 !"
	# sendsms -n 89110000000 -t "Weather station - BATTERY NO GOOD: $4 $2 $3 !"
	exit
fi

#
# type of sensor
#
if [ "$1" == "TEMP" ]
then
    #
    # nuber of sensor 0 (main unit)
    #
    if [ "$2" == "0" ]
    then
	if [ "$4" == "MIN" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power on port 4 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 4 -s 1 
	    exit
	fi
	if [ "$4" == "MAX" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power off port 4 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 4 -s 0 
	    exit
	fi
    fi

    #
    # nuber of sensor 1 (outdoor complected sensor)
    #
    if [ "$2" == "1" ]
    then
	if [ "$4" == "MIN" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power on port 1 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 1 -s 1 
	    exit
	fi
	if [ "$4" == "MAX" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power off port 1 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 1 -s 0 
	    exit
	fi
    fi

    #
    # nuber of sensor 2
    #
    if [ "$2" == "2" ]
    then
	if [ "$4" == "MIN" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power on port 2 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 2 -s 1 
	    exit
	fi
	if [ "$4" == "MAX" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    # power off port 2 triger C2000-CP1
	    # /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 2 -s 0 
	    exit
	fi
    fi
fi

if [ "$1" == "HUMYDITY" ]
then
    if [ "$2" == "0" ]
    then
	if [ "$4" == "MIN" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 3 -s 1 
	    exit
	fi
	if [ "$4" == "MAX" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 3 -s 0 
	    exit
	fi
    fi

    if [ "$2" == "1" ]
    then
	if [ "$4" == "MIN" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 4 -s 1 
	    exit
	fi
	if [ "$4" == "MAX" ]
	then
	    echo "$1 $2 $3 $4  ..."
	    /usr/bin/php5 /etc/wmr/C2000-CP1.php -p 4 -s 0 
	    exit
	fi
    fi
fi

if [ "$1" == "RAIN" ]
then
	echo "$1 $2 $3 ... etc"
    exit
fi

if [ "$1" == "WIND" ]
then
	echo "$1 $2 $3 ... etc"
    exit
fi

if [ "$1" == "UV" ]
then
	echo "$1 $2 $3 ... etc"
    exit
fi
