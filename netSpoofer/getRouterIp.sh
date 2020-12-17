#!/bin/bash
/usr/local/bin/ip route | head -n 1 | cut -d" " -f 3
