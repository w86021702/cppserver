#coding=utf-8
# -*- coding: utf-8 -*-  

import urllib
import re

def getHtml(url):
	page = urllib.urlopen(url)
	html = page.read()
	#print html
	return html

#    html = getHtml("http://tieba.baidu.com/p/2738151262")
#    print html

def getGameInfo(html):
	#pattern = re.compile('<ul class="new-list">.*?>.*?</a>', re.S)  
	#pattern = re.compile('<a href="/mjzr/433693.html" title=".*?" data-statis="text:txt_index-549314_yxzl_po-1_news-433693">06月26日11:00安卓新服火爆开启</a>', re.S)  
	pattern = re.compile(r'mjzr/.*?', re.S)  
	items = re.findall(pattern, html)
	for item in items:
		print item, item[0], item[1]
    #reg = r''
	game_info = {}
	game_info['game_name'] = ''
	return ""

if __name__ == '__main__':
	#search_url = str(raw_input('url:'))
	search_url = "http://www.9game.cn/kf/"
	page = getHtml(search_url)
	getGameInfo(page)

