/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef LIBINTL_INTERNAL_MESSAGECATALOG_HPP_
#define LIBINTL_INTERNAL_MESSAGECATALOG_HPP_

#include <algorithm>
#include <string>

namespace libintllite
{

namespace internal
{

class MessageCatalog
{
private:
	MessageCatalog(const MessageCatalog&);
	MessageCatalog& operator=(const MessageCatalog&);

	uint32_t numberOfStrings;
	const std::string* sortedOrigStringsArray;
	const std::string* translatedStringsArray;

public:
	// The ownership of these arrays is transfered to the created message
	// catalog object!
	// Does not throw exceptions!
	MessageCatalog(uint32_t numberOfStrings,
			const std::string* sortedOrigStringsArray,
			const std::string* translatedStringsArray) :
					numberOfStrings(numberOfStrings),
					sortedOrigStringsArray(sortedOrigStringsArray),
					translatedStringsArray(translatedStringsArray)
	{
	}

	~MessageCatalog()
	{
		delete[] this->sortedOrigStringsArray;
		delete[] this->translatedStringsArray;
	}

	// Returns NULL, if the original string was not found.
	// Does not throw exceptions!
	const std::string* getTranslatedStrPtr(const std::string& orig) const
	{
		const std::string* lastSortedOrigStringEndIter
				= this->sortedOrigStringsArray + this->numberOfStrings;
		const std::string* origStrPtr = std::lower_bound(this->sortedOrigStringsArray,
				lastSortedOrigStringEndIter,
				orig);
		if (!origStrPtr || (origStrPtr == lastSortedOrigStringEndIter))
		{
			return NULL;
		}
		else
		{
			return &this->translatedStringsArray[origStrPtr - this->sortedOrigStringsArray];
		}
	}
};

} // namespace internal

} // namespace libintllite

#endif // LIBINTL_INTERNAL_MESSAGECATALOG_HPP_
