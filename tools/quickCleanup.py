with open('user.kw') as _file:
	for line in _file:
		bb = []
		a = range(0, 9)
		for i in a:
		    if  int(line[i]) > 5:
			bb.append (int (line [i]) -6)
		    elif int(line[i]) < 3:
			bb.append (int (line [i]) +6)
		    else:
			bb.append (int (line [i]))

                str1 = ''.join(str(e) for e in bb)

		print str1
