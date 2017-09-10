#!/usr/bin/python3

import os
import subprocess

FILE_LOCAL = "engauge_en.ts"
FILE_DOWNLOAD = "for_use_engauge-digitizer_engauge_ents_en.ts"
TMP_LOCAL = ".local"
TMP_DOWNLOAD = ".download"

def massageDownload (content):
    # Remove translation values
    start = 0
    out = ''
    lastEnd = 0
    while True:
        start = content.find ("<translation>", start)
        if start == -1:
            break
        end = content.find ("</translation>", start)
        out = out + content [lastEnd : start] + '<translation type="unfinished"></translation>'
        lastEnd = end + len ("</translation>")
        start = lastEnd
    out = out + content [lastEnd :]
    
    return out

def massageLocal (content):
    return content

def main ():
    with open (FILE_LOCAL, "r") as fLocal:
        content = massageLocal (fLocal.read ())
        with open (TMP_LOCAL, "w") as tLocal:
            tLocal.write (content)
            tLocal.close ()
        fLocal.close ()

    with open (FILE_DOWNLOAD, "r") as fDownload:
        content = massageDownload (fDownload.read ())
        with open (TMP_DOWNLOAD, "w") as tDownload:
            tDownload.write (content)
            tDownload.close ()
        fDownload.close ()    

    p = subprocess.Popen (['meld',
                           TMP_LOCAL,
                           TMP_DOWNLOAD])
    p.wait ()

    os.remove (TMP_LOCAL)
    os.remove (TMP_DOWNLOAD)

main ()
