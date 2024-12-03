
import json


def SerializeClass(instance, path):
    with open(path, mode="w", encoding="utf-8") as write_file:
        json.dump(instance, write_file, indent=4)


def DeserializeClass(path):
    with open(path, 'r', encoding="utf-8") as read_file:
        data = json.load(read_file)

    return data
