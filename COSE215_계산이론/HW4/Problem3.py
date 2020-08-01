import re

f = open("D:/대학교/2학년/1학기/COSE215_계산이론/HW4/Kyeongseok_Yang_Research_Report.txt", 'rt', encoding='UTF8')
lines = f.read()


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

pattern_both = re.compile(r"""
((
\s                  #starts with whitespace
(?P<ssn>            #group name: ssn
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
)
\s                #ends with whitespace
)
|
(?P<email>
\s     #starts with a whitespace
(
[a-zA-Z0-9]+            #email account name
[@]                     #@
[a-zA-Z]+               #group name
[.]ac[.]kr                  #academy of korea 
)
\s     #ends with a whitespace
))""", re.VERBOSE)

p = re.compile('@[a-zA-Z]+[.]')

matched = pattern_both.finditer(lines)

for m in matched:
    if pattern_ssn.match(m.group()):
        print((m.group()[:9]).strip() + "XXXXXX")
    elif pattern_email.match(m.group()):
        X = "@" + "X" * 4 + "."
        print((p.sub(X, m.group())).strip())

f.close()