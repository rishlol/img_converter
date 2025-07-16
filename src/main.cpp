#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <thread>
#include <unordered_set>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Accepted image output formats
const unordered_set<string> VALID_EXTS = {
	".bmp", ".dib", ".jpeg", ".jpg", ".jpe",
	".png", ".pbm", ".pgm", ".ppm", ".tiff",
	".tif", ".webp", ".jp2"
};

// Validate image output format
bool valid_format(string& f) {
	auto res = f.find('.');
	if (res == string::npos) {
		f = '.' + f;
	} else if(res != 0) {
		f = f.substr(res);
	}

	if (VALID_EXTS.find(f) == VALID_EXTS.end()) {
		return false;
	}
	return true;
}

// Ensure file is acceptable image
inline bool valid_image_file(const fs::path &p) {
    return fs::is_regular_file(p) && VALID_EXTS.find(p.extension().string()) != VALID_EXTS.end();
}

// Change image encoding and extension/format
inline void convert_img(fs::path p, string f) {
    // Skip conversion if not needed
	if (p.extension().string() == f) {
		return;
	}
	cout << "Converting " << p.string() << " to " << f << endl;
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

	// Check for recurse option
	bool recursive = false;
	if (argc > 3) {
		for (int i = 3; i < argc; i += 1) {
			if (string(argv[i]) == "-r") {
				recursive = true;
				break;
			}
		}
	}

	// Get input args
	string input = argv[1];
	string format = argv[2];
	fs::path p(input);

	if (!fs::exists(p)) {
		cerr << "File/directory does not exist!";
		return 2;
	} else if (!valid_format(format)) {
		cerr << "Enter valid image format!";
		return 1;
	} else if (fs::is_regular_file(p)) {
		convert_img(p, format);
	} else if (fs::is_directory(p) && !recursive) {
		vector<thread> threads;
		fs::directory_iterator d(p);
		fs::directory_iterator end;
		while (d != end) {
			fs::path p = (*d).path();
			if (valid_image_file(p)) {
				threads.emplace_back(thread(convert_img, p, format));
			}
			d++;
		}
		for (thread& t : threads) {
			t.join();
		}
	} else if (fs::is_directory(p) && recursive) {
		vector<thread> threads;
		fs::recursive_directory_iterator d(p);
		fs::recursive_directory_iterator end;
		while (d != end) {
			fs::path p = (*d).path();
			if (valid_image_file(p)) {
				threads.emplace_back(thread(convert_img, p, format));
			}
			d++;
		}
		for (thread &t : threads) {
			t.join();
		}
	}

	return 0;
}
