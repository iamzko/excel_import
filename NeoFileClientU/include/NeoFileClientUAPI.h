#ifndef NEOFILECLIENTU_API_H
#define NEOFILECLIENTU_API_H

#ifdef NEOFILECLIENTU_EXPORTS
#define NEOFILECLIENTU_API __declspec(dllexport)
#else
#define NEOFILECLIENTU_API __declspec(dllimport)
#endif //~ NEOFILECLIENTU_EXPORTS

#include <windows.h>

enum CallbackReasonEnum {
	CR_TRANSFER_START = 0,
	CR_TRANSFER_FILE_START,
	CR_TRANSFER_FILE_FINISHED,
	CR_TRANSFER_FILE_IGNORED,
	CR_TRANSFER_FILE_ERROR,
	CR_TRANSFER_FINISHED,
	CR_TRANSFER_ERROR,
	CR_UPDATE_PROGRESS,
};

enum FinishStatusEnum {
	FS_NOT_BEGIN = 0,
	FS_IN_PROGRESS,
	FS_FINISHED,
	FS_IGNORED,
	FS_ERROR,
};

typedef struct _FILEINFO {
	const wchar_t* pszFilePath;
	const wchar_t* pszSvrFilePath;
	__int64 nFileSize;
	wchar_t szModifiedTime[32];
	FinishStatusEnum finishStatus;
	__int64 nTransferredBytes;
	__int64 nIgnoredBytes;
	DWORD dwTimeSpent; // in milliseconds
	wchar_t szFilePathRename[MAX_PATH]; // Only valid on CR_TRANSFER_FILE_START of download mode, ignored in other places
	wchar_t szSvrFilePathRename[MAX_PATH]; // Only valid on CR_TRANSFER_FILE_START of upload mode, ignored in other places
	void* lpPerFileData;
} FILEINFO, *LPFILEINFO;

typedef struct _FILETRANSPARAM {
	CallbackReasonEnum reason;
	__int64 nTotalBytes;
	__int64 nTransferredBytes;
	__int64 nIgnoredBytes;
	DWORD dwTotalTimeSpent; // in milliseconds
	void* lpCustExecuteData;
	LPFILEINFO lpFileInfo;
} FILETRANSPARAM;
typedef BOOL (CALLBACK * LP_FILE_TRANSFER_CALLBACK_ROUTINE)(FILETRANSPARAM* param);

// File Transmition class
class NEOFILECLIENTU_API CTransmitFile {
public:
	/*
	Get an instance of CTransmitFile for upload/download
	@param
		bUpload: TRUE for upload, FALSE for download
	@ret
		An instance of CTransmitFile, NULL for failure
	*/
	static CTransmitFile* CreateInstance(BOOL bUpload);

	/*
	Free memory occupied by CTransmitFile, etc.
	@param
		pTransmitFile: The instance to be destroyed
	*/
	static void DestroyInstance(CTransmitFile* pTransmitFile);

public:
	/*
	Establish connections with server.
	@param
		szSvrIp: Server IP
		nPort: Server port
		cSocket: number of concurrent socket for transmiting file, consider it as threads.
	@ret
		TRUE indicate success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL ConnectServer(const wchar_t* szSvrIp, USHORT nPort, int cSocket) = 0;

	/*
	Disconnect server.
	*/
	virtual void CloseConnection() = 0;

	/*
	Set file segment size in bytes for transmitting. Recommanded size: 320KB for LAN, 95KB for WAN.
	@param
		nDataChunkSize: File segment size in bytes
	*/
	virtual void SetDataChunkSize(__int64 nDataChunkSize) = 0;	// in bytes, default is 95KiB

	/*
	Set transfer speed limit.
	@param
		nBPS: Maximum speed in bytes per second, 0 for no speed limit
	*/
	virtual void SetLimitSpeed(int nBPS) = 0; // in bytes per second, default no speed limit(0)

