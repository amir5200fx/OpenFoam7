#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::OSstream::OSstream
(
	ostream& os,
	const string& name,
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	:
	Ostream(format, version, compression),
	name_(name),
	os_(os)
{
	if (os_.good())
	{
		setOpened();
		setGood();
		os_.precision(precision_);
	}
	else
	{
		setState(os_.rdstate());
	}
}


// ************************************************************************* //