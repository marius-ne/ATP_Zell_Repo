InstanceCounter = 0

def GetNextId() -> str:
    InstanceCounter += 1

    return str(InstanceCounter)