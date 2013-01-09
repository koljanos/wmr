#define WMR_C_TXT_1 "- BYTE: Длина полученного пакета: %d: "
#define WMR_C_TXT_2 "- BYTE: hid_set_output_report - завершился с низвестным значением: %d\n"
#define WMR_C_TXT_4 "- BYTE: hid_init - завершился с низвестным значением: %d\n"
#define WMR_C_TXT_5 "- BYTE: hid_new_HIDInterface - ошибка, не удалось выделить память?\n"
#define WMR_C_TXT_6 "- Не удалось окрыть USB устройство, повторение попытки через 5 секунд ..\n"
#define WMR_C_TXT_7 "- BYTE: hid_force_open - завершился с низвестным значением: %d\n"
#define WMR_C_TXT_8 "- BYTE: hid_write_identification - завершился с низвестным значением: %d\n"
#define WMR_C_TXT_9 "- BYTE: hid_interrupt_read - завершился с низвестным значением: %d\n"
#define WMR_C_TXT_10 "- BYTE: Ошибка контрольной суммы: %d подсчитано: %d\n"
#define WMR_C_TXT_11 "- BYTE: Неизвестный тип пакета: %02x, пропуск\n"
#define WMR_C_TXT_12 "- EXEC: updEn:%d  run.UPD[0]:%d  run.UPD[1]:%d  Key:%d\n"
#define WMR_C_TXT_13 "- MAIN: Выход дочернего процесса: %d\n"
#define WMR_C_TXT_14 "- MAIN: Выход родительского процесса: %d\n"
#define WMR_C_TXT_15 "- Повторная инициализация USB устройства ...\n"
#define WMR_C_TXT_16 "- Повторная инициализации не удалась\n\n"
#define WMR_C_TXT_17 "- Выход, текущий PID:%d, мастер PID:%d\n"
#define WMR_C_TXT_18 "- Ожидание потомка PID:%d (%d) статус:%d\n"
#define WMR_C_TXT_19 "- Потомок закончил свою работу PID:%d статус:%d\n"
#define WMR_C_TXT_20 "- Получили сигнал завершения работы, подготовка к выходу\n\n"
#define WMR_C_TXT_21 "\n%s успешно завершил работу\n"
#define WMR_C_TXT_22 "- USB: Открытие Oregon Scientific USB устройства ...\n"
#define WMR_C_TXT_23 "- USB: Не удалось инициализировать устройство, выход\n\n"
#define WMR_C_TXT_24 "- USB: Найдено устройство: %s\n"
#define WMR_C_TXT_25 "- CONFIG: Не удается открыть файл конфигурации %s - выход\n"
#define WMR_C_TXT_26 "- CONFIG: Конфигурация успешно прочитана из файла: %s\n"
#define WMR_C_TXT_27 "- SQL: Ошибка - выход\n\n"
#define WMR_C_TXT_28 "- FILE: Ошибка, не удалось открыть файл журнала - выход\n\n"
#define WMR_C_TXT_29 "- DAEMON: Ошибка не удалось перейти в режим демона - выход\n\n"
#define WMR_C_TXT_30 "- DAEMON: Успешный запуск, работаю...\n\n"
#define WMR_C_TXT_31 "- DAEMON: Ошибка не удалось установить SID - выход\n\n"
#define WMR_C_TXT_32 "- DAEMON: Ошибка не удалось изменить корневую директорию - выход\n\n"
#define WMR_C_TXT_33 "- Запрос на завершение работы %s в демон режиме...\n\n"
#define WMR_C_TXT_34 "- Закрытие SQL базы\n"
#define WMR_C_TXT_35 "- Закрытие записи погодных данных в лог\n"
#define WMR_C_TXT_36 "- Закрытие WMR\n"
#define WMR_C_TXT_37 "- WMR (WMR данные) Ошибка инициализации\n\n"
#define WMR_C_TXT_38 "- WMR (буфер обмена данными о погоде) Ошибка инициализации\n\n"
#define WMR_C_TXT_39 "- Процесс запустил команду: \n\n"
#define WMR_C_TXT_40 "- PID: Удаление успешно\n"
#define WMR_ALARM_C_TXT_1 "ALARM: Ошибка выполнения команды: %s\nОповещение о критических показаниях отключено.\nПожалуйста, проверьте конфигурацию.\n"
#define WMR_ALARM_C_TXT_2 "ALARM: Успешно выполнен: %s\n"
#define WMR_SQL_C_TXT_1 "SQL: Не могу создать таблицу: %s! %s\n"
#define WMR_SQL_C_TXT_2 "SQL: Не могу добавить данные: %s\n"
#define WMR_SQL_C_TXT_3 "SQL: Не удается открыть базу данных: %s\n"
#define WMR_SQL_C_TXT_4 "SQL: Успешно открыл базы данных %s\n"
#define WMR_RRDTOOL_C_TXT_1 "RRD встроенная процедура: Файл%s не найден, отключить обновление\n"
#define WMR_RRDTOOL_C_TXT_2 "RRD встроенная процедура: Ошибка обновления файла %s ошибка: %d  количество добавлений: %d\n"
#define WMR_RRDTOOL_C_TXT_3 "RRD встроенная процедура: номер: %d текущее: %d значение: %f\n"
#define WMR_RRDTOOL_C_TXT_4 "RRD встроенная процедура: Файл: %s количество добавлений: %d\n"
#define WMR_RRDTOOL_C_TXT_5 "RRD встроенная процедура: Ошибка закрытия RRD файла, код: %d (%d)\n"
#define WMR_RRDTOOL_C_TXT_6 "RRDTool: Файл: %s датчик: %d\n"
#define WMR_RRDTOOL_C_TXT_7 "RRDTool: Ошибка: rrdtool исполняемый файл указанный в пути не найден: %s\n- Отключены обновления базы данных RRD\n"
#define WMR_RRDTOOL_C_TXT_8 "RRDTool: Файл %s не найден, создаю\n"
#define WMR_RRDTOOL_C_TXT_9 "RRDTool: Создание: ошибка выполнения команды: %s\n"
#define WMR_RRDTOOL_C_TXT_10 "RRDTool: Обновление: ошибка выполнения команды: %s\n"
#define WMR_RRDTOOL_C_TXT_11 "RRDTool: Выполнение: %s\n"
#define WMR_SENSOR_C_TXT_1 "- WMR: пакет датчика барометра: макс измеренное значение превысило 1050\n"
#define WMR_SENSOR_C_TXT_2 "- WMR: пакет датчика ветра выходит за рамки измерений\n!"
#define WMR_UTIL_C_TXT_1 "- WMR (разделяемая память), ошибка инициализации\n\n"
#define WMR_UTIL_C_TXT_2 "- WMR (разделяемая память), ошибка инициализации, мастер ключ: %d\n"
#define WMR_UTIL_C_TXT_3 "- ОШИБКА: выделение разделяемой памяти = %d\n- Перезапустите меня пожалуйста... :)\n"
#define WMR_UTIL_C_TXT_4 "- WMR (разделяемая память), не удалось подключится, мастер ключ: %d\n"
#define WMR_UTIL_C_TXT_5 "- WMR (разделяемая память), неправильный ключ инициализации\n\n"
#define WMR_UTIL_C_TXT_6 "- WMR (разделяемая память), ошибка инициализации - ключ используемый потомком: %d\n\n"
#define WMR_UTIL_C_TXT_7 "- WMR (разделяемая память), не удалось подключится, ключ потомка: %d\n"
#define WMR_UTIL_C_TXT_8 "- WMR [%d/%d] (разделяемая память) Прикрепить:%d  Создатель:%d разделяемая память:%d\n"
#define WMR_UTIL_C_TXT_9 "- WMR очистка структуры weather, PID:%d  MAINpid:%d  selN:%d\n"
#define WMR_UTIL_C_TXT_10 "- WMR [%d/%d] (разделяемая память) Прикрепить:%d Создатель:%d Последние соединение:%d\n"
#define WMR_UTIL_C_TXT_11 "- WMR (разделяемая память), [%d] открепить не удалось: %d - ключ: %d/%d\n"
#define WMR_UTIL_C_TXT_12 "- WMR (разделяемая память), [%d] открепление успешно - ключ: %d/%d\n"
#define WMR_UTIL_C_TXT_13 "- WMR (разделяемая память), [%d] удаление сегмента не удалось: %d  - ключ: %d/%d\n"
#define WMR_UTIL_C_TXT_14 "- WMR (разделяемая память), [%d] удаление сегмента успешно - ключ: %d/%d\n"
#define WMR_UTIL_C_TXT_15 "- WMR: hid_close - ошибка выполнения: %d\n"
#define WMR_UTIL_C_TXT_16 "- WMR: hid_cleanup - ошибка выполнения: %d\n"
#define WMR_UTIL_C_TXT_17 "- Очистка файлов, ошибка выполнения команды: %s\n"
#define WMR_UTIL_C_TXT_18 "- Очистка файлов, успешно: %s\n"
#define WMR_UTIL_C_TXT_19 "\tУже запущена другая копия %s\n\tДля выхода из запущенной программы, выполните: kill -TERM `pidof wmrd`\n\tВыход ...\n\n"
#define WMR_UTIL_C_TXT_20 "- Создание файла блокировки, успешно: %s\n"
#define WMR_UTIL_C_TXT_21 "- Создание файла блокировки, ошибка: %s\n- Выход ...\n"
#define WMR_UTIL_C_TXT_22 "- ОШИБКА: Не удается удалить файл блокировки: %s\n"
#define WMR_UTIL_C_TXT_23 "- Удалил файл блокировки, успешно: %s\n"
#define WMR_UTIL_C_TXT_24 ", - Добавление PID в файл блокировки, успешно: %s\n"
#define WMR_UTIL_C_TXT_25 ", - Добавление PID в файл блокировки, ошибка: %s\n- Выход ...\n"
#define WMR_UTIL_C_TXT_26 ", - Добавление PID:%d потомка в файл блокировки, успешно:%s\n"
#define WMR_UTIL_C_TXT_27 ", - Добавление PID:%d потомка в файл блокировки, ошибка: %s\n"
#define WMR_UTIL_C_TXT_28 "- ОШИБКА: Невозможно прочитать файл блокировки: %s\n\n"
#define WMR_UTIL_C_TXT_29 "- ОШИБКА: не могу остановить демона PID%d\n\n"
#define WMR_UPDEXEC_C_TXT_1 "- UPD запускаю файл: %s (%d) [%d]\n"
#define WMR_UPDEXEC_C_TXT_2 "- UPD Exec ошибка: выполниния файла: (%s)\n"
#define WMR_UPDEXEC_C_TXT_3 "- UPD Выполнен файл: OK (%s /%s) [%d]\n"
#define WMR_UPDEXEC_C_TXT_4 "- UPD Exec ошибка: не удалось открыть каталог: %s\n"
#define WMR_UPDEXEC_C_TXT_5 "- UPD Потомок получил сигнал завершения: (%d) PID:%d  PPID:%d\n"
#define WMR_UPDEXEC_C_TXT_6 "- Ожидание потомка PID:%d/%d/%d статус:%d сигнал:%d\n"
#define WMR_UPDEXEC_C_TXT_7 "- UPD Exec: Дочерний процесс, PID:%d  CPID:%d запуск:%d время ожидания:%d\n"
#define WMR_UPDEXEC_C_TXT_8 "- UPD Exec: Выход из доченего роцесса, PID:%d CPID:%d PPID:%d запуск:%d\n"
#define WMR_UPDEXEC_C_TXT_9 "- UPD Exec: Выход из родительского процесса, PID:%d CPID:%d PPID:%d запуск:%d\n"
#define WMR_UPDEXEC_C_TXT_10 "- WMR (буфер обмена данными о погоде) - ошибка инициализации\n\n"
#define WMR_UPDEXEC_C_TXT_11 "- UPD Exec команда:\n\n"
#define WMR_UPDEXEC_C_TXT_12 "- UPD Exec Ошибка: не удалось создать дочерний процесс, повторить ...\n"
#define WMR_CONF_C_TXT_1 "\nКонфигурационный файл (%s) - настройки:\n" \
"- Режим демона:\t\t%d\n" \
"- Системное логирование включить:\t%d\n" \
"- Путь к файлу блокировки:\t%s\n" \
"- SQL включить:\t\t%d\n" \
"- SQL путь и имя базы:\t%s\n" \
"- Файл журнала включить:\t%d\n" \
"- Файл журнала путь:\t%s\n" \
"- RRD базы данных включить:\t%d\n" \
"- RRD путь к исполняемому файлу:\t%s\n" \
"- RRD путь сохранения баз:\t%s\n" \
"- UPD включить:\t\t%d\n" \
"- UPD время:\t\t%d\n" \
"- UPD путь к исполняемой папке:\t%s\n" \
"- Скрипт обнуления файлов - путь:\t%s\n" \
"- Сигнализацию включить:\t\t%d\n" \
"- Скрипт сигнализации - путь:\t%s\n" \
"- SNPM включить:\t\t%d\n" \
"- Debug включить:\t\t%d\n\n" \
"- Корректировка датчиков:\n" \
"\t\tТемпература:\t\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tВлажность:\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tВода:\t\t%d %d %d %d\n" \
"\t\tДавление:\t%d\n" \
"\t\tВетер:\t\t%d\n" \
"\t\tОсадки:\t\t%d\n" \
"\t\tУФ излучение:\t\t%d\n" \
"- Сигнализация датчиков (мин/макс):\n" \
"\t\tТемпература мин:\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tТемпература макс:\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tВлажность мин:\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tВлажность макс:\t%d %d %d %d %d %d %d %d %d %d\n" \
"\t\tВода мин:\t%d %d %d %d  \n" \
"\t\tВода макс:\t%d %d %d %d  \n" \
"\t\tДавление:\t%d/%d\n" \
"\t\tВетер:\t\t%d/%d\n" \
"\t\tОсадки:\t\t%d/%d\n" \
"\t\tУФ излучение:\t\t%d/%d\n" \
"- Стандарт данных датчиков:\n" \
"\t\tТемпература:\t\t%d\n" \
"\t\tДавление:\t%d\n" \
"\t\tВетер:\t\t%d\n" \
"\t\tОсадки:\t\t%d\n" \
"\t\tТемп. воды:\t\t%d\n" \
"\t\tУФ излучение:\t\t%d  \n"
#define WMR_CONF_C_TXT_2 "\nКонфигурация SNMP протокола:\n" \
"- Порт сервера:\t\t%d\n" \
"- Cmmunity:\t\t%s\n" \
"- Расположение:\t\t%s\n" \
"- Долгота:\t\t%s\n" \
"- Широта:\t\t%s\n" \
"- Контактный E-mail:\t\t%s\n" \
"- Контактный телефон:\t%s\n" \
"- Контакт в Skype:\t%s\n" \
"- Контакт в ICQ:\t\t%s\n" \
"- Страничка WWW:\t\t%s\n\n"
#define WMR_CONF_C_TXT_3 "Нет конфигурационного файла %s, не могу сохранть информацию логирования!\n"
#define WMR_CONF_C_TXT_4 "Ошибка при чтении файла %s, строка (%s)\n"
#define WMR_CONF_C_TXT_5 "Путь к файлу конфигурации НЕ определен\nИспользовано по умолчанию: /etc/wmr/wmr.conf\nИспользуйте:\n\t\t%s -c </путь/к/файлу/конфигурации>\tПуть к конфигурационноиу файлу\n"
#define WMR_CONF_C_TXT_7 "Путь к файлу блокировки НЕ определен\nИспользовано по умолчанию: /var/lock/%s.lock\nИспользуйте:\n\t\t%s </путь/к/файлу/блокировки>\tПуть к файлу блокировки\n"
#define WMR_CONF_C_TXT_8 "Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600/RMS300 USB Station Reader\n\n" \
"(С) 2012-2013 Den68 <idg68@yandex.ru>\n" \
"Благодарность Barnaby Gray <barnaby@pickle.me.uk> (идея 2009)\n" \
"Смотрите http://www.nkl.ru/support/wmr/ для получения дополнительной информации\n\n" \
"Параметры:\n" \
"-s Включить SysLog хранения информации работа регистратора\n" \
"-c </путь/к/конфигурационному.файлу>\tПуть к конфигурационному файлу\n" \
"-l </путь/к/файлу/блокировки/>\tМесто где создавать файл блокировки\n" \
"-v Посмотреть конфигурационный файл информации statment\n" \
"-k Прекращение работы демон, выход из программы\n" \
"-h Эта справка\n\n"
