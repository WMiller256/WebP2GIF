/* webp-gif.c++
 *
 * William Miller
 * Jun 9, 2020
 *
 * Utility to convert animated WebP files to GIF format
 *
 */

#include "webp2gif.h"

int main(int argn, char** argv) {
	Magick::InitializeMagick(*argv);
	
	std::vector<std::string> files;
	std::string otype;
	
	po::options_description desc("Usage");
	
	try {
		desc.add_options()
			("input,i",  po::value<std::vector<std::string>>()->multitoken(), "The input file or files to convert.")
			("output,o", po::value<std::string>(&otype)->default_value("jpg"), "The output format. Must be png, jpg or tif.")
		;
	}
	catch (...) {
		std::cout << "Error in boost program options initialization" << std::endl;
		exit(1);
	}

	po::variables_map vm;
	po::store(po::command_line_parser(argn, argv).options(desc).run(), vm);
	po::notify(vm);

	if (vm.count("input")) {
		files = vm["input"].as<std::vector<std::string>>();
	}
	else {
		std::cout << "No input specified." << std::endl;
		exit(0);
	}

	WebPAnimInfo info;
	std::pair<int, int> canvas;
	int done = 0;
	for (auto file : files) {
		fs::path outpath = file;
		outpath.replace_extension(".gif");
		std::vector<std::vector<uchar>> frames = read(file, canvas, info);
		write(outpath, frames, canvas);
		print_percent(done++, files.size());
	}
}

std::vector<std::vector<uchar>> read(std::string filename, std::pair<int, int> &canvas, WebPAnimInfo &info) {
	std::ifstream fp(filename, std::ios::binary);
	std::vector<uchar> buffer(std::istreambuf_iterator<char>(fp), {});

	WebPData webp;
	webp.bytes = buffer.data();
	webp.size = buffer.size();

	WebPAnimDecoder* dec = WebPAnimDecoderNew(&webp, NULL);
	if (dec == NULL) {
		std::cout << "Error parsing "+yellow+filename+res+"\n" << std::flush;
		exit(2);
	}

	if (!WebPAnimDecoderGetInfo(dec, &info)) {
		std::cout << "Error retrieving animation info from "+yellow+filename+res+"\n";
		exit(3);
	}
	canvas = std::make_pair(info.canvas_width, info.canvas_height);

	std::vector<std::vector<uchar>> frames;
	// Assumes storage is RGBA - 32 bit depth
	size_t fsize = canvas.first*canvas.second*4;
	int timestamp;
	int idx(0);
	while (WebPAnimDecoderHasMoreFrames(dec)) {
		uchar* frame;
		if (!WebPAnimDecoderGetNext(dec, &frame, &timestamp)) {
			std::cout << "Error parsing frame "+magenta+std::to_string(idx)+res+"\n" << std::flush;
			exit(4);
		}
		idx++;
		frames.push_back(std::vector<uchar>(frame, frame + fsize));
	}
	return frames;
}

void write(fs::path path, std::vector<std::vector<uchar>> frames, std::pair<int, int> canvas) {
	std::vector<Magick::Image> out;
	for (auto frame : frames) {
		out.push_back(Magick::Image(canvas.first, canvas.second, "RGBA", Magick::StorageType::CharPixel, frame.data()));
	}
	Magick::writeImages(out.begin(), out.end(), path.string());
}

void print_percent(int current, int total) {
	float percent = ((float)current/(float)(total - 1))*100.0;
	int idx = (int)percent - 1 >= 0 ? (int)percent : 0;
	if (total == 1 || current > total || percent > 100) return;

	std::string p = std::to_string(int(percent));
	std::cout << backspace+"\033[38;2;"+std::to_string(r[idx])+";"+std::to_string(g[idx])+";"+std::to_string(b[idx])+"m"+
	             std::string(3 - p.length(), '0')+p+"%"+res << std::flush;
	if (percent == 100) {
		std::cout << res+"\n" << std::flush;
	}
}
