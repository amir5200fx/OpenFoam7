#include <gradingDescriptors.hxx>

#include <token.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::gradingDescriptors::gradingDescriptors()
	:
	List<gradingDescriptor>(1, gradingDescriptor())
{}


tnbLib::gradingDescriptors::gradingDescriptors(const gradingDescriptor& gd)
	:
	List<gradingDescriptor>(1, gd)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::gradingDescriptors tnbLib::gradingDescriptors::inv() const
{
	gradingDescriptors ret(*this);

	forAll(ret, i)
	{
		ret[i] = operator[](ret.size() - i - 1).inv();
	}

	return ret;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, gradingDescriptors& gds)
{
	// Examine next token
	token t(is);

	if (t.isNumber())
	{
		gds = gradingDescriptors(gradingDescriptor(t.number()));
	}
	else
	{
		is.putBack(t);

		// Read the list for gradingDescriptors
		is >> static_cast<List<gradingDescriptor>&>(gds);

		// Check state of Istream
		is.check("operator>>(Istream&, gradingDescriptor&)");

		// Normalize the blockFractions and nDivFractions
		// of the list of gradingDescriptors

		scalar sumBlockFraction = 0;
		scalar sumNDivFraction = 0;

		forAll(gds, i)
		{
			sumBlockFraction += gds[i].blockFraction_;
			sumNDivFraction += gds[i].nDivFraction_;
		}

		forAll(gds, i)
		{
			gds[i].blockFraction_ /= sumBlockFraction;
			gds[i].nDivFraction_ /= sumNDivFraction;
		}
	}

	return is;
}


// ************************************************************************* //
