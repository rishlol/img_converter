#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void replace_f_ext(fs::path& p_og, fs::path& p_new) {
	cout << "Extension: " << p_og.extension() << endl;
	if (p_og.extension() == ".jpg") {
		cout << "jpg!" << endl;
		p_new.replace_extension(".png");
	}
	else if (p_og.extension() == ".png") {
		cout << "png!" << endl;
		p_new.replace_extension(".jpg");
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Usage: img_convert <input>";
		return 1;
	}

	bool recursive = false;
	if (argc > 2) {
		for (int i = 2; i < argc; i += 1) {
			if (string(argv[i]) == "-r") {
				cout << "BAZINGA" << endl;
				recursive = true;
			}
		}
	}
	cout << recursive << endl;

	// Get input arg
	string input = argv[1];
	fs::path p(input);
	if (!fs::exists(p)) {
		cerr << "File/directory does not exist!";
		return 2;
	}
	else if (fs::is_regular_file(p)) {
		cout << "Converting " << p.string() << "..." << endl;
		cv::Mat img = cv::imread(p.string());
		fs::path new_p = p;
		replace_f_ext(p, new_p);
		cv::imwrite(new_p.string(), img);
	}
	else if (fs::is_directory(p) && !recursive) {
		fs::directory_iterator d(p);
		fs::directory_iterator end;
		while (d != end) {
			if (fs::is_regular_file((*d).path())) {
				cout << "Converting " << (*d).path().string() << "..." << endl;
				cv::Mat img = cv::imread((*d).path().string());
				fs::path p = (*d).path();
				fs::path new_p = p;
				replace_f_ext(p, new_p);
				cv::imwrite(new_p.string(), img);
			}
			d++;
		}
	}
	else if (fs::is_directory(p) && recursive) {
		fs::recursive_directory_iterator d(p);
		fs::recursive_directory_iterator end;
		while (d != end) {
			if (fs::is_regular_file((*d).path())) {
				cout << "Converting " << (*d).path().string() << "..." << endl;
				cv::Mat img = cv::imread((*d).path().string());
				fs::path p = (*d).path();
				fs::path new_p = p;
				replace_f_ext(p, new_p);
				cv::imwrite(new_p.string(), img);
			}
			d++;
		}
	}

	return 0;
}