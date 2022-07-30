//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef TIPDUMP_RGBAIMAGE_H
#define TIPDUMP_RGBAIMAGE_H

#include <cstdint>
#include <vector>

namespace fd::font {

	/**
	 * Simple image size structure.
	 */
	struct ImageSize {
		std::uint32_t width {};
		std::uint32_t height {};
	};

	/**
	 * A RGBA color.
	 */
	union RgbaColor {
		std::uint32_t u32 {};

		// Color component accessor.
		struct {
			std::uint8_t r;
			std::uint8_t g;
			std::uint8_t b;
			std::uint8_t a;
		};
	};

	/**
	 * A standard RGBA8888 image.
	 */
	struct RgbaImage {
		RgbaImage();

		/**
		 * Constructor taking in an image size.
		 * Shorthand for Resize(size).
		 * \see RgbaImage::Resize
		 */
		explicit RgbaImage(ImageSize size);

		/**
		 * Resize this image.
		 * \param[in] size Size to resize to.
		 */
		void Resize(ImageSize size);

		/**
		 * Clear this image, freeing its buffer.
		 */
		void Clear();

		/**
		 * Get access to this image's data buffer (const version).
		 * \return A const pointer to the image buffer.
		 */
		[[nodiscard]] const RgbaColor* GetBuffer() const;

		/**
		 * Get access to this image's data buffer for writing
		 * \return A pointer to the image buffer.
		 */
		[[nodiscard]] RgbaColor* GetBuffer();

		/**
		 * Get the stride of this image.
		 * \return The stride.
		 */
		[[nodiscard]] std::size_t GetStride() const;

		/**
		 * Get the size of this image.
		 * \return The size.
		 */
		[[nodiscard]] ImageSize GetSize() const;

	   private:
		ImageSize size {};
		std::vector<RgbaColor> pixels;
	};

} // namespace fd::font

#endif // TIPDUMP_RGBAIMAGE_H
