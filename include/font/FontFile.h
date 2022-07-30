//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//

#ifndef TIPDUMP_FONTFILE_H
#define TIPDUMP_FONTFILE_H

#include <font/FontStructures.h>
#include <font/RgbaImage.h>

#include <iosfwd>
#include <vector>

namespace fd::font {

	enum class ReadError : std::uint8_t {
		NoError = 0,
		NotTip,				  ///< NOT a TIP0/TIP1 file
		FailureReadingHeader, ///< Failure reading TIP header.
		FailureReadingImage	  ///< Failure reading an image
	};

	constexpr const char* ReadErrorToString(ReadError err) {
		constexpr const char* table[] = {
			"No error",
			"Not a FNTC file. Please choose a different file",
			"Failure reading FNTC header",
			"Failure reading a FNT image"
		};
		return table[static_cast<std::size_t>(err)];
	}

	/**
	 * High level version of a font file.
	 */
	struct File {
		/**
		 * Read from a binary C++ iostream
		 */
		ReadError ReadFromStream(std::istream& is);

		RgbaImage& GetImage();

		const Header& GetHeader() const;

	   private:
		RgbaImage image;

		Header header;
	};

} // namespace fd::font

#endif // TIPDUMP_FONTFILE_H
