#ifndef GRIPPER_HPP
#define GRIPPER_HPP

#include <string>

namespace WzlPlanner
{

    enum GripperStateOpen
    {
        Opened,
        Closed,
        Opening,
        Closing
    };

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

    // mockup gripper for testing purpose
    class GripperMockup : public GripperBase
    {
        
        private: 
            // io indizes for communication with the pneumatic control unit
            int ioOpen_, ioClose_;
            GripperStateOpen gripperState_;

        public:
            GripperMockup(const std::string id) 
                : GripperBase(id)
            {
                gripperState_ = GripperStateOpen::Opened;
            } 

            bool IsOpen() const { return this->gripperState_ == GripperStateOpen::Opened; }
            bool IsClose() const { return this->gripperState_ == GripperStateOpen::Closed; }

            void Open() override { gripperState_ = GripperStateOpen::Opened; }
            void Close() override { gripperState_ = GripperStateOpen::Closed; }
    };

    // simple single jaw gripper with pneumatic actuator
    class GripperPneumaticSingle : public GripperBase
    {
        
        private: 
            // io indizes for communication with the pneumatic control unit
            int ioOpen_, ioClose_;
            GripperStateOpen gripperState_;

        public:
            GripperPneumaticSingle(const std::string id, const int ioOpen, const int ioClose) 
                : GripperBase(id)
            {
                this->ioOpen_ = ioOpen;
                this->ioClose_ = ioClose;
            } 

            bool IsOpen() const { return this->gripperState_ == GripperStateOpen::Opened; }
            bool IsClose() const { return this->gripperState_ == GripperStateOpen::Closed; }

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

            GripperStateOpen gripperState_;

        public:
            GripperPneumaticDouble(const std::string id, const int ioOpen1, const int ioClose1,
                const int ioOpen2, const int ioClose2) 
                    : GripperBase(id)
            {
                this->ioOpen1 = ioOpen1;
                this->ioClose1 = ioClose1;
                this->ioOpen2 = ioOpen2;
                this->ioClose2 = ioClose2;
            }

            bool IsOpen() const { return this->gripperState_ == GripperStateOpen::Opened; }
            bool IsClose() const { return this->gripperState_ == GripperStateOpen::Closed; }

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
            int ioRun_;

        public:
            GripperDeburringSpindle(const std::string id, const int ioRun) 
                : GripperBase(id)
            {
                this->ioRun_ = ioRun;
            }

            // start deburring spindle
            void Open() override;

            // stio deburring spindle
            void Close() override;
           
    };

} // namespace WzlPlanner

#endif // GRIPPER_HPP