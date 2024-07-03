class TaskBase:
    def __init__(self):
        self.subtasks = []

    def AddSubtask(self, subtask):
        self.subtasks.append(subtask)

    def Execute(self):
        self.LogStart()

        for subtask in self.subtasks:
            subtask.Execute()

        self.LogEnd()


    def LogStart(self):
        pass

    def LogEnd(self):
        pass

    _id : str
