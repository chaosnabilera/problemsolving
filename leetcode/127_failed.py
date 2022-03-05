from typing import List

def countDiff(word1, word2):
	cnt = 0
	for i in range(len(word1)):
		if word1[i] != word2[i]:
			cnt += 1
	return cnt

def canJump(word1, word2):
	cnt = 0
	for i in range(len(word1)):
		if word1[i] != word2[i]:
			cnt += 1
		if cnt > 1:
			return False
	return True

class Solution:
	def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
		bedcount = countDiff(beginWord, endWord)

		difflist = [[] for i in range(len(beginWord)+1)]
		for i in range(len(wordList)):
			difflist[countDiff(beginWord,wordList[i])].append(i)

		# check for sanity
		for i in range(1,bedcount+1):
			if len(difflist[i]) == 0:
				return 0

		# check for sanity 2
		ci = -1
		for i in range(len(wordList)):
			if wordList[i] == endWord:
				ci = i
				break
		if ci < 0:
			return 0

		# Map of number to difference to beginWord
		numtodiffcnt = [-1]*len(wordList)
		for i in range(1,len(beginWord)+1):
			for n in difflist[i]:
				numtodiffcnt[n] = i

		# Find necessary links
		numjump = [None for i in range(len(wordList))]
		numjump[ci] = 0
		curlvidx = [ci]
		nextlvidx = []
		lv = 1
		while len(curlvidx) > 0:
			for i in curlvidx:
				i_diffcnt = numtodiffcnt[i]
				for n in difflist[i_diffcnt]:
					if (numjump[n] == None) and (n != i) and canJump(wordList[n], wordList[i]):
						numjump[n] = lv
						nextlvidx.append(n)

				for n in difflist[i_diffcnt-1]:
					if (numjump[n] == None) and canJump(wordList[n], wordList[i]):
						numjump[n] = lv
						nextlvidx.append(n)
			lv += 1
			curlvidx = nextlvidx
			nextlvidx = []

		print(numjump)
		print(difflist)

		# Find minimum among diff = 1
		minjump = 0xFFFFFFFF
		for i in range(len(difflist[1])):
			if numjump[difflist[1][i]] != None and minjump > numjump[difflist[1][i]]:
				minjump = numjump[difflist[1][i]]

		if minjump == 0xFFFFFFFF:
			return 0
		else:
			return minjump+2

sol = Solution()


bw = "ymain"
ew = "oecij"
wl = ["ymann","yycrj","oecij","ymcnj","yzcrj","yycij","xecij","yecij","ymanj","yzcnj","ymain"]

# bw = "hit"
# ew = "cog"
# wl = ["hot","dot","tog","cog"]

# bw = "a"
# ew = "c"
# wl = ["a","b","c"]

# bw = "cet"
# ew = "ism"
# wl = ["kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"]

# bw = 'hit'
# ew = 'cog'
# wl = ["hot","dot","dog","lot","log","cog"]

# bw = beginWord = "hit"
# ew = endWord = "cog"
# wl = wordList = ["hot","dot","dog","lot","log"]
print(sol.ladderLength(bw, ew, wl))