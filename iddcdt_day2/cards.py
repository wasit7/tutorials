# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 23:15:40 2015

@author: Wasit
"""
import random

hand1=[]
hand2=[]
cards=['A','B','C','D','E','F']
random.shuffle(cards)
score=0
while 0 < len(cards):
    hand1.append(cards.pop())
    hand2.append(cards.pop())

while 0 < len(hand1):
    computerCard=hand1.pop()    
    print "Your remaining cards: " , hand2
    while True:
        playerCard = raw_input("choose your card: ")
        if playerCard in hand2:
            hand2.remove(playerCard)
            break
        else:
            print "wrong card name"
    print "computer card: "+computerCard
    print "player card: "+playerCard
    if playerCard<computerCard:
        score=score+1
        print "You win, score: ", score
    else:
        print "You lose, score: ", score