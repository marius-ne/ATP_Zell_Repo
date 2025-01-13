# ReStackCell:

## PointNet

Vision-Modul für die Detektion der Betriebsmittel mittels einer 2D-Topdown-Kamera. Es wurde eine Realsense-Kamera über die Zelle montiert, die orthogonal auf den Zellenboden gerichtet ist.

Der Ros-Knoten beinhaltet ein YoloV8-Modell, das unter Verwendung gelabelter, realer Bilder trainiert wurde. Es kann folgende Betriebsmittel und Bauteile klassifizieren:

- Carrier-Boxen
- Spanneinheiten
- Getriebe-Bauteile

Der ROS-Knoten kommuniziert mit den Treibern der RealSense und als Ergebnis wird eine Liste von 2D-Bounding-Boxes mit einer KlassenId gepublished.

Die linke obere Ecke der Bounding-Box wird in 3D-Koordinaten umgerechnet, wlche der jeweiligen Ecke des Bauteiles in 3D-Koordinaten entspricht.

Für die Umrechnung muss desweiteren ein Offset in Weltkoordinaten zwischen gemessener Bauteilecke und Koordinatenursprung des Teiles addiert werden. Die erhaltene 3D-Position des gemesssenen Bauteiles kann auf das Bohrloch-Grid „gesnappt" werden, um Mesungenauigkeiten zu eliminieren. Dies funktioniert, solange die Ungenauigkeit der Messung unter dem halben Abstand zweier Bohrlöcher liegt.

## Unity Synthetic Data Generation

Ein Versuch synthetische Daten mittels Unity zu erzeugen, um das YOLO-Netz zu trainieren. Daten werden erzeugt, haben für YOLO jedoch noch das falsche Format.

Projekt ist depricated, da für die Abteilung das Omniverse das Tool der Wahl ist?

## RestackCell Unity HMI

Aufgrund Zeitmangel nicht fertig gestellt.

## PCL Segmentation

Implementierung der Autopilot Punktwolkenbearbeitung in Ros2 Humble und PCL.

Die Implementierung erfolgte in PCL (Point Cloud Library) und C++, da diese eine direkte und funktionierende Ros-Schnittstelle zur Verfügung stellt, um im richtigen Format auf 3D-Pointclouds zu subscriben.

Die Implementierung führt zunächst eine Segmentierung durch Eliminierung der zur Arbeitsplatte gehörenden Punkte durch.

Danach werden zugehörige Sub-Punktwolken geclustert. Diese werden dann klassifiziert (todo mit PointNet oder klassisch Ransac) und danach zunächst eine grobe Posenbestimmung mit RANSAC. Im Anschluss wird mit Hilfe der initialen Ransac-Pose eine feinere Justierung der Pose mit einem -Matching IPC (Iterarive Point Cloud) , welcher präziser arbeitet, jedoch grobe Initialwerte benötigt, damit das Verfahren nicht in ein falsches lokales Minimum konvergiert.

## Opc Ua Client

Ros-Node, der den Opcua-Client implementiert.

Dieser bietet eine Service-Schnittstelle, um um mit anderen Ros-Nodes zu kommunizieren und sendet eingegangene Anfragen an den Opcua-Server auf der SPS weiter.

Wie wie einzelnen Kanäle der Pneumatik angesprochen werden müssen, ist im Repository dokumentiert.

## Pose Estimation ToF

Matching und Posenbestimmung der Betriebsmittel unter Verwendung der ToF-Kamera.

In dem Verfahren werden die Punkte der Tischplatte aus der ToF-Punktwolke wegsegmentiert, auf die restliche Punktwolke eine DBSCAN durchgeführt, um Ausreißer zu elemenieren.

Auf die resultierenden Punktwolken wird versucht mit einem ICP die jeweilige abgetastete (Punktwolkenformat) CAD-Datei zu matchen. Die Score des ICP wird neben der Posenbestimmung gleichzeitig für die Klassifikation der Betriebsmittelart verwendet (vorsicht bzgtl. Robustheit!)

## Vision 2D Restackcell

Betriebsmittelart

## HeliosToFCameraDriverRos

Die offiziellen Ros-Treiber für die Helios-ToF-Kamera waren zu generalisiert und haben mit dem der vorhandenen Hardware nicht zufriedenstellend funktioniert.

