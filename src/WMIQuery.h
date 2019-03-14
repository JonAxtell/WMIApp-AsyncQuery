#pragma once

//#################################################################################################################################
//
template<typename COBJECT>
bool WMIQuery(::IWbemServices *pSvc, std::vector<COBJECT *>& obj, std::string className)
{
    try
    {
        TWBEMObjectQuery<TWBEMObjectSink<COBJECT> >* query = new TWBEMObjectQuery<TWBEMObjectSink<COBJECT> >(pSvc, className.c_str());
        std::wcout << L"Querying " << query->WMIClassName().c_str() << std::endl;
        query->Query();
        while (!query->IsDone())
        {
            ::Sleep(100);
        }
        if (!query->HasIndicated())
        {
            std::wcout << L"WMIQuery Object " << query->WMIClassName().c_str() << L" not populated." << std::endl;
            delete query;
            return false;
        }

        std::wcout << L"Object " << query->WMIClassName().c_str() << L" populated with " << query->Sink()->Count() << L" items" << std::endl;

        // Transfer the objects out of the sink before the sink loses focus
        obj = *reinterpret_cast<std::vector<COBJECT *> *>(&query->Sink()->Objects());
        delete query;
        return true;
    }
    catch (HRESULT hres)
    {
        throw std::runtime_error(std::string("WMIQuery Query for ") + className + std::string(" details failed. Error code = 0x") + NumberToHex(hres));
    }
    catch (std::runtime_error err)
    {
        throw err;
    }
    return false;
}
