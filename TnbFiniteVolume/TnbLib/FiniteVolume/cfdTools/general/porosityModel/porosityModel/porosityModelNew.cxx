#include <porosityModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::porosityModel> tnbLib::porosityModel::New
(
	const word& name,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
{
	const word modelType(dict.lookup("type"));

	Info << "Porosity region " << name << ":" << nl
		<< "    selecting model: " << modelType << endl;

	meshConstructorTable::iterator cstrIter =
		meshConstructorTablePtr_->find(modelType);

	if (cstrIter == meshConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << typeName << " type " << modelType << nl << nl
			<< "Valid " << typeName << " types are:" << nl
			<< meshConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<porosityModel>
		(
			cstrIter()
			(
				name,
				modelType,
				mesh,
				dict,
				cellZoneName
				)
			);
}


// ************************************************************************* //