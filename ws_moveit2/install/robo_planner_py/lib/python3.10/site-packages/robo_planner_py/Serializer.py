
import json
from xml.dom.minidom import parseString

def SerializeClass(instance, path):
    #with open(path, 'w') as f:
    #    json.dumps(instance, default=lambda o: o.__dict__, indent=4)

    f = open(path, "w")
    f.write("Woops! \n\tI have deleted the content!")
    f.close()

#def SerializeXml(instance, path):
#    person = vars(instance()) # vars is pythonic way of converting to dictionary
#    xml = dicttoxml(person, attr_type=False, custom_root='Person') # set root node to Person
#    print(xml)

#    dom = parseString(xml)
#    print(dom.toprettyxml())

def DeserializeClass(path):
    with open(path, 'r') as f:
        data = json.load(f)

    return data