'''
links      | email      | login | password  	- Keys
http://fds | fgd@fgd.ru | admin | fgdfgdf 	- Values
'''
repeat="y"
while repeat == "y":
	keys=['links', 'mails', 'logins', 'passwords']
	print(keys)	
	#print(keys[1])

	values=[]
	#print(values)
	link, email, login, password= input("Enter the link: "), input("Enter email: "), input("Enter login: "), input("Enter password: ")
	values.append(link)
	values.append(email)
	values.append(login)
	values.append(password)
	print(values)
	#print(values[2])

	row={}
	for i in range(len(keys)):
		#print(keys[i])
		#row[keys[i]] = None
		row[keys[i]] = values[i]
	print(row)

	createfile = input("Create new file? (y/n): ")
	if createfile == "y":
		namefile = input("Name the file where the passwords will be stored: ")
		with open(namefile,'w') as file:
			#file.write(str(row))
			for key, value in row.items():
				#print("Key: " + key)
				keyRow="|	"+str(key)+"	|"
				file.write(keyRow)
			file.write("\n")
			for key, value in row.items():
				valueRow="|	"+str(value)+"	|"
				file.write(valueRow)
			file.close()

	elif createfile == "n":
		namefile = input("Write the name of the file in which you want to make changes: ")
		with open(namefile,'a') as file:
			file.write("\n")
			for key, value in row.items():
				valueRow="|	"+str(value)+"	|"
				file.write(valueRow)
			file.write("\n")
			file.close()

	repeat = input("Do you want to continue? (y/n): ")
	if repeat == "n":
		break
	while (repeat!="y" and repeat!="n"):
		repeat = input("Please enter the correct answer (y/n): ")