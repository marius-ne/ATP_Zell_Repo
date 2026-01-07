# ReStackCell:

## Opc Ua Client

Ros-Node, der den Opcua-Client implementiert.

Dieser bietet eine Service-Schnittstelle, um um mit anderen Ros-Nodes zu kommunizieren und sendet eingegangene Anfragen an den Opcua-Server auf der SPS weiter.

Wie wie einzelnen Kanäle der Pneumatik angesprochen werden müssen, ist im Repository dokumentiert.

Relevanten Packages: opcua_client, opcua_interfaces

## Mod Bus Client & Screwdriver Interface

Ros-Node, der den Modbus-Client implementiert.

Die ModBus Client bietet eine ROS2 Schnittstelle um mit einem ModBus Server zu kommunizieren.

Das Screwdriver Interface bietet eine High-Level Schnittstelle zur Steuerung des OnRobot Screwdrivers an die mit dem ModBus Client kommuniziert.

Relevante Packages: modbus_client, modbus_interfaces, modbus_screwdriver_interfaces

## LeRobot Data Collection

Eine Ros-Node die es erlaubt Daten in dem LeRobot Dataset Format, mit hilfe einer simplen GUI, aufzunehmen. 

Ist für Imitation Learning relevant.

Relevante Packages: lerobot_data_collection

## RestackCell:

Für den Ablauf zu verwendende Gesamtprojekt, setzt sich zusammen aus:

- Robo Scheduler C++ (robo_planner package)
- MoveIt Backend
- Opcua Client
- ModBus Client
- Ros Message Interfaces (robo_planner_msgs, wzl_scheduler_interfaces)

### Ros-Knoten:

#### Ros Scheduler C++:

Der Scheduler, oder auch Robo-Planner in C++.

Durch die Launch-Datei im Launch-Folder iiwa_planner_launch.py wird der Scheduler (Ros-Knoten im genannten Projekt), sowie andere Knoten in der Projektmappe gestartet:

- Robo-Planner/Scheduler
- OPC-UA Client
- OPC-UA Client IO link
- MODBUS Client
- MoveitBackend
- Robot State Publisher

Hier eine kurze Erläuterung der Konzepte und wichtigsten Dateien des Projektes.

### Moveit Backend:

Wrapper der Moveit-Library. Bietet Ros-Services an, über die die Szene initialisiert und Roboterbewegungen durchgeführt werden können.

Für PointToPoint-Bewegungen wird der ompl-Planer verwendet, welcher nichtdeterministisch eine Trajektorie um Hindernisse berechnet.

Für gradlinige, kartesische Bewegungen wird der Pilz-Industrial-Planner verwendet.

### Config:

Die iiwa_description sowie moveit_config Ordner sind in dem iiwa Ros2 treiber Ordner unter `/home/remanpilot/iiwa_ws/src/iiwa_ros2`

Es wurde lediglich die richtige Flansch in das URDF Model hinzugefügt.

## Installation der notwendigen Ressourcen:

### ROS 2 Humble unter Ubuntu 22.04:

https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html


### Roboter-Treiber für den Kuka iiwa:

https://github.com/ICube-Robotics/iiwa_ros2


### MoveIt:

https://moveit.picknik.ai/humble/doc/tutorials/getting_started/getting_started.html

Sollte MoveIt bei der installation nicht gebaut werden können, kann dieser build-Befehl verwendet werden

```
colcon build parallel-workers 1
```

### OPC UA:

Installation über

```
pip install opcua
```

### ModBus

Es wird die pymodbus Python library benutzt.

Installation über

```
pip install -U pymodbus
```

### Real Sense Treiber

Für die lerobot_data_collection_node wird die realsense Kamera benutzt. Der Treiber der dafür benutzt wird ist pyrealsense2.

Installation über

```
pip install pyrealsense2
```

## Roboter mit Use Case starten

Um den Roboter mit dem Usecase zu starten sollten folgende Schritte ausgeführt werden:

1. Zelle und Roboter starten
2. iiwa_ROS2 Applikation auf dem Roboter starten
3. IIWA Robot Driver auf dem PC starten
5. Robo Planner/Scheduler starten

Wie die einzelnen Schritte ausgeführt werden, wird in den folgenden Abschnitten detailiert

Um das Projekt zu bauen muss folgendes im verzeichnis `/ws/restackcell/ws_moveit2` ausgeführt werden

```
colcon build
```

### Zelle und Roboter starten

- Hauptschalter am Schrank auf ein drehen
- Druckluft Hahn (blau) an der Wand aufdrehen
- Druckluftventil unten in der Zelle aufdrehen und sicherstellen, dass Druck vorhanden ist
- Sicherstellen dass alle Teile der Zelle am richtigen Ort stehen und, dass die Tools in der Werkzeugwechselstation sind

