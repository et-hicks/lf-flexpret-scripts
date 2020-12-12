import sys

print(sys.argv)

filename = sys.argv[1]
lines = int(sys.argv[2])

f = open(filename, 'w')

while lines < 4097:
	f.write('00000000\n')
	lines += 1
f.close()
