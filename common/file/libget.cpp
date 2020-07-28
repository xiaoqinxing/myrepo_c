OSLIBRARYHANDLE OsUtils::LibMap(
    const CHAR* pLibraryName)
{
    OSLIBRARYHANDLE hLibrary = NULL;
    const UINT bind_flags = RTLD_NOW | RTLD_LOCAL;

    CAMX_ASSERT(NULL != pLibraryName);

    hLibrary = dlopen(pLibraryName, bind_flags);

    if (NULL == hLibrary)
    {
        const CHAR* pErrorMessage = dlerror();

        CAMX_LOG_ERROR(CamxLogGroupUtils,
                       "dlopen: %s, on '%s'",
                       pErrorMessage ? pErrorMessage : "N/A",
                       pLibraryName);
        CAMX_ASSERT_ALWAYS();
    }

    return hLibrary;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// OsUtils::LibUnmap
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult OsUtils::LibUnmap(
    OSLIBRARYHANDLE hLibrary)
{
    CamxResult result = CamxResultSuccess;

    CAMX_ASSERT(NULL != hLibrary);

    if (NULL != hLibrary)
    {
        if (0 != dlclose(hLibrary))
        {
            const CHAR* pErrorMessage = dlerror();

            CAMX_LOG_ERROR(CamxLogGroupUtils, "dlclose error: %s", pErrorMessage ? pErrorMessage
                                                                            : "N/A");
            result = CamxResultEFailed;
            CAMX_ASSERT_ALWAYS();
        }
    }
    else
    {
        result = CamxResultEInvalidArg;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// OsUtils::LibGetAddr
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VOID* OsUtils::LibGetAddr(
    OSLIBRARYHANDLE hLibrary,
    const CHAR*     pProcName)
{
    VOID* pProcAddr = NULL;

    if (hLibrary != NULL)
    {
        pProcAddr = dlsym(hLibrary, pProcName);
    }
    return pProcAddr;
}