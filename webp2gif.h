/* webp-gif.h
 *
 * William Miller
 * Jun 9, 2020
 *
 * Utility to convert WebP files to GIF format. Draws from 
 * the anim_dump example in the WebP source.
 *
 */

#pragma once

#include <cctype>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <valarray>
#include <vector>

// Boost
#include <boost/program_options.hpp>

// ImageMagick
#include <Magick++.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp> 

// WebP
#include "webp/types.h"
#include "webp/decode.h"
#include "webp/encode.h"
#include "webp/demux.h"
#include "webp/mux.h"
#include "webp/mux_types.h"

#include "colors.h"

namespace po = boost::program_options;
namespace fs = std::experimental::filesystem;

typedef uint8_t uchar;

std::vector<std::vector<uchar>> read(std::string filename, std::pair<int, int> &canvas, WebPAnimInfo &info);
void write(fs::path path, std::vector<std::vector<uchar>> frames, std::pair<int, int> canvas);
void read_write(std::string file, std::pair<int, int> &canvas, WebPAnimInfo &info);

template <typename T>
void split(const std::string &s, char delim, T result);
double fps(const std::string &s);
std::string exec(std::string command);

void print_percent(int current, int total);

const std::string backspace({8, 8, 8, 8});

// For progress coloring
static std::vector<int> r = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 249, 244, 239, 234, 229, 224, 
							  219, 214, 209, 204, 198, 193, 188, 183, 178, 173, 168, 163, 158, 153, 
							  147, 142, 137, 132, 127, 122, 117, 112, 107, 102, 96, 91, 86, 81, 76, 
							  71, 66, 61, 56, 51, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, 0};

static std::vector<int> g = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 51, 56, 61, 66, 71, 76, 81, 86, 
							  91, 96, 102, 107, 112, 117, 122, 127, 132, 137, 142, 147, 153, 158, 
							  163, 168, 173, 178, 183, 188, 193, 198, 204, 209, 214, 219, 224, 229, 
							  234, 239, 244, 249, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
							  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

static std::vector<int> b = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
							  0, 0, 0, 0, 0, 0, 0, 0, 0};

