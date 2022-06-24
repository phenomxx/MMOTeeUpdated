s = input("String: ")
delim = input("Delimiter: ")

a = s.split(delim)
for b in a:
	b += delim

s2 = ""
for b in a:
	s2 += b + "\n"

f = open("conv.txt", "w")
f.write(s2)
f.close()
