//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <font/FontFile.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "stb_image_write.h"

namespace fs = std::filesystem;

// Cheap format hack.
// TODO: Replace with fmt.
template <class... Args>
std::string CheapFormat(std::string_view sv, Args&&... args) {
	static char tempFormatBuf[2048]; // only used for formatting, string ctor makes a copy of this
	int res = snprintf(&tempFormatBuf[0], std::size(tempFormatBuf), sv.data(), args...);

	if(res == -1)
		return "";

	return { &tempFormatBuf[0], static_cast<std::size_t>(res) };
}

int main(int argc, char** argv) {
	if(argc < 2) {
		if(argc == 1)
			std::cout << "Required path to font file missing..\n";

		std::cout << "Usage: " << argv[0] << " [Path to font file]\n";
		return 0;
	}

	auto path = fs::path(argv[1]);
	auto source = path; // copied as we mutate path a bit. this will always be the original user input

	if(!fs::exists(path)) {
		std::cout << "Error: Provided path " << std::quoted(source.string()) << " doesn't exist.\n";
		return 1;
	}

	std::ifstream ifs(path.string(), std::ifstream::binary);

	if(!ifs) {
		std::cout << "Error: Couldn't open source file for reading.\n";
		std::cout << "Please check permissions.\n";
		return 0;
	}

	fd::font::File file;

	if(auto res = file.ReadFromStream(ifs); res != fd::font::ReadError::NoError) {
		std::cout << CheapFormat("Error: Could not read file: %s\n", fd::font::ReadErrorToString(res));
		return 1;
	}

	auto outputDir = path.remove_filename() / CheapFormat("%s", path.stem().c_str());

	std::cout << "Output Directory: " << outputDir << '\n';

	if(!fs::exists(outputDir))
		fs::create_directories(outputDir);

	auto outName = (outputDir / "font.png");
	auto rgba = file.GetImage();
	stbi_write_png(outName.c_str(), rgba.GetSize().width, rgba.GetSize().height, 4, rgba.GetBuffer(), rgba.GetStride());
	return 0;
}