#include <solidParticle.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const std::size_t tnbLib::solidParticle::sizeofFields_
(
	sizeof(solidParticle) - sizeof(particle)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidParticle::solidParticle
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	particle(mesh, is, readFields)
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			d_ = readScalar(is);
			is >> U_;
		}
		else
		{
			is.read(reinterpret_cast<char*>(&d_), sizeofFields_);
		}
	}

	// Check state of Istream
	is.check("solidParticle::solidParticle(Istream&)");
}


void tnbLib::solidParticle::readFields(Cloud<solidParticle>& c)
{
	bool valid = c.size();

	particle::readFields(c);

	IOField<scalar> d(c.fieldIOobject("d", IOobject::MUST_READ), valid);
	c.checkFieldIOobject(c, d);

	IOField<vector> U(c.fieldIOobject("U", IOobject::MUST_READ), valid);
	c.checkFieldIOobject(c, U);

	label i = 0;
	forAllIter(Cloud<solidParticle>, c, iter)
	{
		solidParticle& p = iter();

		p.d_ = d[i];
		p.U_ = U[i];
		i++;
	}
}


void tnbLib::solidParticle::writeFields(const Cloud<solidParticle>& c)
{
	particle::writeFields(c);

	label np = c.size();

	IOField<scalar> d(c.fieldIOobject("d", IOobject::NO_READ), np);
	IOField<vector> U(c.fieldIOobject("U", IOobject::NO_READ), np);

	label i = 0;
	forAllConstIter(Cloud<solidParticle>, c, iter)
	{
		const solidParticle& p = iter();

		d[i] = p.d_;
		U[i] = p.U_;
		i++;
	}

	d.write(np > 0);
	U.write(np > 0);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const solidParticle& p)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const particle&>(p)
			<< token::SPACE << p.d_
			<< token::SPACE << p.U_;
	}
	else
	{
		os << static_cast<const particle&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.d_),
			solidParticle::sizeofFields_
		);
	}

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const solidParticle&)");

	return os;
}


// ************************************************************************* //