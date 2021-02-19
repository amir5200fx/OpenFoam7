#include <volumeFractionSource.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmLaplacian.hxx>
#include <surfaceInterpolate.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(volumeFractionSource, 0);
		addToRunTimeSelectionTable
		(
			option,
			volumeFractionSource,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::volScalarField& tnbLib::fv::volumeFractionSource::alpha() const
{
	const word alphaName = IOobject::groupName("alpha", phaseName_);

	if (!mesh_.foundObject<volScalarField>(alphaName))
	{
		volScalarField* alphaPtr =
			new volScalarField
			(
				IOobject
				(
					alphaName,
					mesh_.time().constant(),
					mesh_,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				mesh_
			);

		alphaPtr->store();
	}

	return mesh_.lookupObject<volScalarField>(alphaName);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::fv::volumeFractionSource::D
(
	const label fieldi
) const
{
	const surfaceScalarField& phi =
		mesh().lookupObject<surfaceScalarField>(phiName_);

	if (phi.dimensions() == dimVolume / dimTime)
	{
		const turbulenceModel& turbulence =
			mesh().lookupObject<turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		return turbulence.nuEff();
	}
	else if (phi.dimensions() == dimMass / dimTime)
	{
		const compressible::turbulenceModel& turbulence =
			mesh().lookupObject<compressible::turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		return
			fieldNames_[fieldi] == turbulence.transport().T().name()
			? turbulence.kappaEff()
			: fieldNames_[fieldi] == turbulence.transport().he().name()
			? turbulence.alphaEff()
			: turbulence.muEff();
	}
	else
	{
		FatalErrorInFunction
			<< "Dimensions of " << phi.name() << " not recognised"
			<< exit(FatalError);
		return tmp<volScalarField>(nullptr);
	}
}


template <class Type>
void tnbLib::fv::volumeFractionSource::addDivSup
(
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	const surfaceScalarField& phi =
		mesh().lookupObject<surfaceScalarField>(phiName_);

	const volScalarField AByB(this->alpha() / (1 - this->alpha()));

	eqn -= AByB * fvm::div(phi, eqn.psi());
}


void tnbLib::fv::volumeFractionSource::addUDivSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	const surfaceScalarField& phi =
		mesh().lookupObject<surfaceScalarField>(phiName_);

	const volScalarField AByB(this->alpha() / (1 - this->alpha()));

	const word scheme("div(" + phiName_ + "," + eqn.psi().name() + ")");

	eqn -= fvm::div(fvc::interpolate(AByB)*phi, eqn.psi(), scheme);
}


void tnbLib::fv::volumeFractionSource::addRhoDivSup
(
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	const surfaceScalarField& phi =
		mesh().lookupObject<surfaceScalarField>(phiName_);

	const volScalarField AByB(this->alpha() / (1 - this->alpha()));

	eqn -= AByB * fvc::div(phi);
}


template <class Type, class AlphaFieldType>
void tnbLib::fv::volumeFractionSource::addLaplacianSup
(
	const AlphaFieldType& alpha,
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	const volScalarField B(1 - this->alpha());

	const volScalarField D(this->D(fieldi));

	const word scheme("laplacian(" + D.name() + "," + eqn.psi().name() + ")");

	eqn +=
		fvm::laplacian(D, eqn.psi())
		- 1 / B * fvm::laplacian(B*D, eqn.psi(), scheme);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::volumeFractionSource::volumeFractionSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(name, modelType, dict, mesh),
	phaseName_(dict.lookupType<word>("phase")),
	phiName_("phi"),
	rhoName_("rho"),
	UName_("U")
{
	read(dict);
	alpha();
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::volumeFractionSource::~volumeFractionSource()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::volumeFractionSource::addSup
(
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == rhoName_)
	{
		addRhoDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(geometricOneField(), eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == UName_)
	{
		addUDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(geometricOneField(), eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == rhoName_)
	{
		addRhoDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(geometricOneField(), eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == UName_)
	{
		addUDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(geometricOneField(), eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& rho,
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& rho,
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& rho,
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == rhoName_)
	{
		addRhoDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(alpha, eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	if (fieldNames_[fieldi] == UName_)
	{
		addUDivSup(eqn, fieldi);
	}
	else
	{
		addDivSup(eqn, fieldi);
		addLaplacianSup(alpha, eqn, fieldi);
	}
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(alpha, eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(alpha, eqn, fieldi);
}


void tnbLib::fv::volumeFractionSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{
	addDivSup(eqn, fieldi);
	addLaplacianSup(alpha, eqn, fieldi);
}


bool tnbLib::fv::volumeFractionSource::read(const dictionary& dict)
{
	if (option::read(dict))
	{
		if (coeffs_.found("fields"))
		{
			coeffs_.lookup("fields") >> fieldNames_;
		}

		applied_.setSize(fieldNames_.size(), false);

		dict.readIfPresent("phi", phiName_);

		dict.readIfPresent("rho", rhoName_);

		dict.readIfPresent("U", UName_);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //