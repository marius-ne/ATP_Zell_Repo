
import json
from xml.dom.minidom import parseString

def SerializeClass(instance, path):
    with open(path, mode="w", encoding="utf-8") as write_file:
        json.dump(instance, write_file, indent=4)


def DeserializeClass(path):
    with open(path, 'r', encoding="utf-8") as read_file:
        data = json.load(read_file)

    return data


def SerializeXml(instance, path):
    #person = vars(instance()) # vars is pythonic way of converting to dictionary
    xml = dicttoxml(instance, attr_type=False) # set root node to Person
    print(xml)

    dom = parseString(xml)
    print(dom.toprettyxml())

