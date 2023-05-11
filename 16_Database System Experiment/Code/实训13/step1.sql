 # 请将你实现flight_booking数据库的语句写在下方：
create table "user"
(
	 user_id int primary key,
	 firstname varchar(50) not null,
	 lastname varchar(50) not null,
	 dob date not null,
	 sex char(1) not null,
	 email varchar(50) default(''),
	 phone varchar(30) default(''),
	 username varchar(20) not null,
	 "password" char(32) not null,
	 admin_tag tinyint not null default(0)
);
create unique index username_index on "user"(username);
create table passenger
(
	 passenger_id int primary key,
	 id char(18) not null,
	 firstname varchar(50) not null,
	 lastname varchar(50) not null,
	 mail varchar(50) default(''),
	 phone varchar(20) not null,
	 sex char(1) not null,
	 dob timestamp
);
create unique index passenger_index on passenger(id);
create table airport
(
	 airport_id smallint primary key,
	 iata char(3) not null,
	 icao char(4) not null,
	 "name" varchar(50) not null,
	 city varchar(50) default(''),
	 country varchar(50) default(''),
	 latitude decimal(11,8) default(0),
	 longitude decimal(11,8) default(0)
);
CREATE unique INDEX airport_index1 ON airport(icao);
CREATE unique INDEX airport_index2 ON airport(iata);
CREATE INDEX airport_index3 ON airport("name");
create table airline
(
	 airline_id int primary key,
	 "name" varchar(30) not null,
	 iata char(2) not null,
	 airport_id smallint not null,
	 Constraint FK_airline foreign key(airport_id) references airport(airport_id)
);
CREATE INDEX airline_index ON airline(airport_id);
CREATE unique INDEX airline_index2 ON airline(iata);
create table airplane
(
	 airplane_id int primary key,
	 "type" varchar(50) not null,
	 capacity smallint not null,
	 identifier varchar(50) not null,
	 airline_id int not null,
	 Constraint FK_airplane foreign key(airline_id) references airline(airline_id)
);
CREATE INDEX airplane_index ON airplane(airline_id);
create table flightschedule
(
	flight_no char(8) primary key,
	departure timestamp not null,
	arrival timestamp not null,
	duration smallint not null,
	monday tinyint default (0),
	tuesday tinyint default (0),
	wednesday tinyint default (0),
	thursday tinyint default(0),
	friday tinyint default (0),
	saturday tinyint default(0),
	sunday tinyint default(0),
	airline_id int not null,
	"from" smallint not null,
	"to" smallint not null,
	Constraint FK_flightschedule1 foreign key("from") references airport(airport_id),
	Constraint FK_flightschedule2 foreign key("to") references airport(airport_id),
	Constraint FK_flightschedule3 foreign key(airline_id) references airline(airline_id)
);
CREATE INDEX flightschedule_index1 ON flightschedule(airline_id);
CREATE INDEX flightschedule_index2 ON flightschedule("from");
CREATE INDEX flightschedule_index3 ON flightschedule("to");
create table flight
(
	flight_id int primary key,
	flight_no char(8) not null,
	departure timestamp not null,
	arrivals timestamp not null,
	duration smallint not null,
	airline_id int not null,
	airplane_id int not null,
	"from" smallint not null,
	"to" smallint not null,
	Constraint FK_flight1 foreign key(airline_id) references airline(airline_id),
	Constraint FK_flight2 foreign key(airplane_id) references airplane(airplane_id),
	Constraint FK_flight3 foreign key("from") references airport(airport_id),
	Constraint FK_flight4 foreign key("to") references airport(airport_id),
	Constraint FK_flight5 foreign key(flight_no) references flightschedule(flight_no)
);
CREATE INDEX flight_index1 ON flight(airline_id);
CREATE INDEX flight_index2 ON flight(arrivals);
CREATE INDEX flight_index3 ON flight(departure);
CREATE INDEX flight_index4 ON flight(flight_no);
CREATE INDEX flight_index5 ON flight("from");
CREATE INDEX flight_index6 ON flight("to");
create table ticket
(
	ticket_id int primary key,
	seat char(4) default(''),
	price decimal(10,2) not null,
	flight_id int  not null,
	user_id int  not null,
	passenger_id int  not null,
	Constraint FK_ticket2 foreign key(user_id) references "user"(user_id),
	Constraint FK_ticket1 foreign key(flight_id) references flight(flight_id),
	Constraint FK_ticket3 foreign key(passenger_id) references passenger(passenger_id)
);
CREATE INDEX ticket_index1 ON ticket(flight_id);
CREATE INDEX ticket_index2 ON ticket(passenger_id);
CREATE INDEX ticket_index3 ON ticket(user_id);