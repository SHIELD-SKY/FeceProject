#!/usr/bin/env python
# -*- coding=utf-8 -*-

import socket
import os
import sys
import struct
#211.64.93.214

def socket_client():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(('47.93.87.89', 6666))
        #s.connect(('192.168.3.4', 6666))
    except socket.error as msg:
        print msg
        sys.exit(1)

    print s.recv(1024)

    while 1:
        filepath = '/root/桌面/result.jpg'
        if os.path.isfile(filepath):

            #print str(os.stat(filepath).st_size)
            s.send(str(os.stat(filepath).st_size))
            fp = open(filepath, 'rb')
            while 1:
                data = fp.read(1024)
                if not data:
                    print '{0} file send over...'.format(filepath)
                    break
                s.send(data)
        res=s.recv(1024)
        print str(res)
	#print 'endednedendenden'
        s.close()
	return str(res)
        break


if __name__ == '__main__':
    socket_client()
