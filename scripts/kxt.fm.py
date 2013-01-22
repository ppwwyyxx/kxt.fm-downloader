#!/usr/bin/python
#-*- coding: utf-8-*-
# $File: kxt.fm.py
# $Date: Tue Jan 22 21:09:56 2013 +0800
# Author: ppwwyyxxc@gmail.com
# This scripts requires python3

_songurl = "http://kxt.fm/?p="
import sys
import urllib
import re
import http.cookiejar


def retrieve_addr(page):
    pattern = '.*soundFile.*'
    raw_addr = re.search(pattern,
                         page).group(0).rpartition(':')[-1][1:-4].strip()

    # fix wrong format of b64 code
    rem = 3 - (len(raw_addr) - 1) % 4
    raw_addr = raw_addr + '=' * rem

    import base64
    addr = base64.b64decode(raw_addr)

    match = re.search(b'^.*mp3', addr)
    return match.group(0).decode().strip()


def down(index):
    url = _songurl + index.strip()
    jar = http.cookiejar.CookieJar()
    jar.extract_cookies(urllib.request.urlopen(url),
                        urllib.request.Request(url))
    handler = urllib.request.HTTPCookieProcessor(jar)
    opener = urllib.request.build_opener(handler)
    urllib.request.install_opener(opener)

    page = urllib.request.urlopen(url).read().decode()
    #page = open("index.html","r").read()
    addr = retrieve_addr(page)
    print(addr)
    file_name = re.search('[^/]*mp3', addr).group(0).strip()

    req = urllib.request.Request(addr)
    req.add_header('Connection', 'keep-alive')
    req.add_header('User-Agent', 'Mozilla/5.0 (X11; Linux x86_64) \
                   AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 \
                   Safari/537.4')
    req.add_header('Referer',
                   'http://ear.duomi.com/wp-content/plugins/audio-player/assets/player.swf?ver=2.0.4.1')
    music = urllib.request.urlopen(req).read()
    ofile = open(file_name, "wb")
    ofile.write(music)
    ofile.close()


if __name__ == "__main__":
    index = sys.argv[1]
    down(index)
