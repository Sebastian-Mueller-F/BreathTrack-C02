# Projekt: BreathTrack CO2

## Wie führt man das Projekt aus

### Projekt herunterladen

- Klonen Sie das Repository auf Ihren lokalen Rechner:
  ```bash
  git clone https://github.com/Sebastian-Mueller-F/BreathTrack-C02.git
  ```
- Laden Sie das benötigte Submodul herunter:
  ```bash
  cd BreathTrack-C02
  git submodule update --init --recursive
  ```
- Das Submodul enthält eine Version, in der zusätzliche Trenddaten in einer Graphanzeige integriert wurden. Stellen Sie sicher, dass das Submodul korrekt geladen wurde, um diese Funktionalität zu nutzen.

### Entwicklungsumgebung und Voraussetzungen

- Das Projekt wurde auf einem Mac mit **Qt Creator 14.01** unter Verwendung von **Qt 6.7.2 (Clang 14.0 (Apple), x86_64)** entwickelt. Zusätzlich wurden die Kits wie im Bild dargestellt eingerichtet.
- Das Projekt wurde ebenfalls auf einer Linux-VM (Ubuntu, VM Ware) mit **Qt 6.4.1** getestet und kompiliert. Dabei wurden auch die Executables erstellt. Mehr dazu finden Sie im Abschnitt „Executables“.

### Projektkonfiguration und Build-Prozess

- Öffnen Sie das Projekt über die `CMakeLists.txt`, um die Konfiguration und den Build-Prozess nachzuvollziehen. Dieser Ansatz stellt sicher, dass auch die Ausgabe von `qDebug`-Statements, die zur besseren Nachvollziehbarkeit des Codes enthalten sind, sichtbar ist.
- Das Projekt ist mit **Qt 6.x** kompatibel, jedoch **nicht** mit Qt 5.x, da bestimmte Komponenten, wie beispielsweise die Timeline im Frontend, die neueren Versionen von Qt erfordern.

### Executable-Erstellung

- Es wurden zwei Methoden ausprobiert, um ein lauffähiges Executable für Linux bereitzustellen:

  1. **Statische Verlinkung**: Ein ausführbares Image wurde mit Hilfe von `linuxdeployqt` bzw. `appimagetool-x86_64.AppImage` erstellt. Hierbei traten unerwartete Probleme auf.

  2. **Dynamische Verlinkung**: Die benötigten Qt-Abhängigkeiten wurden manuell auf dem Ziel-Linux-System verlinkt. Diese Methode funktionierte in den durchgeführten Tests. Die dynamische Verlinkung hat in meinen Tests funktioniert, konnte jedoch nicht auf einer vollständig sauberen Linux-Umgebung getestet werden. Es wurde versucht, die Systemvariable `PATH` während der Tests zu leeren, um eine saubere Umgebung zu simulieren. Ein Skript `install.sh` wurde erstellt, das im Release-Build-Ordner liegt und versucht, diese Aufgaben zu automatisieren.

- Weitere Details und Problembeschreibungen finden Sie im Abschnitt „Executables“.

### Ausführung des Projekts

- Stellen Sie sicher, dass **Qt 6.4.1 oder höher** sowie **CMake** auf Ihrem System installiert sind. Das ausführbare Programm kann dann aus dem Build-Ordner direkt gestartet werden.
- Sollte es dabei zu Problemen kommen, die das Begutachten des Projekts verhindern, kontaktieren Sie bitte umgehend [Kontaktinformationen].
