# -*- coding: utf-8 -*-
"""
Created on Thu Sep 17 13:51:02 2015

@author: Wasit
"""

from bs4 import BeautifulSoup
import urllib2
import codecs


if __name__ == "__main__":
    url = "https://th.wikipedia.org/wiki"
    content = urllib2.urlopen(url).read()
    soup = BeautifulSoup(content)
    alltext=u''
    
    for node in soup.findAll('p'):
        alltext+=unicode.join(u'',map(unicode,node.findAll(text=True)))
        
    with codecs.open("text.txt", "w", "utf-8-sig") as temp:
        temp.write(alltext)
