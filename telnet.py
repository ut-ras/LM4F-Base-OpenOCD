#!/usr/bin/python3

import telnetlib , sys

connection = telnetlib.Telnet("localhost","4444")
for command in sys.argv[1:]:
	connection.read_until(b">")
	connection.write(command.encode('ascii') + b"\n")
connection.close()
