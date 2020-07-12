#include <NASCore.hxx>

#include <IStringStream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::NASCore::NASCore()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::fileFormats::NASCore::parseNASCoord
(
	const string& s
)
{
	size_t expSign = s.find_last_of("+-");

	if (expSign != string::npos && expSign > 0 && !isspace(s[expSign - 1]))
	{
		scalar mantissa = readScalar(IStringStream(s.substr(0, expSign))());
		scalar exponent = readScalar(IStringStream(s.substr(expSign + 1))());

		if (s[expSign] == '-')
		{
			exponent = -exponent;
		}
		return mantissa * pow(10, exponent);
	}
	else
	{
		return readScalar(IStringStream(s)());
	}
}


// ************************************************************************* //