### iiwa_ROS2 Applikation starten
Um die iiwa_ROS2 Applikation auf dem Roboter zu starten, erst in der Leiste oben auf Applications drücken, dann iiwa_ros2 auswählen und links auf den grünen Pfeil/Start-Knopf drücken und letztens den FRI control mode 'POSITION' auswählen.

### IIWA Robot Driver auf dem PC starten

Der Roboter-Treiber übersetzt die ankommenden ROS-Befehle für den Roboter und zurück, und kommuniziert mit diesem.

Der Befehl mit der IP für den realen Roboter (IP = 192.168.30.30)

```
ros2 launch iiwa_bringup iiwa.launch.py use_fake_hardware:="false" use_planning:=true base_frame_file:=base_frame_custom.yaml robot_ip:="192.168.30.30"```

Der Befehl mit der IP für den simulierten Roboter (IP = 192.168.56.101)

```
ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur16e robot_ip:=192.168.56.101 description_package:=ur_description launch_rviz:=false
```

Für einen Netzwerktest, ob der pyhsikalische Roboter richtig verbunden ist oder die Simulation läuft, kann der Parameter launch_rviz = true gesetzt werden. Der Roboter sollte in Rviz mit den richtigen Gelenkwinkeln und Kollisions-Erweiterungen aus der URDF-Datei dargestellt werden (derzeit mit einem Quader als Tool-Substituierung, sowie einen Quader für die Kabelhalterung in der Nähe des TCP).

Wenn der Roboter in der Rviz-darstellung aussieht, als würde er auf dem Boden liegen, besteht keine Verbindung. In dem Fall sollte zunächst über einen „ping"- Befehl an die IP-Adresse des Roboters die Verbindung überprüft werden.

Noch einmal die IP-Adresse des Roboters:
Real: 192.168.20.20
Simulation (default): 192.168.56.101

Zu beachten ist, dass der IIWA Robot Driver auf dem PC zeitnah nach dem Starten der Applikation gestartet wird, sonst wird keine Verbindung aufgebaut!

Wenn alles richtig gelaufen ist, sollte im Terminal wo der UR Robot Driver gestartet wurde, folgende Nachricht sichtbar sein:

```

``` 

### Moveit starten

Um Moveit! mit OMPL und PILZ Plannern zu starten, muss folgende Launch-Datei gestartet werden:

<!-- ```
ros2 launch robo_planner ur_planner_pilz.launch.py ur_type:=ur16e use_fake_hardware:=false launch_rviz:=true description_package:=ur_description ur_type:=ur16e description_file:=ur.urdf.xacro
``` -->

```
ros2 launch robo_planner ur_planner_pilz.launch.py
``` 

Dabei ist zu beachten, dass der workspace im Projekt „Restackcell" gesourced ist, das kann man wie folgend aus dem home Directory machen.

```
source ws/restackcell/ws_moveit2/install/setup.bash
``` 

Die Robo_Planner launch-Datei lädt alle notwendigen Config-Dateien des UR-Roboters aus den Paketen des Shared-Folders unter
`opt/ros/humble/share/` und `/ws/restackcell/ws_moveit2/src/robo_planner/config/`

### Robo Planner/Scheduler starten

Das Programm kann entweder in einer simulierten UR-Umgebung oder am echten Roboter gestartet werden. Der simulierte Roboter ist über die gleiche Ethernet-Schnittstelle wie der reale Roboter ansprechbar, weswegen sich nicht viel in der Kommunikation ändert. Beim Aufruf muss lediglich die Roboter-IP umgestellt werden.

Das Ablaufprogramm des Schedulers/Planners wird über diese Launch-Datei gestartet:

```
ros2 launch robo_planner ur_planner_launch.py
```

Falls der Ablauf der in Main.cpp ist, nicht zufriedenstellend ist, gibt es ein Beispielablauf in der text Datei UseCase_Ablauf.txt im `robo_planer/src` Ordner. Dieser Ablauf kann einfach in Main.cpp kopiert werden um einen standard UseCase Ablauf zu haben.

Dabei ist zu beachten, dass der workspace im Projekt „Restackcell" gesourced ist, das kann man wie folgend aus dem home Directory machen.

```
source ws/restackcell/ws_moveit2/install/setup.bash

``` 
## IIWA mit UseCase Starten

WICHTIG, ICH HABE DEN IIWA DRIVER AN EINIGEN STELLEN MODIFIZIERT


## Lerobot Data Collection Starten

