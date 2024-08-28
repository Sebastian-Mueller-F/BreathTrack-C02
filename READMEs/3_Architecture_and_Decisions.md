
# Architekturüberblick

Das Projekt „BreathTracker“ basiert auf einer klar getrennten Architektur, die aus Backend- und Frontend-Komponenten besteht. Die Hauptziele der Architektur sind Skalierbarkeit, Wartbarkeit und eine saubere Trennung der Verantwortlichkeiten. Die folgende Beschreibung gibt einen Überblick über die grundlegenden Architekturentscheidungen und deren Implementierung im `main.cpp`.

## 1. Backend-Komponenten

Die Backend-Komponenten bilden das Herzstück der Datenverarbeitung. Sie sind für die Erfassung, Verarbeitung und Verteilung der Sensordaten verantwortlich. Diese Komponenten sind eng integriert und verwenden sowohl klassische Designmuster als auch die Vorteile des Qt-Frameworks.

### a. Sensor und Sensor-Simulator

- **Sensor**: Die Sensor-Komponente ist dafür verantwortlich, den CO2-Gehalt der Atemluft zu messen. Im aktuellen Setup wird ein **Sensorsimulator** verwendet, der zufällige Werte generiert, um die Funktionalität eines echten Sensors zu emulieren. Diese Werte werden über das `newCo2ValueGenerated`-Signal an das System verteilt.
- **Abstraktion über ein Interface**: Ein zentraler Punkt der Architektur ist die Abstraktion des Sensors über das `I_Sensor`-Interface. Dies ermöglicht es, den Sensorsimulator oder einen echten Hardware-Sensor nahtlos in das System zu integrieren, ohne dass Änderungen an den konsumierenden Modulen erforderlich sind.

### b. AverageCalculator

- **Funktionalität**: Der `AverageCalculator` ist für die Mittelwertbildung der CO2-Werte zuständig. Er verwendet dabei zwei verschiedene Mittelwertberechnungsverfahren: Simple Moving Average (SMA) und Exponential Moving Average (EMA).
- **Datenpuffer**: Die CO2-Werte werden in einem zirkularen Puffer mit einer maximalen Datensätze-Kapazität von 60 Sekunden gespeichert. Der `AverageCalculator` abonniert das `newCo2ValueGenerated`-Signal des Sensors und berechnet basierend auf den neuen Werten fortlaufend die Mittelwerte.
- **Singletons für Averager**: Die Instanzen der `SMA` und `EMA` Averager werden als Singletons implementiert und im `AverageCalculator` verwendet. Dies stellt sicher, dass es nur eine Instanz dieser Berechnungslogik im System gibt.

### c. DataBufferManager

- **Funktionalität**: Der `DataBufferManager` verwaltet die Rohdaten sowie die berechneten SMA- und EMA-Werte. Diese Puffer sind zirkular und bieten eine strukturierte Speicherung der Zeitreihen für die Trendanzeige.
- **Verteilung der Daten**: Die abonnierten Module (z.B. `LiveDataAPI`) können die Puffer abonnieren, um die jeweils neuesten Daten zu erhalten und diese an das Frontend weiterzuleiten.

## 2. Frontend-Komponenten

Das Frontend ist für die Visualisierung der Daten verantwortlich und interagiert über klar definierte APIs mit dem Backend. Dabei wird eine saubere Trennung zwischen Backend- und Frontend-Komponenten gewahrt.

### a. Frontend API

- **Architektur**: Die `FrontendApi` fungiert als Vermittler zwischen dem Backend und den verschiedenen Frontend-Modulen wie `LiveDataAPI` und `TrendDataAPI`. Alle notwendigen Abhängigkeiten werden über die Konstruktoren der Frontend-Module injiziert, was die Modularität und Testbarkeit des Systems erhöht.
- **Signale und Slots**: Das Frontend nutzt die von Qt bereitgestellten Mechanismen, um auf Backend-Ereignisse wie `newCo2ValueGenerated` zu reagieren und diese Daten in den entsprechenden UI-Komponenten darzustellen.

### b. QML-Integration

- **Funktionalität**: Die UI-Komponenten sind in QML implementiert und verwenden die bereitgestellten Frontend-APIs, um auf die Daten des Backends zuzugreifen. Die Integration der QML-Engine und das Laden der QML-Dateien erfolgt im `initializeQmlEngine`.

## 3. Hauptprogramm (main.cpp)

- **Initialisierung**: Das Hauptprogramm initialisiert sowohl das Backend als auch das Frontend und sorgt dafür, dass alle Komponenten korrekt miteinander verknüpft sind.
- **Laufzeit**: Das Backend läuft kontinuierlich, sammelt und verarbeitet die Daten, während das Frontend diese in Echtzeit darstellt.

## 4. Grafikübersicht

