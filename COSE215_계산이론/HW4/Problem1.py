import re

morseCode_in = input()
morseCode = morseCode_in.split()
original = ""

morseCode_dic = {
    re.compile('[.][-]'): 'a',
    re.compile('[-][.]{3}'): 'b',
    re.compile('([-][.]){2}'): 'c',
    re.compile('[-][.]{2}'): 'd',
    re.compile('[.]'): 'e',
    re.compile('[.]{2}[-][.]'): 'f',
    re.compile('[-]{2}[.]'): 'g',
    re.compile('[.]{4}'): 'h',
    re.compile('[.]{2}'): 'i',
    re.compile('[.][-]{3}'): 'j',
    re.compile('[-][.][-]'): 'k',
    re.compile('[.][-][.]{2}'): 'l',
    re.compile('[-]{2}'): 'm',
    re.compile('[-][.]'): 'n',
    re.compile('[-]{3}'): 'o',
    re.compile('[.][-]{2}[.]'): 'p',
    re.compile('[-]{2}[.][-]'): 'q',
    re.compile('[.][-][.]'): 'r',
    re.compile('[.]{3}'): 's',
    re.compile('[-]'): 't',
    re.compile('[.]{2}[-]'): 'u',
    re.compile('[.]{3}[-]'): 'v',
    re.compile('[.][-]{2}'): 'w',
    re.compile('[-][.]{2}[-]'): 'x',
    re.compile('[-][.][-]{2}'): 'y',
    re.compile('[-]{2}[.]{2}'): 'z',
    re.compile('[-]{5}'): '0',
    re.compile('[.][-]{4}'): '1',
    re.compile('[.]{2}[-]{3}'): '2',
    re.compile('[.]{3}[-]{2}'): '3',
    re.compile('[.]{4}[-]'): '4',
    re.compile('[.]{5}'): '5',
    re.compile('[-][.]{4}'): '6',
    re.compile('[-]{2}[.]{3}'): '7',
    re.compile('[-]{3}[.]{2}'): '8',
    re.compile('[-]{4}[.]'): '9',
    re.compile('([.][-]){3}'): '.',
    re.compile('[-]{2}[.]{2}[-]{2}'): ',',
    re.compile('[.]{2}[-]{2}[.]{2}'): '?',
    re.compile('[.][-]{4}[.]'): "'",
    re.compile('([-][.]){2}[-]{2}'): '!',
    re.compile('[-][.]{2}[-][.]'): '/',
    re.compile('[-][.][-]{2}[.]'): '(',
    re.compile('[-][.][-]{2}[.][-]'): ')',
    re.compile('[.][-][.]{3}'): '&',
    re.compile('[-]{3}[.]{3}'): ':',
    re.compile('([-][.]){3}'): ';',
    re.compile('[-][.]{3}[-]'): '=',
    re.compile('([.][-]){2}[.]'): '+',
    re.compile('[-][.]{4}[-]'): '-',
    re.compile('[.]{2}[-]{2}[.][-]'): '_',
    re.compile('([.][-][.]){2}'): '"',
    re.compile('[.]{3}[-][.]{2}[-]'): '$',
    re.compile('[.][-]([-][.]){2}'): '@',
    re.compile('[.]([.][-]){2}'): '¿',
    re.compile('[-]{2}[.]{3}[-]'): '¡'
}
keys = morseCode_dic.keys()

for code in morseCode:
    for key in keys:
        m = key.match(code)
        if m and m.start() == 0 and m.end() == len(code):
            original += morseCode_dic[key]
            break

print(original)
