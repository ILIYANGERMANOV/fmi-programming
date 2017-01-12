import sys, os, re

arguments_count = len(sys.argv)
if(arguments_count > 3):
	TESTS_PATH = sys.argv[3]
elif(arguments_count == 1):
	sys.exit("pyhton prepare_task INPUT_FILE TASK_NUMBER TESTS_DIR (optional)")

FILE_PATH = sys.argv[1]
TASK_NUMBER = sys.argv[2]
TESTS_DIR = "../testing"
	
COMMENT = "/**\n *  \n * Solution to homework task \n * Introduction to programming course \n * Faculty of Mathematics and Informatics of Sofia University \n * Winter semester 2016/2017 \n * \n * @author %s \n * @idnumber %s \n * @task %s \n * @compiler %s \n * \n */"

NAME = "Iliyan Germanov"
FACULTY_NUMBER = "81521"
COMPILER = "GCC"	

def generate_output_file_with_ascii_encoding(filepath):
	output_file_name = "fn%s_prob%s_gcc.cpp" % (FACULTY_NUMBER, TASK_NUMBER)
	command = "iconv -t ASCII %s > %s" %(filepath, output_file_name)
	os.system(command)
	return "./" + output_file_name

def append_comment_to_file():
	with file(FILE_PATH, "r+") as f:
		content = f.read();
		f.seek(0)
		f.write(COMMENT % (NAME, FACULTY_NUMBER, TASK_NUMBER, COMPILER))
		f.write('\n')
		f.write(content)
		f.truncate()

def print_tests_result(filepath, tests_dir):
	os.system("cp %s %s" % (filepath, tests_dir))
	os.chdir(tests_dir)
	print os.system("./test.sh") 
	

append_comment_to_file()
generated_file_path = generate_output_file_with_ascii_encoding(FILE_PATH)
print_tests_result(generated_file_path, TESTS_DIR)
