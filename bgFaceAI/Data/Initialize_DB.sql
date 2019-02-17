DROP TABLE IF EXISTS 'face_info';
CREATE TABLE 'face_info'(
face_tag INTEGER PRIMARY KEY NOT NULL,
face_data BLOB NOT NULL,
face_hash VARCHAR(64) NOT NULL
);

/**
测试数据

INSERT 
INTO 'face_info'(face_tag, face_data, face_hash)
VALUES(999, '0101010102020202', 'ABCDEFGHIJKLMN');
**/

DROP TABLE IF EXISTS 'people_info';
CREATE TABLE 'people_info'(
person_number INTEGER PRIMARY KEY NOT NULL,
person_name VARCHAR(64) NOT NULL,
person_sex VARCHAR(16) NOT NULL,
person_birthday VARCHAR(64) NOT NULL,
person_country VARCHAR(128) NOT NULL,
person_nation VARCHAR(128) NOT NULL,
person_id_type VARCHAR(64) NOT NULL,
person_id_number VARCHAR(64) NOT NULL,
person_address VARCHAR(128) NOT NULL,
person_contact_way VARCHAR(128) NOT NULL,
person_state INTEGER NOT NULL
);

DROP TABLE IF EXISTS 'people_face_info';
CREATE TABLE 'people_face_info'(
face_tag INTEGER NOT NULL,
person_number INTEGER NOT NULL
);

/**
测试数据
**/

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('王煜', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002673', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('何奇', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002659', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('陈艺夫', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002635', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('宾益贤', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002619', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('黄嘉杰', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002643', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('廖伟灿', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002649', '广州市黄埔区', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('周健华', '男', '1990-01-01', '中华人民共和国', '汉族', '工作证', 'G1002599', '广州市黄埔区', '020-110', 1);