	/*
	Add one file for transfer
	@param
		szFilePath: Client file path, file must exist for uploading
		szSvrFilePath: Server relative (to server default folder) file path or absolute path
		lpPerFileData: Custom data stored for the file, used in tranfer callback. If you don't intend to use callback, just leave it NULL.
	@ret
		Index for newly added file, -1 indicates error occurred, consult GetLastErrorMessage for specific error.
	@remark
		lpPerFileData can be through param->lpFileInfo->lpPerFileData in file related callback
	*/
	virtual int AddFile(const wchar_t* szFilePath, const wchar_t* szSvrFilePath, void* lpPerFileData = NULL) = 0;	// returns file index, -1 on error

	/*
	Actually transfer files from/to server.
	@param
		pCallbackFunc: Address of callback function for transfer event callback. If you don't intend to use callback, just leave it NULL.
		lpCustomExecutionData: Custom data for callback function, refer to it as lpCustExecuteData of FILETRANSPARAM field for callback function
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	@remark
		This transfer is always blocked. Callback routine should be declared like this:
		BOOL CALLBACK MyCallBackRoutine(FILETRANSPARAM* param);
	*/
	virtual BOOL Execute(LP_FILE_TRANSFER_CALLBACK_ROUTINE pCallbackFunc = NULL, void* lpCustomExecutionData = NULL) = 0;

	/*
	Forcefully stops the current transfer from another thread, use it with caution.
	*/
	virtual void Stop() = 0;

	/*
	Get file count, can be called at any time.
	@ret
		returns current file count
	*/
	virtual int GetFileCount() = 0;

	/*
	Get total file size, can be called after transfer
	@ret
		returns total file size in 64-bit int
	*/
	virtual __int64 GetTotalSize() = 0;

	/*
	Get transferred size for this session, ignored size does not count.
	@ret
		returns transferred file size
	*/
	virtual __int64 GetTransferredSize() = 0;

	/*
	Get time consumed durring a transfer, called after Execute.
	@ret
		returns total time consumed in milliseconds
	*/
	virtual DWORD GetTimeSpent() = 0;	//	in milliseconds

	/*
	Get file status at nIndex
	@param
		nIndex: File index for query
		LPFILEINFO: returned FILEINFO structure for file status
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL GetFileFinishStatus(int nIndex, LPFILEINFO lpFileInfo) = 0; // Typically used to query file status AFTER transmition

	/*
	Clear file queue and any transfer status but does not close connection for next transfer.
	*/
	virtual void Clear() = 0;

	/*
	Get error message for last execution error
	@param
		szBuf: Returned buffer to store error info
		nBufLen: Buffer size, recommanded size: 1024
	@ret
		returned buffer size in bytes
	*/
	virtual int GetLastErrorMessage(wchar_t* szBuf, int nBufLen) = 0;

protected:
	CTransmitFile();
	CTransmitFile(CTransmitFile&);
	virtual ~CTransmitFile();
};

typedef void* SVRFOLDERCONTENT;
typedef struct _FOLDERCONTENTITEM {
	const wchar_t* pszFileName;
	BOOL bIsFolder;
} FOLDERCONTENTITEM, * LPFOLDERCONTENTITEM;

// Server file operation class
class NEOFILECLIENTU_API CFileOperation {
public:
	/*
	Get an instance of CFileOperation for server file manipulation
	@ret
		An instance of CFileOperation, NULL for failure
	*/
	static CFileOperation* CreateInstance();

	/*
	Free memory occupied by instance of CFileOperation, etc.
	@param
		pFileOperation: The instance to be destroyed
	*/
	static void DestroyInstance(CFileOperation* pFileOperation);

public:
	/*
	Establish connections with server.
	@param
		szSvrIp: Server IP
		nPort: Server port
	@ret
		TRUE indicate success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL ConnectServer(const wchar_t* szSvrIp, USHORT nPort) = 0;

	/*
	Disconnect from server.
	*/
	virtual void CloseConnection() = 0;


