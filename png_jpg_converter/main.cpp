#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Usage: img_convert <input>";
		return 1;
	}

	string input = argv[1];
	fs::path p(input);
	if (fs::is_regular_file(p)) {
		cv::Mat img = cv::imread(p.string());
		fs::path new_p = p;
		if (p.extension() == ".jpg") {
			new_p.replace_extension(".png");
		}
		else if (p.extension() == ".png") {
			new_p.replace_extension(".jpg");
		}

		cv::imwrite(new_p.string(), img);
	}
	else if (fs::is_directory(p)) {
		cout << p << " is a directory" << endl;
	}

	return 0;
}