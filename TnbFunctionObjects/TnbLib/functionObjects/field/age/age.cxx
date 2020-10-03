#include <age.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <inletOutletFvPatchField.hxx>
#include <wallFvPatch.hxx>
#include <zeroGradientFvPatchField.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(age, 0);
		addToRunTimeSelectionTable(functionObject, age, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::wordList tnbLib::functionObjects::age::patchTypes() const
{
	wordList result
	(
		mesh_.boundary().size(),
		inletOutletFvPatchField<scalar>::typeName
	);

	forAll(mesh_.boundary(), patchi)
	{
		if (isA<wallFvPatch>(mesh_.boundary()[patchi]))
		{
			result[patchi] = zeroGradientFvPatchField<scalar>::typeName;
		}
	}

	return result;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::age::age
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	phiName_(),
	rhoName_(),
	nCorr_(0),
	schemesField_()

{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::age::~age()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::age::read(const dictionary& dict)
{
	phiName_ = dict.lookupOrDefault<word>("phi", "phi");
	rhoName_ = dict.lookupOrDefault<word>("rho", "rho");

	dict.readIfPresent("nCorr", nCorr_);

	schemesField_ = dict.lookupOrDefault<word>("schemesField", typeName);

	return true;
}


bool tnbLib::functionObjects::age::execute()
{
	return true;
}


bool tnbLib::functionObjects::age::write()
{
	volScalarField t
	(
		IOobject
		(
			typeName,
			mesh_.time().timeName(),
			mesh_,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		mesh_,
		dimensionedScalar(dimTime, 0),
		patchTypes()
	);

	const word divScheme("div(phi," + schemesField_ + ")");

	// Set under-relaxation coeff
	scalar relaxCoeff = 0.0;
	if (mesh_.relaxEquation(schemesField_))
	{
		relaxCoeff = mesh_.equationRelaxationFactor(schemesField_);
	}

	// This only works because the null constructed inletValue for an
	// inletOutletFvPatchField is zero. If we needed any other value we would
	// have to loop over the inletOutlet patches and explicitly set the
	// inletValues. We would need to change the interface of inletOutlet in
	// order to do this.

	const surfaceScalarField& phi =
		mesh_.lookupObject<surfaceScalarField>(phiName_);

	if (phi.dimensions() == dimMass / dimTime)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		for (label i = 0; i <= nCorr_; ++i)
		{
			fvScalarMatrix tEqn
			(
				fvm::div(phi, t, divScheme) == rho
			);

			tEqn.relax(relaxCoeff);

			tEqn.solve(schemesField_);
		}
	}
	else
	{
		for (label i = 0; i <= nCorr_; ++i)
		{
			fvScalarMatrix tEqn
			(
				fvm::div(phi, t, divScheme) == dimensionedScalar(1)
			);

			tEqn.relax(relaxCoeff);

			tEqn.solve(schemesField_);
		}
	}

	Info << "Min/max age:" << min(t).value() << ' ' << max(t).value() << endl;

	t.write();

	return true;
}


// ************************************************************************* //