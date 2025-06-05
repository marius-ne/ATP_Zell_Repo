#ifndef MODBUSDATA_HPP
#define MODBUSDATA_HPP

#include <memory>
#include <string>

namespace WzlPlanner
{
    // singleton
    class ModBusData
    {
        public:
        int address = -1; // Adress of the register to read/write
        int count = -1; // how many registers to read
        
        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ShankPosition_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 0;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ZAxesForce_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ScrewLength_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 2;

            return data;
        }
        
        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_TargetTorque_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 3;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_Command_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 4;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_Extenderlength_Write()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 5;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_StatusErrors_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 256;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_CurrentTorque_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 257;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ShankZAxesPosition_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 258;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ZForce_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 259;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_TorqueAngleGradient_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 260;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_AchievedTorque_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 261;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_AdditionalResults_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 262;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_CurrentExtender_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 263;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_MaximumShankPosition_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 264;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_CorrectedShankWithExtender_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 265;
            data->count = 1;

            return data;
        }
        
        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_QuickChangerVersion_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 266;
            data->count = 1;

            return data;
        }

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_DeviceType_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 1536;
            data->count = 1;

            return data;
        }
    };

} // namespace

#endif