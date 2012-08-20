; TitanEngine.Dumper.functions:
funcproto LOCAL,CargaTitanEngine


;**************
 
funcproto dummy,DumpProcess,QWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpProcessW, QWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpProcessEx, DWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpProcessExW, DWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpMemory, QWORD,QWORD, QWORD, QWORD
funcproto dummy,DumpMemoryW, QWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpMemoryEx, DWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpMemoryExW,DWORD, QWORD, QWORD, QWORD
funcproto dummy,DumpRegions, QWORD, QWORD, BYTE
funcproto dummy,DumpRegionsW, QWORD, QWORD, BYTE
funcproto dummy,DumpRegionsEx, DWORD, QWORD, BYTE
funcproto dummy,DumpRegionsExW, DWORD, QWORD, BYTE
funcproto dummy,DumpModule, QWORD, QWORD, QWORD
funcproto dummy,DumpModuleW, QWORD, QWORD, QWORD
funcproto dummy,DumpModuleEx, DWORD, QWORD, QWORD
funcproto dummy,DumpModuleExW, DWORD,QWORD, QWORD
funcproto dummy,PastePEHeader, QWORD, QWORD, QWORD
funcproto dummy,PastePEHeaderW, QWORD, QWORD, QWORD
funcproto dummy,ExtractSection, QWORD, QWORD, DWORD
funcproto dummy,ExtractSectionW, QWORD, QWORD, DWORD
funcproto dummy,ResortFileSections, QWORD
funcproto dummy,ResortFileSectionsW, QWORD
funcproto dummy,FindOverlay, QWORD, QWORD,QWORD
funcproto dummy,FindOverlayW, QWORD, QWORD, QWORD
funcproto dummy,ExtractOverlay, QWORD, QWORD
funcproto dummy,ExtractOverlayW, QWORD,QWORD
funcproto dummy,AddOverlay, QWORD, QWORD
funcproto dummy,AddOverlayW, QWORD, QWORD
funcproto dummy,CopyOverlay, QWORD, QWORD
funcproto dummy,CopyOverlayW, QWORD, QWORD
funcproto dummy,RemoveOverlay, QWORD
funcproto dummy,RemoveOverlayW, QWORD
funcproto dummy,MakeAllSectionsRWE, QWORD
funcproto dummy,MakeAllSectionsRWEW, QWORD
funcproto dummy,AddNewSectionEx, QWORD, QWORD, DWORD, DWORD, QWORD, DWORD
funcproto dummy,AddNewSectionExW, QWORD, QWORD, DWORD, DWORD, QWORD, DWORD
funcproto dummy,AddNewSection, QWORD, QWORD, DWORD
funcproto dummy,AddNewSectionW, QWORD, QWORD, DWORD
funcproto dummy,ResizeLastSection, QWORD, DWORD, BYTE
funcproto dummy,ResizeLastSectionW, QWORD, DWORD, BYTE
funcproto dummy,SetSharedOverlay, QWORD
funcproto dummy,SetSharedOverlayW, QWORD
funcproto dummy,GetSharedOverlay 
funcproto dummy,GetSharedOverlayW  
funcproto dummy,DeleteLastSection, QWORD
funcproto dummy,DeleteLastSectionW, QWORD
funcproto dummy,DeleteLastSectionEx, QWORD, DWORD
funcproto dummy,DeleteLastSectionExW, QWORD, DWORD
funcproto dummy,GetPE32DataFromMappedFile, QWORD, DWORD, DWORD
funcproto dummy,GetPE32Data, QWORD, DWORD, DWORD
funcproto dummy,GetPE32DataW, QWORD, DWORD, DWORD
funcproto dummy,GetPE32DataFromMappedFileEx, QWORD, QWORD
funcproto dummy,GetPE32DataEx, QWORD, QWORD
funcproto dummy,GetPE32DataExW, QWORD, QWORD
funcproto dummy,SetPE32DataForMappedFile, QWORD, DWORD, DWORD, QWORD
funcproto dummy,SetPE32Data, QWORD, DWORD, DWORD, QWORD
funcproto dummy,SetPE32DataW, QWORD, DWORD, DWORD, QWORD
funcproto dummy,SetPE32DataForMappedFileEx,  QWORD, QWORD
funcproto dummy,SetPE32DataEx, QWORD, QWORD
funcproto dummy,GetPE32SectionNumberFromVA,  QWORD, QWORD
funcproto dummy,ConvertVAtoFileOffset, QWORD, QWORD, BYTE
funcproto dummy,ConvertVAtoFileOffsetEx, QWORD, DWORD, QWORd, QWORD, BYTE, BYTE
funcproto dummy,ConvertFileOffsetToVA, QWORD, QWORD, BYTE
funcproto dummy,ConvertFileOffsetToVAEx, QWORD, DWORD, QWORD, QWORD, BYTE
funcproto dummy,FixHeaderCheckSum,QWORD
funcproto dummy,FixHeaderCheckSumW, QWORD
funcproto dummy,RealignPE,QWORD, DWORD, DWORD
funcproto dummy,RealignPEEx,QWORD, DWORD, DWORD
funcproto dummy,RealignPEExW, QWORD, DWORD, DWORD
funcproto dummy,WipeSection,QWORD, DWORD, BYTE
funcproto dummy,WipeSectionW, QWORD, DWORD, BYTE
funcproto dummy,IsPE32FileValidEx, QWORD, DWORD, QWORD
funcproto dummy,IsPE32FileValidExW, QWORD, DWORD, QWORD
funcproto dummy,FixBrokenPE32FileEx, QWORD, QWORD, QWORD
funcproto dummy,FixBrokenPE32FileExW, QWORD, QWORD, QWORD
funcproto dummy,IsFileDLL, QWORD, QWORD
funcproto dummy,IsFileDLLW, QWORD, QWORD
funcproto dummy,GetPEBLocation,QWORD
funcproto dummy,HideDebugger,QWORD, DWORD
funcproto dummy,UnHideDebugger, QWORD, DWORD
funcproto dummy,RelocaterCleanup  
funcproto dummy,RelocaterInit, DWORD, QWORD, QWORD
funcproto dummy,RelocaterAddNewRelocation, QWORD, QWORD, DWORD
funcproto dummy,RelocaterEstimatedSize 
funcproto dummy,RelocaterExportRelocation,QWORD, DWORD, QWORD
funcproto dummy,RelocaterExportRelocationEx, QWORD,QWORD
funcproto dummy,RelocaterExportRelocationExW,QWORD, QWORD
funcproto dummy,RelocaterGrabRelocationTable, QWORD, QWORD, DWORD
funcproto dummy,RelocaterGrabRelocationTableEx,QWORD, QWORD, QWORD, DWORD
funcproto dummy,RelocaterMakeSnapshot,QWORD, QWORD, QWORD, QWORD
funcproto dummy,RelocaterMakeSnapshotW,QWORD, QWORD, QWORD, QWORD
funcproto dummy,RelocaterCompareTwoSnapshots,QWORD, QWORD, QWORD, QWORD, QWORD, QWORD
funcproto dummy,RelocaterCompareTwoSnapshotsW, QWORD, QWORD, QWORD, QWORD, QWORD, QWORD
funcproto dummy,RelocaterChangeFileBase, QWORD, QWORD
funcproto dummy,RelocaterChangeFileBaseW, QWORD, QWORD
funcproto dummy,RelocaterRelocateMemoryBlock,QWORD, QWORD, QWORD , DWORD, QWORD, QWORD
funcproto dummy,RelocaterWipeRelocationTable, QWORD
funcproto dummy,RelocaterWipeRelocationTableW, QWORD
funcproto dummy,ResourcerLoadFileForResourceUse,QWORD
funcproto dummy,ResourcerLoadFileForResourceUseW,QWORD
funcproto dummy,ResourcerFreeLoadedFile,QWORD
funcproto dummy,ResourcerExtractResourceFromFileEx, QWORD, QWORD, QWORD, QWORD
funcproto dummy,ResourcerExtractResourceFromFile, QWORD, QWORD, QWORD, QWORD
funcproto dummy,ResourcerExtractResourceFromFileW, QWORD, QWORD, QWORD, QWORD
funcproto dummy,ResourcerFindResource, QWORD, QWORD, DWORD, QWORD, DWORD, DWORD, QWORD, QWORD
funcproto dummy,ResourcerFindResourceW, QWORD, QWORD, DWORD, QWORD, DWORD, DWORD,QWORD, QWORD
funcproto dummy,ResourcerFindResourceEx,  QWORD, DWORD, QWORD, DWORD, QWORD, DWORD, DWORD, QWORD, QWORD
funcproto dummy,ResourcerEnumerateResource, QWORD, QWORD 
funcproto dummy,ResourcerEnumerateResourceW, QWORD, QWORD 
funcproto dummy,ResourcerEnumerateResourceEx,  QWORD, DWORD,QWORD 
funcproto dummy,ThreaderImportRunningThreadData, DWORD
funcproto dummy,ThreaderGetThreadInfo,QWORD, DWORD
funcproto dummy,ThreaderEnumThreadInfo,QWORD 
funcproto dummy,ThreaderPauseThread,QWORD
funcproto dummy,ThreaderResumeThread, QWORD
funcproto dummy,ThreaderTerminateThread,QWORD, DWORD
funcproto dummy,ThreaderPauseAllThreads, BYTE
funcproto dummy,ThreaderResumeAllThreads,BYTE
funcproto dummy,ThreaderPauseProcess 
funcproto dummy,ThreaderResumeProcess  
funcproto dummy,ThreaderCreateRemoteThread,QWORD, BYTE, QWORD, QWORD
funcproto dummy,ThreaderInjectAndExecuteCode,QWORD, DWORD, DWORD
funcproto dummy,ThreaderCreateRemoteThreadEx, QWORD, QWORD, BYTE, QWORD, QWORD
funcproto dummy,ThreaderInjectAndExecuteCodeEx,QWORD, QWORD, DWORD, DWORD
funcproto dummy,ThreaderSetCallBackForNextExitThreadEvent, QWORD
funcproto dummy,ThreaderIsThreadStillRunning, QWORD
funcproto dummy,ThreaderIsThreadActive,QWORD
funcproto dummy,ThreaderIsAnyThreadActive  
funcproto dummy,ThreaderExecuteOnlyInjectedThreads 
funcproto dummy,ThreaderGetOpenHandleForThread, DWORD
funcproto dummy,ThreaderGetThreadData  
funcproto dummy,ThreaderIsExceptionInMainThread  
funcproto dummy,StaticDisassembleEx,QWORD,QWORD
funcproto dummy,StaticDisassemble,QWORD
funcproto dummy,DisassembleEx,QWORD,QWORD
funcproto dummy,Disassemble,QWORD
funcproto dummy,StaticLengthDisassemble,QWORD
funcproto dummy,LengthDisassembleEx, QWORD, QWORD
funcproto dummy,LengthDisassemble,QWORD
funcproto dummy,InitDebug, QWORD,QWORD, QWORD
funcproto dummy,InitDebugW, QWORD, QWORD, QWORD
funcproto dummy,InitDebugEx, QWORD, QWORD, QWORd, QWORD
funcproto dummy,InitDebugExW, QWORD, QWORD, QWORD,QWORD
funcproto dummy,InitDLLDebug, QWORD, BYTE, QWORD, QWORD, QWORD
funcproto dummy,InitDLLDebugW, QWORD, BYTE, QWORD, QWORD, QWORD
funcproto dummy,StopDebug  
funcproto dummy,SetBPXOptions, DWORD
funcproto dummy,IsBPXEnabled, QWORD
funcproto dummy,EnableBPX, QWORD
funcproto dummy,DisableBPX, QWORD
funcproto dummy,SetBPX, QWORD, DWORD, QWORD
funcproto dummy,SetBPXEx, QWORD, DWORD, DWORD, DWORD, DWORD, QWORD, QWORD, QWORD, QWORD
funcproto dummy,DeleteBPX,  QWORD
funcproto dummy,SafeDeleteBPX, QWORD
funcproto dummy,SetAPIBreakPoint, QWORD, QWORD, DWORD, DWORD, QWORD
funcproto dummy,DeleteAPIBreakPoint, QWORD, QWORD, DWORD
funcproto dummy,SafeDeleteAPIBreakPoint, QWORD, QWORD, DWORD
funcproto dummy,SetMemoryBPX, QWORD, DWORD, QWORD
funcproto dummy,SetMemoryBPXEx, QWORD, DWORD, DWORD, BYTE, QWORD
funcproto dummy,RemoveMemoryBPX, QWORD, DWORD
funcproto dummy,GetContextFPUDataEx, QWORD, QWORD 
funcproto dummy,GetContextDataEx,QWORD, DWORD
funcproto dummy,GetContextData,DWORD
funcproto dummy,SetContextFPUDataEx,QWORD, QWORD 
funcproto dummy,SetContextDataEx, QWORD, DWORD, QWORD
funcproto dummy,SetContextData, DWORD, QWORD
funcproto dummy,ClearExceptionNumber  
funcproto dummy,CurrentExceptionNumber  
funcproto dummy,MatchPatternEx,QWORD, QWORD , DWORD, QWORD , DWORD, QWORD
funcproto dummy,MatchPattern, QWORD , DWORD, QWORD , DWORD, QWORD
funcproto dummy,FindEx, QWORD, QWORD, DWORD, QWORD, DWORD, QWORD
funcproto dummy,Find, QWORD, DWORD, QWORD, DWORD, QWORD
funcproto dummy,FillEx, QWORD, QWORD, DWORD, QWORD
funcproto dummy,Fill, QWORD, DWORD, QWORD
funcproto dummy,PatchEx, QWORD, QWORD, DWORD, QWORD, DWORD, BYTE, BYTE
funcproto dummy,Patch, QWORD, DWORD, QWORD, DWORD, BYTE, BYTE
funcproto dummy,ReplaceEx, QWORD, QWORD, DWORD, QWORD, DWORD, DWORD, QWORD, DWORD, QWORD
funcproto dummy,Replace, QWORD, DWORD, QWORD, DWORD, DWORD, QWORD, DWORD, QWORD
funcproto dummy,GetDebugData  
funcproto dummy,GetTerminationData  
funcproto dummy,GetExitCode  
funcproto dummy,GetDebuggedDLLBaseAddress  
funcproto dummy,GetDebuggedFileBaseAddress 
funcproto dummy,GetRemoteString, QWORD, QWORD, QWORD, DWORD
funcproto dummy,GetFunctionParameter, QWORD, DWORD, DWORD, DWORD
funcproto dummy,GetJumpDestinationEx, QWORD, QWORD, BYTE
funcproto dummy,GetJumpDestination, QWORD, QWORD
funcproto dummy,IsJumpGoingToExecuteEx, QWORD, QWORD, QWORD, QWORD
funcproto dummy,IsJumpGoingToExecute  
funcproto dummy,SetCustomHandler, DWORD, QWORD
funcproto dummy,ForceClose  
funcproto dummy,StepInto, QWORD
funcproto dummy,StepOver, QWORD
funcproto dummy,SingleStep, DWORD, QWORD
funcproto dummy,GetUnusedHardwareBreakPointRegister, QWORD
funcproto dummy,SetHardwareBreakPointEx, QWORD, QWORD, DWORD, DWORD, DWORD, QWORD, QWORD
funcproto dummy,SetHardwareBreakPoint,  QWORD, DWORD, DWORD, DWORD, QWORD
funcproto dummy,DeleteHardwareBreakPoint, DWORD
funcproto dummy,RemoveAllBreakPoints, DWORD
funcproto dummy,GetProcessInformation  
funcproto dummy,GetStartupInformation  
funcproto dummy,DebugLoop  
funcproto dummy,SetDebugLoopTimeOut, DWORD
funcproto dummy,SetNextDbgContinueStatus, DWORD
funcproto dummy,AttachDebugger, DWORD, BYTE, QWORD, QWORD
funcproto dummy,DetachDebugger, DWORD
funcproto dummy,DetachDebuggerEx, DWORD
funcproto dummy,DebugLoopEx, DWORD
funcproto dummy,AutoDebugEx, QWORD, BYTE, QWORD, QWORD, DWORD, QWORD
funcproto dummy,AutoDebugExW, QWORD, BYTE, QWORD, QWORD, DWORD, QWORD
funcproto dummy,IsFileBeingDebugged  
funcproto dummy,SetErrorModel, BYTE
funcproto dummy,FindOEPInit  
funcproto dummy,FindOEPGenerically,QWORD, QWORD, QWORD
funcproto dummy,FindOEPGenericallyW, QWORD, QWORD,QWORD
funcproto dummy,ImporterCleanup  
funcproto dummy,ImporterSetImageBase, QWORD
funcproto dummy,ImporterSetUnknownDelta, QWORD
funcproto dummy,ImporterGetCurrentDelta  
funcproto dummy,ImporterInit, DWORD, QWORD
funcproto dummy,ImporterAddNewDll, QWORD, QWORD
funcproto dummy,ImporterAddNewAPI, QWORD, QWORD
funcproto dummy,ImporterAddNewOrdinalAPI, QWORD, QWORD
funcproto dummy,ImporterGetAddedDllCount  
funcproto dummy,ImporterGetAddedAPICount  
funcproto dummy,ImporterGetLastAddedDLLName  
funcproto dummy,ImporterMoveIAT  
funcproto dummy,ImporterExportIAT, QWORD, QWORD
funcproto dummy,ImporterEstimatedSize  
funcproto dummy,ImporterExportIATEx, QWORD, QWORD
funcproto dummy,ImporterExportIATExW, QWORD, QWORD
funcproto dummy,ImporterFindAPIWriteLocation, QWORD
funcproto dummy,ImporterFindOrdinalAPIWriteLocation, QWORD
funcproto dummy,ImporterFindAPIByWriteLocation, QWORD
funcproto dummy,ImporterFindDLLByWriteLocation, QWORD
funcproto dummy,ImporterGetDLLName, QWORD
funcproto dummy,ImporterGetAPIName, QWORD
funcproto dummy,ImporterGetAPIOrdinalNumber, QWORD
funcproto dummy,ImporterGetAPINameEx, QWORD, QWORD
funcproto dummy,ImporterGetRemoteAPIAddress, QWORD, QWORD
funcproto dummy,ImporterGetRemoteAPIAddressEx, QWORD, QWORD
funcproto dummy,ImporterGetLocalAPIAddress, QWORD, QWORD
funcproto dummy,ImporterGetDLLNameFromDebugee,QWORD, QWORD
funcproto dummy,ImporterGetAPINameFromDebugee, QWORD, QWORD
funcproto dummy,ImporterGetAPIOrdinalNumberFromDebugee, QWORD, QWORD
funcproto dummy,ImporterGetDLLIndexEx, QWORD, QWORD
funcproto dummy,ImporterGetDLLIndex, QWORD, QWORD, QWORD
funcproto dummy,ImporterGetRemoteDLLBase, QWORD, QWORD
funcproto dummy,ImporterRelocateWriteLocation,QWORD
funcproto dummy,ImporterIsForwardedAPI, QWORD, QWORD
funcproto dummy,ImporterGetForwardedAPIName, QWORD, QWORD
funcproto dummy,ImporterGetForwardedDLLName, QWORD, QWORD
funcproto dummy,ImporterGetForwardedDLLIndex, QWORD, QWORD, QWORD
funcproto dummy,ImporterGetForwardedAPIOrdinalNumber,QWORD, QWORD
funcproto dummy,ImporterGetNearestAPIAddress, QWORD, QWORD
funcproto dummy,ImporterGetNearestAPIName, QWORD, QWORD
funcproto dummy,ImporterCopyOriginalIAT, QWORD, QWORD
funcproto dummy,ImporterCopyOriginalIATW, QWORD, QWORD
funcproto dummy,ImporterLoadImportTable, QWORD
funcproto dummy,ImporterLoadImportTableW, QWORD
funcproto dummy,ImporterMoveOriginalIAT, QWORD, QWORD, QWORD
funcproto dummy,ImporterMoveOriginalIATW, QWORD, QWORD, QWORD
funcproto dummy,ImporterAutoSearchIAT, QWORD, QWORD, QWORD, QWORD, DWORD, QWORD, QWORD
funcproto dummy,ImporterAutoSearchIATW, QWORD, QWORD, QWORD, QWORD, DWORD, QWORD, QWORD
funcproto dummy,ImporterAutoSearchIATEx, QWORD, QWORD, QWORD, DWORD, QWORD, QWORD
funcproto dummy,ImporterEnumAddedData, QWORD
funcproto dummy,ImporterAutoFixIATEx, QWORD, QWORD, QWORD, BYTE, BYTE, QWORD, QWORD, QWORD, DWORD, DWORD, BYTE, BYTE, QWORD
funcproto dummy,ImporterAutoFixIATExW, QWORD, QWORD, QWORD, BYTE, BYTE, QWORD, QWORD, QWORD, DWORD, DWORD, BYTE, BYTE, QWORD
funcproto dummy,ImporterAutoFixIAT, QWORD, QWORD, QWORD, QWORD, DWORD, DWORD
funcproto dummy,ImporterAutoFixIATW, QWORD, QWORD, QWORD, QWORD, DWORD, DWORD
funcproto dummy,HooksSafeTransitionEx, QWORD, DWORD, BYTE
funcproto dummy,HooksSafeTransition, QWORD, BYTE
funcproto dummy,HooksIsAddressRedirected, QWORD
funcproto dummy,HooksGetTrampolineAddress, QWORD
funcproto dummy,HooksGetHookEntryDetails, QWORD
funcproto dummy,HooksInsertNewRedirection, QWORD, QWORD, DWORD
funcproto dummy,HooksInsertNewIATRedirectionEx, QWORD, QWORD, QWORD, QWORD
funcproto dummy,HooksInsertNewIATRedirection, QWORD, QWORD, QWORD
funcproto dummy,HooksRemoveRedirection, QWORD, BYTE
funcproto dummy,HooksRemoveRedirectionsForModule,QWORD
funcproto dummy,HooksRemoveIATRedirection, QWORD, QWORD, BYTE
funcproto dummy,HooksDisableRedirection, QWORD, BYTE
funcproto dummy,HooksDisableRedirectionsForModule, QWORD
funcproto dummy,HooksDisableIATRedirection, QWORD, QWORD, BYTE
funcproto dummy,HooksEnableRedirection, QWORD, BYTE
funcproto dummy,HooksEnableRedirectionsForModule, QWORD
funcproto dummy,HooksEnableIATRedirection, QWORD, QWORD, BYTE
funcproto dummy,HooksScanModuleMemory, QWORD, QWORD
funcproto dummy,HooksScanEntireProcessMemory, QWORD
funcproto dummy,HooksScanEntireProcessMemoryEx  
funcproto dummy,TracerInit  
funcproto dummy,TracerLevel1, QWORD, QWORD
funcproto dummy,HashTracerLevel1, QWORD, QWORD, DWORD
funcproto dummy,TracerDetectRedirection, QWORD, QWORD
funcproto dummy,TracerFixKnownRedirection, QWORD, QWORD, DWORD
funcproto dummy,TracerFixRedirectionViaImpRecPlugin, QWORD, QWORD, QWORD
funcproto dummy,ExporterCleanup  
funcproto dummy,ExporterSetImageBase, QWORD
funcproto dummy,ExporterInit, DWORD, QWORD, DWORD, QWORD
funcproto dummy,ExporterAddNewExport, QWORD, DWORD
funcproto dummy,ExporterAddNewOrdinalExport, DWORD, DWORD
funcproto dummy,ExporterGetAddedExportCount  
funcproto dummy,ExporterEstimatedSize  
funcproto dummy,ExporterBuildExportTable, QWORD, QWORD
funcproto dummy,ExporterBuildExportTableEx, QWORD, QWORD
funcproto dummy,ExporterBuildExportTableExW, QWORD, QWORD
funcproto dummy,ExporterLoadExportTable, QWORD
funcproto dummy,ExporterLoadExportTableW, QWORD
funcproto dummy,LibrarianSetBreakPoint, QWORD, DWORD, BYTE, QWORD
funcproto dummy,LibrarianRemoveBreakPoint, QWORD, DWORD
funcproto dummy,LibrarianGetLibraryInfo, QWORD
funcproto dummy,LibrarianGetLibraryInfoW, QWORD
funcproto dummy,LibrarianGetLibraryInfoEx, QWORD 
funcproto dummy,LibrarianGetLibraryInfoExW, QWORD  
funcproto dummy,LibrarianEnumLibraryInfo, QWORD 
funcproto dummy,LibrarianEnumLibraryInfoW, QWORD 
funcproto dummy,GetActiveProcessId, QWORD
funcproto dummy,GetActiveProcessIdW, QWORD
funcproto dummy,EnumProcessesWithLibrary, QWORD, QWORD 
funcproto dummy,TLSBreakOnCallBack, QWORD, DWORD, QWORD
funcproto dummy,TLSGrabCallBackData, QWORD, QWORD, QWORD
funcproto dummy,TLSGrabCallBackDataW, QWORD, QWORD, QWORD
funcproto dummy,TLSBreakOnCallBackEx, QWORD, QWORD
funcproto dummy,TLSBreakOnCallBackExW, QWORD, QWORD
funcproto dummy,TLSRemoveCallback, QWORD
funcproto dummy,TLSRemoveCallbackW, QWORD
funcproto dummy,TLSRemoveTable, QWORD
funcproto dummy,TLSRemoveTableW, QWORD
funcproto dummy,TLSBackupData, QWORD
funcproto dummy,TLSBackupDataW, QWORD
funcproto dummy,TLSRestoreData  
funcproto dummy,TLSBuildNewTable, QWORD, QWORD, QWORD, QWORD, DWORD
funcproto dummy,TLSBuildNewTableEx, QWORD, QWORD, QWORD, DWORD
funcproto dummy,TLSBuildNewTableExW, QWORD, QWORD, QWORD, DWORD
funcproto dummy,TranslateNativeName, QWORD
funcproto dummy,TranslateNativeNameW, QWORD
funcproto dummy,HandlerGetActiveHandleCount, DWORD
funcproto dummy,HandlerIsHandleOpen, DWORD, QWORD
funcproto dummy,HandlerGetHandleName, QWORD, DWORD, QWORD, BYTE
funcproto dummy,HandlerGetHandleNameW, QWORD, DWORD, QWORD, BYTE
funcproto dummy,HandlerEnumerateOpenHandles, DWORD, QWORD, DWORD
funcproto dummy,HandlerGetHandleDetails, QWORD, DWORD, QWORD, DWORD
funcproto dummy,HandlerCloseRemoteHandle, QWORD, QWORD
funcproto dummy,HandlerEnumerateLockHandles,QWORD, BYTE, BYTE, QWORD, DWORD
funcproto dummy,HandlerEnumerateLockHandlesW,QWORD, BYTE, BYTE, QWORD, DWORD
funcproto dummy,HandlerCloseAllLockHandles, QWORD, BYTE, BYTE
funcproto dummy,HandlerCloseAllLockHandlesW, QWORD, BYTE, BYTE
funcproto dummy,HandlerIsFileLocked, QWORD, BYTE, BYTE
funcproto dummy,HandlerIsFileLockedW, QWORD, BYTE, BYTE
funcproto dummy,HandlerEnumerateOpenMutexes,QWORD, DWORD, QWORD, DWORD
funcproto dummy,HandlerGetOpenMutexHandle, QWORD, DWORD, QWORD
funcproto dummy,HandlerGetOpenMutexHandleW, QWORD, DWORD, QWORD
funcproto dummy,HandlerGetProcessIdWhichCreatedMutex, QWORD
funcproto dummy,HandlerGetProcessIdWhichCreatedMutexW, QWORD
funcproto dummy,RemoteLoadLibrary, QWORD, QWORD, BYTE
funcproto dummy,RemoteLoadLibraryW, QWORD, QWORD, BYTE
funcproto dummy,RemoteFreeLibrary, QWORD, QWORD, QWORD, BYTE
funcproto dummy,RemoteFreeLibraryW, QWORD, QWORD, QWORD, BYTE
funcproto dummy,RemoteExitProcess, QWORD, DWORD
funcproto dummy,StaticFileLoad, QWORD, DWORD, BYTE, QWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticFileLoadW, QWORD, DWORD, BYTE, QWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticFileUnload, QWORD, BYTE, QWORD, DWORD, QWORD, QWORD
funcproto dummy,StaticFileUnloadW, QWORD, BYTE, QWORD, DWORD, QWORD, QWORD
funcproto dummy,StaticFileOpen, QWORD, DWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticFileOpenW, QWORD, DWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticFileGetContent, QWORD, DWORD, QWORD, QWORD , DWORD
funcproto dummy,StaticFileClose, QWORD
funcproto dummy,StaticMemoryDecrypt, QWORD, DWORD, DWORD, DWORD, QWORD
funcproto dummy,StaticMemoryDecryptEx, QWORD, DWORD, DWORD, QWORD 
funcproto dummy,StaticMemoryDecryptSpecial, QWORD, DWORD, DWORD, DWORD, QWORD 
funcproto dummy,StaticSectionDecrypt,  QWORD, DWORD, BYTE, DWORD, DWORD, QWORD
funcproto dummy,StaticMemoryDecompress, QWORD , DWORD, QWORD , DWORD, DWORD
funcproto dummy,StaticRawMemoryCopy, QWORD, QWORD, QWORD, DWORD, BYTE, QWORD
funcproto dummy,StaticRawMemoryCopyW, QWORD, QWORD, QWORD, DWORD, BYTE, QWORD
funcproto dummy,StaticRawMemoryCopyEx, QWORD, DWORD, DWORD, QWORD
funcproto dummy,StaticRawMemoryCopyExW, QWORD, DWORD, DWORD, QWORD
funcproto dummy,StaticRawMemoryCopyEx64,QWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticRawMemoryCopyEx64W,QWORD, QWORD, QWORD, QWORD
funcproto dummy,StaticHashMemory, QWORD , DWORD,QWORD , BYTE, DWORD
funcproto dummy,StaticHashFileW, QWORD, QWORD, BYTE, DWORD
funcproto dummy,StaticHashFile, QWORD, QWORD, BYTE, DWORD
funcproto dummy,EngineUnpackerInitialize, QWORD, QWORD, BYTE, BYTE, BYTE, QWORD 
funcproto dummy,EngineUnpackerInitializeW, QWORD, QWORD, BYTE, BYTE, BYTE, QWORD 
funcproto dummy,EngineUnpackerSetBreakCondition, QWORD , DWORD, QWORD, DWORD, DWORD, QWORD, BYTE, DWORD, DWORD
funcproto dummy,EngineUnpackerSetEntryPointAddress, QWORD 
funcproto dummy,EngineUnpackerFinalizeUnpacking  
funcproto dummy,SetEngineVariable, DWORD, BYTE
funcproto dummy,EngineCreateMissingDependencies, QWORD, QWORD, BYTE
funcproto dummy,EngineCreateMissingDependenciesW, QWORD, QWORD, BYTE
funcproto dummy,EngineFakeMissingDependencies, QWORD
funcproto dummy,EngineDeleteCreatedDependencies 
funcproto dummy,EngineCreateUnpackerWindow, QWORD, QWORD, QWORD, QWORD, QWORD 
funcproto dummy,EngineAddUnpackerWindowLogMessage, QWORD
funcproto dummy,ExtensionManagerIsPluginLoaded,QWORD
funcproto dummy,ExtensionManagerIsPluginEnabled, QWORD
funcproto dummy,ExtensionManagerDisableAllPlugins  
funcproto dummy,ExtensionManagerDisablePlugin, QWORD
funcproto dummy,ExtensionManagerEnableAllPlugins 
funcproto dummy,ExtensionManagerEnablePlugin, QWORD
funcproto dummy,ExtensionManagerUnloadAllPlugins 
funcproto dummy,ExtensionManagerUnloadPlugin, QWORD
funcproto dummy,ExtensionManagerGetPluginInfo, QWORD

