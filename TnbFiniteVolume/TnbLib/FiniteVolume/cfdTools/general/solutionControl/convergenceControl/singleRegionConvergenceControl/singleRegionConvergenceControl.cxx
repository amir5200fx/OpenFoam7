#include <singleRegionConvergenceControl.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(singleRegionConvergenceControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::singleRegionConvergenceControl::singleRegionConvergenceControl
(
	const singleRegionSolutionControl& control
)
	:
	convergenceControl(control),
	mesh_(control.mesh()),
	residualControl_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::singleRegionConvergenceControl::~singleRegionConvergenceControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::singleRegionConvergenceControl::readResidualControls()
{
	const dictionary residualDict
	(
		control_.dict().subOrEmptyDict("residualControl")
	);

	DynamicList<residualData> data(residualControl_);

	forAllConstIter(dictionary, residualDict, iter)
	{
		const word& fName = iter().keyword();

		if (iter().isDict())
		{
			FatalErrorInFunction
				<< "Solution convergence criteria specified in "
				<< control_.algorithmName() << '.' << residualDict.dictName()
				<< " must be given as single values. Corrector loop "
				<< "convergence criteria, if appropriate, are specified as "
				<< "dictionaries in " << control_.algorithmName()
				<< ".<loopName>ResidualControl." << exit(FatalError);
		}

		const label fieldi =
			residualControlIndex(fName, residualControl_, false);
		if (fieldi == -1)
		{
			residualData rd;
			rd.name = fName.c_str();
			rd.absTol = readScalar(residualDict.lookup(fName));
			data.append(rd);
		}
		else
		{
			residualData& rd = data[fieldi];
			rd.absTol = readScalar(residualDict.lookup(fName));
		}
	}

	residualControl_.transfer(data);

	if (control_.debug > 1)
	{
		forAll(residualControl_, i)
		{
			const residualData& rd = residualControl_[i];
			Info << residualDict.dictName() << '[' << i << "]:" << nl
				<< "    name     : " << rd.name << nl
				<< "    absTol   : " << rd.absTol << endl;
		}
	}

	return true;
}


void tnbLib::singleRegionConvergenceControl::printResidualControls() const
{
	Info << nl;

	Info << control_.algorithmName() << ": "
		<< (residualControl_.empty() ? "No c" : "C")
		<< "onvergence criteria found" << nl;

	forAll(residualControl_, i)
	{
		Info << control_.algorithmSpace() << "  " << residualControl_[i].name
			<< ": tolerance " << residualControl_[i].absTol << nl;
	}

	Info << endl;
}


bool tnbLib::singleRegionConvergenceControl::hasResidualControls() const
{
	return !residualControl_.empty();
}


bool tnbLib::singleRegionConvergenceControl::criteriaSatisfied() const
{
	if (!hasResidualControls())
	{
		return false;
	}

	bool achieved = true;
	bool checked = false; // ensure that some checks were actually performed

	if (control_.debug)
	{
		Info << control_.algorithmName() << ": Residuals" << endl;
	}

	DynamicList<word> fieldNames(getFieldNames(mesh_));

	forAll(fieldNames, i)
	{
		const word& fieldName = fieldNames[i];
		const label fieldi =
			residualControlIndex(fieldName, residualControl_);
		if (fieldi != -1)
		{
			scalar residual;
			getInitialResiduals
			(
				mesh_,
				fieldName,
				0,
				residual,
				residual
			);

			checked = true;

			bool absCheck = residual < residualControl_[fieldi].absTol;

			achieved = achieved && absCheck;

			if (control_.debug)
			{
				Info << control_.algorithmSpace() << "  " << fieldName
					<< ": tolerance " << residual << " ("
					<< residualControl_[fieldi].absTol << ")"
					<< (absCheck ? " CONVERGED" : "") << endl;
			}
		}
	}

	return checked && achieved;
}


// ************************************************************************* //