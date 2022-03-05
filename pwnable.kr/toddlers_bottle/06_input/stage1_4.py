import os
import subprocess
import sys

iArgv = ['a' for i in range(100)]
iArgv[0] = "/home/input2/input"

# argv
iArgv[ord('A')] = ""   # strcmp "\x00" = strcmp ""
iArgv[ord('B')] = "\x20\x0a\x0d"

# stdio
stdinF = open("stdinF","wb")
stdinF.write("\x00\x0a\x00\xff")
stdinF.close()

stdoutF = open("stdoutF","wb")
stdoutF.write("\x00\x0a\x02\xff")
stdoutF.close()

# env
os.environ["\xde\xad\xbe\xef"] = "\xca\xfe\xba\xbe"

# file
fileF = open("\x0a","wb")
fileF.write("\x00\x00\x00\x00")
fileF.close()

# network
iArgv[ord('C')] = sys.argv[1]

subprocess.Popen(iArgv, stdin=open("stdinF","rb"), stderr=open("stdoutF","rb"))