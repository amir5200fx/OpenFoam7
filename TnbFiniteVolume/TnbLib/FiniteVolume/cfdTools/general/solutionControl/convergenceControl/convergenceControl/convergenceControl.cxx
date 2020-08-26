#include <convergenceControl.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(convergenceControl, 0);
}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::DynamicList<tnbLib::word> tnbLib::convergenceControl::getFieldNames
(
	const fvMesh& mesh
)
{
	DynamicList<word> fieldNames;

	getFieldTypeNames<scalar>(mesh, fieldNames);
	getFieldTypeNames<vector>(mesh, fieldNames);
	getFieldTypeNames<sphericalTensor>(mesh, fieldNames);
	getFieldTypeNames<symmTensor>(mesh, fieldNames);
	getFieldTypeNames<tensor>(mesh, fieldNames);

	return fieldNames;
}


void tnbLib::convergenceControl::getInitialResiduals
(
	const fvMesh& mesh,
	const word& fieldName,
	const label solvei,
	scalar& r0,
	scalar& r
)
{
	getInitialTypeResiduals<scalar>(mesh, fieldName, solvei, r0, r);
	getInitialTypeResiduals<vector>(mesh, fieldName, solvei, r0, r);
	getInitialTypeResiduals<sphericalTensor>(mesh, fieldName, solvei, r0, r);
	getInitialTypeResiduals<symmTensor>(mesh, fieldName, solvei, r0, r);
	getInitialTypeResiduals<tensor>(mesh, fieldName, solvei, r0, r);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::convergenceControl::convergenceControl(const solutionControl& control)
	:
	control_(control)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::convergenceControl::~convergenceControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::convergenceControl::converged()
{
	if
		(
			control_.time().timeIndex() != control_.time().startTimeIndex()
			&& criteriaSatisfied()
			)
	{
		Info << nl << control_.algorithmName() << " solution converged in "
			<< control_.time().timeName() << " iterations" << nl << endl;

		return true;
	}

	return false;
}


bool tnbLib::convergenceControl::endIfConverged(Time& time)
{
	if (converged())
	{
		if (time.writeTime())
		{
			time.stopAt(Time::stopAtControl::noWriteNow);
			time.setEndTime(time);
		}
		else
		{
			time.writeAndEnd();
		}

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //