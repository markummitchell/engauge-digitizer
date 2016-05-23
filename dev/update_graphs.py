#!/usr/bin/python3

import os

with os.popen ('cd .. && /usr/bin/git --no-pager log --pretty=format:"%h %cd" .') as pipe:
    for line in pipe:
        # <commit> Fri Nov 10 12:34:56 2014 -8:00
        fields = line.strip().split(" ")
        print (fields[0] + " " + fields[5] + " " + fields[2] + " " + fields[3])
        cmd = "git checkout " + fields[0] + " ."
        os.system (cmd)

