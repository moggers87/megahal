#!/usr/bin/env python
"""A Simple script to learn from a chatlog in the irssi log format
"""


import megahal as mh

mh.initalize()

file = 'tdtrs.log'

with open(file) as log:
    for line in log:
        if line[6] == '<':
            phrase = line.partition('>')[2]
            phrase = phrase.strip()
            mh.learn(phrase)
        elif line[7] == '*':
            #deal with actions some other day
            pass

mh.cleanup()
