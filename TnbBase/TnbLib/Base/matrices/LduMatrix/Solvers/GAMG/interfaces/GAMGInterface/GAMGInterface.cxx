#include <GAMGInterface.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGInterface, 0);
	defineRunTimeSelectionTable(GAMGInterface, lduInterface);
	defineRunTimeSelectionTable(GAMGInterface, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GAMGInterface::GAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	Istream& is
)
	:
	index_(index),
	coarseInterfaces_(coarseInterfaces),
	faceCells_(is),
	faceRestrictAddressing_(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::GAMGInterface::combine(const GAMGInterface& coarseGi)
{
	const labelList& coarseFra = coarseGi.faceRestrictAddressing_;

	forAll(faceRestrictAddressing_, ffi)
	{
		faceRestrictAddressing_[ffi] = coarseFra[faceRestrictAddressing_[ffi]];
	}

	faceCells_ = coarseGi.faceCells_;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::GAMGInterface::interfaceInternalField
(
	const labelUList& internalData
) const
{
	return interfaceInternalField<label>(internalData);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::GAMGInterface::agglomerateCoeffs
(
	const scalarField& fineCoeffs
) const
{
	tmp<scalarField> tcoarseCoeffs(new scalarField(size(), 0.0));
	scalarField& coarseCoeffs = tcoarseCoeffs.ref();

	if (fineCoeffs.size() != faceRestrictAddressing_.size())
	{
		FatalErrorInFunction
			<< "Size of coefficients " << fineCoeffs.size()
			<< " does not correspond to the size of the restriction "
			<< faceRestrictAddressing_.size()
			<< abort(FatalError);
	}
	if (debug && max(faceRestrictAddressing_) > size())
	{
		FatalErrorInFunction
			<< "Face restrict addressing addresses outside of coarse interface"
			<< " size. Max addressing:" << max(faceRestrictAddressing_)
			<< " coarse size:" << size()
			<< abort(FatalError);
	}

	forAll(faceRestrictAddressing_, ffi)
	{
		coarseCoeffs[faceRestrictAddressing_[ffi]] += fineCoeffs[ffi];
	}

	return tcoarseCoeffs;
}


void tnbLib::GAMGInterface::write(Ostream& os) const
{
	os << faceCells_ << token::SPACE << faceRestrictAddressing_;
}


// ************************************************************************* //