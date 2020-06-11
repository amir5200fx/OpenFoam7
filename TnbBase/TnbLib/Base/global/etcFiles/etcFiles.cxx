#include <etcFiles.hxx>

#include <OSspecific.hxx>
#include <tnbVersion.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::fileNameList tnbLib::findEtcDirs(const fileName& local)
{
	fileNameList dirs;

	// Search for user directories in
	// * ~/.OpenFOAM/VERSION
	// * ~/.OpenFOAM
	//
	fileName searchDir = home() / ".OpenFOAM";
	if (isDir(searchDir))
	{
		fileName fullName = searchDir / FOAMversion / local;
		if (isDir(fullName))
		{
			dirs.append(fullName);
		}

		fullName = searchDir / local;
		if (isDir(fullName))
		{
			dirs.append(fullName);
		}
	}

	// Search for group (site) directories in
	// * $WM_PROJECT_SITE/VERSION/etc/
	// * $WM_PROJECT_SITE/etc/
	//
	searchDir = getEnv("WM_PROJECT_SITE");
	if (searchDir.size())
	{
		if (isDir(searchDir))
		{
			fileName fullName = searchDir / FOAMversion / "etc" / local;
			if (isDir(fullName))
			{
				dirs.append(fullName);
			}

			fullName = searchDir / "etc" / local;
			if (isDir(fullName))
			{
				dirs.append(fullName);
			}
		}
	}
	else
	{
		// Or search for group (site) files in
		// * $WM_PROJECT_INST_DIR/site/VERSION/etc/
		// * $WM_PROJECT_INST_DIR/site/etc/
		//
		searchDir = getEnv("WM_PROJECT_INST_DIR");
		if (isDir(searchDir))
		{
			fileName fullName = searchDir / "site" / FOAMversion / "etc" / local;
			if (isDir(fullName))
			{
				dirs.append(fullName);
			}

			fullName = searchDir / "site/etc" / local;
			if (isDir(fullName))
			{
				dirs.append(fullName);
			}
		}
	}

	// Search for other (shipped) files in
	// * $WM_PROJECT_DIR/etc
	//
	searchDir = getEnv("WM_PROJECT_DIR");
	if (isDir(searchDir))
	{
		fileName fullName = searchDir / "etc" / local;
		if (isDir(fullName))
		{
			dirs.append(fullName);
		}
	}

	return dirs;
}


tnbLib::fileNameList tnbLib::findEtcFiles
(
	const fileName& name,
	bool mandatory,
	bool findFirst
)
{
	fileNameList results;

	// Search for user files in
	// * ~/.OpenFOAM/VERSION
	// * ~/.OpenFOAM
	//
	fileName searchDir = home() / ".OpenFOAM";
	if (isDir(searchDir))
	{
		fileName fullName = searchDir / FOAMversion / name;
		if (isFile(fullName))
		{
			results.append(fullName);
			if (findFirst)
			{
				return results;
			}
		}

		fullName = searchDir / name;
		if (isFile(fullName))
		{
			results.append(fullName);
			if (findFirst)
			{
				return results;
			}
		}
	}

	// Search for group (site) files in
	// * $WM_PROJECT_SITE/VERSION/etc/
	// * $WM_PROJECT_SITE/etc/
	//
	searchDir = getEnv("WM_PROJECT_SITE");
	if (searchDir.size())
	{
		if (isDir(searchDir))
		{
			fileName fullName = searchDir / FOAMversion / "etc" / name;
			if (isFile(fullName))
			{
				results.append(fullName);
				if (findFirst)
				{
					return results;
				}
			}

			fullName = searchDir / "etc" / name;
			if (isFile(fullName))
			{
				results.append(fullName);
				if (findFirst)
				{
					return results;
				}
			}
		}
	}
	else
	{
		// Or search for group (site) files in
		// * $WM_PROJECT_INST_DIR/site/VERSION/etc/
		// * $WM_PROJECT_INST_DIR/site/etc/
		//
		searchDir = getEnv("WM_PROJECT_INST_DIR");
		if (isDir(searchDir))
		{
			fileName fullName = searchDir / "site" / FOAMversion / "etc" / name;
			if (isFile(fullName))
			{
				results.append(fullName);
				if (findFirst)
				{
					return results;
				}
			}

			fullName = searchDir / "site/etc" / name;
			if (isFile(fullName))
			{
				results.append(fullName);
				if (findFirst)
				{
					return results;
				}
			}
		}
	}

	// Search for other (shipped) files in
	// * $WM_PROJECT_DIR/etc
	//
	searchDir = getEnv("WM_PROJECT_DIR");
	if (isDir(searchDir))
	{
		fileName fullName = searchDir / "etc" / name;
		if (isFile(fullName))
		{
			results.append(fullName);
			if (findFirst)
			{
				return results;
			}
		}
	}

	// Not found
	if (results.empty())
	{
		// Abort if the file is mandatory, otherwise return null
		if (mandatory)
		{
			std::cerr
				<< "--> FOAM FATAL ERROR in tnbLib::findEtcFiles() :"
				" could not find mandatory file\n    '"
				<< name.c_str() << "'\n\n" << std::endl;
			::exit(1);
		}
	}

	// Return list of matching paths or empty list if none found
	return results;
}


tnbLib::fileName tnbLib::findEtcFile(const fileName& name, bool mandatory)
{
	fileNameList results(findEtcFiles(name, mandatory, true));

	if (results.size())
	{
		return results[0];
	}
	else
	{
		return fileName();
	}
}


// ************************************************************************* //