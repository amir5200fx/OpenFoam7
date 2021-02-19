#include <bladeModel.hxx>

#include <unitConversion.hxx>
#include <Tuple2.hxx>
#include <vector.hxx>
#include <IFstream.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

bool tnbLib::bladeModel::readFromFile() const
{
	return fName_ != fileName::null;
}


void tnbLib::bladeModel::interpolateWeights
(
	const scalar& xIn,
	const List<scalar>& values,
	label& i1,
	label& i2,
	scalar& ddx
) const
{
	i2 = 0;
	label nElem = values.size();

	if (nElem == 1)
	{
		i1 = i2;
		ddx = 0.0;
		return;
	}
	else
	{
		while ((i2 < nElem) && (values[i2] < xIn))
		{
			i2++;
		}

		if (i2 == 0)
		{
			i1 = i2;
			ddx = 0.0;
			return;
		}
		else if (i2 == nElem)
		{
			i2 = nElem - 1;
			i1 = i2;
			ddx = 0.0;
			return;
		}
		else
		{
			i1 = i2 - 1;
			ddx = (xIn - values[i1]) / (values[i2] - values[i1]);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::bladeModel::bladeModel(const dictionary& dict)
	:
	profileName_(),
	profileID_(),
	radius_(),
	twist_(),
	chord_(),
	fName_(fileName::null)
{
	List<Tuple2<word, vector>> data;
	if (readFromFile())
	{
		IFstream is(fName_);
		is >> data;
	}
	else
	{
		dict.lookup("data") >> data;
	}

	if (data.size() > 0)
	{
		profileName_.setSize(data.size());
		profileID_.setSize(data.size());
		radius_.setSize(data.size());
		twist_.setSize(data.size());
		chord_.setSize(data.size());

		forAll(data, i)
		{
			profileName_[i] = data[i].first();
			profileID_[i] = -1;
			radius_[i] = data[i].second()[0];
			twist_[i] = degToRad(data[i].second()[1]);
			chord_[i] = data[i].second()[2];
		}
	}
	else
	{
		FatalErrorInFunction
			<< "No blade data specified" << exit(FatalError);
	}
}

// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::bladeModel::~bladeModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::List<tnbLib::word>& tnbLib::bladeModel::profileName() const
{
	return profileName_;
}


const tnbLib::List<tnbLib::label>& tnbLib::bladeModel::profileID() const
{
	return profileID_;
}


const tnbLib::List<tnbLib::scalar>& tnbLib::bladeModel::radius() const
{
	return radius_;
}


const tnbLib::List<tnbLib::scalar>& tnbLib::bladeModel::twist() const
{
	return twist_;
}


const tnbLib::List<tnbLib::scalar>& tnbLib::bladeModel::chord() const
{
	return chord_;
}


tnbLib::List<tnbLib::label>& tnbLib::bladeModel::profileID()
{
	return profileID_;
}


void tnbLib::bladeModel::interpolate
(
	const scalar radius,
	scalar& twist,
	scalar& chord,
	label& i1,
	label& i2,
	scalar& invDr
) const
{
	interpolateWeights(radius, radius_, i1, i2, invDr);

	twist = invDr * (twist_[i2] - twist_[i1]) + twist_[i1];
	chord = invDr * (chord_[i2] - chord_[i1]) + chord_[i1];
}


// ************************************************************************* //