WÄRE AUCH SCHLAU IRGENDWIE DIE SPACEMOUSE HIER ZU ERWÄNEN, VIELLEICHT SPACEMOUSE NODE AUCH IN RESTACKCELL ORDNER MACHEN. SPACENAV DRIVER KANN MAN SO RUNTERLADEN, ICH HABE ABER DEN SKRIPT LEICHT MODIFIZIERT.


## Wichtige Fallstricke:

### Koordinatensystem-Unterschiede:

- In MoveIt und ROS sind die X- und Y-Koordinaten des `tool0`-Links (TCP) im Vergleich zum Roboterkoordinatensystem invertiert.
- Bei der Übertragung ins Roboterprogramm muss in der Z-Rotation ein Wert von `-Pi` (Minus Pi) addiert werden.
- Um die Orientation vom Teachpanel auszulesen, einmal auf 'Tool Position' tippen und auf 'RPY[rad]' stellen

### Arbeitsraum-Einschränkungen:

- Die MoveIt-Methode „SetWorkspace" ist für mobile Roboter konzipiert und nicht für stationäre Roboter geeignet.
- Um Kollisionen mit Zellenwänden zu verhindern, müssen diese als separate Kollisionsobjekte modelliert werden.

### Mögliche Ursachen für fehlgeschlagene MoveIt-Planungen:

1. Aktuelle Gelenkpositionen außerhalb der zulässigen Grenzen
2. Zielgelenkpositionen außerhalb der zulässigen Grenzen
3. Bestehende Kollision des Roboters mit sich selbst oder der Umgebung
4. Kollision in der geplanten Zielpose
5. Nicht gestarteter oder nicht funktionierender Robotercontroller
6. Nicht laufendes RemoteCap-Programm auf dem Universal Robot

### Geschwindigkeitskontrolle bei Trajektorien:

- Der Befehl `computeCartesianPath` führt Bewegungen entlang einer Trajektorie immer mit maximaler Geschwindigkeit aus.
- Für eine präzisere Geschwindigkeitskontrolle wird der **Pilz Industrial Planner** empfohlen.

### Jetson-Board Anmeldedaten

- Username: _Autopilot_
- Kennwort: _123456_

### Roadmap ReStackCell

- 6D-Posen Erkennung über YOLO der Getriebehälften (gtr)
- 6D-Posen Erkennung über YOLO für BEMIs (gtr)
- Einbindung WZL-Rechner für KI-Anwendungen (gtr)
- Implementierung Vision Überwachung Anlagen Konfiguration (gtr, wml)
- Aufzeichnen Hardware Architektur Schaltschrank (bln)
- Aufzeichnen Software Architektur (wml)
- Proof of Concept: Dockersieren der ROS2 Packages der ReStackCell (wml)
- Weitere Umsetzung Use-Case1 (wml)
- Buchsen für das Restacking einsetzen (wml)

### Roadmap Hannover Messe
- [ ] Plexiglas, Abdeckplatten bestellen (wml)
- [ ] Schloss versetzen zum Schließen der Türen
- [ ] Beschriftung der Werkzeuge (gtr)
- [ ] bln Werkstückträger demontieren
- [ ] Kabelkanäle oberhalb der Platte legen; Kabelbinder nutzen
- [ ] Bildschirmhalter beschaffen
- [ ] Start der Zelle vereinfachen
- [ ] Zelle abschließend säubern
- [ ] Schrauben checken und festziehen
- [ ] Transport abklären
- [ ] Zugangsdaten abklären, können wir die Zelle mit einem Laptop remote starten?
- [ ] Netzwerkarchitektur von bln skizzieren lassen

#### Use Case 1 Implementierung
- [ ] Greiffinger 2-Finger-Greifer fertigen, montieren (wml)
- [ ] Verfeinern der Position der Lageraufnahme und -platzierung
- [ ] Alle Lagerpositionen implementieren
- [ ] Getriebebox nach dem Einsetzen der Lager **horizontal** verfahren
- [ ] Kollisionsmodell anpassen; Sensorturm demontiert

#### Pose Estimation (gtr)
- [ ] Kamera oberhalb der Zelle montieren
- [ ] Kamera kalibrieren
- [ ] Testbilder aufzeichnen
- [ ] synthetische Daten generieren (Key-Points definieren und Bilder aufzeichnen)
- [ ] (optional) Textur der CAD-Modelle anpassen
- [ ] YOLO-Pose Estimation Netz antrainieren
- [ ] Pose Estimation testen
- [ ] Realtime-Integration in ROS
- [ ] UI-Anzeige mit Pose Estimation Bildern

### Roadmap Reman-Cell