Die beigefügte Grafik bietet eine visuelle Darstellung der Architektur. Sie zeigt die Beziehungen zwischen den verschiedenen Komponenten, wie die Signale zwischen Sensor, `AverageCalculator`, `DataBufferManager` und den Frontend-APIs fließen, sowie die Abhängigkeiten zwischen den Modulen.

---

# Source Code: Architekturentscheidungen und -entscheidungen

Bei der Architektur des Projekts wurden mehrere zentrale Überlegungen angestellt, die zu den folgenden Entscheidungen führten:

## Backend-Kommunikation

- **Überlegung**: Die Kommunikation innerhalb des Backends stellt einen kritischen Teil der Softwarearchitektur dar. Eine der erwogenen Optionen war, vollständig auf das Qt-Framework zu verzichten und stattdessen das **Observer-Pattern** zur Informationsverteilung zu nutzen.
  - **Vorteil**: Durch das Observer-Pattern könnte das Backend von der Qt-Abhängigkeit befreit werden, was eine nahtlose Anbindung an andere, nicht-Qt-basierte Frontends ermöglicht. Diese Flexibilität ist besonders bei großen Systemen von Vorteil, wo es entscheidend sein kann, für die Zukunft offen und anpassbar zu bleiben.
  - **Nachteil**: Der Verzicht auf das Qt-Framework würde jedoch auch bedeuten, auf die etablierten und effizienten Mechanismen von Qt, wie **Signals und Slots** sowie das **Memory Management** via `QObject`, zu verzichten.

## Entscheidung für das Qt Framework

- **Entscheidung**: Nach Abwägung der Vor- und Nachteile wurde entschieden, das Qt-Framework vollständig zu nutzen. Insbesondere wurden die Funktionen wie **Signals und Slots** sowie das `QObject`-basierte **Memory Management** leveraged.
  - **Begründung**: Die Nutzung von Qt ermöglicht eine robuste und effiziente Implementierung, die weniger anfällig für Fehler ist und gleichzeitig den Code kompakter und wartbarer macht. Zudem profitiert das Projekt von den integrierten Mechanismen zur Speicherverwaltung, bei der Objekte, die an `QObject`-Instanzen gebunden sind, automatisch beim Zerstören des Parents freigegeben werden.
  - **Beispiel**: Module wie der `AverageCalculator`, die die Funktionalitäten anderer Klassen handeln, sind als `QObject`-Parent bei diesen registriert. Dies stellt sicher, dass die zugehörigen Objekte automatisch freigegeben werden, wenn der Destruktor des `AverageCalculator` aufgerufen wird.

## Trennung von Frontend und Backend

- **Problemstellung**: Eine unkontrollierte Verwendung von Qt-Signalen und `QObject`-Klassen kann zu einer chaotischen Kommunikation zwischen Backend und Frontend führen, was die Wartbarkeit und Erweiterbarkeit der Software stark beeinträchtigen könnte.
- **Lösung**: Es wurde versucht, eine **klare Trennung** zwischen Frontend und Backend zu erreichen.
  - **Im Backend**: Es gibt keinerlei Referenzen oder Abhängigkeiten zu Frontend-Modulen. Das Backend agiert unabhängig und sendet lediglich Signale, auf die das Frontend reagieren kann.
  - **Im Frontend**: Obwohl Module wie die `LiveDataAPI` auf Signale des Backends (z.B. `newCo2ValueGenerated`) hören, werden alle Abhängigkeiten explizit über den Konstruktor der Klasse hinterlegt. Diese Abhängigkeiten werden zentral über das `FrontendApi` an die einzelnen Frontend-Module übergeben.
  - **Vorteil**: Diese Architektur macht die Software skalierbarer, modularer und sauberer. Jede Schicht des Systems bleibt für sich geschlossen und reduziert die Wahrscheinlichkeit von unerwartetem Verhalten durch unkontrollierte Signalflüsse.

## Verwendung von Singleton-Klassen

- **Überlegung**: Singletons bieten den Vorteil, dass sie sicherstellen, dass eine Klasse nur einmal im System existiert. Dies ist besonders nützlich für global genutzte Ressourcen wie Konfigurationsmanager oder Logger.
- **Entscheidung**: Singleton-Instanzen wurden nur dort verwendet, wo eine Klasse eindeutig nur einmalig existieren sollte.
  - **Sicherheitsmaßnahmen**: Trotz der globalen Verfügbarkeit und Aufrufbarkeit wurde darauf geachtet, dass dies nicht zu einer chaotischen Kommunikation führt. Auch Singleton-Instanzen werden über Dependency Injection an Module übergeben, was eine kontrollierte und nachvollziehbare Verwendung ermöglicht.
  - **Vorteil**: Diese kontrollierte Verwendung von Singletons verhindert die typischen Probleme von globalem Zustand und fördert eine klare und nachvollziehbare Architektur.
