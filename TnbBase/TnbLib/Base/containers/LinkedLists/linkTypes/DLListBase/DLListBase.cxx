#include <DLListBase.hxx>

#include <IOstreams.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::DLListBase::iterator tnbLib::DLListBase::endIter_
(
	const_cast<DLListBase&>(static_cast<const DLListBase&>(DLListBase()))
);

tnbLib::DLListBase::const_iterator tnbLib::DLListBase::endConstIter_
(
	static_cast<const DLListBase&>(DLListBase()),
	reinterpret_cast<const link*>(0)
);

tnbLib::DLListBase::const_reverse_iterator tnbLib::DLListBase::endConstRevIter_
(
	static_cast<const DLListBase&>(DLListBase()),
	reinterpret_cast<const link*>(0)
);


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DLListBase::insert(DLListBase::link* a)
{
	nElmts_++;

	if (!first_)
	{
		a->prev_ = a;
		a->next_ = a;
		first_ = last_ = a;
	}
	else
	{
		a->prev_ = a;
		a->next_ = first_;
		first_->prev_ = a;
		first_ = a;
	}
}


void tnbLib::DLListBase::append(DLListBase::link* a)
{
	nElmts_++;

	if (!first_)
	{
		a->prev_ = a;
		a->next_ = a;
		first_ = last_ = a;
	}
	else
	{
		last_->next_ = a;
		a->prev_ = last_;
		a->next_ = a;
		last_ = a;
	}
}


bool tnbLib::DLListBase::swapUp(DLListBase::link* a)
{
	if (first_ != a)
	{
		link* ap = a->prev_;

		if (ap == first_)
		{
			first_ = a;
			ap->prev_ = a;
		}
		else
		{
			ap->prev_->next_ = a;
		}

		if (a == last_)
		{
			last_ = ap;
			a->next_ = ap;
		}
		else
		{
			a->next_->prev_ = ap;
		}

		a->prev_ = ap->prev_;
		ap->prev_ = a;

		ap->next_ = a->next_;
		a->next_ = ap;

		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::DLListBase::swapDown(DLListBase::link* a)
{
	if (last_ != a)
	{
		link* an = a->next_;

		if (a == first_)
		{
			first_ = an;
			a->prev_ = an;
		}
		else
		{
			a->prev_->next_ = an;
		}

		if (an == last_)
		{
			last_ = a;
			an->next_ = a;
		}
		else
		{
			an->next_->prev_ = a;
		}

		an->prev_ = a->prev_;
		a->prev_ = an;

		a->next_ = an->next_;
		an->next_ = a;

		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::DLListBase::link* tnbLib::DLListBase::removeHead()
{
	nElmts_--;

	if (!first_)
	{
		FatalErrorInFunction
			<< "remove from empty list"
			<< abort(FatalError);
	}

	DLListBase::link* f = first_;
	first_ = f->next_;

	if (!first_)
	{
		last_ = 0;
	}

	f->deregister();
	return f;
}


tnbLib::DLListBase::link* tnbLib::DLListBase::remove(DLListBase::link* l)
{
	nElmts_--;

	link* ret = l;

	if (l == first_ && first_ == last_)
	{
		first_ = 0;
		last_ = 0;
	}
	else if (l == first_)
	{
		first_ = first_->next_;
		first_->prev_ = first_;
	}
	else if (l == last_)
	{
		last_ = last_->prev_;
		last_->next_ = last_;
	}
	else
	{
		l->next_->prev_ = l->prev_;
		l->prev_->next_ = l->next_;
	}

	ret->deregister();
	return ret;
}


tnbLib::DLListBase::link* tnbLib::DLListBase::replace
(
	DLListBase::link* oldLink,
	DLListBase::link* newLink
)
{
	link* ret = oldLink;

	newLink->prev_ = oldLink->prev_;
	newLink->next_ = oldLink->next_;

	if (oldLink == first_ && first_ == last_)
	{
		first_ = newLink;
		last_ = newLink;
	}
	else if (oldLink == first_)
	{
		first_ = newLink;
		newLink->next_->prev_ = newLink;
	}
	else if (oldLink == last_)
	{
		last_ = newLink;
		newLink->prev_->next_ = newLink;
	}
	else
	{
		newLink->prev_->next_ = newLink;
		newLink->next_->prev_ = newLink;
	}

	ret->deregister();
	return ret;
}


// ************************************************************************* //