	// Query server info
	/*
	Query server connection status
	@param
		szBuf: Buffer for the query
		nBufLen: Buffer size
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL QueryConnections(wchar_t* szBuf, int nBufLen) = 0;


	// File operation
	/*
	Copy server file to another place
	@param
		szExistFilePath: path to exist file to copy
		szNewFilePath: path to destination file
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL CopyServerFile(const wchar_t* szExistFilePath, const wchar_t* szNewFilePath) = 0;

	/*
	Delete file on server
	@param
		szSvrFilePath: Relative or absolute file path to delete
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL DeleteServerFile(const wchar_t* szSvrFilePath) = 0;

	/*
	Move server file to another place
	@param
		szOldFilePath: path to exist file to copy
		szNewFilePath: path to the file's new destination
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL MoveServerFile(const wchar_t* szOldFilePath, const wchar_t* szNewFilePath) = 0;

	/*
	Copy server folder to another place
	@param
		szExistFolder: path to exist folder to copy
		szNewFolder: path to the folder's new destination
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL CopyServerFolder(const wchar_t* szExistFolder, const wchar_t* szNewFolder) = 0;

	/*
	Delete server folder
	@param
		szFolder: path to exist folder to delete
		bRecursive: If set to TRUE, the whole folder will be deleted even if it contains subfolders
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL DeleteServerFolder(const wchar_t* szFolder, BOOL bRecursive) = 0;

	/*
	Move server folder to another place
	@param
		szOldFolder: path to the folder to move
		szNewFolder: path to the folder's new destination
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL MoveServerFolder(const wchar_t* szOldFolder, const wchar_t* szNewFolder) = 0;
	

	// Query server folder content
	/*
	List folder content and store result in SVRFOLDERCONTENT handle
	@param
		szFolder: the destination folder to list its contents
		bRecursive: If set to TRUE, the result will contain content of subfolders
		pContent: SVRFOLDERCONTENT handle to hold the result
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL QueryServerFolderContent(const wchar_t* szFolder, BOOL bRecursive, SVRFOLDERCONTENT* pContent) = 0;

	/*
	Check if the content handle reached its last item
	@param
		content: Content handle to check
	@ret
		TRUE to indicate last item sentinel is arrived
	*/
	virtual BOOL IsServerFolderContentEOF(SVRFOLDERCONTENT content) = 0;

	/*
	Get the current server content item and move the item pointer inside content handle to next item.
	@param
		content: Content handle to parse
		pItem: Returns current item
	@ret
		TRUE to indicate success, FALSE when last item is arrived or error occurred
	*/
	virtual BOOL GetNextSvrFileNameFromServerFolderContent(SVRFOLDERCONTENT content, LPFOLDERCONTENTITEM pItem) = 0;

	/*
	Free content handle
	@param
		content: Content handle to free
	*/
	virtual void FreeServerFolderContentResult(SVRFOLDERCONTENT content) = 0;


	/*
	Get specific file size and modified time on server.
	@param
		szSvrFilePath: Relative or absolute file path on server
		nFileSize: Returned file size in bytes
		FILETIME: Returned FILETIME structure
	@ret
		TRUE for success, otherwise consult GetLastErrorMessage for specific error.
	*/
	virtual BOOL QueryServerFileInfo(const wchar_t* szSvrFilePath, __int64* nFileSize, FILETIME* ftModifiedTime) = 0;


	/*
	Get error message for last execution error
	@param
		szBuf: Returned buffer to store error info
		nBufLen: Buffer size, recommanded size: 1024
	@ret
		returned buffer size in bytes
	*/
	virtual int GetLastErrorMessage(wchar_t* szBuf, int nBufLen) = 0;

protected:
	CFileOperation();
	CFileOperation(CFileOperation&);
	virtual ~CFileOperation();
};

#endif //~ NEOFILECLIENTU_API_H