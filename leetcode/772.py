class Solution:
    def calculate(self, s: str) -> int:
        operator = []
        number = []
        precedence = {'':0,')':0,'+':1,'-':1,'*':2,'/':2}
        opfunc = {
            '+':lambda x,y:number.append(x+y),
            '-':lambda x,y:number.append(x-y),
            '*':lambda x,y:number.append(x*y),
            '/':lambda x,y:number.append(x//y),
        }
        digits = ''
        
        def operate_stacks(curop):
            nonlocal operator, number

            if curop == ')' and operator[-1] == '(':
                operator.pop()
                return            

            if (len(operator) == 0) or (curop == '(') or (operator[-1] == '(') or (precedence[operator[-1]] < precedence[curop]):
                operator.append(curop)
                return
            
            while (len(operator) > 0) and (operator[-1] != '(') and (precedence[operator[-1]] >= precedence[curop]):
                num2 = number.pop()
                num1 = number.pop()
                op = operator.pop()
                opfunc[op](num1,num2)
                
            if curop == ')':
                operator.pop()
            else:
                operator.append(curop)
        
        for c in s:
            #print(operator,number)
            if c in '+-*/()':
                if digits:
                    number.append(int(digits))
                    digits = ''
                operate_stacks(c)
            else:
                digits += c
                
        if digits:
            number.append(int(digits))
        
        
        #print(operator,number)
        operate_stacks('')
        
        return number[-1]


# istr = "(((12)-(((((1)+(2))*(3)-(5))-(4)/(3))*21/3)+192)-901)*(2+6*3+5-(3*14/7+2)*5)+3"
istr = "(0-3)/4"

estr = istr.replace('/','//')

ref = eval(estr)
print(ref)

sol = Solution()
print(sol.calculate(istr))


