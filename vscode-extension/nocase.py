while True:
	string = input('Enter string to make regex case insensitive (-q to quit): ')
	if string == '-q':
		break
	string_new = ''
	for c in string:
		if c.isalpha():
			string_new += f'[{c.lower()}{c.upper()}]'
		else:
			string_new += f'{c}'
	print(string_new)
