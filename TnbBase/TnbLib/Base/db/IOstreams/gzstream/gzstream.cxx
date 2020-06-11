#include <gzstream.hxx>

#include <iostream>
#include <string.h>  // for memcpy

#ifdef GZSTREAM_NAMESPACE
namespace GZSTREAM_NAMESPACE {
#endif

	// ----------------------------------------------------------------------------
	// Internal classes to implement gzstream. See header file for user classes.
	// ----------------------------------------------------------------------------

	// --------------------------------------
	// class gzstreambuf:
	// --------------------------------------

	gzstreambuf* gzstreambuf::open(const char* _name, int _open_mode) {
		if (is_open())
			return 0;
		mode = _open_mode;
		// no append nor read/write mode
		if ((mode & std::ios::ate) || (mode & std::ios::app)
			|| ((mode & std::ios::in) && (mode & std::ios::out)))
			return 0;
		char  fmode[10];
		char* fmodeptr = fmode;
		if (mode & std::ios::in)
			*fmodeptr++ = 'r';
		else if (mode & std::ios::out)
			*fmodeptr++ = 'w';
		*fmodeptr++ = 'b';
		*fmodeptr = '\0';
		file = gzopen(_name, fmode);
		if (file == 0)
			return 0;
		opened = 1;
		return this;
	}

	gzstreambuf * gzstreambuf::close() {
		if (is_open()) {
			sync();
			opened = 0;
			if (gzclose(file) == Z_OK)
				return this;
		}
		return 0;
	}

	int gzstreambuf::underflow() { // used for input buffer only
		if (gptr() && (gptr() < egptr()))
			return *reinterpret_cast<unsigned char *>(gptr());

		if (!(mode & std::ios::in) || !opened)
			return EOF;
		// Josuttis' implementation of inbuf
		int n_putback = gptr() - eback();
		if (n_putback > 4)
			n_putback = 4;
		memcpy(buffer + (4 - n_putback), gptr() - n_putback, n_putback);

		int num = gzread(file, buffer + 4, bufferSize - 4);
		if (num <= 0) // ERROR or EOF
			return EOF;

		// reset buffer pointers
		setg(buffer + (4 - n_putback),   // beginning of putback area
			buffer + 4,                 // read position
			buffer + 4 + num);          // end of buffer

	  // return next character
		return *reinterpret_cast<unsigned char *>(gptr());
	}

	int gzstreambuf::flush_buffer() {
		// Separate the writing of the buffer from overflow() and
		// sync() operation.
		int w = pptr() - pbase();
		if (gzwrite(file, pbase(), w) != w)
			return EOF;
		pbump(-w);
		return w;
	}

	int gzstreambuf::overflow(int c) { // used for output buffer only
		if (!(mode & std::ios::out) || !opened)
			return EOF;
		if (c != EOF) {
			*pptr() = c;
			pbump(1);
		}
		if (flush_buffer() == EOF)
			return EOF;
		return c;
	}

	int gzstreambuf::sync() {
		// Changed to use flush_buffer() instead of overflow( EOF)
		// which caused improper behavior with std::endl and flush(),
		// bug reported by Vincent Ricard.
		if (pptr() && pptr() > pbase()) {
			if (flush_buffer() == EOF)
				return -1;
		}
		return 0;
	}

	// --------------------------------------
	// class gzstreambase:
	// --------------------------------------

	gzstreambase::gzstreambase(const char* name, int mode) {
		init(&buf);
		open(name, mode);
	}

	gzstreambase::~gzstreambase() {
		buf.close();
	}

	void gzstreambase::open(const char* _name, int _open_mode) {
		if (!buf.open(_name, _open_mode))
			setstate(std::ios::badbit);
		// clear( rdstate() | std::ios::badbit);
	}

	void gzstreambase::close() {
		if (buf.is_open())
			if (!buf.close())
				setstate(std::ios::badbit);
		// clear( rdstate() | std::ios::badbit);
	}

#ifdef GZSTREAM_NAMESPACE
} // namespace GZSTREAM_NAMESPACE
#endif

// ============================================================================