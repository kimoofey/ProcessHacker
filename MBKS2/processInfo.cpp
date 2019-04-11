
#include "stdafx.h"
#include "processInfo.h"
#pragma comment(lib, "Mincore.lib")

void PrintProcessNameAndID(DWORD processID)
{
	VS_FIXEDFILEINFO    *pFileInfo = NULL;
	BYTE                *pVersionInfo = NULL;
	UINT                pLenFileInfo = 0;

	BYTE                *pBlock = NULL;
	TCHAR                SubBlock[50];
	TCHAR                Description[50];

		// Get the process description
		//DWORD SomePtr;
		//DWORD InfoSize = GetFileVersionInfoSize(szProcessExecutable, &SomePtr);
		//GetFileVersionInfo(szProcessExecutable, NULL, InfoSize, pVersionInfo);
		//
		//VerQueryValue(pVersionInfo, TEXT("\\"), (LPVOID *)&pFileInfo, &pLenFileInfo);
		////HRESULT hr;
		//struct LANGANDCODEPAGE {
		//	WORD wLanguage;
		//	WORD wCodePage;
		//} *lpTranslate;
		//// Read the list of languages and code pages.
		//VerQueryValue(pBlock,
		//	TEXT("\\VarFileInfo\\Translation"),
		//	(LPVOID*)&lpTranslate,
		//	&pLenFileInfo);
		//// Read the file description for each language and code page.
		//for (int i = 0; i < (pLenFileInfo / sizeof(struct LANGANDCODEPAGE)); i++)
		//{
		//	StringCchPrintf(SubBlock, 50,
		//		TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
		//		lpTranslate[i].wLanguage,
		//		lpTranslate[i].wCodePage);
		//	// Retrieve file description for language and code page "i". 
		//	VerQueryValue(pBlock, SubBlock,	(LPVOID*)&Description, &pLenFileInfo);
		//}
}

vector<ProcessInformation> EnumerateProcesses(void)
{
	vector<ProcessInformation> ProcessList;
	ProcessInformation * NewProcessInfo;
	NewProcessInfo = new ProcessInformation[500];

	// Get the list of process identifiers.
	DWORD aProcesses[512], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return ProcessList;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			NewProcessInfo[i] = aProcesses[i];
			ProcessList.push_back(*NewProcessInfo);
		}
	}
	return ProcessList;
}

ProcessInformation::ProcessInformation() : processID(0) {}

ProcessInformation::ProcessInformation(DWORD processID) : processID(processID)
{
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	ProcessName = ProcessGetName(processID);
	ProcessDescription = ProcessGetDescription(processID);
	ProcessExecutablePath = ProcessGetExecutablePath(processID, ProcessName);
	ProcessParentID = ProcessGetParentID(processID);
	ProcessOwner = ProcessGetOwner(processID);
	ProcessSID = ProcessGetSID(processID);
	ProcessType = ProcessGetType(processID);
	ProcessDEPUsage = ProcessGetDEPUsage(processID);
	ProcessASLRUsage = ProcessGetASLRUsage(processID);
	ProcessOpenedHandles = ProcessGetOpenedHandles(processID);
	ProcessDLLList = ProcessGetDLLList(processID);
}

ProcessInformation::~ProcessInformation()
{
}

DWORD ProcessInformation::ProcessGetId()
{
	return 0;
}

string ProcessInformation::ProcessGetName(DWORD processID)
{
	HMODULE hMod;
	DWORD cbNeeded;
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	if (NULL != hProcess)
	{
		// Get the process name.
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	std::string ProcessN = szProcessName;
	return ProcessN;
}

string ProcessInformation::ProcessGetDescription(DWORD processID)
{
	return string();
}

string ProcessInformation::ProcessGetExecutablePath(DWORD processID, std::string ProcessN)
{
	TCHAR szProcessExecutable[MAX_PATH] = TEXT("<unknown>");
	HMODULE hMod;
	DWORD cbNeeded;

	if (NULL != hProcess)
	{
		// Get the process executable path
		GetModuleFileNameEx(hProcess, hMod, szProcessExecutable, sizeof(ProcessN.c_str()) / sizeof(TCHAR));
		std::string ExecPath = szProcessExecutable;
		return ExecPath;
	}
}

	DWORD ProcessInformation::ProcessGetParentID(DWORD processID)
	{
		return 0;
	}

	string ProcessInformation::ProcessGetOwner(DWORD processID)
	{
		return string();
	}

	string ProcessInformation::ProcessGetSID(DWORD processID)
	{
		return string();
	}

	string ProcessInformation::ProcessGetType(DWORD processID)
	{
		return string();
	}

	string ProcessInformation::ProcessGetDEPUsage(DWORD processID)
	{
		return string();
	}

	string ProcessInformation::ProcessGetASLRUsage(DWORD processID)
	{
		return string();
	}

	vector<HANDLE_Info> ProcessInformation::ProcessGetOpenedHandles(DWORD processID)
	{
		return vector<HANDLE_Info>();
	}

	vector<string> ProcessInformation::ProcessGetDLLList(DWORD processID)
	{
		return vector<string>();
	}

	bool ProcessInformation::ProcessSetIntegrityLevel(DWORD processID, IntegrityLevel NewLevel)
	{
		return false;
	}
