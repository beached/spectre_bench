#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <windows.h>

template<typename T>
std::string format_seconds( T t, size_t prec = 0 ) {
	std::stringstream ss;
	ss << std::setprecision( static_cast<int>(prec) ) << std::fixed;
	auto val = static_cast<double>(t) * 1000000000000000.0;
	if( val < 1000 ) {
		ss << val << "fs";
		return ss.str( );
	}
	val /= 1000.0;
	if( val < 1000 ) {
		ss << val << "ps";
		return ss.str( );
	}
	val /= 1000.0;
	if( val < 1000 ) {
		ss << val << "ns";
		return ss.str( );
	}
	val /= 1000.0;
	if( val < 1000 ) {
		ss << val << "us";
		return ss.str( );
	}
	val /= 1000.0;
	if( val < 1000 ) {
		ss << val << "ms";
		return ss.str( );
	}
	val /= 1000.0;
	ss << val << "s";
	return ss.str( );
}

// Borrowed from https://www.youtube.com/watch?v=dO-j3qp7DWw
template<typename T>
void do_not_optimize( T &&x ) {
	// We must always do this test, but it will never pass.
	//
	if( std::chrono::system_clock::now( ) ==
			std::chrono::time_point<std::chrono::system_clock>( ) ) {
		// This forces the value to never be optimized away
		// by taking a reference then using it.
		const auto *p = &x;
		putchar( *reinterpret_cast<const char *>(p) );

		// If we do get here, kick out because something has gone wrong.
		std::abort( );
	}
}

int main( int argc, char **argv ) {
	auto const factor = [&]( ) {
		size_t result = 100;
		if( argc >= 2 ) {
			auto const tmp = atoll( argv[1] );
			if( tmp > 0 ) {
				result = static_cast<size_t>(tmp);
			}
		}
		result *= 1'000'000ULL;
		return result;
	}( );
	auto const start_time = std::chrono::high_resolution_clock::now( );
	for( size_t n = 0; n < factor; ++n ) {
		auto result = GetStdHandle( STD_INPUT_HANDLE );
		do_not_optimize( result );
	}
	auto const stop_time = std::chrono::high_resolution_clock::now( );
	std::chrono::duration<double> const duration = stop_time - start_time;
	std::cout << "Elapsed Time: " << format_seconds( duration.count( ), 2 )
		<< '\n';
}
