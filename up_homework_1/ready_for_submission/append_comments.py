import sys, os, re
FILE_PATH = sys.argv[1]
TASK_NUMBER = sys.argv[2]

COMMENT = "/**\n*  \n* Solution to homework task \n* Introduction to programming course \n* Faculty of Mathematics and Informatics of Sofia University \n* Winter semester 2016/2017 \n* \n* @author %s \n* @idnumber %s \n* @task %s \n* @compiler %s \n* \n*/"

NAME = "Iliyan Germanov"
FACULTY_NUMBER = "81521"
COMPILER = "GCC"	

with file(FILE_PATH, "r+") as f:
	content = f.read();
	f.seek(0)
	f.write(COMMENT % (NAME, FACULTY_NUMBER, TASK_NUMBER, COMPILER))
	f.write('\n')
	f.write(content)
	f.truncate()
