create table MAIN
(
tdate datetime PRIMARY KEY UNIQUE,
battery int(2),
powered int(2),
ddate datetime,
rf int(2),
level int(2)
);

create table TEMP 
(
tdate datetime PRIMARY KEY UNIQUE,
battery int(2),
sensor int,
smile int,
trend char(2),
temp float(5),
humidity int(3),
dewpoint float(5)
);

create table PRESSURE
(
tdate datetime PRIMARY KEY UNIQUE,
pressure float(8),
forecast int,
altpressure float(8),
altforecast int
);

create table RAIN
(
tdate datetime PRIMARY KEY UNIQUE,
battery int,
sensor int,
power int,
rate int,
hour_total float(8),
day_total float(8),
all_total float(8),
since datetime
);

create table WATER
(
tdate datetime PRIMARY KEY UNIQUE,
battery int,
sensor int,
temp float(8)
);

create table WIND
(
tdate datetime PRIMARY KEY UNIQUE,
battery int,
power int,
dir char(5),
speed float(5),
avgspeed float(5),
low_speed float(5),
high_speed float(5),
wind_chill float(5)
);

create table UV
(
tdate datetime PRIMARY KEY UNIQUE,
battery int,
uvindex int
);
