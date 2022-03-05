import subprocess

if __name__ == '__main__':
	tproc = subprocess.Popen(["python","mediansort_tester.py","1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	aproc = subprocess.Popen(["python","mediansort.py"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	
	tnq = tproc.stdout.readline()
	print(tnq)
	aproc.stdin.write(tnq)

	while aproc.poll() and tproc.poll(): 
		aout = aproc.stdout.readline()
		print('aout',aout)
		tproc.stdin.write(aout)
		tout = aproc.stdout.readline()
		print('tout',tout)
		aproc.stdin.write(tout)