import sys
import glob
import os, os.path
import subprocess

# Move to the directory of this script
if os.path.dirname(sys.argv[0]) != "":
    os.chdir(os.path.dirname(sys.argv[0]))

lang_all = ["lang-cz", "lang-en", "lang-hu", "lang-pl", "lang-sk"]
day_all = ["day-cz", "day-hu", "day-pl", "day-sk", "day-mix1", "day-mix2"]

# Chcek argument number
if(len(sys.argv) != 3):
    sys.stderr.write(
        "Using:\n%s lang day\n\nlang <- %s\n day <- %s\n\n" %
        (sys.argv[0], str(["ALL"]+lang_all), str(["ALL"]+day_all))
    )
    sys.exit(-1)

langs = sys.argv[1].split(" ")
days = sys.argv[2].split(" ")

if langs[0] == "ALL":
    langs = lang_all

if days[0] == "ALL":
    days = day_all

def check_path(path):
    if not os.path.exists(path):
        sys.stderr.write('ERROR: no such path: "%s". Skiping.\n' % (path))
        sys.stderr.flush()
        return False
    return True


for l in langs:
    path = os.path.join("src",l)
    if not check_path(path):
        continue
    for d in days:
        path = os.path.join("src",l,d)
        if not check_path(path):
            continue
        res_path = os.path.join("build",l,d)
        if not os.path.exists(res_path):
            os.makedirs(res_path)
        for f in glob.glob(os.path.join(path,"*.tex")):
            print("Making %s."%(f))
            subprocess.call(
                ["pdflatex", "-output-directory", res_path, f],
                stdout = subprocess.PIPE
            )


