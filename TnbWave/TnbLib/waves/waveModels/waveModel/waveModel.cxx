#include <waveModel.hxx>

#include <Time.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(waveModel, 0);
	defineRunTimeSelectionTable(waveModel, objectRegistry);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveModel::waveModel(const waveModel& wave)
	:
	db_(wave.db_),
	amplitude_(wave.amplitude_, false)
{}


tnbLib::waveModel::waveModel
(
	const objectRegistry& db,
	const dictionary& dict
)
	:
	db_(db),
	amplitude_(Function1<scalar>::New("amplitude", dict))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::waveModel::~waveModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::waveModel::g() const
{
	return mag(db_.lookupObject<uniformDimensionedVectorField>("g").value());
}


void tnbLib::waveModel::write(Ostream& os) const
{
	writeEntry(os, amplitude_());
}


// ************************************************************************* //