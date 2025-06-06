#ifndef TASKINCLUDE_HPP
#define TASKINCLUDE_HPP

// Header file to imclude all available task headfiles at once

#include "TaskList.h"

// include atomic tasks
#include "Atomic/TaskGetObjectInScene.h"
#include "Atomic/TaskGripperClose.h"
#include "Atomic/TaskGripperOpen.h"
#include "Atomic/TaskMoveToPose.h"
#include "Atomic/TaskOpenDoor.h"
#include "Atomic/TaskSetRobotValueVelocity.h"
#include "Atomic/TaskOpcuaRequest.h"
#include "Atomic/TaskModBusRequest.h"
#include "Atomic/TaskFollowTrajectory.h"
#include "Atomic/TaskWait.h"
#include "Atomic/TaskPartAttach.h"
#include "Atomic/TaskPartDetach.h"
#include "Atomic/TaskModBusRequest.h"
#include "Atomic/TaskModBusInterpretReadResult.h"

// include composed tasks
#include "Composed/TaskGripperChange.h"
#include "Composed/TaskGripperChangePick.h"
#include "Composed/TaskGripperChangePlace.h"
#include "Composed/TaskPick.h"
#include "Composed/TaskPickAndPlace.h"
#include "Composed/TaskPlace.h"
#include "Composed/TaskScanScene.h"

#endif