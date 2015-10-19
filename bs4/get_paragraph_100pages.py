# -*- coding: utf-8 -*-
"""
Created on Thu Sep 17 13:51:02 2015

@author: Wasit
"""

from bs4 import BeautifulSoup
import urllib2
import codecs
import re

def mybot(url,alltext):
    content = urllib2.urlopen(url).read()
    soup = BeautifulSoup(content)    
    
    for node in soup.findAll('p'):
        alltext+=unicode.join(u'',map(unicode,node.findAll(text=True)))
    #generating next paths
    next_paths=[]    
    for link in soup.findAll('a'):
        try:
            if re.match( u'^/wiki', str(link.get('href'))  ):
                #print link.get('href')             
                #print "\n"
                next_paths.append(link.get('href') )
        except ValueError:
            #print ValueError
            pass
    next_url="https://th.wikipedia.org"+next_paths[0]
    return (next_url,alltext)
    
if __name__ == "__main__":
    url = "https://th.wikipedia.org/wiki"
    alltext=u''
    for i in xrange(100):
        url,alltext=mybot(url,alltext)  
            
    #print alltext    
    with codecs.open("text.txt", "w", "utf-8-sig") as temp:
        temp.write(alltext)
