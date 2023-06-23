// Fill out your copyright notice in the Description page of Project Settings.


#include "PathUtils.h"
#include "ShlObj.h"

PathUtils::PathUtils()
{
}

PathUtils::~PathUtils()
{
}

const TCHAR* PathUtils::UserRoamingDir()
{
	static FString WindowsUserSettingsDir;
	if (!WindowsUserSettingsDir.Len())
	{
		TCHAR* UserPath;

		// get the local AppData directory
		HRESULT Ret = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &UserPath);
		if (SUCCEEDED(Ret))
		{
			// make the base user dir path
			WindowsUserSettingsDir = FString(UserPath).Replace(TEXT("\\"), TEXT("/")) + TEXT("/");
		}
	}
	return *WindowsUserSettingsDir;
}