.data

szTitanDll	db "TitanEngine_x64.dll",0

szDumpProcess db "DumpProcess",0
szDumpProcessW db "DumpProcessW",0
szDumpProcessEx db "DumpProcessEx",0
szDumpProcessExW db "DumpProcessExW",0
szDumpMemory db "DumpMemory",0
szDumpMemoryW db "DumpMemoryW",0
szDumpMemoryEx db "DumpMemoryEx",0
szDumpMemoryExW db "DumpMemoryExW",0
szDumpRegions db "DumpRegions",0
szDumpRegionsW db "DumpRegionsW",0
szDumpRegionsEx db "DumpRegionsEx",0
szDumpRegionsExW db "DumpRegionsExW",0
szDumpModule db "DumpModule",0
szDumpModuleW db "DumpModuleW",0
szDumpModuleEx db "DumpModuleEx",0
szDumpModuleExW db "DumpModuleExW",0
szPastePEHeader db "PastePEHeader",0
szPastePEHeaderW db "PastePEHeaderW",0
szExtractSection db "ExtractSection",0
szExtractSectionW db "ExtractSectionW",0
szResortFileSections db "ResortFileSections",0
szResortFileSectionsW db "ResortFileSectionsW",0
szFindOverlay db "FindOverlay",0
szFindOverlayW db "FindOverlayW",0
szExtractOverlay db "ExtractOverlay",0
szExtractOverlayW db "ExtractOverlayW",0
szAddOverlay db "AddOverlay",0
szAddOverlayW db "AddOverlayW",0
szCopyOverlay db "CopyOverlay",0
szCopyOverlayW db "CopyOverlayW",0
szRemoveOverlay db "RemoveOverlay",0
szRemoveOverlayW db "RemoveOverlayW",0
szMakeAllSectionsRWE db "MakeAllSectionsRWE",0
szMakeAllSectionsRWEW db "MakeAllSectionsRWEW",0
szAddNewSectionEx db "AddNewSectionEx",0
szAddNewSectionExW db "AddNewSectionExW",0
szAddNewSection db "AddNewSection",0
szAddNewSectionW db "AddNewSectionW",0
szResizeLastSection db "ResizeLastSection",0
szResizeLastSectionW db "ResizeLastSectionW",0
szSetSharedOverlay db "SetSharedOverlay",0
szSetSharedOverlayW db "SetSharedOverlayW",0
szGetSharedOverlay db "GetSharedOverlay",0
szGetSharedOverlayW db "GetSharedOverlayW",0
szDeleteLastSection db "DeleteLastSection",0
szDeleteLastSectionW db "DeleteLastSectionW",0
szDeleteLastSectionEx db "DeleteLastSectionEx",0
szDeleteLastSectionExW db "DeleteLastSectionExW",0
szGetPE32DataFromMappedFile db "GetPE32DataFromMappedFile",0
szGetPE32Data db "GetPE32Data",0
szGetPE32DataW db "GetPE32DataW",0
szGetPE32DataFromMappedFileEx db "GetPE32DataFromMappedFileEx",0
szGetPE32DataEx db "GetPE32DataEx",0
szGetPE32DataExW db "GetPE32DataExW",0
szSetPE32DataForMappedFile db "SetPE32DataForMappedFile",0
szSetPE32Data db "SetPE32Data",0
szSetPE32DataW db "SetPE32DataW",0
szSetPE32DataForMappedFileEx db "SetPE32DataForMappedFileEx",0
szSetPE32DataEx db "SetPE32DataEx",0
szGetPE32SectionNumberFromVA db "GetPE32SectionNumberFromVA",0
szConvertVAtoFileOffset db "ConvertVAtoFileOffset",0
szConvertVAtoFileOffsetEx db "ConvertVAtoFileOffsetEx",0
szConvertFileOffsetToVA db "ConvertFileOffsetToVA",0
szConvertFileOffsetToVAEx db "ConvertFileOffsetToVAEx",0
szFixHeaderCheckSum db "FixHeaderCheckSum",0
szFixHeaderCheckSumW db "FixHeaderCheckSumW",0
szRealignPE db "RealignPE",0
szRealignPEEx db "RealignPEEx",0
szRealignPEExW db "RealignPEExW",0
szWipeSection db "WipeSection",0
szWipeSectionW db "WipeSectionW",0
szIsPE32FileValidEx db "IsPE32FileValidEx",0
szIsPE32FileValidExW db "IsPE32FileValidExW",0
szFixBrokenPE32FileEx db "FixBrokenPE32FileEx",0
szFixBrokenPE32FileExW db "FixBrokenPE32FileExW",0
szIsFileDLL db "IsFileDLL",0
szIsFileDLLW db "IsFileDLLW",0
szGetPEBLocation db "GetPEBLocation",0
szHideDebugger db "HideDebugger",0
szUnHideDebugger db "UnHideDebugger",0
szRelocaterCleanup db "RelocaterCleanup",0
szRelocaterInit db "RelocaterInit",0
szRelocaterAddNewRelocation db "RelocaterAddNewRelocation",0
szRelocaterEstimatedSize db "RelocaterEstimatedSize",0
szRelocaterExportRelocation db "RelocaterExportRelocation",0
szRelocaterExportRelocationEx db "RelocaterExportRelocationEx",0
szRelocaterExportRelocationExW db "RelocaterExportRelocationExW",0
szRelocaterGrabRelocationTable db "RelocaterGrabRelocationTable",0
szRelocaterGrabRelocationTableEx db "RelocaterGrabRelocationTableEx",0
szRelocaterMakeSnapshot db "RelocaterMakeSnapshot",0
szRelocaterMakeSnapshotW db "RelocaterMakeSnapshotW",0
szRelocaterCompareTwoSnapshots db "RelocaterCompareTwoSnapshots",0
szRelocaterCompareTwoSnapshotsW db "RelocaterCompareTwoSnapshotsW",0
szRelocaterChangeFileBase db "RelocaterChangeFileBase",0
szRelocaterChangeFileBaseW db "RelocaterChangeFileBaseW",0
szRelocaterRelocateMemoryBlock db "RelocaterRelocateMemoryBlock",0
szRelocaterWipeRelocationTable db "RelocaterWipeRelocationTable",0
szRelocaterWipeRelocationTableW db "RelocaterWipeRelocationTableW",0
szResourcerLoadFileForResourceUse db "ResourcerLoadFileForResourceUse",0
szResourcerLoadFileForResourceUseW db "ResourcerLoadFileForResourceUseW",0
szResourcerFreeLoadedFile db "ResourcerFreeLoadedFile",0
szResourcerExtractResourceFromFileEx db "ResourcerExtractResourceFromFileEx",0
szResourcerExtractResourceFromFile db "ResourcerExtractResourceFromFile",0
szResourcerExtractResourceFromFileW db "ResourcerExtractResourceFromFileW",0
szResourcerFindResource db "ResourcerFindResource",0
szResourcerFindResourceW db "ResourcerFindResourceW",0
szResourcerFindResourceEx db "ResourcerFindResourceEx",0
szResourcerEnumerateResource db "ResourcerEnumerateResource",0
szResourcerEnumerateResourceW db "ResourcerEnumerateResourceW",0
szResourcerEnumerateResourceEx db "ResourcerEnumerateResourceEx",0
szThreaderImportRunningThreadData db "ThreaderImportRunningThreadData",0
szThreaderGetThreadInfo db "ThreaderGetThreadInfo",0
szThreaderEnumThreadInfo db "ThreaderEnumThreadInfo",0
szThreaderPauseThread db "ThreaderPauseThread",0
szThreaderResumeThread db "ThreaderResumeThread",0
szThreaderTerminateThread db "ThreaderTerminateThread",0
szThreaderPauseAllThreads db "ThreaderPauseAllThreads",0
szThreaderResumeAllThreads db "ThreaderResumeAllThreads",0
szThreaderPauseProcess db "ThreaderPauseProcess",0
szThreaderResumeProcess db "ThreaderResumeProcess",0
szThreaderCreateRemoteThread db "ThreaderCreateRemoteThread",0
szThreaderInjectAndExecuteCode db "ThreaderInjectAndExecuteCode",0
szThreaderCreateRemoteThreadEx db "ThreaderCreateRemoteThreadEx",0
szThreaderInjectAndExecuteCodeEx db "ThreaderInjectAndExecuteCodeEx",0
szThreaderSetCallBackForNextExitThreadEvent db "ThreaderSetCallBackForNextExitThreadEvent",0
szThreaderIsThreadStillRunning db "ThreaderIsThreadStillRunning",0
szThreaderIsThreadActive db "ThreaderIsThreadActive",0
szThreaderIsAnyThreadActive db "ThreaderIsAnyThreadActive",0
szThreaderExecuteOnlyInjectedThreads db "ThreaderExecuteOnlyInjectedThreads",0
szThreaderGetOpenHandleForThread db "ThreaderGetOpenHandleForThread",0
szThreaderGetThreadData db "ThreaderGetThreadData",0
szThreaderIsExceptionInMainThread db "ThreaderIsExceptionInMainThread",0
szStaticDisassembleEx db "StaticDisassembleEx",0
szStaticDisassemble db "StaticDisassemble",0
szDisassembleEx db "DisassembleEx",0
szDisassemble db "Disassemble",0
szStaticLengthDisassemble db "StaticLengthDisassemble",0
szLengthDisassembleEx db "LengthDisassembleEx",0
szLengthDisassemble db "LengthDisassemble",0
szInitDebug db "InitDebug",0
szInitDebugW db "InitDebugW",0
szInitDebugEx db "InitDebugEx",0
szInitDebugExW db "InitDebugExW",0
szInitDLLDebug db "InitDLLDebug",0
szInitDLLDebugW db "InitDLLDebugW",0
szStopDebug db "StopDebug",0
szSetBPXOptions db "SetBPXOptions",0
szIsBPXEnabled db "IsBPXEnabled",0
szEnableBPX db "EnableBPX",0
szDisableBPX db "DisableBPX",0
szSetBPX db "SetBPX",0
szSetBPXEx db "SetBPXEx",0
szDeleteBPX db "DeleteBPX",0
szSafeDeleteBPX db "SafeDeleteBPX",0
szSetAPIBreakPoint db "SetAPIBreakPoint",0
szDeleteAPIBreakPoint db "DeleteAPIBreakPoint",0
szSafeDeleteAPIBreakPoint db "SafeDeleteAPIBreakPoint",0
szSetMemoryBPX db "SetMemoryBPX",0
szSetMemoryBPXEx db "SetMemoryBPXEx",0
szRemoveMemoryBPX db "RemoveMemoryBPX",0
szGetContextDataEx db "GetContextDataEx",0
szGetContextData db "GetContextData",0
szSetContextDataEx db "SetContextDataEx",0
szSetContextData db "SetContextData",0
szClearExceptionNumber db "ClearExceptionNumber",0
szCurrentExceptionNumber db "CurrentExceptionNumber",0
szFindEx db "FindEx",0
szFind db "Find",0
szFillEx db "FillEx",0
szFill db "Fill",0
szPatchEx db "PatchEx",0
szPatch db "Patch",0
szReplaceEx db "ReplaceEx",0
szReplace db "Replace",0
szGetDebugData db "GetDebugData",0
szGetTerminationData db "GetTerminationData",0
szGetExitCode db "GetExitCode",0
szGetDebuggedDLLBaseAddress db "GetDebuggedDLLBaseAddress",0
szGetDebuggedFileBaseAddress db "GetDebuggedFileBaseAddress",0
szGetRemoteString db "GetRemoteString",0
szGetFunctionParameter db "GetFunctionParameter",0
szGetJumpDestinationEx db "GetJumpDestinationEx",0
szGetJumpDestination db "GetJumpDestination",0
szIsJumpGoingToExecuteEx db "IsJumpGoingToExecuteEx",0
szIsJumpGoingToExecute db "IsJumpGoingToExecute",0
szSetCustomHandler db "SetCustomHandler",0
szForceClose db "ForceClose",0
szStepInto db "StepInto",0
szStepOver db "StepOver",0
szSingleStep db "SingleStep",0
szGetUnusedHardwareBreakPointRegister db "GetUnusedHardwareBreakPointRegister",0
szSetHardwareBreakPointEx db "SetHardwareBreakPointEx",0
szSetHardwareBreakPoint db "SetHardwareBreakPoint",0
szDeleteHardwareBreakPoint db "DeleteHardwareBreakPoint",0
szRemoveAllBreakPoints db "RemoveAllBreakPoints",0
szGetProcessInformation db "GetProcessInformation",0
szGetStartupInformation db "GetStartupInformation",0
szDebugLoop db "DebugLoop",0
szSetDebugLoopTimeOut db "SetDebugLoopTimeOut",0
szSetNextDbgContinueStatus db "SetNextDbgContinueStatus",0
szAttachDebugger db "AttachDebugger",0
szDetachDebugger db "DetachDebugger",0
szDetachDebuggerEx db "DetachDebuggerEx",0
szDebugLoopEx db "DebugLoopEx",0
szAutoDebugEx db "AutoDebugEx",0
szAutoDebugExW db "AutoDebugExW",0
szIsFileBeingDebugged db "IsFileBeingDebugged",0
szFindOEPInit db "FindOEPInit",0
szFindOEPGenerically db "FindOEPGenerically",0
szFindOEPGenericallyW db "FindOEPGenericallyW",0
szImporterCleanup db "ImporterCleanup",0
szImporterSetImageBase db "ImporterSetImageBase",0
szImporterSetUnknownDelta db "ImporterSetUnknownDelta",0
szImporterGetCurrentDelta db "ImporterGetCurrentDelta",0
szImporterInit db "ImporterInit",0
szImporterAddNewDll db "ImporterAddNewDll",0
szImporterAddNewAPI db "ImporterAddNewAPI",0
szImporterAddNewOrdinalAPI db "ImporterAddNewOrdinalAPI",0
szImporterGetAddedDllCount db "ImporterGetAddedDllCount",0
szImporterGetAddedAPICount db "ImporterGetAddedAPICount",0
szImporterGetLastAddedDLLName db "ImporterGetLastAddedDLLName",0
szImporterMoveIAT db "ImporterMoveIAT",0
szImporterExportIAT db "ImporterExportIAT",0
szImporterEstimatedSize db "ImporterEstimatedSize",0
szImporterExportIATEx db "ImporterExportIATEx",0
szImporterExportIATExW db "ImporterExportIATExW",0
szImporterFindAPIWriteLocation db "ImporterFindAPIWriteLocation",0
szImporterFindAPIByWriteLocation db "ImporterFindAPIByWriteLocation",0
szImporterFindDLLByWriteLocation db "ImporterFindDLLByWriteLocation",0
szImporterGetDLLName db "ImporterGetDLLName",0
szImporterGetAPIName db "ImporterGetAPIName",0
szImporterGetAPIOrdinalNumber db "ImporterGetAPIOrdinalNumber",0
szImporterGetAPINameEx db "ImporterGetAPINameEx",0
szImporterGetRemoteAPIAddress db "ImporterGetRemoteAPIAddress",0
szImporterGetRemoteAPIAddressEx db "ImporterGetRemoteAPIAddressEx",0
szImporterGetLocalAPIAddress db "ImporterGetLocalAPIAddress",0
szImporterGetDLLNameFromDebugee db "ImporterGetDLLNameFromDebugee",0
szImporterGetAPINameFromDebugee db "ImporterGetAPINameFromDebugee",0
szImporterGetAPIOrdinalNumberFromDebugee db "ImporterGetAPIOrdinalNumberFromDebugee",0
szImporterGetDLLIndexEx db "ImporterGetDLLIndexEx",0
szImporterGetDLLIndex db "ImporterGetDLLIndex",0
szImporterGetRemoteDLLBase db "ImporterGetRemoteDLLBase",0
szImporterRelocateWriteLocation db "ImporterRelocateWriteLocation",0
szImporterIsForewardedAPI db "ImporterIsForwardedAPI",0
szImporterGetForwardedAPIName db "ImporterGetForwardedAPIName",0
szImporterGetForwardedDLLName db "ImporterGetForwardedDLLName",0
szImporterGetForwardedDLLIndex db "ImporterGetForwardedDLLIndex",0
szImporterGetForwardedAPIOrdinalNumber db "ImporterGetForwardedAPIOrdinalNumber",0
szImporterGetNearestAPIAddress db "ImporterGetNearestAPIAddress",0
szImporterGetNearestAPIName db "ImporterGetNearestAPIName",0
szImporterCopyOriginalIAT db "ImporterCopyOriginalIAT",0
szImporterCopyOriginalIATW db "ImporterCopyOriginalIATW",0
szImporterLoadImportTable db "ImporterLoadImportTable",0
szImporterLoadImportTableW db "ImporterLoadImportTableW",0
szImporterMoveOriginalIAT db "ImporterMoveOriginalIAT",0
szImporterMoveOriginalIATW db "ImporterMoveOriginalIATW",0
szImporterAutoSearchIAT db "ImporterAutoSearchIAT",0
szImporterAutoSearchIATW db "ImporterAutoSearchIATW",0
szImporterAutoSearchIATEx db "ImporterAutoSearchIATEx",0
szImporterEnumAddedData db "ImporterEnumAddedData",0
szImporterAutoFixIATEx db "ImporterAutoFixIATEx",0
szImporterAutoFixIATExW db "ImporterAutoFixIATExW",0
szImporterAutoFixIAT db "ImporterAutoFixIAT",0
szImporterAutoFixIATW db "ImporterAutoFixIATW",0
szHooksSafeTransitionEx db "HooksSafeTransitionEx",0
szHooksSafeTransition db "HooksSafeTransition",0
szHooksIsAddressRedirected db "HooksIsAddressRedirected",0
szHooksGetTrampolineAddress db "HooksGetTrampolineAddress",0
szHooksGetHookEntryDetails db "HooksGetHookEntryDetails",0
szHooksInsertNewRedirection db "HooksInsertNewRedirection",0
szHooksInsertNewIATRedirectionEx db "HooksInsertNewIATRedirectionEx",0
szHooksInsertNewIATRedirection db "HooksInsertNewIATRedirection",0
szHooksRemoveRedirection db "HooksRemoveRedirection",0
szHooksRemoveRedirectionsForModule db "HooksRemoveRedirectionsForModule",0
szHooksRemoveIATRedirection db "HooksRemoveIATRedirection",0
szHooksDisableRedirection db "HooksDisableRedirection",0
szHooksDisableRedirectionsForModule db "HooksDisableRedirectionsForModule",0
szHooksDisableIATRedirection db "HooksDisableIATRedirection",0
szHooksEnableRedirection db "HooksEnableRedirection",0
szHooksEnableRedirectionsForModule db "HooksEnableRedirectionsForModule",0
szHooksEnableIATRedirection db "HooksEnableIATRedirection",0
szHooksScanModuleMemory db "HooksScanModuleMemory",0
szHooksScanEntireProcessMemory db "HooksScanEntireProcessMemory",0
szHooksScanEntireProcessMemoryEx db "HooksScanEntireProcessMemoryEx",0
szTracerInit db "TracerInit",0
szTracerLevel1 db "TracerLevel1",0
szHashTracerLevel1 db "HashTracerLevel1",0
szTracerDetectRedirection db "TracerDetectRedirection",0
szTracerFixKnownRedirection db "TracerFixKnownRedirection",0
szTracerFixRedirectionViaModule db "TracerFixRedirectionViaModule",0
szTracerDetectRedirectionViaModule db "TracerDetectRedirectionViaModule",0
szTracerFixRedirectionViaImpRecPlugin db "TracerFixRedirectionViaImpRecPlugin",0
szExporterCleanup db "ExporterCleanup",0
szExporterSetImageBase db "ExporterSetImageBase",0
szExporterInit db "ExporterInit",0
szExporterAddNewExport db "ExporterAddNewExport",0
szExporterAddNewOrdinalExport db "ExporterAddNewOrdinalExport",0
szExporterGetAddedExportCount db "ExporterGetAddedExportCount",0
szExporterEstimatedSize db "ExporterEstimatedSize",0
szExporterBuildExportTable db "ExporterBuildExportTable",0
szExporterBuildExportTableEx db "ExporterBuildExportTableEx",0
szExporterBuildExportTableExW db "ExporterBuildExportTableExW",0
szExporterLoadExportTable db "ExporterLoadExportTable",0
szExporterLoadExportTableW db "ExporterLoadExportTableW",0
szLibrarianSetBreakPoint db "LibrarianSetBreakPoint",0
szLibrarianRemoveBreakPoint db "LibrarianRemoveBreakPoint",0
szLibrarianGetLibraryInfo db "LibrarianGetLibraryInfo",0
szLibrarianGetLibraryInfoW db "LibrarianGetLibraryInfoW",0
szLibrarianGetLibraryInfoEx db "LibrarianGetLibraryInfoEx",0
szLibrarianGetLibraryInfoExW db "LibrarianGetLibraryInfoExW",0
szLibrarianEnumLibraryInfo db "LibrarianEnumLibraryInfo",0
szLibrarianEnumLibraryInfoW db "LibrarianEnumLibraryInfoW",0
szGetActiveProcessId db "GetActiveProcessId",0
szGetActiveProcessIdW db "GetActiveProcessIdW",0
szEnumProcessesWithLibrary db "EnumProcessesWithLibrary",0
szTLSBreakOnCallBack db "TLSBreakOnCallBack",0
szTLSGrabCallBackData db "TLSGrabCallBackData",0
szTLSGrabCallBackDataW db "TLSGrabCallBackDataW",0
szTLSBreakOnCallBackEx db "TLSBreakOnCallBackEx",0
szTLSBreakOnCallBackExW db "TLSBreakOnCallBackExW",0
szTLSRemoveCallback db "TLSRemoveCallback",0
szTLSRemoveCallbackW db "TLSRemoveCallbackW",0
szTLSRemoveTable db "TLSRemoveTable",0
szTLSRemoveTableW db "TLSRemoveTableW",0
szTLSBackupData db "TLSBackupData",0
szTLSBackupDataW db "TLSBackupDataW",0
szTLSRestoreData db "TLSRestoreData",0
szTLSBuildNewTable db "TLSBuildNewTable",0
szTLSBuildNewTableEx db "TLSBuildNewTableEx",0
szTLSBuildNewTableExW db "TLSBuildNewTableExW",0
szTranslateNativeName db "TranslateNativeName",0
szTranslateNativeNameW db "TranslateNativeNameW",0
szHandlerGetActiveHandleCount db "HandlerGetActiveHandleCount",0
szHandlerIsHandleOpen db "HandlerIsHandleOpen",0
szHandlerGetHandleName db "HandlerGetHandleName",0
szHandlerGetHandleNameW db "HandlerGetHandleNameW",0
szHandlerEnumerateOpenHandles db "HandlerEnumerateOpenHandles",0
szHandlerGetHandleDetails db "HandlerGetHandleDetails",0
szHandlerCloseRemoteHandle db "HandlerCloseRemoteHandle",0
szHandlerEnumerateLockHandles db "HandlerEnumerateLockHandles",0
szHandlerEnumerateLockHandlesW db "HandlerEnumerateLockHandlesW",0
szHandlerCloseAllLockHandles db "HandlerCloseAllLockHandles",0
szHandlerCloseAllLockHandlesW db "HandlerCloseAllLockHandlesW",0
szHandlerIsFileLocked db "HandlerIsFileLocked",0
szHandlerIsFileLockedW db "HandlerIsFileLockedW",0
szHandlerEnumerateOpenMutexes db "HandlerEnumerateOpenMutexes",0
szHandlerGetOpenMutexHandle db "HandlerGetOpenMutexHandle",0
szHandlerGetOpenMutexHandleW db "HandlerGetOpenMutexHandleW",0
szHandlerGetProcessIdWhichCreatedMutex db "HandlerGetProcessIdWhichCreatedMutex",0
szHandlerGetProcessIdWhichCreatedMutexW db "HandlerGetProcessIdWhichCreatedMutexW",0
szRemoteLoadLibrary db "RemoteLoadLibrary",0
szRemoteLoadLibraryW db "RemoteLoadLibraryW",0
szRemoteFreeLibrary db "RemoteFreeLibrary",0
szRemoteFreeLibraryW db "RemoteFreeLibraryW",0
szRemoteExitProcess db "RemoteExitProcess",0
szStaticFileLoad db "StaticFileLoad",0
szStaticFileLoadW db "StaticFileLoadW",0
szStaticFileUnload db "StaticFileUnload",0
szStaticFileUnloadW db "StaticFileUnloadW",0
szStaticMemoryDecrypt db "StaticMemoryDecrypt",0
szStaticMemoryDecryptEx db "StaticMemoryDecryptEx",0
szStaticMemoryDecryptSpecial db "StaticMemoryDecryptSpecial",0
szStaticSectionDecrypt db "StaticSectionDecrypt",0
szStaticMemoryDecompress db "StaticMemoryDecompress",0
szStaticRawMemoryCopy db "StaticRawMemoryCopy",0
szStaticRawMemoryCopyW db "StaticRawMemoryCopyW",0
szStaticHashMemory db "StaticHashMemory",0
szStaticHashFileW db "StaticHashFileW",0
szStaticHashFile db "StaticHashFile",0
szSetEngineVariable db "SetEngineVariable",0
szEngineCreateMissingDependencies db "EngineCreateMissingDependencies",0
szEngineCreateMissingDependenciesW db "EngineCreateMissingDependenciesW",0
szEngineFakeMissingDependencies db "EngineFakeMissingDependencies",0
szEngineDeleteCreatedDependencies db "EngineDeleteCreatedDependencies",0
szExtensionManagerIsPluginLoaded db "ExtensionManagerIsPluginLoaded",0
szExtensionManagerIsPluginEnabled db "ExtensionManagerIsPluginEnabled",0
szExtensionManagerDisableAllPlugins db "ExtensionManagerDisableAllPlugins",0
szExtensionManagerDisablePlugin db "ExtensionManagerDisablePlugin",0
szExtensionManagerEnableAllPlugins db "ExtensionManagerEnableAllPlugins",0
szExtensionManagerEnablePlugin db "ExtensionManagerEnablePlugin",0
szExtensionManagerUnloadAllPlugins db "ExtensionManagerUnloadAllPlugins",0
szExtensionManagerUnloadPlugin db "ExtensionManagerUnloadPlugin",0
szExtensionManagerGetPluginInfo db "ExtensionManagerGetPluginInfo",0

