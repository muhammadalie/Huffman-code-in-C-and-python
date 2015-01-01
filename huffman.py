import sys,string
def frequency (str) :
	freqs = {}
	for i in str :
		freqs[i] = freqs.get(i,0) + 1
	return freqs

def sortFreq (freqs) :
	letters = freqs.keys()
	tuples = []
	for let in letters :
		tuples.append((freqs[let],let))
	tuples.sort()
	return tuples

def buildTree(tuples) :
	while len(tuples) > 1 :
		leastTwo = tuple(tuples[0:2])
		theRest = tuples[2:]
		combFreq = leastTwo[0][0] + leastTwo[1][0]
		tuples= theRest + [(combFreq,leastTwo)]
		tuples.sort()
	return tuples[0]
def trimTree(tree):
	p=tree[1]
	if type(p)==type(""):return p
	else:return(trimTree(p[0]),trimTree(p[1]))
codes={}
def assignCodes(node,pat=''):
	global codes
	if type(node)==type(""):
		codes[node]=pat
	else:
		assignCodes(node[0],pat+"0")
		assignCodes(node[1],pat+"1")
def encode(str):
	global codes
	output=""
	for i in str:
		output+=codes[i]
	return output

def decode (tree, str):
	output = ""
	p = tree
	for bit in str :
		if bit == '0'	:p=p[0]
		else		:p=p[1]
		if type(p) ==type(""):
			output +=p
			p = tree
	return output

f=frequency('aaabccdeeeeeffg')
s=sortFreq(f)
print s
tree=buildTree(s)
print tree
trim=trimTree(tree)
print trim
assignCodes(trim)
k=encode('aaabccdeeeeeffg')
print k
m=decode(trim,k)
print m
