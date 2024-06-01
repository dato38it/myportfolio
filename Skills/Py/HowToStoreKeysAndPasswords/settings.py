#passwd1='TestP@$$wd'
import os
#print(os.environ)
#print(type(os.environ))
#print(type(os.environ['PROGRAMDATA']))
#os.environ['passwd1']='TestP@$$wd'
#print(os.environ['passwd1'])
#os.environ['passwd1']='TestP@$$wd'
"""with open('.env', 'r') as file:
	#print(file.readline())
	line=file.readline()
	try:
		os.environ[line[:line.find("=")]]=line[line.find("=")+1:]
	except ValueError:
		pass"""
import dotenv
dotenv.load_dotenv('.env')
passwd1=os.environ['passwd1']
passwd2=os.environ['passwd2']
TIMEOUT=int(os.environ.get('TIMEOUT', 10))
