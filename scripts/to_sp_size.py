import sys


filename = sys.argv[1]
lines = int(sys.argv[2])

f = open(filename, 'a')

while lines < 4096:
	f.write('00000000\n')
	lines += 1
f.close()
