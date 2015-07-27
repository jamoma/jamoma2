/** @file
 *
 * @ingroup jamoma2
 *
 * @brief Store a string value within Jamoma's symbol table.
 *
 * @details Defines an interface for representing a string so that it can be efficiently passed between methods and compared to other string.
 *
 * @warning This class is a stub.
 *
 * @author Timothy Place, Nathan Wolek
 *
 * @copyright Copyright © 2015 by Jamoma authors and contributors @n
 * This code is licensed under the terms of the "BSD 3-Clause License" @n
 * https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once


namespace Jamoma {
	
	class Symbol {
	public:
		Symbol(const String name) {}
		Symbol& operator = (String str) { return *this; }
	};

} // namespace Jamoma
