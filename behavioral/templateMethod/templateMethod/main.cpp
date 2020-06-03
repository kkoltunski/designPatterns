#include "header.h"

int main(){
	
	sd2RequestFrame reqFrame(99);
	sd2ResponseFrame resFrame(80);

	reqFrame.setNewData("This is profibus DP sd2 request frame.");
	resFrame.setNewData("DP sd2 response frame example");

	reqFrame.generate();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	resFrame.generate();

	return 0;
}