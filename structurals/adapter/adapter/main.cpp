#include "header.h"

int main(){
	std::string flacPath = R"(C:\Users\user\Desktop\09......flac)";
	std::string mp3Path = R"(C:\Users\user\Desktop\09......mp3)";

	flacFile flacFileExample(flacPath);
	mp3File mp3FileExample(mp3Path);
	mp3FileAdapter mp3Adapter(mp3Path);

	return 0;
}