Die eigene Implementierung beinhaltet einen Ros-Knoten, der eine angeschlossene Kamera erkennt, und zyklisch eine Punktwolke published.

Das offizielle Repo für die Helios-ToF gibt es hier:
https://github.com/lucidvisionlabs/arena_camera_ros2

## RoboScheduler

Zwischenstand zum Scheduler in C++.

Veralteter Stand, aktueller Stand befindet sich im Projekt RestackCell

## RestackCell:

Für den Ablauf zu verwendende Gesamtprojekt, setzt sich zusammen aus:

- Robo Scheduler C++ (robo_planner package)
- Robo Scheduler Python (WIRD NICHT WEITEREINTWICKELT)
- MoveIt Backend
- Opcua Client
- ToF Camera Modul
- Ros Message Interfaces

### Ros-Knoten:

#### Ros Scheduler C++:

Der Scheduler, oder auch Robo-Planner in C++.

Durch die Launch-Datei im Launch-Folder ur_planner_launch.py wird der Scheduler (Ros-Knoten im genannten Projekt), sowie andere Knoten in der Projektmappe gestartet:

- Robo-Planner/Scheduler
- OPC-UA Client
- OPC-UA Client IO link
- MoveitBackend
- Robot State Publisher
- Todo: Vision Node

Hier eine kurze Erläuterung der Konzepte und wichtigsten Dateien des Projektes.

### Moevit Backend:

Wrapper der Moveit-Library. Bietet Ros-Services an, über die die Szene initialisiert und Roboterbewegungen durchgeführt werden können.

Für PointToPoint-Bewegungen wird der ompl-Planer verwendet, welcher nichtdeterministisch eine Trajektorie um Hindernisse berechnet.

Für gradlinige, kartesische Bewegungen wird der Pilz-Industrial-Planner verwendet.

### Config:

Das MoveIt Backend verwendet die Urdf-File und die Joint-Limits aus dem Ros-Shared-Folder des Paketes „ur_description" (`/ws/restackcell/ws_moveit2/src/robo_planner/config/custom_ur_description`)

Die Joint Limits wurden, in Anbetracht der Kabelführung und der Kabelführungsschiene nahe des TCP, manuell mit dem derzeitigen Aufbau des UR in der RestackCell ermittelt. Bei einem Ummontieren müssen gegebenfalls die Join-Limits aus der Ur_Description-Config angepasst werden, da der Roboter ansonsten Gefahr laufen kann Suizid durch Selbstverkabelung zu begehen.

Die Standard-Udrf-File (`/opt/ros/humble/share/ur_description/urdf/ur_macro.xacro`) wurde um zwei Kollisionsboxen erweitert, die beide statisch mit dem „tool0"-Link verknüpft sind. Die seitliche Kabelführungsschiene, sowie eine Box entlang der TCP-z-Achse, welche das größte vorhandene Tool umschließt. Da der UseCase eine Werkzeugwechselvorrichtung beinhaltet und eine dynamische Anpassung der Urdf-File während der Laufzeit nicht trivial ist, wurde für die kollisionsfreie Bahnplanung von den Worst Case-Toolmaßen ausgegangen.

Alternativ bleibt zu überprüfen, ob die verschiedenen Tools nicht auch als Objekte in der Werkzeugwechselstation der Szene positioniert werden können, die in Laufzeit über ein „Attach" beim Werkzeugwechsel an den Roboter-Tcp angedockt werden können.

Im Config-Ordner unter (`/ws/restackcell/ws_moveit2/src/robo_planner/config/custom_ur_description/config`) liegen unter anderem die Joint-Limits und die Roboterkalibrierung des verwendeten UR16e-Modells ab.

Die Kalibrierung wurde mit dem Ur16e der RestackCell durchgeführt anhand:
https://github.com/UniversalRobots/Universal_Robots_ROS_Driver/blob/master/ur_calibration/README.md

Die durch den genannten Link beschriebene Kalibrierungsdatei liegt unter `/ws/restackcell/ws_moveit2/src/robo_planner/config/custom_ur_description/config/ur16e/default_kinematics.yaml` ab.

### MoveIt Config

Die MoveIt-Config-Datei in `/ws/restackcell/ws_moveit2/src/robo_planner/config/custom_moveit_config/config` wurde modifiziert.
https://moveit.picknik.ai/humble/doc/examples/ompl_interface/ompl_interface_tutorial.html

