#ifndef TASKMODBUSINTERPRETREADRESULT_HPP
#define TASKMODBUSINTERPRETREADRESULT_HPP

#include <memory>

#include "../Task.h"
#include "TaskModBusRequest.h"

namespace WzlPlanner
{
    class TaskModBusInterpretReadResult : public Task
    {
    private:
        std::shared_ptr<TaskModBusRead> modbus_read_task_;
        int value_;
        std::shared_ptr<ModBusData> data_;
        std::optional<int> comparison_value_int_;
        std::optional<std::string> comparison_value_string_;
        std::unordered_map<int, std::string> translation_table;


    public:
        TaskModBusInterpretReadResult(const std::shared_ptr<TaskModBusRead>& read_task)
            : modbus_read_task_(read_task), value_(0)
        {
        }

        /**
         * @brief Sets an integer comparison value, resetting any string comparison.
         * @param value The integer value to compare the read result against.
         */
        void SetComparisonValue(int value)
        {
            comparison_value_int_ = value;
            comparison_value_string_.reset();
        }

        /**
         * @brief Sets a string comparison value, resetting any integer comparison.
         * @param value The string value to compare the read result against.
         */
        void SetComparisonValue(const std::string& value)
        {
            comparison_value_string_ = value;
            comparison_value_int_.reset();
        }

        bool Execute() override
        {
            LogStart();
            value_ = modbus_read_task_->GetResult();
            data_ = modbus_read_task_->GetData();

            // If the read value should be compared to an integer
            if (data_->compare_response_int) 
            {
                // If a comparison integer was given
                if (comparison_value_int_.has_value()) 
                {
                    // If the given value is NOT within a range of ±2 to the read value -> Fail
                    if (std::abs(value_ - comparison_value_int_.value()) > 2) 
                    {
                        Log("ModBus read result from" + data_->name + "does not match expected integer value: " + std::to_string(value_));
                        LogEnd();
                        return false;
                    } 
                    else
                    {
                        Log("ModBus read result from " + data_->name + " matches expected integer value: " + std::to_string(value_));
                        
                    }
                } else // If no comparison integer was given
                {
                    Log("No integer comparison value set for ModBus read result from " + data_->name);
                    LogEnd();
                    return false;
                }


            } else if (data_->translate_response) // If the read value should be translated to a string
            {
                translation_table = data_->response_mapping_table;
                // If the read value is in the translation table
                if (translation_table.find(value_) != translation_table.end())
                {
                    std::string translated_value = translation_table[value_];
                    Log("ModBus read result from " + data_->name + " translates to: " + translated_value);
                }
                else // If the read value is NOT in the translation table
                {
                    Log("ModBus read result from " + data_->name + " does not have a translation in the table for value: " + std::to_string(value_));
                    LogEnd();
                    return false;
                }

                // If the translated value should be compared to a string
                if (data_->compare_response_string)
                {
                    // If a comparison string was given
                    if (comparison_value_string_.has_value())
                    {
                        // If the translated value does NOT match the comparison string -> Fail
                        if (translation_table[value_] != comparison_value_string_.value())
                        {
                            Log("ModBus read result from " + data_->name + " does not match expected string value: " + translation_table[value_]);
                            LogEnd();
                            return false;
                        }
                        else 
                        {
                            Log("ModBus read result from " + data_->name + " matches expected string value: " + translation_table[value_]);
                        }
                    } else // If no comparison string was given
                    {
                        Log("No string comparison value set for ModBus read result from " + data_->name);
                        LogEnd();
                        return false;
                    }
                }
            }

            LogEnd();
            return true; // If no fail condition was met, then success
        }
    };
}

#endif