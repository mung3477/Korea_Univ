import re

f = open("D:/대학교/2학년/1학기/COSE215_계산이론/HW4/Kyeongseok_Yang_Research_Report.txt", 'rt', encoding='UTF8')
lines = f.readlines()
phone = card = 0

pattern_phone = re.compile(r"""
\s
010[-]
\d{4}[-]
\d{4}
\s
""", re.VERBOSE)

pattern_card = re.compile(r"""
\s
\d{4}[-]
\d{4}[-]
\d{4}[-]
\d{4}
\s
""", re.VERBOSE)

for line in lines:
    m = pattern_phone.findall(line)
    phone += len(m)

    m = pattern_card.findall(line)
    card += len(m)

print(phone, card, sep='\n')

f.close()