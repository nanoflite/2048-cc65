import sys
import json

def chunker(seq, size):
  return (seq[pos:pos + size] for pos in xrange(0, len(seq), size))

translation_table = {
  0x42: 0x5D,
  0x43: 0x40
}

def translate(char, platform):

  if platform == 'c64': return char

  if char in translation_table:
    return translation_table[char]

  return char
  
platform = sys.argv[1]
name = sys.argv[2]
fp = open(sys.argv[3], 'r')
js = json.load(fp)

print "unsigned char %s[] = {" % name
for group in chunker(js['charData'], 40):
  for char in group:
    print "0x%02x," % translate( char, platform ),
  print ""
print "};"
print "unsigned int %s_len = %d;" % ( name, len( js['charData'] ) )

fp.close()
