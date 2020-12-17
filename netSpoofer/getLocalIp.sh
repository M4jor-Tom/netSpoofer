#!/bin/bash
/sbin/ifconfig | grep "192." | cut -d" " -f 2
