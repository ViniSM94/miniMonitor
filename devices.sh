#!/bin/bash

#create number of devices based on the paramether. Sends a message every 1 second
for (( counter=1; counter<=$1; counter++ ))
do 
	(
		echo "name:dev$counter msg:message$counter"
		sleep 1
	) | telnet localhost 1234	
done

#send message quit to finish the application
(
	echo "quit"
	sleep 1
) | telnet localhost 1234