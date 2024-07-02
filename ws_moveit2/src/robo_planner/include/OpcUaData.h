#ifndef OPCUADATA_HPP
#define OPCUADATA_HPP

#include <memory>
#include <string>

namespace WzlPlanner
{
    // songleton
    class OpcUaData
    {
        public:
        std::string actuatorId = "";
        int actuatorWriteType = -1;
        int actuatorReadType = -1;
        bool actuatorCommandBool1 = false;
        bool actuatorCommandBool2 = false;

        
    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_AlarmWriteAus()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5016";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_AlarmWriteAn()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5016";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_LampeFarbeWriteAus()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5019";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = false;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_LampeFarbeWriteRot()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5019";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_LampeFarbeWriteOrange()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5019";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = false;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_LampeFarbeWriteGrün()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5019";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_TuerWriteStop()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5040";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = false;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_TuerWriteAuf()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5040";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_TuerWriteZu()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5040";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = false;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_TuerRead()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5040";
        data->actuatorReadType = 2;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_SpindelWriteAus()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5015";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_SpindelWriteAn()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5015";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_AnpressdruckSpindelWriteAn()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5006";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_AnpressdruckSpindelWriteAus()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5006";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_GreiferWriteAuf()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5004";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = false;
        data->actuatorCommandBool2 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_GreiferWritZu()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5004";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_GreiferWritNeutral()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5004";
        data->actuatorWriteType = 2;
        data->actuatorCommandBool1 = true;
        data->actuatorCommandBool2 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi1WriteAuf()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5008";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi1WriteZu()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5008";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi2WriteAuf()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5007";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi2WriteZu()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5007";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi3WriteAuf()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5003";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = false;

        return data;
    }

    static std::shared_ptr<WzlPlanner::OpcUaData> GetOpcUaData_Bemi3WriteZu()
    {
        auto data = std::make_shared<WzlPlanner::OpcUaData>();
        data->actuatorId = "ns=4;i=5003";
        data->actuatorWriteType = 1;
        data->actuatorCommandBool1 = true;

        return data;
    }

    };

} // namepspace

#endif