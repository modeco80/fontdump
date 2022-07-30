//
// FontDump
//
// (C) 2021-2022 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef TIPDUMP_TRIVIALSTREAMREAD_H
#define TIPDUMP_TRIVIALSTREAMREAD_H

#include <iostream>

namespace fd {

	// This is endian specific to all hell and back. Later on maybe port ssxtools stream
	// code so we can do this in a smarter way.

	template <class T>
	bool MaybeRead(std::istream& is, T& t) {
		if(!is)
			return false;

		is.read(reinterpret_cast<char*>(&t), sizeof(T));
		return true;
	}

} // namespace fd

#endif // TIPDUMP_TRIVIALSTREAMREAD_H
