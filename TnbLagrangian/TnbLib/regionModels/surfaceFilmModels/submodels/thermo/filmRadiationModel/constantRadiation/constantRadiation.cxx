#include <constantRadiation.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(constantRadiation, 0);

			addToRunTimeSelectionTable
			(
				filmRadiationModel,
				constantRadiation,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			constantRadiation::constantRadiation
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmRadiationModel(typeName, film, dict),
				qrConst_
				(
					IOobject
					(
						typeName + ":qrConst",
						film.time().timeName(),
						film.regionMesh(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					film.regionMesh()
				),
				mask_
				(
					IOobject
					(
						typeName + ":mask",
						film.time().timeName(),
						film.regionMesh(),
						IOobject::READ_IF_PRESENT,
						IOobject::AUTO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimless, 1.0)
				),
				absorptivity_(readScalar(coeffDict_.lookup("absorptivity"))),
				timeStart_(readScalar(coeffDict_.lookup("timeStart"))),
				duration_(readScalar(coeffDict_.lookup("duration")))
			{
				mask_ = pos0(mask_);
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			constantRadiation::~constantRadiation()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void constantRadiation::correct()
			{}


			tmp<volScalarField> constantRadiation::Shs()
			{
				tmp<volScalarField> tShs
				(
					volScalarField::New
					(
						typeName + ":Shs",
						film().regionMesh(),
						dimensionedScalar(dimMass / pow3(dimTime), 0)
					)
				);

				const scalar time = film().time().value();

				if ((time >= timeStart_) && (time <= timeStart_ + duration_))
				{
					scalarField& Shs = tShs.ref();
					const scalarField& qr = qrConst_;
					const scalarField& alpha = filmModel_.alpha();

					Shs = mask_ * qr*alpha*absorptivity_;
				}

				return tShs;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //