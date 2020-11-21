#include <particle.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::string tnbLib::particle::propertyList_ = tnbLib::particle::propertyList();

const std::size_t tnbLib::particle::sizeofPosition_
(
	offsetof(particle, facei_) - offsetof(particle, coordinates_)
);

const std::size_t tnbLib::particle::sizeofFields_
(
	sizeof(particle) - offsetof(particle, coordinates_)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::particle::particle(const polyMesh& mesh, Istream& is, bool readFields)
	:
	mesh_(mesh),
	coordinates_(),
	celli_(-1),
	tetFacei_(-1),
	tetPti_(-1),
	facei_(-1),
	stepFraction_(0.0),
	behind_(0.0),
	nBehind_(0),
	origProc_(Pstream::myProcNo()),
	origId_(-1)
{
	if (is.format() == IOstream::ASCII)
	{
		is >> coordinates_ >> celli_ >> tetFacei_ >> tetPti_;

		if (readFields)
		{
			is >> facei_ >> stepFraction_ >> behind_ >> nBehind_
				>> origProc_ >> origId_;
		}
	}
	else
	{
		if (readFields)
		{
			is.read(reinterpret_cast<char*>(&coordinates_), sizeofFields_);
		}
		else
		{
			is.read(reinterpret_cast<char*>(&coordinates_), sizeofPosition_);
		}
	}

	// Check state of Istream
	is.check("particle::particle(Istream&, bool)");
}


void tnbLib::particle::writePosition(Ostream& os) const
{
	if (os.format() == IOstream::ASCII)
	{
		os << coordinates_
			<< token::SPACE << celli_
			<< token::SPACE << tetFacei_
			<< token::SPACE << tetPti_;
	}
	else
	{
		os.write(reinterpret_cast<const char*>(&coordinates_), sizeofPosition_);
	}

	// Check state of Ostream
	os.check("particle::writePosition(Ostream& os, bool) const");
}


FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const particle& p)
{
	if (os.format() == IOstream::ASCII)
	{
		os << p.coordinates_
			<< token::SPACE << p.celli_
			<< token::SPACE << p.tetFacei_
			<< token::SPACE << p.tetPti_
			<< token::SPACE << p.facei_
			<< token::SPACE << p.stepFraction_
			<< token::SPACE << p.behind_
			<< token::SPACE << p.nBehind_
			<< token::SPACE << p.origProc_
			<< token::SPACE << p.origId_;
	}
	else
	{
		os.write
		(
			reinterpret_cast<const char*>(&p.coordinates_),
			particle::sizeofFields_
		);
	}

	return os;
}


// ************************************************************************* //