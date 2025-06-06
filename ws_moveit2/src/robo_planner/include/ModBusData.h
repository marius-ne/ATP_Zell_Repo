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
        std::unordered_map<int, std::string> response_mapping_table;
        
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
        
            data->response_mapping_table = {
                {1, "Screwdriver busy"},
                {2, "Z-axis (or general initialization) busy"},
                {4, "Error: Z-axis safety activated"},
                {8, "Error: not calibrated"},
                {16, "initialize: Z stall current not reached"},
                {32, "initialize: No Z index mark found"},
                {48, "initialize: Unable to home Z axis"},
                {64, "initialize: Z index placement not ok"},
                {80, "initialize: No index mark found on torque encoders"},
                {96, "initialize: too big torque difference during initialization"},
                {112, "Index mark value has changed"},
                {256, "Error QC type"},
                {512, "Error power supply"}
            };

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

            data->response_mapping_table = {
                {0, "no additional result data"},
                {1, "Screwdriver: command unknown"},
                {2, "Screwdriver: not screwing in"},
                {3, "Screwdriver: timeout waiting for correct torque (2 sec)"},
                {4, "Screwdriver: torque exceeded unexpected (premature)"},
                {5, "Screwdriver: unable to loosen screw (max torque exceeded)"},
                {6, "Screwdriver: Z-axis reached the end"},
                {7, "Screwdriver: Z-axis obstructed during move"}
            };

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

        static std::shared_ptr<WzlPlanner::ModBusData> GetModBusData_ToolType_Read()
        {
            auto data = std::make_shared<WzlPlanner::ModBusData>();
            data->address = 1536;
            data->count = 1;

            data->response_mapping_table = {
                {16, "VG10"},
                {17, "VGC10"},
                {24, "VGP20"},
                {32, "RG2"},
                {33, "RG6"},
                {34, "RG2-FT"},
                {80, "SG"},
                {112, "3FG15"},
                {128, "Screwdriver"},
                {256, "Lift100 v1"},
                {257, "Lift100 v2"},
                {160, "MG10"},
                {176, "Sander"},
                {192, "2FG7"},
                {193, "2FG14"},
                {240, "2FGP20"}
            };

            return data;
        }
    };

} // namespace

#endif