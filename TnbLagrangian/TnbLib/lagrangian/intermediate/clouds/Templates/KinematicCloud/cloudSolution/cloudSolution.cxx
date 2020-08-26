#include <cloudSolution.hxx>

#include <Time.hxx>
#include <localEulerDdtScheme.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cloudSolution::cloudSolution
(
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	mesh_(mesh),
	dict_(dict),
	active_(dict.lookup("active")),
	transient_(false),
	calcFrequency_(1),
	maxCo_(0.3),
	iter_(1),
	trackTime_(0),
	coupled_(false),
	cellValueSourceCorrection_(false),
	maxTrackTime_(0),
	resetSourcesOnStartup_(true),
	schemes_()
{
	if (active_)
	{
		read();
	}
}


tnbLib::cloudSolution::cloudSolution
(
	const cloudSolution& cs
)
	:
	mesh_(cs.mesh_),
	dict_(cs.dict_),
	active_(cs.active_),
	transient_(cs.transient_),
	calcFrequency_(cs.calcFrequency_),
	maxCo_(cs.maxCo_),
	iter_(cs.iter_),
	trackTime_(cs.trackTime_),
	coupled_(cs.coupled_),
	cellValueSourceCorrection_(cs.cellValueSourceCorrection_),
	maxTrackTime_(cs.maxTrackTime_),
	resetSourcesOnStartup_(cs.resetSourcesOnStartup_),
	schemes_(cs.schemes_)
{}


tnbLib::cloudSolution::cloudSolution
(
	const fvMesh& mesh
)
	:
	mesh_(mesh),
	dict_(dictionary::null),
	active_(false),
	transient_(false),
	calcFrequency_(0),
	maxCo_(great),
	iter_(0),
	trackTime_(0),
	coupled_(false),
	cellValueSourceCorrection_(false),
	maxTrackTime_(0),
	resetSourcesOnStartup_(false),
	schemes_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cloudSolution::~cloudSolution()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cloudSolution::read()
{
	// For transient runs the Lagrangian tracking may be transient or steady
	transient_ = dict_.lookupOrDefault("transient", false);

	// For LTS and steady-state runs the Lagrangian tracking cannot be transient
	if (transient_)
	{
		if (fv::localEulerDdt::enabled(mesh_))
		{
			IOWarningInFunction(dict_)
				<< "Transient tracking is not supported for LTS"
				" simulations, switching to steady state tracking."
				<< endl;
			transient_ = false;
		}

		if (mesh_.steady())
		{
			IOWarningInFunction(dict_)
				<< "Transient tracking is not supported for steady-state"
				" simulations, switching to steady state tracking."
				<< endl;
			transient_ = false;
		}
	}

	dict_.lookup("coupled") >> coupled_;
	dict_.lookup("cellValueSourceCorrection") >> cellValueSourceCorrection_;
	dict_.readIfPresent("maxCo", maxCo_);

	if (steadyState())
	{
		dict_.lookup("calcFrequency") >> calcFrequency_;
		dict_.lookup("maxTrackTime") >> maxTrackTime_;

		if (coupled_)
		{
			dict_.subDict("sourceTerms").lookup("resetOnStartup")
				>> resetSourcesOnStartup_;
		}
	}

	if (coupled_)
	{
		const dictionary&
			schemesDict(dict_.subDict("sourceTerms").subDict("schemes"));

		wordList vars(schemesDict.toc());
		schemes_.setSize(vars.size());
		forAll(vars, i)
		{
			// read solution variable name
			schemes_[i].first() = vars[i];

			// set semi-implicit (1) explicit (0) flag
			Istream& is = schemesDict.lookup(vars[i]);
			const word scheme(is);
			if (scheme == "semiImplicit")
			{
				schemes_[i].second().first() = true;
			}
			else if (scheme == "explicit")
			{
				schemes_[i].second().first() = false;
			}
			else
			{
				FatalErrorInFunction
					<< "Invalid scheme " << scheme << ". Valid schemes are "
					<< "explicit and semiImplicit" << exit(FatalError);
			}

			// read under-relaxation factor
			is >> schemes_[i].second().second();
		}
	}
}


tnbLib::scalar tnbLib::cloudSolution::relaxCoeff(const word& fieldName) const
{
	forAll(schemes_, i)
	{
		if (fieldName == schemes_[i].first())
		{
			return schemes_[i].second().second();
		}
	}

	FatalErrorInFunction
		<< "Field name " << fieldName << " not found in schemes"
		<< abort(FatalError);

	return 1;
}


bool tnbLib::cloudSolution::semiImplicit(const word& fieldName) const
{
	forAll(schemes_, i)
	{
		if (fieldName == schemes_[i].first())
		{
			return schemes_[i].second().first();
		}
	}

	FatalErrorInFunction
		<< "Field name " << fieldName << " not found in schemes"
		<< abort(FatalError);

	return false;
}


bool tnbLib::cloudSolution::solveThisStep() const
{
	return active_ && (mesh_.time().timeIndex() % calcFrequency_ == 0);
}


bool tnbLib::cloudSolution::canEvolve()
{
	if (transient_)
	{
		trackTime_ = mesh_.time().deltaTValue();
	}
	else
	{
		trackTime_ = maxTrackTime_;
	}

	return solveThisStep();
}


bool tnbLib::cloudSolution::output() const
{
	return active_ && mesh_.time().writeTime();
}


// ************************************************************************* //