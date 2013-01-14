#!/bin/sh
# Create Database and table SQLITE3 for WMR Weather SQL Logger 


wmrconf=${wmrconf:-/etc/wmr/wmr.conf}

        if [ ! -f $wmrconf ]; then
                echo "Error: '(" $wmrconf " not found)'"
                exit 1
        fi

        SQLBASEPATH=`cat $wmrconf | grep SQLBASEPATH | awk '{ print $2 }'`
	SQLBASEFILE=`basename ${SQLBASEPATH}`
        SQLBASEDIR=`echo ${SQLBASEPATH} | sed -e 's/'${SQLBASEFILE}'//g'`

        if [ -f "${SQLBASEPATH}" ]; then
            echo "Delete: '(Old sql data base removed - give path from wmr.conf)'"
            rm -f ${SQLBASEPATH}
	else
	    mkdir -p ${SQLBASEDIR}
        fi

        if [ ! -x "`which sqlite3`" ]; then
            echo "Error: '(sqlite3 not found)'"
	    exit 1
        fi

        if [ -f "../contrib/wmr.sql" ]; then
            SQLBASESOURCE="../contrib/wmr.sql"
	else
    	    if [ -f "/etc/wmr/wmr.sql" ]; then
        	SQLBASESOURCE="/etc/wmr/wmr.sql"
	    else
		echo "Error: '(wmr.sql not found in path: /etc/wmr/, ../contrib/)'"
		exit 1
	    fi
        fi

	sqlite3 ${SQLBASEPATH} < ${SQLBASESOURCE}
	cp -f ${SQLBASEPATH} ${SQLBASEPATH}.TMPL
	echo "Ok: sqlite base created: " ${SQLBASEPATH}
	echo ""

exit 0
