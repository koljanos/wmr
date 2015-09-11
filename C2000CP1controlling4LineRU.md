# Alarm / События #
```
Добавлена возможность вызывать исполняемый файл при наступления 
какого либо события. 
Событием считается переход границы заданных параметров в описании  датчика в конфигурационном файле, в секции Alarm. 
```
```
Поддерживаются минимальный  порог и максимальный порог. 
Исполняемому файлу (скрипту), в случе наступления того или иного
 события передаются следующие параметры: 
```
```
/path/to/script/wmr_alarm.sh 'ТИП ДАТЧИКА' 'НОМЕР ДАТЧИКА' 'ТЕКУЩИЕ ПОКАЗАНИЯ' 'МАКС/МИН'  

    например:

    /path/to/script/wmr_alarm.sh TEMP 1 -22 MIN
    /path/to/script/wmr_alarm.sh PRESSURE 0 778 MAX
    /path/to/script/wmr_alarm.sh HUMIDITY 3 12 MIN 

Контроль питания реализуется типом сенсора 'BATTERY', при этом скрипту обработки
событий передаются следуюшие параметры:

    /path/to/script/wmr_alarm.sh BATTERY 'NUM SENSOR' 'VALUE SENSOR' 'TYPE SENSOR'

    например:

    /path/to/script/wmr_alarm.sh BATTERY 1 7 TEMP
    /path/to/script/wmr_alarm.sh BATTERY 0 11 MAIN

Существующие типы обработки сенсоров:

    Информационные сенсоры: "TEMP", "HUMIDITY", "PRESSURE", "WIND", "RAIN", "UV"
    Проверка состояния батареи питания: "MAIN", "WATER", "TEMP", "WIND", "RAIN", "UV"
```
```
Добавлен протокол и библиотека управления Блоком сигнально-пусковым
 С2000-СП1, С2000-СП1 исп.01
 (http://www.bolid.ru/production/devices/devices_48.html)  
```
![http://www.nkl.ru/support/wmr/oregon_img/BOLID_C2000_SP1.jpg](http://www.nkl.ru/support/wmr/oregon_img/BOLID_C2000_SP1.jpg)
```
Блок расчитан на управление 4 силовыми линиями, по интерфейсу RS485, доступен по цене.   
```
```
Скрипт управления вызываемый по событиям: script/wmr_alarm.sh  
Скрипт управления Болид С2000-СП1: script/controlling/C2000-CP1.php   
```
```
В скрипте подразумевается что сетевой адрес устройства С2000-СП1 равен
127, в дальнейшем я доработаю библиотеку, и добавлю управление другими 
устройствами компании Болид напрямую.
```
```
Если у вас есть желание помочь, и есть в наличие приборы компании Болид -
пишите! необходимо снимать логи протокола обмена в разных условиях эксплуатации.
```
```
Это решение можно использовать для включения/регулировок отопления, включения 
вентиляции, апарата увлажнения воздуха, поливом растений, автоматическое 
закрывание роль-ставен при сильном порывистом ветре или при повышенном излучении 
ультрофиолета (датчик UV), управление кондиционером, и иные задачи связанные с 
автоматизацией по погодным критериям "умного дома".
```
# ТЕХНИЧЕСКИЕ ХАРАКТЕРИСТИКИ С2000-СП1 #
```
Независимое управление каждым из четырех реле по интерфейсу RS-485
Программируемая логика управления реле позволяет:
- управлять различными исполнительными устройствами 
  (световые и звуковые оповещатели, электромагнитные замки и другие)
- использовать реле для передачи извещений на пульт централизованного наблюдения
- организовывать взаимодействие с системой видеонаблюдения
- осуществлять автоматическое переключение линий с помощью интерфейса RS-485
- контроль за напряжением питания на каждом из двух вводов и наличием связи по 
  интерфейсу RS-485
- световые индикаторы состояния каждого реле
- мощные выходные реле "С2000-СП1" исп.01 позволяют:
     управлять силовыми исполнительными устройствами (световые и звуковые оповещатели, электромагнитные замки и другие)
     управлять силовой автоматикой (вентиляция, дымоудаление и др.)
- передача сообщений по интерфейсу RS-485 на пульт "С2000" или АРМ "Орион" 
  (и не только ..(c) @Den68)
```
# СПЕЦИФИКАЦИЯ #
```
- Количество выходов - 4 релейных выхода с переключаемыми контактами
- Напряжение питания - 10 В ... 28 В
- Потребляемый ток прибором, не более
  "С2000-СП1" - 140 мА
  "С2000-СП1" исп.01 - 300 мА
- Максимальная коммутируемая мощность каждого реле
  "С2000-СП1" - 30 ВА
  "С2000-СП1" исп.01 - 2500 ВА
- Максимальное коммутируемое напряжение
- "С2000-СП1" - 100 В
  "С2000-СП1" исп.01 - ~280 В, =125 В
- Максимальный коммутируемый ток одного канала
  "С2000-СП1" - 2 А
  "С2000-СП1" исп.01 - 7 (10*) А (* кратковременно)
- Рабочий диапазон температур - от минус 30 до +55 °С
- Габаритные размеры - 150 х 103 х 35 мм
```