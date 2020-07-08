#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::word& tnbLib::argList::executable() const
{
	return executable_;
}


inline const tnbLib::fileName& tnbLib::argList::rootPath() const
{
	return rootPath_;
}


inline const tnbLib::fileName& tnbLib::argList::caseName() const
{
	return case_;
}


inline const tnbLib::fileName& tnbLib::argList::globalCaseName() const
{
	return globalCase_;
}


inline const tnbLib::ParRunControl& tnbLib::argList::parRunControl() const
{
	return parRunControl_;
}


inline tnbLib::fileName tnbLib::argList::path() const
{
	return rootPath() / caseName();
}


inline const tnbLib::stringList& tnbLib::argList::args() const
{
	return args_;
}


inline tnbLib::stringList& tnbLib::argList::args()
{
	return args_;
}


inline const tnbLib::string& tnbLib::argList::arg(const label index) const
{
	return args_[index];
}


inline tnbLib::label tnbLib::argList::size() const
{
	return args_.size();
}


inline const tnbLib::HashTable<tnbLib::string>& tnbLib::argList::options() const
{
	return options_;
}


inline tnbLib::HashTable<tnbLib::string>& tnbLib::argList::options()
{
	return options_;
}


inline const tnbLib::string& tnbLib::argList::option(const word& opt) const
{
	return options_[opt];
}


inline bool tnbLib::argList::optionFound(const word& opt) const
{
	return options_.found(opt);
}


inline tnbLib::IStringStream tnbLib::argList::optionLookup(const word& opt) const
{
	return IStringStream(options_[opt]);
}


// * * * * * * * * * * * * Template Specializations  * * * * * * * * * * * * //

namespace tnbLib
{
	// Template specialization for string
	template<>
	inline tnbLib::string
		tnbLib::argList::argRead<tnbLib::string>(const label index) const
	{
		return args_[index];
	}

	// Template specialization for word
	template<>
	inline tnbLib::word
		tnbLib::argList::argRead<tnbLib::word>(const label index) const
	{
		return args_[index];
	}

	// Template specialization for fileName
	template<>
	inline tnbLib::fileName
		tnbLib::argList::argRead<tnbLib::fileName>(const label index) const
	{
		return args_[index];
	}

	// Template specialization for string
	template<>
	inline tnbLib::string
		tnbLib::argList::optionRead<tnbLib::string>(const word& opt) const
	{
		return options_[opt];
	}

	// Template specialization for word
	template<>
	inline tnbLib::word
		tnbLib::argList::optionRead<tnbLib::word>(const word& opt) const
	{
		return options_[opt];
	}

	// Template specialization for fileName
	template<>
	inline tnbLib::fileName
		tnbLib::argList::optionRead<tnbLib::fileName>(const word& opt) const
	{
		return options_[opt];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline T tnbLib::argList::argRead(const label index) const
{
	T val;

	IStringStream(args_[index])() >> val;
	return val;
}


template<class T>
inline T tnbLib::argList::optionRead(const word& opt) const
{
	T val;

	optionLookup(opt)() >> val;
	return val;
}


template<class T>
inline bool tnbLib::argList::optionReadIfPresent
(
	const word& opt,
	T& val
) const
{
	if (optionFound(opt))
	{
		val = optionRead<T>(opt);
		return true;
	}
	else
	{
		return false;
	}
}


template<class T>
inline bool tnbLib::argList::optionReadIfPresent
(
	const word& opt,
	T& val,
	const T& deflt
) const
{
	if (optionReadIfPresent<T>(opt, val))
	{
		return true;
	}
	else
	{
		val = deflt;
		return false;
	}
}


template<class T>
inline T tnbLib::argList::optionLookupOrDefault
(
	const word& opt,
	const T& deflt
) const
{
	if (optionFound(opt))
	{
		return optionRead<T>(opt);
	}
	else
	{
		return deflt;
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline const tnbLib::string& tnbLib::argList::operator[](const label index) const
{
	return args_[index];
}


inline const tnbLib::string& tnbLib::argList::operator[](const word& opt) const
{
	return options_[opt];
}


// ************************************************************************* //