<?php
//
// * 2012 Den68 <idg68@yandex.ru>
// * Latest download URL: http://www.nkl.ru/support/wmr/
// * Global download URL: http://code.google.com/p/wmr/
//
// Болид С2000-СП1 протокол обмена.
// библиотека функций.
//
// Включить порт(реле):	     function on_C2000-CP1(файл дескриптор,номер порта)
// Выключить порт(реле):     function off_C2000-CP1(файл дескриптор,номер порта)
// Статус всех портов(реле): function status_C2000-CP1(файл дескриптор)
// Тест всех портов(реле):   function test_C2000-CP1(файл дескриптор)
//

$opt = getopt('p:s:');

if	  (  $opt['s'] == NULL )
{ 
	C2000_usage(); exit(-1);
} else if (( $opt['p'] == NULL ) && ( $opt['s'] <= 1 ))
{
	C2000_usage(); exit(-1);
}

// for Windows:
// exec('mode COM6: BAUD=9600 PARITY=none DATA=8 STOP=1 to=on xon=off odsr=off octs=off dtr=off rts=off idsr=off');
// $f = fopen("COM6","r+");
//
// for Linux:
// 
$f = fopen("/dev/ttyUSB0","r+");

$pbyte = array( "ON"	=> array(0x4B,0xC3,0x4C,0xCA), "OFF"	=> array(0xA9,0x21,0xAE,0x28), "STAT"	=> array(0xC8,0x40,0xCF,0x49));

	switch($opt['s'])
	{
		case 0:
			off_C2000_CP1($f,$pbyte,$opt['p']);
			break; 
		case 1:
			on_C2000_CP1($f,$pbyte,$opt['p']);
			break; 
		case 2:
			status_C2000_CP1($f,$pbyte);
			break; 
		case 3:
			test_C2000_CP1($f,$pbyte);
			break;
		default:
			echo "\n\tno parametr specifed, exit...\n\n";
			exit -1;
		
	}

fclose($f);
exit(0);

///////////////////////////// LIB //////////////////////////////////////////////

function C2000_usage()
{
	echo "Use: <this_script.php> -p 1 -s 1\n\n";
	echo "\t-p 1 is port-rele in C2000-CP1, valid 1,2,3,4 \n";
	echo "\t-s 1 is status-rele in C2000-CP1 - on- 1, off- 0, status- 2, test- 3\n";
	echo "\n\tno parametr specifed, exit...\n\n";
	exit (-1);
}

function on_C2000_CP1($f,$pbyte,$opt)
{
	status_com(write_com($f,array(0x7f,0x08,0x00,0x41,dechex($opt),0x00,0x00,0x01,$pbyte["ON"][($opt - 1)]),6),1,$opt[0]); //Включение порта 
	status_com(write_com($f,array(0x7f,0x06,0x00,0x17,0x00,0x00,0x10),6),0,$opt); // Enter Update
	echo "Порт [".$opt."] Включен\n";
}

function off_C2000_CP1($f,$pbyte,$opt)
{
	status_com(write_com($f,array(0x7f,0x08,0x00,0x41,dechex($opt),0x00,0x00,0x02,$pbyte["OFF"][($opt - 1)]),6),1,$opt[0]); //Выключение порта 
	status_com(write_com($f,array(0x7f,0x06,0x00,0x17,0x00,0x00,0x10),6),0,$opt); // Enter Update
	echo "Порт [".$opt."] Выключен\n";
}


function status_C2000_CP1($f,$pbyte)
{
	for ($i=0; $i < 4; $i++)
	{
		status_com(write_com($f,array(0x7f,0x08,0x00,0x43,dechex($i + 1),0x00,0x00,0x01,$pbyte["STAT"][$i]),6),2,($i + 1)); //Статус порта
	}
}


function test_C2000_CP1($f,$pbyte)
{

	for ($i=0; $i < 4; $i++)
	{
		status_com(write_com($f,array(0x7f,0x08,0x00,0x41,dechex($i + 1),0x00,0x00,0x01,$pbyte["ON"][$i]),6),1,($i + 1)); //Включение порта 
		status_com(write_com($f,array(0x7f,0x06,0x00,0x17,0x00,0x00,0x10),6),0,($i + 1)); // Enter Update
		sleep (5);
		status_com(write_com($f,array(0x7f,0x08,0x00,0x41,dechex($i + 1),0x00,0x00,0x02,$pbyte["OFF"][$i]),6),1,($i + 1)); //Выключение порта 
		status_com(write_com($f,array(0x7f,0x06,0x00,0x17,0x00,0x00,0x10),6),0,($i + 1)); // Enter Update
	}
}

function status_com($fresult,$ok,$port)
{
	switch ($ok)
	{
		case 0:
			if ( ( ord($fresult[2]) == 0x18) && ( ord($fresult[5]) == 0xEC) )
			{
				echo "Enter - Порт [".$port."]\n";
        		}
		case 1: 
			if ( ( ord($fresult[2]) == 0x42) && ( ord($fresult[5]) == 0xFD) )
			{
				echo "Command OK - Порт [".$port."]\n";
        		}
			break; 
		case 2: 
			if ( ( ord($fresult[4]) == 0x01) && ( ord($fresult[5]) == 0xB6) )
			{
				echo "Порт [".$port."] Включен\n";
        		} else
			if ( ( ord($fresult[4]) == 0x02) && ( ord($fresult[5]) == 0x54) )
			{
				echo "Порт [".$port."] Выключен\n";
        		} 
			break; 

	}

}

function write_com($f_file,$cmd_bit,$size_read)
{

	for($i=0; $i < count($cmd_bit); $i++)
	{
		$c .= chr($cmd_bit[$i]);
	}

	fwrite($f_file,$c);
	return (fread($f_file,$size_read));

}

?>

