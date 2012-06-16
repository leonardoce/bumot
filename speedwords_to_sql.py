import sys

def error(l):
    print >>sys.stderr, "ERROR:", l

def output(s):
    print s

def stosingle(s):
    result = "'"
    for c in s:
        if c=="'":
            result += "''"
        else:
            result += c

    result += "'"

    return result

def convert(fileName):
    for l in open(fileName):
        l = l.strip()
        if len(l)==0: continue
        if l[0]=='#': continue

        pair = l.split("\t")
        if len(pair)!=2:
            error(l)
            continue

        if pair[0][0]!="-" and pair[0][-1]!="-":
            finrap = pair[0].replace('-','')
        else:
            finrap = pair[0]

        query = "INSERT INTO dict (rap, mot, finrap) VALUES (" + \
          stosingle(pair[0]) + "," + \
          stosingle(finrap) + "," + \
          stosingle(pair[1]) + ");"

        output(query)

convert("Speedwords.dict")