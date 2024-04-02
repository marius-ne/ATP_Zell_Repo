#ifndef GRIPPER_HPP
#define GRIPPER_HPP

#include <string>

namespace WzlPlanner
{
    // base class for gripper
    class GripperBase
    {
        private:
            std::string id_;

        protected:
            bool isOpened = false;
            bool isClosed = false;

        public:
            virtual void Open() = 0;
            virtual void Close() = 0;

            std::string GetId() const { return id_; }

            GripperBase(const std::string id) 
            {
                id_ = id;

                isOpened = true;
            }

        private:
            
    };

    // simple single jaw gripper with pneumatic actuator
    class GripperPneumaticSingle : public GripperBase
    {
        
        private: 
            // io indizes for communication with the pneumatic control unit
            int ioOpen, ioClose;

        public:
            GripperPneumaticSingle(const std::string id) : GripperBase(id)
            {} 

            void Open() override;
            void Close() override;
    };

    // gripper with 2 jaws which are controlled simultaneouly by pneumatic actuator
    class GripperPneumaticDouble : public GripperBase
    {
        private:
            // io indizes for communication with the pneumatic control unit for gripper 1
            int ioOpen1, ioClose1;

            // io indizes for communication with the pneumatic control unit for gripper 2
            int ioOpen2, ioClose2;

        public:
            GripperPneumaticDouble(const std::string id) : GripperBase(id)
            {}

            void Open() override;
            void Close() override;


    };

    class GripperCameraToF : public GripperBase
    {
        private:

        public:
            GripperCameraToF(const std::string id) : GripperBase(id)
            {}

            void Open() override {}
            void Close() override {}
            void Scan();
    };

    class GripperDeburringSpindle : public GripperBase
    {
        private:

        public:
            GripperDeburringSpindle(const std::string id) : GripperBase(id)
            {}

            void Open() override {}
            void Close() override {}
            void Activate();
    };

} // namespace WzlPlanner

#endif // GRIPPER_HPP