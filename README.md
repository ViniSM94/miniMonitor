# miniMonitor
Simple project developed to monitor the communication on a TCP port 

This simple project has been developed in Linux(CentOS7) using C++11 in addition to boost library. It consists on a simple C++ file, that will act as the listener to the port 1234, and the devices shell script, use to create some samples that will send data to the monitor.

Instructions:

- First it would be required to open the TCP port 1234 in the firewall
- Next, the boost libraries should be installed.
- Run the make command to build the project
- Start the monitor application with ./monitor
- Connect the devices running the script ./devices.sh and the number of devices to be created, e.g "./devices.sh 4".
