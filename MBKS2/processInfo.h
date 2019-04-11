#pragma once
using namespace std;

enum IntegrityLevel { High, Low };
struct HANDLE_Info
{

};

class ProcessInformation
{
private:

	HANDLE hProcess;
    DWORD processID;
	string ProcessName;
	string ProcessDescription;
	string ProcessExecutablePath;
	DWORD ProcessParentID;
	string ProcessOwner;
	string ProcessSID;
	string ProcessType;	//x32/x64
	string ProcessDEPUsage;
	string ProcessASLRUsage;
	vector<HANDLE_Info> ProcessOpenedHandles;
	vector<string> ProcessDLLList;

public:

	ProcessInformation();
	ProcessInformation(DWORD processID);
	~ProcessInformation();

	DWORD ProcessGetId();
	string ProcessGetName(DWORD processID);
	string ProcessGetDescription(DWORD processID);
	string ProcessGetExecutablePath(DWORD processID, std::string ProcessN);
	DWORD ProcessGetParentID(DWORD processID);
	string ProcessGetOwner(DWORD processID);
	string ProcessGetSID(DWORD processID);
	string ProcessGetType(DWORD processID);	//x32/x64
	string ProcessGetDEPUsage(DWORD processID);
	string ProcessGetASLRUsage(DWORD processID);
	vector<HANDLE_Info> ProcessGetOpenedHandles(DWORD processID);
	vector<string> ProcessGetDLLList(DWORD processID);

	bool ProcessSetIntegrityLevel(DWORD processID, IntegrityLevel NewLevel);

};

vector<ProcessInformation> EnumerateProcesses(void);