szGetContextFPUDataEx	db "GetContextFPUDataEx",0
szMatchPatternEx		db "MatchPatternEx",0
szMatchPattern			db "MatchPattern",0
szSetErrorModel			db "SetErrorModel",0			
szImporterFindOrdinalAPIWriteLocation	db "ImporterFindOrdinalAPIWriteLocation",0

szStaticFileOpen	db "StaticFileOpen",0
szStaticFileOpenW	db "StaticFileOpenW",0
szStaticFileGetContent	db "StaticFileGetContent",0
szStaticFileClose		db "StaticFileClose",0

szStaticRawMemoryCopyEx		db "StaticRawMemoryCopyEx",0
szStaticRawMemoryCopyExW	db "StaticRawMemoryCopyExW",0
szStaticRawMemoryCopyEx64	db "StaticRawMemoryCopyEx64",0
szStaticRawMemoryCopyEx64W	db "StaticRawMemoryCopyEx64W",0

szEngineUnpackerInitialize				db "EngineUnpackerInitialize",0 
szEngineUnpackerInitializeW				db	"EngineUnpackerInitializeW",0 
szEngineUnpackerSetBreakCondition		db "EngineUnpackerSetBreakCondition",0
szEngineUnpackerSetEntryPointAddress	db "EngineUnpackerSetEntryPointAddress",0 
szEngineUnpackerFinalizeUnpacking		db "EngineUnpackerFinalizeUnpacking",0  
szSetContextFPUDataEx					db "SetContextFPUDataEx",0
szEngineCreateUnpackerWindow			db "EngineCreateUnpackerWindow",0 
szEngineAddUnpackerWindowLogMessage		db	"EngineAddUnpackerWindowLogMessage",0

