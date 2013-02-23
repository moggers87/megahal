#!/usr/bin/env python
"""A Simple script to learn from a chatlog in the irssi log format
"""
import argparse
import megahal as mh

parser = argparse.ArgumentParser(description='A Simple script to learn from a chatlog in the irssi log format')
parser.add_argument('irclog', type=str, help='Log to be processed')
file = parser.parse_args().irclog

mh.initialize()

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
