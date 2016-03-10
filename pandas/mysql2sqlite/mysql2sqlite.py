# -*- coding: utf-8 -*-
"""
Created on Wed Mar 02 11:29:21 2016

@author: Wasit
"""

from sqlalchemy import create_engine
engine = create_engine('mysql+mysqldb://scott:tiger@localhost/foo')