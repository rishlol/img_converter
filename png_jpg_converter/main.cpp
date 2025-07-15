#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

inline void replace_f_ext(fs::path& p, string &f) {
	cv::Mat img = cv::imread(p.string());
	fs::path new_p = p;
	new_p.replace_extension(f);
	cv::imwrite(new_p.string(), img);
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Usage: img_converter <input_path> <output_format> [-r]";
		return 1;
	}

	bool recursive = false;
	if (argc > 3) {
		for (int i = 3; i < argc; i += 1) {
			if (string(argv[i]) == "-r") {
				recursive = true;
				break;
			}
		}
	}
	cout << recursive << endl;

	// Get input arg
	string input = argv[1];
	string format = argv[2];
	fs::path p(input);
	if (!fs::exists(p)) {
		cerr << "File/directory does not exist!";
		return 2;
	}
	else if (fs::is_regular_file(p)) {
		cout << "Converting " << p.string() << " to " << format << endl;
		replace_f_ext(p, format);
	}
	else if (fs::is_directory(p) && !recursive) {
		fs::directory_iterator d(p);
		fs::directory_iterator end;
		while (d != end) {
			if (fs::is_regular_file((*d).path())) {
				cout << "Converting " << (*d).path().string() << " to " << format << endl;
				fs::path p = (*d).path();
				replace_f_ext(p, format);
			}
			d++;
		}
	}
	else if (fs::is_directory(p) && recursive) {
		fs::recursive_directory_iterator d(p);
		fs::recursive_directory_iterator end;
		while (d != end) {
			if (fs::is_regular_file((*d).path())) {
				cout << "Converting " << (*d).path().string() << " to " << format << endl;
				fs::path p = (*d).path();
				replace_f_ext(p, format);
			}
			d++;
		}
	}

	return 0;
}