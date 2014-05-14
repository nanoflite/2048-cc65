import sys
import json

def chunker(seq, size):
  return (seq[pos:pos + size] for pos in xrange(0, len(seq), size))

fp = open(sys.argv[1], 'r')
js = json.load(fp)

print "unsigned char introscreen[] = {"
for group in chunker(js['charData'], 40):
  for char in group:
    print "0x%02x," % char,
  print ""
print "};"
print "unsigned int introscreen_len = %d;" % len( js['charData'] )

fp.close()
