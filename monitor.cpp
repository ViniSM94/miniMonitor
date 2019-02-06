#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;
using namespace std;

//this will hold the Devices' values
struct Device{
	string name="";
	string message="";
};

class Monitor{
	public:
		Monitor();
			
	private:
		static int countMessage;
		string message;
		string readMessage(tcp::socket &socket);
		string makeString(boost::asio::streambuf& streambuf);
		Device assignDevice(const string &message);
		bool validProtocol(const string &message);
};

int Monitor::countMessage=0;

//start the monitor listener. It will listen on port 1234 until it receives the message quit
Monitor::Monitor(){
	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));		
		
		//the application will run until the message quit is received	
		while(true)
		{
			tcp::socket socket(io_service);
			Device dev;
			acceptor.accept(socket);
			message = readMessage(socket);			
			//transform everything to upper for validation purposes
			boost::to_upper(message);
			if(message=="QUIT"){
				break;
			}						
			//valid protocol in this case should be 'name:someName msg:someMessage'
			if(validProtocol(message)){
				dev = assignDevice(message);
				cout<<"Device name:\n";
				cout<<dev.name<<'\n';
				cout<<"Message received:\n";
				cout<<dev.message<<'\n';
				countMessage++;
			}
			else{
				cout<<"Invalid message\n";
			}
			cout<<'\n';
		}
		
		cout<<"Ending application"<<'\n';
		cout<<"Messages read: "<<countMessage<<'\n';

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

string Monitor::readMessage(tcp::socket &socket){
             
    boost::asio::streambuf readBuffer;
    string fullMsg = "";
	string letter = "";
	
	//checks the text char by char until it finds a line break
    while(letter!="\n"){
		boost::asio::read(socket, readBuffer,boost::asio::transfer_exactly(1));
        letter = makeString(readBuffer);		
		//remove the character from the buffer
		readBuffer.consume(1);
		fullMsg+=letter;
	}
	//clean the message of any unwanted character that might come before or after
	boost::algorithm::trim(fullMsg);	
	return fullMsg;
}

//method to convert the boost buffer to normal C++ string
string Monitor::makeString(boost::asio::streambuf& streambuf)
{
	return {boost::asio::buffers_begin(streambuf.data()),boost::asio::buffers_end(streambuf.data())};
}

Device Monitor::assignDevice(const string &paramMessage){
	Device dev;
	//example of message: "name:DEVICE1 msg:MESSAGE1"
	string devName = paramMessage.substr(paramMessage.find("NAME:")+5, paramMessage.find("MSG:")-(paramMessage.find("NAME:")+5));
	string devMsg = paramMessage.substr(paramMessage.find("MSG:")+4, paramMessage.length());
	dev.name=devName;
	dev.message=devMsg;
	return dev;
}

//simple method to confirm that the protocol contains the data we need.
bool Monitor::validProtocol(const string &message){
	
	if((message.find("NAME:")!= -1)&&(message.find("MSG:")!= -1)){
		return true;
	}
	else{
		return false;
	}
}

int main()
{
	cout<<"Starting Mini Monitoring "<<'\n';
	cout<<"Receiving messages: "<<'\n';
	Monitor m;	
	return 0;
}