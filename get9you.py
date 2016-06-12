#coding=utf-8
# -*- coding: utf-8 -*-  

import urllib
import re
import time

def getHtml(url):
    page = urllib.urlopen(url)
    html = page.read().decode('utf=8')
    #print html
    return html

def getGameInfo(html):
    game_list = []

    pattern = re.compile('<div class="event-page-list (.*?)">(.*?)</ul>.*?</div>.*?</div>', re.S)
    items = re.findall(pattern, html)
    for item in items:
        #print item
        #print item[0], item[1]
        plat_from = item[0]

        pattern1 = re.compile('<li class=".*?">.*?<div class="time">.*?<span class="d">(.*?)</span>.*?<span class="t">(.*?)</span>.*?<p class="des">(.*?)</p>', re.S)
        games = re.findall(pattern1, item[1])
        for game in games:
            #print item
            date_time = game[0]
            if game[0] == u"昨天":
                date_time = time.strftime('%m-%d', time.gmtime(time.time() - 24 * 3600))
            elif game[0] == u"今天":
                date_time = time.strftime('%m-%d', time.gmtime(time.time()))
            elif game[0] == u"明天":
                date_time = time.strftime('%m-%d', time.gmtime(time.time() + 24 * 3600))
            print plat_from, date_time, game[1], game[2]
            game_info = {}
            game_info['plat_form'] = plat_from
            game_info['date'] = date_time + " " + game[1]
            game_info['server'] = game[2]
            game_list.append(game_info)

    print game_list
    return game_list

if __name__ == '__main__':
    #search_url = str(raw_input('url:'))
    search_url = "http://www.9game.cn/wangpaizhanjian/eventlist/"
    page = getHtml(search_url)
    getGameInfo(page)

