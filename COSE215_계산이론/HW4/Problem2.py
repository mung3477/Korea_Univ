import re

f = open("D:/대학교/2학년/1학기/COSE215_계산이론/HW4/Kyeongseok_Yang_Research_Report.txt", 'rt', encoding='UTF8')
lines = f.readlines()
ssn = email = 0

pattern_ssn = re.compile(r"""
\s                  #starts with whitespace
(
    (
        (98|99|01)                                 #year 98, 99, 01
        (
            (0[13578]|1[02])(0[1-9]|[12]\d|3[01])           #monthes which have day 31
            |(0[469]|11)(0[1-9]|[12]\d|30)                 #monthes which don't have day 31
            |(02(0[1-9]|1\d|2[0-8]))                       #Feburary
        )
    )
   |
    (
        00                                         #year 00...
        (
            (
                02(0[1-9]| 1\d| 2[0-9])                     #Feburary (leap year)
            )
           |
            (
                (0[13578]| 1[02])(0[1-9]| [12]\d| 3[01])      #monthes which have day 31
            )
           |
            (
                (0[469]|11)(0[1-9]| [12]\d| 30)               #monthes which don't have day 31
            )
        )
    )
)
(
[-]                #dash
[1-4]              #Gender
\d{6}              #Area code, Acceptance, Checksum
)
\s                #ends with whitespace
""", re.VERBOSE)

pattern_email = re.compile(r"""
\s     #starts with a whitespace
[a-zA-Z0-9]+            #email account name
[@]                     #@
[a-zA-Z]+               #group name
[.]ac[.]kr                  #academy of korea 
\s     #ends with a whitespace
""", re.VERBOSE)

for line in lines:
    print(line)
    m = pattern_ssn.findall(line)
    ssn += len(m)

    m = pattern_email.findall(line)
    email += len(m)

print(ssn, email, sep='\n')

f.close()