Der RRT connect planner wird benutzt für alle OMPL bewegungen

Der Wert der „longest_distance_segment_fraction" reduziert, da der Postprocessor der Trajektorie ansonsten gerne in ein Hindernis geglättet hat und die Bewegung dadurch nicht ausgeführt werden konnte.

## Installation der notwendigen Ressourcen:

### ROS 2 Humble unter Ubuntu 22.04:

https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html

### Roboter-Treiber für den Universal Robot UR:

https://github.com/UniversalRobots/Universal_Robots_ROS2_Driver

### Arena SDK für die 3D ToF-Kamera Helios2 (sofern verwendet):

https://thinklucid.com/downloads-hub/

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

## Roboter mit Use Case starten

Um den Roboter mit dem Usecase zu starten sollten folgende Schritte ausgeführt werden:

1. Zelle und Roboter starten ODER Simulation starten
2. UR Robot Driver starten
3. URCaps Einrichten und starten
4. Moveit starten
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

### Simulation starten

Soll der UR-Roboter auf dem Rechner simuliert werden:

```
ros2 run ur_client_library start_ursim.sh -m ur16e
```

Sofern beim oberen Befehl ein Docker Permission denied auftaucht, dann folgendes eingeben:

```
sudo chmod 666 /var/run/docker.sock
```

Dabei wird ein Docker-Container gestartet und der UR kann über den im Terminal angezeigten Link im Browser simuliert werden. Die Konfiguration des simulierten Roboters funktioniert analog zu dem realen.

### UR Robot Driver starten

Der Roboter-Treiber übersetzt die ankommenden ROS-Befehle für den Roboter und zurück, und kommuniziert mit diesem.

In beiden Fällen, ob simulierter UR, oder echter über Ethernet-Kabel verbunden, wird der Roboter-Treiber benötigt.

Der Befehl mit der IP für den realen Roboter (IP = 192.168.20.20)

```
ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur16e robot_ip:=192.168.20.20 description_package:=ur_description launch_rviz:=false
```

Der Befehl mit der IP für den simulierten Roboter (IP = 192.168.56.101)

```
ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur16e robot_ip:=192.168.56.101 description_package:=ur_description launch_rviz:=false
```

Für einen Netzwerktest, ob der pyhsikalische Roboter richtig verbunden ist oder die Simulation läuft, kann der Parameter launch_rviz = true gesetzt werden. Der Roboter sollte in Rviz mit den richtigen Gelenkwinkeln und Kollisions-Erweiterungen aus der URDF-Datei dargestellt werden (derzeit mit einem Quader als Tool-Substituierung, sowie einen Quader für die Kabelhalterung in der Nähe des TCP).

Wenn der Roboter in der Rviz-darstellung aussieht, als würde er auf dem Boden liegen, besteht keine Verbindung. In dem Fall sollte zunächst über einen „ping"- Befehl an die IP-Adresse des Roboters die Verbindung überprüft werden.

Noch einmal die IP-Adresse des Roboters:
Real: 192.168.20.20
Simulation (default): 192.168.56.101

### URCaps Einrichten und starten


Um die URCaps zu starten, erst in der Leiste oben auf Program drücken, dann auf URCaps und external control. 

Das Program kann nun unten rechts am Panel mit dem Startknopf gestartet werden. 

Zu beachten ist, dass der UR Robot Driver vor dem URCaps gestartet werden muss!

Wenn alles richtig gelaufen ist, sollte im Terminal wo der UR Robot Driver gestartet wurde, folgende Nachricht sichtbar sein:

```
Robot connected to reverse interface. Ready to receive control commands.
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

- 6D-Posen Erkennung über Foundation Pose der Getriebehälften (gtr)
- 6D-Posen Erkennung über Foundation Pose für BEMIs (gtr)
- Einbindung WZL-Rechner für KI-Anwendungen (gtr)
- Implementierung Vision Überwachung Anlagen Konfiguration (gtr, wml)
- Aufzeichnen Hardware Architektur Schaltschrank (bln)
- Aufzeichnen Software Architektur (wml)
- Proof of Concept: Dockersieren der ROS2 Packages der ReStackCell (wml)
- Weitere Umsetzung Use-Case1 (wml)