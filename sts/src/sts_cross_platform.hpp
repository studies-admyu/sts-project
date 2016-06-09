#pragma once

/* Additional macro for Microsoft Visual Studio compilers */
#ifdef _MSC_VER
	#if _MSC_VER < 1900
		// Microsoft Visual Studio 2013 and older
		#define noexcept
	#endif
#endif
