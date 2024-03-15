#ifndef GRIPPER_HPP
#define GRIPPER_HPP

namespace WzlPlanner
{
    // base class for gripper
    class GripperBase
    {
        protected:
            bool isOpened = false;
            bool isClosed = false;

        public:
            virtual void Open() = 0;
            virtual void Close() = 0;

            GripperBase() 
            {
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
            void Open() override;
            void Close() override;


    };

} // namespace WzlPlanner

#endif // GRIPPER_HPP