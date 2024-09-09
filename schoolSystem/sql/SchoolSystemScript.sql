CREATE DATABASE schoolSystem;
USE schoolSystem;

CREATE TABLE tbl_admin(
	id INT AUTO_INCREMENT,
	name VARCHAR(25) NOT NULL UNIQUE,
	pass VARCHAR(256) NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE tbl_teacher(
	id INT AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	lastName VARCHAR(50) NOT NULL,
	userName VARCHAR(50) NOT NULL UNIQUE,
	pass VARCHAR(256) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE tbl_student(
	id INT AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	lastName VARCHAR(50) NOT NULL,
	userName VARCHAR(50) NOT NULL UNIQUE,
	pass VARCHAR(256) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE tbl_lesson(
	id INT AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE mm_lesson_teacher(
	id INT AUTO_INCREMENT,
	fk_lesson INT NOT NULL,
	fk_teacher INT NOT NULL,
	FOREIGN KEY (fk_lesson) REFERENCES tbl_lesson(id),
	FOREIGN KEY (fk_teacher) REFERENCES tbl_teacher(id),
	PRIMARY KEY(id)
);

CREATE TABLE mm_lesson_student(
	id INT AUTO_INCREMENT,
	fk_lesson INT NOT NULL,
	fk_student INT NOT NULL,
	FOREIGN KEY (fk_lesson) REFERENCES tbl_lesson(id),
	FOREIGN KEY (fk_student) REFERENCES tbl_student(id),
	PRIMARY KEY(id)
);

CREATE TABLE tbl_address(
	id INT AUTO_INCREMENT,
	country VARCHAR(100) NOT NULL,
	city VARCHAR(50) NOT NULL,
	postCode VARCHAR(25) NOT NULL,
	street VARCHAR(100) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE mm_address_teacher(
	id INT AUTO_INCREMENT,
	fk_address INT NOT NULL,
	fk_teacher INT NOT NULL,
	FOREIGN KEY (fk_address) REFERENCES tbl_address(id),
	FOREIGN KEY (fk_teacher) REFERENCES tbl_teacher(id),
	PRIMARY KEY(id)
);

CREATE TABLE mm_address_student(
	id INT AUTO_INCREMENT,
	fk_address INT NOT NULL,
	fk_student INT NOT NULL,
	FOREIGN KEY (fk_address) REFERENCES tbl_address(id),
	FOREIGN KEY (fk_student) REFERENCES tbl_student(id),
	PRIMARY KEY(id)
);

CREATE TABLE tbl_class(
	id INT AUTO_INCREMENT,
	name VARCHAR(25) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE mm_class_teacher(
	id INT AUTO_INCREMENT,
	fk_class INT NOT NULL,
	fk_teacher INT NOT NULL,
	FOREIGN KEY (fk_class) REFERENCES tbl_class(id),
	FOREIGN KEY (fk_teacher) REFERENCES tbl_teacher(id),
	PRIMARY KEY(id)
);

CREATE TABLE mm_class_student(
	id INT AUTO_INCREMENT,
	fk_class INT NOT NULL,
	fk_student INT NOT NULL,
	FOREIGN KEY (fk_class) REFERENCES tbl_class(id),
	FOREIGN KEY (fk_student) REFERENCES tbl_student(id),
	startDate DATE NOT NULL,
	endDate DATE DEFAULT NULL,
	PRIMARY KEY(id)
);

INSERT INTO tbl_admin(name, pass) VALUES("Admin", "admin12345");