.code

function CargaTitanEngine
	begin_alloc
		alloc_var hTitanLibrary:QWORD
	end_alloc
	
	invoke LoadLibrary,addr szTitanDll
	mov hTitanLibrary,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpProcess
	mov DumpProcess,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpProcessW
	mov DumpProcessW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpProcessEx
	mov DumpProcessEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpProcessExW
	mov DumpProcessExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpMemory
	mov DumpMemory,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpMemoryW
	mov DumpMemoryW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpMemoryEx
	mov DumpMemoryEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpMemoryExW
	mov DumpMemoryExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpRegions
	mov DumpRegions,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpRegionsW
	mov DumpRegionsW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpRegionsEx
	mov DumpRegionsEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpRegionsExW
	mov DumpRegionsExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpModule
	mov DumpModule,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpModuleW
	mov DumpModuleW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpModuleEx
	mov DumpModuleEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDumpModuleExW
	mov DumpModuleExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szPastePEHeader
	mov PastePEHeader,rax
	invoke GetProcAddress, hTitanLibrary,addr szPastePEHeaderW
	mov PastePEHeaderW,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtractSection
	mov ExtractSection,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtractSectionW
	mov ExtractSectionW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResortFileSections
	mov ResortFileSections,rax
	invoke GetProcAddress, hTitanLibrary,addr szResortFileSectionsW
	mov ResortFileSectionsW,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindOverlay
	mov FindOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindOverlayW
	mov FindOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtractOverlay
	mov ExtractOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtractOverlayW
	mov ExtractOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddOverlay
	mov AddOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddOverlayW
	mov AddOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szCopyOverlay
	mov CopyOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szCopyOverlayW
	mov CopyOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoveOverlay
	mov RemoveOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoveOverlayW
	mov RemoveOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szMakeAllSectionsRWE
	mov MakeAllSectionsRWE,rax
	invoke GetProcAddress, hTitanLibrary,addr szMakeAllSectionsRWEW
	mov MakeAllSectionsRWEW,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddNewSectionEx
	mov AddNewSectionEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddNewSectionExW
	mov AddNewSectionExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddNewSection
	mov AddNewSection,rax
	invoke GetProcAddress, hTitanLibrary,addr szAddNewSectionW
	mov AddNewSectionW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResizeLastSection
	mov ResizeLastSection,rax
	invoke GetProcAddress, hTitanLibrary,addr szResizeLastSectionW
	mov ResizeLastSectionW,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetSharedOverlay
	mov SetSharedOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetSharedOverlayW
	mov SetSharedOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetSharedOverlay
	mov GetSharedOverlay,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetSharedOverlayW
	mov GetSharedOverlayW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteLastSection
	mov DeleteLastSection,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteLastSectionW
	mov DeleteLastSectionW,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteLastSectionEx
	mov DeleteLastSectionEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteLastSectionExW
	mov DeleteLastSectionExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32DataFromMappedFile
	mov GetPE32DataFromMappedFile,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32Data
	mov GetPE32Data,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32DataW
	mov GetPE32DataW,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32DataFromMappedFileEx
	mov GetPE32DataFromMappedFileEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32DataEx
	mov GetPE32DataEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32DataExW
	mov GetPE32DataExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetPE32DataForMappedFile
	mov SetPE32DataForMappedFile,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetPE32Data
	mov SetPE32Data,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetPE32DataW
	mov SetPE32DataW,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetPE32DataForMappedFileEx
	mov SetPE32DataForMappedFileEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetPE32DataEx
	mov SetPE32DataEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPE32SectionNumberFromVA
	mov GetPE32SectionNumberFromVA,rax
	invoke GetProcAddress, hTitanLibrary,addr szConvertVAtoFileOffset
	mov ConvertVAtoFileOffset,rax
	invoke GetProcAddress, hTitanLibrary,addr szConvertVAtoFileOffsetEx
	mov ConvertVAtoFileOffsetEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szConvertFileOffsetToVA
	mov ConvertFileOffsetToVA,rax
	invoke GetProcAddress, hTitanLibrary,addr szConvertFileOffsetToVAEx
	mov ConvertFileOffsetToVAEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szFixHeaderCheckSum
	mov FixHeaderCheckSum,rax
	invoke GetProcAddress, hTitanLibrary,addr szFixHeaderCheckSumW
	mov FixHeaderCheckSumW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRealignPE
	mov RealignPE,rax
	invoke GetProcAddress, hTitanLibrary,addr szRealignPEEx
	mov RealignPEEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szRealignPEExW
	mov RealignPEExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szWipeSection
	mov WipeSection,rax
	invoke GetProcAddress, hTitanLibrary,addr szWipeSectionW
	mov WipeSectionW,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsPE32FileValidEx
	mov IsPE32FileValidEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsPE32FileValidExW
	mov IsPE32FileValidExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szFixBrokenPE32FileEx
	mov FixBrokenPE32FileEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szFixBrokenPE32FileExW
	mov FixBrokenPE32FileExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsFileDLL
	mov IsFileDLL,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsFileDLLW
	mov IsFileDLLW,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetPEBLocation
	mov GetPEBLocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szHideDebugger
	mov HideDebugger,rax
	invoke GetProcAddress, hTitanLibrary,addr szUnHideDebugger
	mov UnHideDebugger,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterCleanup
	mov RelocaterCleanup,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterInit
	mov RelocaterInit,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterAddNewRelocation
	mov RelocaterAddNewRelocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterEstimatedSize
	mov RelocaterEstimatedSize,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterExportRelocation
	mov RelocaterExportRelocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterExportRelocationEx
	mov RelocaterExportRelocationEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterExportRelocationExW
	mov RelocaterExportRelocationExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterGrabRelocationTable
	mov RelocaterGrabRelocationTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterGrabRelocationTableEx
	mov RelocaterGrabRelocationTableEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterMakeSnapshot
	mov RelocaterMakeSnapshot,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterMakeSnapshotW
	mov RelocaterMakeSnapshotW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterCompareTwoSnapshots
	mov RelocaterCompareTwoSnapshots,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterCompareTwoSnapshotsW
	mov RelocaterCompareTwoSnapshotsW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterChangeFileBase
	mov RelocaterChangeFileBase,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterChangeFileBaseW
	mov RelocaterChangeFileBaseW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterRelocateMemoryBlock
	mov RelocaterRelocateMemoryBlock,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterWipeRelocationTable
	mov RelocaterWipeRelocationTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szRelocaterWipeRelocationTableW
	mov RelocaterWipeRelocationTableW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerLoadFileForResourceUse
	mov ResourcerLoadFileForResourceUse,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerLoadFileForResourceUseW
	mov ResourcerLoadFileForResourceUseW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerFreeLoadedFile
	mov ResourcerFreeLoadedFile,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerExtractResourceFromFileEx
	mov ResourcerExtractResourceFromFileEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerExtractResourceFromFile
	mov ResourcerExtractResourceFromFile,rax	
	invoke GetProcAddress, hTitanLibrary,addr szResourcerExtractResourceFromFileW
	mov ResourcerExtractResourceFromFileW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerFindResource
	mov ResourcerFindResource,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerFindResourceW
	mov ResourcerFindResourceW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerFindResourceEx
	mov ResourcerFindResourceEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerEnumerateResource
	mov ResourcerEnumerateResource,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerEnumerateResourceW
	mov ResourcerEnumerateResourceW,rax
	invoke GetProcAddress, hTitanLibrary,addr szResourcerEnumerateResourceEx
	mov ResourcerEnumerateResourceEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderImportRunningThreadData
	mov ThreaderImportRunningThreadData,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderGetThreadInfo
	mov ThreaderGetThreadInfo,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderEnumThreadInfo
	mov ThreaderEnumThreadInfo,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderPauseThread
	mov ThreaderPauseThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderResumeThread
	mov ThreaderResumeThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderTerminateThread
	mov ThreaderTerminateThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderPauseAllThreads
	mov ThreaderPauseAllThreads,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderResumeAllThreads
	mov ThreaderResumeAllThreads,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderPauseProcess
	mov ThreaderPauseProcess,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderResumeProcess
	mov ThreaderResumeProcess,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderCreateRemoteThread
	mov ThreaderCreateRemoteThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderInjectAndExecuteCode
	mov ThreaderInjectAndExecuteCode,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderCreateRemoteThreadEx
	mov ThreaderCreateRemoteThreadEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderInjectAndExecuteCodeEx
	mov ThreaderInjectAndExecuteCodeEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderSetCallBackForNextExitThreadEvent
	mov ThreaderSetCallBackForNextExitThreadEvent,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderIsThreadStillRunning
	mov ThreaderIsThreadStillRunning,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderIsThreadActive
	mov ThreaderIsThreadActive,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderIsAnyThreadActive
	mov ThreaderIsAnyThreadActive,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderExecuteOnlyInjectedThreads
	mov ThreaderExecuteOnlyInjectedThreads,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderGetOpenHandleForThread
	mov ThreaderGetOpenHandleForThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderGetThreadData
	mov ThreaderGetThreadData,rax
	invoke GetProcAddress, hTitanLibrary,addr szThreaderIsExceptionInMainThread
	mov ThreaderIsExceptionInMainThread,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticDisassembleEx
	mov StaticDisassembleEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticDisassemble
	mov StaticDisassemble,rax
	invoke GetProcAddress, hTitanLibrary,addr szDisassembleEx
	mov DisassembleEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDisassemble
	mov Disassemble,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticLengthDisassemble
	mov StaticLengthDisassemble,rax
	invoke GetProcAddress, hTitanLibrary,addr szLengthDisassembleEx
	mov LengthDisassembleEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szLengthDisassemble
	mov LengthDisassemble,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDebug
	mov InitDebug,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDebugW
	mov InitDebugW,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDebugEx
	mov InitDebugEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDebugExW
	mov InitDebugExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDLLDebug
	mov InitDLLDebug,rax
	invoke GetProcAddress, hTitanLibrary,addr szInitDLLDebugW
	mov InitDLLDebugW,rax
	invoke GetProcAddress, hTitanLibrary,addr szStopDebug
	mov StopDebug,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetBPXOptions
	mov SetBPXOptions,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsBPXEnabled
	mov IsBPXEnabled,rax
	invoke GetProcAddress, hTitanLibrary,addr szEnableBPX
	mov EnableBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szDisableBPX
	mov DisableBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetBPX
	mov SetBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetBPXEx
	mov SetBPXEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteBPX
	mov DeleteBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szSafeDeleteBPX
	mov SafeDeleteBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetAPIBreakPoint
	mov SetAPIBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteAPIBreakPoint
	mov DeleteAPIBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szSafeDeleteAPIBreakPoint
	mov SafeDeleteAPIBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetMemoryBPX
	mov SetMemoryBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetMemoryBPXEx
	mov SetMemoryBPXEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoveMemoryBPX
	mov RemoveMemoryBPX,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetContextDataEx
	mov GetContextDataEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetContextData
	mov GetContextData,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetContextDataEx
	mov SetContextDataEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetContextData
	mov SetContextData,rax
	invoke GetProcAddress, hTitanLibrary,addr szClearExceptionNumber
	mov ClearExceptionNumber,rax
	invoke GetProcAddress, hTitanLibrary,addr szCurrentExceptionNumber
	mov CurrentExceptionNumber,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindEx
	mov FindEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szFind
	mov Find,rax
	invoke GetProcAddress, hTitanLibrary,addr szFillEx
	mov FillEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szFill
	mov Fill,rax
	invoke GetProcAddress, hTitanLibrary,addr szPatchEx
	mov PatchEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szPatch
	mov Patch,rax
	invoke GetProcAddress, hTitanLibrary,addr szReplaceEx
	mov ReplaceEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szReplace
	mov Replace,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetDebugData
	mov GetDebugData,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetTerminationData
	mov GetTerminationData,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetExitCode
	mov GetExitCode,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetDebuggedDLLBaseAddress
	mov GetDebuggedDLLBaseAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetDebuggedFileBaseAddress
	mov GetDebuggedFileBaseAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetRemoteString
	mov GetRemoteString,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetFunctionParameter
	mov GetFunctionParameter,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetJumpDestinationEx
	mov GetJumpDestinationEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetJumpDestination
	mov GetJumpDestination,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsJumpGoingToExecuteEx
	mov IsJumpGoingToExecuteEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsJumpGoingToExecute
	mov IsJumpGoingToExecute,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetCustomHandler
	mov SetCustomHandler,rax
	invoke GetProcAddress, hTitanLibrary,addr szForceClose
	mov ForceClose,rax
	invoke GetProcAddress, hTitanLibrary,addr szStepInto
	mov StepInto,rax
	invoke GetProcAddress, hTitanLibrary,addr szStepOver
	mov StepOver,rax
	invoke GetProcAddress, hTitanLibrary,addr szSingleStep
	mov SingleStep,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetUnusedHardwareBreakPointRegister
	mov GetUnusedHardwareBreakPointRegister,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetHardwareBreakPointEx
	mov SetHardwareBreakPointEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetHardwareBreakPoint
	mov SetHardwareBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szDeleteHardwareBreakPoint
	mov DeleteHardwareBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoveAllBreakPoints
	mov RemoveAllBreakPoints,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetProcessInformation
	mov GetProcessInformation,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetStartupInformation
	mov GetStartupInformation,rax
	invoke GetProcAddress, hTitanLibrary,addr szDebugLoop
	mov DebugLoop,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetDebugLoopTimeOut
	mov SetDebugLoopTimeOut,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetNextDbgContinueStatus
	mov SetNextDbgContinueStatus,rax
	invoke GetProcAddress, hTitanLibrary,addr szAttachDebugger
	mov AttachDebugger,rax
	invoke GetProcAddress, hTitanLibrary,addr szDetachDebugger
	mov DetachDebugger,rax
	invoke GetProcAddress, hTitanLibrary,addr szDetachDebuggerEx
	mov DetachDebuggerEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szDebugLoopEx
	mov DebugLoopEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szAutoDebugEx
	mov AutoDebugEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szAutoDebugExW
	mov AutoDebugExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szIsFileBeingDebugged
	mov IsFileBeingDebugged,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindOEPInit
	mov FindOEPInit,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindOEPGenerically
	mov FindOEPGenerically,rax
	invoke GetProcAddress, hTitanLibrary,addr szFindOEPGenericallyW
	mov FindOEPGenericallyW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterCleanup
	mov ImporterCleanup,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterSetImageBase
	mov ImporterSetImageBase,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterSetUnknownDelta
	mov ImporterSetUnknownDelta,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetCurrentDelta
	mov ImporterGetCurrentDelta,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterInit
	mov ImporterInit,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAddNewDll
	mov ImporterAddNewDll,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAddNewAPI
	mov ImporterAddNewAPI,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAddNewOrdinalAPI
	mov ImporterAddNewOrdinalAPI,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAddedDllCount
	mov ImporterGetAddedDllCount,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAddedAPICount
	mov ImporterGetAddedAPICount,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetLastAddedDLLName
	mov ImporterGetLastAddedDLLName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterMoveIAT
	mov ImporterMoveIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterExportIAT
	mov ImporterExportIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterEstimatedSize
	mov ImporterEstimatedSize,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterExportIATEx
	mov ImporterExportIATEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterExportIATExW
	mov ImporterExportIATExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterFindAPIWriteLocation
	mov ImporterFindAPIWriteLocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterFindAPIByWriteLocation
	mov ImporterFindAPIByWriteLocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterFindDLLByWriteLocation
	mov ImporterFindDLLByWriteLocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetDLLName
	mov ImporterGetDLLName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAPIName
	mov ImporterGetAPIName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAPIOrdinalNumber
	mov ImporterGetAPIOrdinalNumber,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAPINameEx
	mov ImporterGetAPINameEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetRemoteAPIAddress
	mov ImporterGetRemoteAPIAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetRemoteAPIAddressEx
	mov ImporterGetRemoteAPIAddressEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetLocalAPIAddress
	mov ImporterGetLocalAPIAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetDLLNameFromDebugee
	mov ImporterGetDLLNameFromDebugee,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAPINameFromDebugee
	mov ImporterGetAPINameFromDebugee,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetAPIOrdinalNumberFromDebugee
	mov ImporterGetAPIOrdinalNumberFromDebugee,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetDLLIndexEx
	mov ImporterGetDLLIndexEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetDLLIndex
	mov ImporterGetDLLIndex,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetRemoteDLLBase
	mov ImporterGetRemoteDLLBase,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterRelocateWriteLocation
	mov ImporterRelocateWriteLocation,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterIsForewardedAPI
	mov ImporterIsForwardedAPI,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetForwardedAPIName
	mov ImporterGetForwardedAPIName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetForwardedDLLName
	mov ImporterGetForwardedDLLName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetForwardedDLLIndex
	mov ImporterGetForwardedDLLIndex,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetForwardedAPIOrdinalNumber
	mov ImporterGetForwardedAPIOrdinalNumber,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetNearestAPIAddress
	mov ImporterGetNearestAPIAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterGetNearestAPIName
	mov ImporterGetNearestAPIName,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterCopyOriginalIAT
	mov ImporterCopyOriginalIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterCopyOriginalIATW
	mov ImporterCopyOriginalIATW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterLoadImportTable
	mov ImporterLoadImportTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterLoadImportTableW
	mov ImporterLoadImportTableW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterMoveOriginalIAT
	mov ImporterMoveOriginalIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterMoveOriginalIATW
	mov ImporterMoveOriginalIATW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoSearchIAT
	mov ImporterAutoSearchIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoSearchIATW
	mov ImporterAutoSearchIATW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoSearchIATEx
	mov ImporterAutoSearchIATEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterEnumAddedData
	mov ImporterEnumAddedData,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoFixIATEx
	mov ImporterAutoFixIATEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoFixIATExW
	mov ImporterAutoFixIATExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoFixIAT
	mov ImporterAutoFixIAT,rax
	invoke GetProcAddress, hTitanLibrary,addr szImporterAutoFixIATW
	mov ImporterAutoFixIATW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksSafeTransitionEx
	mov HooksSafeTransitionEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksSafeTransition
	mov HooksSafeTransition,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksIsAddressRedirected
	mov HooksIsAddressRedirected,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksGetTrampolineAddress
	mov HooksGetTrampolineAddress,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksGetHookEntryDetails
	mov HooksGetHookEntryDetails,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksInsertNewRedirection
	mov HooksInsertNewRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksInsertNewIATRedirectionEx
	mov HooksInsertNewIATRedirectionEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksInsertNewIATRedirection
	mov HooksInsertNewIATRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksRemoveRedirection
	mov HooksRemoveRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksRemoveRedirectionsForModule
	mov HooksRemoveRedirectionsForModule,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksRemoveIATRedirection
	mov HooksRemoveIATRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksDisableRedirection
	mov HooksDisableRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksDisableRedirectionsForModule
	mov HooksDisableRedirectionsForModule,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksDisableIATRedirection
	mov HooksDisableIATRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksEnableRedirection
	mov HooksEnableRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksEnableRedirectionsForModule
	mov HooksEnableRedirectionsForModule,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksEnableIATRedirection
	mov HooksEnableIATRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksScanModuleMemory
	mov HooksScanModuleMemory,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksScanEntireProcessMemory
	mov HooksScanEntireProcessMemory,rax
	invoke GetProcAddress, hTitanLibrary,addr szHooksScanEntireProcessMemoryEx
	mov HooksScanEntireProcessMemoryEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szTracerInit
	mov TracerInit,rax
	invoke GetProcAddress, hTitanLibrary,addr szTracerLevel1
	mov TracerLevel1,rax
	invoke GetProcAddress, hTitanLibrary,addr szHashTracerLevel1
	mov HashTracerLevel1,rax
	invoke GetProcAddress, hTitanLibrary,addr szTracerDetectRedirection
	mov TracerDetectRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szTracerFixKnownRedirection
	mov TracerFixKnownRedirection,rax
	invoke GetProcAddress, hTitanLibrary,addr szTracerFixRedirectionViaImpRecPlugin
	mov TracerFixRedirectionViaImpRecPlugin,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterCleanup
	mov ExporterCleanup,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterSetImageBase
	mov ExporterSetImageBase,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterInit
	mov ExporterInit,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterAddNewExport
	mov ExporterAddNewExport,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterAddNewOrdinalExport
	mov ExporterAddNewOrdinalExport,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterGetAddedExportCount
	mov ExporterGetAddedExportCount,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterEstimatedSize
	mov ExporterEstimatedSize,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterBuildExportTable
	mov ExporterBuildExportTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterBuildExportTableEx
	mov ExporterBuildExportTableEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterBuildExportTableExW
	mov ExporterBuildExportTableExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterLoadExportTable
	mov ExporterLoadExportTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szExporterLoadExportTableW
	mov ExporterLoadExportTableW,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianSetBreakPoint
	mov LibrarianSetBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianRemoveBreakPoint
	mov LibrarianRemoveBreakPoint,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianGetLibraryInfo
	mov LibrarianGetLibraryInfo,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianGetLibraryInfoW
	mov LibrarianGetLibraryInfoW,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianGetLibraryInfoEx
	mov LibrarianGetLibraryInfoEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianGetLibraryInfoExW
	mov LibrarianGetLibraryInfoExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianEnumLibraryInfo
	mov LibrarianEnumLibraryInfo,rax
	invoke GetProcAddress, hTitanLibrary,addr szLibrarianEnumLibraryInfoW
	mov LibrarianEnumLibraryInfoW,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetActiveProcessId
	mov GetActiveProcessId,rax
	invoke GetProcAddress, hTitanLibrary,addr szGetActiveProcessIdW
	mov GetActiveProcessIdW,rax
	invoke GetProcAddress, hTitanLibrary,addr szEnumProcessesWithLibrary
	mov EnumProcessesWithLibrary,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBreakOnCallBack
	mov TLSBreakOnCallBack,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSGrabCallBackData
	mov TLSGrabCallBackData,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSGrabCallBackDataW
	mov TLSGrabCallBackDataW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBreakOnCallBackEx
	mov TLSBreakOnCallBackEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBreakOnCallBackExW
	mov TLSBreakOnCallBackExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSRemoveCallback
	mov TLSRemoveCallback,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSRemoveCallbackW
	mov TLSRemoveCallbackW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSRemoveTable
	mov TLSRemoveTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSRemoveTableW
	mov TLSRemoveTableW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBackupData
	mov TLSBackupData,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBackupDataW
	mov TLSBackupDataW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSRestoreData
	mov TLSRestoreData,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBuildNewTable
	mov TLSBuildNewTable,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBuildNewTableEx
	mov TLSBuildNewTableEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szTLSBuildNewTableExW
	mov TLSBuildNewTableExW,rax
	invoke GetProcAddress, hTitanLibrary,addr szTranslateNativeName
	mov TranslateNativeName,rax
	invoke GetProcAddress, hTitanLibrary,addr szTranslateNativeNameW
	mov TranslateNativeNameW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetActiveHandleCount
	mov HandlerGetActiveHandleCount,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerIsHandleOpen
	mov HandlerIsHandleOpen,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetHandleName
	mov HandlerGetHandleName,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetHandleNameW
	mov HandlerGetHandleNameW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerEnumerateOpenHandles
	mov HandlerEnumerateOpenHandles,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetHandleDetails
	mov HandlerGetHandleDetails,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerCloseRemoteHandle
	mov HandlerCloseRemoteHandle,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerEnumerateLockHandles
	mov HandlerEnumerateLockHandles,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerEnumerateLockHandlesW
	mov HandlerEnumerateLockHandlesW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerCloseAllLockHandles
	mov HandlerCloseAllLockHandles,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerCloseAllLockHandlesW
	mov HandlerCloseAllLockHandlesW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerIsFileLocked
	mov HandlerIsFileLocked,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerIsFileLockedW
	mov HandlerIsFileLockedW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerEnumerateOpenMutexes
	mov HandlerEnumerateOpenMutexes,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetOpenMutexHandle
	mov HandlerGetOpenMutexHandle,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetOpenMutexHandleW
	mov HandlerGetOpenMutexHandleW,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetProcessIdWhichCreatedMutex
	mov HandlerGetProcessIdWhichCreatedMutex,rax
	invoke GetProcAddress, hTitanLibrary,addr szHandlerGetProcessIdWhichCreatedMutexW
	mov HandlerGetProcessIdWhichCreatedMutexW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoteLoadLibrary
	mov RemoteLoadLibrary,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoteLoadLibraryW
	mov RemoteLoadLibraryW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoteFreeLibrary
	mov RemoteFreeLibrary,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoteFreeLibraryW
	mov RemoteFreeLibraryW,rax
	invoke GetProcAddress, hTitanLibrary,addr szRemoteExitProcess
	mov RemoteExitProcess,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticFileLoad
	mov StaticFileLoad,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticFileLoadW
	mov StaticFileLoadW,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticFileUnload
	mov StaticFileUnload,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticFileUnloadW
	mov StaticFileUnloadW,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticMemoryDecrypt
	mov StaticMemoryDecrypt,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticMemoryDecryptEx
	mov StaticMemoryDecryptEx,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticMemoryDecryptSpecial
	mov StaticMemoryDecryptSpecial,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticSectionDecrypt
	mov StaticSectionDecrypt,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticMemoryDecompress
	mov StaticMemoryDecompress,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopy
	mov StaticRawMemoryCopy,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopyW
	mov StaticRawMemoryCopyW,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticHashMemory
	mov StaticHashMemory,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticHashFileW
	mov StaticHashFileW,rax
	invoke GetProcAddress, hTitanLibrary,addr szStaticHashFile
	mov StaticHashFile,rax
	invoke GetProcAddress, hTitanLibrary,addr szSetEngineVariable
	mov SetEngineVariable,rax
	invoke GetProcAddress, hTitanLibrary,addr szEngineCreateMissingDependencies
	mov EngineCreateMissingDependencies,rax
	invoke GetProcAddress, hTitanLibrary,addr szEngineCreateMissingDependenciesW
	mov EngineCreateMissingDependenciesW,rax
	invoke GetProcAddress, hTitanLibrary,addr szEngineFakeMissingDependencies
	mov EngineFakeMissingDependencies,rax
	invoke GetProcAddress, hTitanLibrary,addr szEngineDeleteCreatedDependencies
	mov EngineDeleteCreatedDependencies,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerIsPluginLoaded
	mov ExtensionManagerIsPluginLoaded,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerIsPluginEnabled
	mov ExtensionManagerIsPluginEnabled,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerDisableAllPlugins
	mov ExtensionManagerDisableAllPlugins,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerDisablePlugin
	mov ExtensionManagerDisablePlugin,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerEnableAllPlugins
	mov ExtensionManagerEnableAllPlugins,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerEnablePlugin
	mov ExtensionManagerEnablePlugin,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerUnloadAllPlugins
	mov ExtensionManagerUnloadAllPlugins,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerUnloadPlugin
	mov ExtensionManagerUnloadPlugin,rax
	invoke GetProcAddress, hTitanLibrary,addr szExtensionManagerGetPluginInfo
	mov ExtensionManagerGetPluginInfo,rax

	invoke GetProcAddress, hTitanLibrary,addr szGetContextFPUDataEx
	mov GetContextFPUDataEx,rax

	invoke GetProcAddress, hTitanLibrary,addr szMatchPatternEx
	mov MatchPatternEx,rax
	
	invoke GetProcAddress, hTitanLibrary,addr szMatchPattern
	mov MatchPattern,rax

	invoke GetProcAddress, hTitanLibrary,addr szSetErrorModel
	mov SetErrorModel,rax

	invoke GetProcAddress, hTitanLibrary,addr szImporterFindOrdinalAPIWriteLocation
	mov ImporterFindOrdinalAPIWriteLocation,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticFileOpen
	mov StaticFileOpen,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticFileOpenW
	mov StaticFileOpenW,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticFileGetContent
	mov StaticFileGetContent,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticFileClose
	mov StaticFileClose,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopyEx
	mov StaticRawMemoryCopyEx,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopyExW
	mov StaticRawMemoryCopyExW,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopyEx64
	mov StaticRawMemoryCopyEx64,rax

	invoke GetProcAddress, hTitanLibrary,addr szStaticRawMemoryCopyEx64W
	mov StaticRawMemoryCopyEx64W,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineUnpackerInitialize
	mov EngineUnpackerInitialize,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineUnpackerInitializeW
	mov EngineUnpackerInitializeW,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineUnpackerSetBreakCondition
	mov EngineUnpackerSetBreakCondition,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineUnpackerSetEntryPointAddress
	mov EngineUnpackerSetEntryPointAddress,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineUnpackerFinalizeUnpacking
	mov EngineUnpackerFinalizeUnpacking,rax

	invoke GetProcAddress, hTitanLibrary,addr szSetContextFPUDataEx
	mov SetContextFPUDataEx,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineCreateUnpackerWindow
	mov EngineCreateUnpackerWindow,rax

	invoke GetProcAddress, hTitanLibrary,addr szEngineAddUnpackerWindowLogMessage
	mov EngineAddUnpackerWindowLogMessage,rax

	
exitf
