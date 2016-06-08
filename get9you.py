#coding=utf-8
# -*- coding: utf-8 -*-  

import urllib
import re

def getHtml(url):
    page = urllib.urlopen(url)
    html = page.read()
    return html

#    html = getHtml("http://tieba.baidu.com/p/2738151262")
#    print html

def getGameInfo(html):
    reg = r''
    game_info = {}
    game_info['game_name'] = ''
    return ""

if __name__ == '__main__':
    #search_url = str(raw_input('url:'))
    search_url = "http://www.9game.cn/kf/"
    html = getHtml(search_url)

