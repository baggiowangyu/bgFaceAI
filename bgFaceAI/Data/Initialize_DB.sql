DROP TABLE IF EXISTS 'face_info';
CREATE TABLE 'face_info'(
face_tag INTEGER PRIMARY KEY NOT NULL,
face_data BLOB NOT NULL,
face_hash VARCHAR(64) NOT NULL
);

/**
��������

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
��������
**/

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('����', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002673', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('����', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002659', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('���շ�', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002635', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('������', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002619', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('�Ƽν�', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002643', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('��ΰ��', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002649', '�����л�����', '020-110', 1);

INSERT 
INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state)
VALUES('�ܽ���', '��', '1990-01-01', '�л����񹲺͹�', '����', '����֤', 'G1002599', '�����л�����', '020-110', 1);



